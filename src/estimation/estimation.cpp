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

/**
 * Model to be used
 * */
model m;
/**
 * Dimension of the data
 * */
short d;
/**
 * Number of items
 * */
int p;
/**
 * Number of response patterns
 * */
int s;

/**
 * Number of examinees
 * */
int N;

/**
 * Vector of parameters
 * */
std::vector<item_parameter> zeta;

/**
 * Y , s x p, matrix of pattern responses.
 *
 * where s is the number of patterns s <= N (N, number of examinees)
 * p is the number of items
 * */
matrix<char> Y;

/**
 * Dichotomized matrix
 * */
std::vector<matrix<int> > X;

/**
 * nl, frequencies of each pattern allocated in Y
 * */
std::vector<int> nl;

// Latent trait vectors
matrix<double> theta;

// Weights
std::vector<double> w;

//Setting size of matrix r
std::vector<matrix<double> > r;

const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40;
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
int G;

estimation::estimation(int themodel, matrix<char> &data, short d = 1,
					   double convergence_difference = 0.001) {
	// Setting the dimension
	mirt::d = d;

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

	// Number of examinees
	N = data.rows();

	// Number of response patterns
	s = Y.rows();

	// Finding the number of items
	// As the matrix data is s x p
	// we can find out the number of items just seeing the size
	// of any response pattern
	p = Y.columns(0);


	//Finding the number of categories of each item and seeing if it's dichotomous
	this->dichotomous = false;
	for ( int j = 0; j < p; ++j ) {
		int max_category = -1;
		for ( int i = 0; i < s; ++i ) {
			if ( Y(i, j) > max_category ) max_category = Y(i, j);
			dichotomous |= Y(i, j) == 0;
		}
		categories_item.push_back(max_category);
	}

	// If it's dichotomous, we add 1 to data
	if ( dichotomous ) {
		for ( int i = 0; i < s; ++i )
			for ( int j = 0; j < p; ++j )
				++Y(i, j);
		for ( int i = 0; i < p; ++i )
			++categories_item[i];
	}


	/**
	 * After Y, here matrix X (dichotomized matrix) is computed
	 *
	 */
	X = std::vector<matrix<int> >(s);
	for ( int l = 0; l < s; ++l ) {
		for ( int i = 0; i < p; ++i ) {
			std::vector<int> row(categories_item[i]);
			row[Y(l, i) - 1] = 1;
			X[l].add_row(row);
		}
	}

	G = MAX_NUMBER_OF_QUADRATURE_POINTS / (std::min(1 << (d - 1), 8));

	// Latent trait vectors are loaded
	theta = load_quadrature_points(G);

	// Weights are loaded
	w = load_weights(G);

	//Setting size of matrix r
	r = std::vector<matrix<double> >(G);
	for ( int g = 0; g < G; ++g ) {
		r[g] = matrix<double>();
		for ( int i = 0; i < p; ++i )
			r[g].add_row(categories_item[i]);
	}

	//Configurations for the estimation
	mirt::m = model(themodel);
	this->convergence_difference = convergence_difference;
}

estimation::~estimation() {

}

void estimation::initial_values() {
	for ( int i = 0; i < p; ++i )
		zeta.push_back( item_parameter(d, categories_item[i]) );
}

void estimation::EMAlgortihm() {
	//Finding initial values for zeta
	initial_values();

	int iterations = 0;

	double dif;
	do {
		Estep();
		std::cout << "Estep finished" << std::endl;
		dif = Mstep();
		std::cout << ++iterations << std::endl;
	} while ( dif > convergence_difference );
}



} /* namespace mirt */
