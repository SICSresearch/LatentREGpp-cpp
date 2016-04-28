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
	item_parameter(d, 2);
}

item_parameter::item_parameter(short d, short categories, double c) {
	item_parameter(d, categories);
	this->c = c;
	guessing = true;
	++number_of_parameters;
}

item_parameter item_parameter::build_item(const column_vector& v, int d, int mi) {
	item_parameter item(d, mi);
	int j = 0;
	for ( int k = 0; k < d; ++k, ++j )
		item.alpha[k] = v(j);
	for ( int k = 0; k < mi; ++k, ++j )
		item.gamma[k] = v(j);
	//Here, there is a parameter c (guessing) into v
	if ( j < v.size() ) {
		item.c = v(j);
		item.guessing = true;
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
