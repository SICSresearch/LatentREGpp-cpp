/*
 * itemparameter.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Milder
 */

#include "itemparameter.h"
#include <iostream>

namespace irtpp {

item_parameter::item_parameter(matrix<char> &Y, model &m, short dimension, short categories) {
	/**
	 * COMPUTING INITIAL VALUES
	 *
	 *
	 * */

	/**
	 * Initial values for item parameters according to Andrade, Tavares & Valle (2000),
	 *
	 * */
	if ( dimension == 1 ) {
		if ( m.parameters == 1 ) {
			alphas = 0;
			gammas = categories - 1;
			guessing = false;
			for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
		} else if ( m.parameters == 2 ) {
			alphas = dimension;
			gammas = categories - 1;
			guessing = false;

			std::vector<double> biserial_correlation;
			compute_biserial_correlation(Y, biserial_correlation);
			std::cout << "Biserial computed" << std::endl;
			compute_alphas(biserial_correlation, alpha);
			std::cout << "Alphas computed" << std::endl;
			compute_gammas(Y, alpha, biserial_correlation, gamma);
			std::cout << "Gammas computed" << std::endl;
		} else {
			alphas = dimension;
			gammas = categories - 1;
			guessing = true;
			for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
			for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
			c = 1.0/categories;
		}

	} else {
		if ( m.parameters == 1 ) {
			alphas = 0;
			gammas = categories - 1;
			guessing = false;
			for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
		} else if ( m.parameters == 2 ) {
			alphas = dimension;
			gammas = categories - 1;
			guessing = false;
			for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
			for ( int i = 0; i < gammas; ++i ) gamma.push_back(2 - i);
		} else {
			alphas = dimension;
			gammas = categories - 1;
			guessing = true;
			for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
			for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
			c = 1.0/categories;
		}
	}

	number_of_parameters = alphas + gammas + guessing;
}

item_parameter::item_parameter(model &m, short dimension, short categories) {
	/**
	 * COMPUTING INITIAL VALUES
	 *
	 *
	 * */

	if ( m.parameters == 1 ) {
		alphas = 0;
		gammas = categories - 1;
		guessing = false;
		for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
	} else if ( m.parameters == 2 ) {
		alphas = dimension;
		gammas = categories - 1;
		guessing = false;
		for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
		for ( int i = 0; i < gammas; ++i ) gamma.push_back(2 - i);
	} else {
		alphas = dimension;
		gammas = categories - 1;
		guessing = true;
		for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
		for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
		c = 1.0/categories;
	}

	number_of_parameters = alphas + gammas + guessing;
}

void item_parameter::build_item(const column_vector& v, int d, int mi, item_parameter &item) {
	int j = 0;
	for ( int k = 0; k < item.alphas; ++k, ++j )
		item.alpha[k] = v(j);
	for ( int k = 0; k < item.gammas; ++k, ++j )
		item.gamma[k] = v(j);
	if ( item.guessing )
		item.c = v(j);
}

item_parameter::~item_parameter() {
	// TODO Auto-generated destructor stub
}

std::vector<double> item_parameter::get_alpha() {
	return alpha;
}

std::vector<double> item_parameter::get_gamma() {
	return gamma;
}

short item_parameter::get_categories() {
	return gammas + 1;
}

short item_parameter::get_dimension() {
	return alphas;
}

short item_parameter::get_number_of_parameters() {
	return number_of_parameters;
}

void item_parameter::add_single_alpha(double a) {
	alpha.push_back(a);
}

void item_parameter::add_single_gamma(double d) {
	gamma.push_back(d);
}

} /* namespace irtpp */
