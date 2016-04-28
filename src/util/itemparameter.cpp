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
	number_of_parameters = d + categories;
}

item_parameter::item_parameter(short d) {
	//item_parameter::item_parameter(d, 2);
}

item_parameter::item_parameter(short d, short categories, double c) {
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

	this->c = c;
	guessing = true;
	++number_of_parameters;
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

short item_parameter::get_number_of_parameters() {
	return number_of_parameters;
}

} /* namespace mirt */
