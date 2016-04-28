/*
 * itemparameter.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Milder
 */

#include "itemparameter.h"

namespace mirt {

item_parameter::item_parameter() {
	// TODO Auto-generated constructor stub

}

item_parameter::item_parameter(short d, short categories) {
	this->d = d;
	this->categories = categories;

	/**
	 * COMPUTING INITIAL VALUES
	 *
	 * Not supported yet
	 * */

	//Newbie values
	for ( int i = 0; i < d; ++i ) alpha.push_back(1);
	for ( int i = 0; i < categories; ++i ) gamma.push_back(1);

	guessing = false;
}

item_parameter::item_parameter(short d) {
	item_parameter::item_parameter(d, 2);
}

item_parameter::item_parameter(short d, short categories, double c) {
	item_parameter::item_parameter(d, categories);
	this->c = c;
	guessing = true;
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
	return categories;
}

short item_parameter::get_dimension() {
	return d;
}

} /* namespace mirt */
