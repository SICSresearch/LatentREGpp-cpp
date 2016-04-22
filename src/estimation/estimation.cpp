/*
 * estimation.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estimation.h"

namespace mirt {

estimation::estimation() {
	// TODO Auto-generated constructor stub

}

estimation::estimation(model &m, matrix<char> &data, short d = 1, short iterations = -1,
					   double convergence_difference = 0.0001) {
	// Setting the dimension
	this->d = d;

	//Finding the matrix of response patterns Y
	//And its frequency
	std::map<std::vector<char>, int> freq;
	for ( int i = 0; i < data.rows(); ++i )
		++freq[data.get_row(i)];

	std::map<std::vector<char>, int>::iterator it;
	for ( it = freq.begin(); it != freq.end(); ++it ) {
		Y.add_row(it->first);
		nl.push_back(it->second);
	}

	// Number of response patterns
	this->s = Y.rows();

	// Finding the number of items
	// As the matrix data is s x p
	// we can find out the number of items just seeing the size
	// of any response pattern
	this->p = Y.columns(0);


	//Finding the number of categories of each item
	for ( int j = 0; j < p; ++j ) {
		int max_category = -1;
		for ( int i = 0; i < s; ++i )
			if ( Y(i, j) > max_category ) max_category = Y(i, j);
		categories_item.push_back(max_category);
	}

	/**
	 * After Y, here matrix X (dichotomized matrix) is computed
	 *
	 *
	 */
	X = std::vector<matrix<bool> >(s);
	for ( int l = 0; l < s; ++l ) {
		for ( int i = 0; i < p; ++i ) {
			X[l].add_row(categories_item[i]);
			X[Y(l, i)] = 1;
		}
	}

	//Configurations for each estimation
	model_used = m;
	this->iterations = iterations;
	this->convergence_difference = convergence_difference;
}

estimation::~estimation() {

}

void estimation::initial_values() {
	for ( int i = 0; i < p; ++i )
		zeta.push_back( item_parameter(d, categories_item[i]) );
}

void estimation::EMAlgortihm() {
	static int MAX_NUMBER_OF_QUADRATURE_POINTS = 40;

	/**
	 * Defining the number of quadrature points
	 *
	 * As max number of quadrature points is 40
	 *
	 * G will be in 1dimension = 40
	 * 				2dimension = 20
	 * 				3dimension = 10
	 * 				> 4dimension = 5
	 * */
	static int G = MAX_NUMBER_OF_QUADRATURE_POINTS / (std::min(1 << d, 8));

	//Finding initial values for zeta
	initial_values();

	for ( ; ; ) {
		// E step here



		// M step here


	}
}



} /* namespace mirt */
