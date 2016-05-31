/*
 * itemparameter.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Milder
 */

#include "itemparameter.h"

namespace irtpp {

item_parameter::item_parameter() {
	// TODO Auto-generated constructor stub

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
		for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
	} else {
		alphas = dimension;
		gammas = categories - 1;
		guessing = true;
		for ( int i = 0; i < alphas; ++i ) alpha.push_back(1);
		for ( int i = 0; i < gammas; ++i ) gamma.push_back(1);
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

} /* namespace irtpp */
