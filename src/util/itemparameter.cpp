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

item_parameter::item_parameter(short d, short categories, bool guessing) {
	this->d = d;
	this->categories = categories;
	this->guessing = guessing;

	/**
	 * COMPUTING INITIAL VALUES
	 *
	 * Not supported yet
	 * */

	//Newbie values
	for ( int i = 0; i < d; ++i ) alpha.push_back(1);
	for ( int i = 0; i < categories - 1; ++i ) gamma.push_back(1);

	number_of_parameters = d + categories - 1;
	if ( guessing ) {
		c = 0.5;
		++number_of_parameters;
	}
}

item_parameter::item_parameter(short categories) {
	item_parameter(0, categories, false);
}

item_parameter item_parameter::build_item(const column_vector& v, int d, int mi) {
	item_parameter item;
	int j = 0;
	for ( int k = 0; k < d; ++k, ++j )
		item.alpha.push_back(v(j));
	item.d = item.alpha.size();
	for ( int k = 0; k < mi - 1; ++k, ++j )
		item.gamma.push_back(v(j));
	item.categories = item.gamma.size() + 1;
	item.number_of_parameters = item.d + item.get_categories() - 1;

	//Here, there is a parameter c (guessing) into v
	if ( j < v.size() ) {
		item.c = v(j);
		item.guessing = true;
		++item.number_of_parameters;
	}
	return item;
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
