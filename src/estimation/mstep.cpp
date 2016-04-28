/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "mstep.h"

namespace mirt {

/**
 * Function to be maximized
 * */
double Mstep::Qi ( const column_vector& m ) {
	return 0;
}

Mstep::Mstep(model* m, std::vector<item_parameter>* zeta, std::vector<matrix<double> >* r) {
	/**
	 * Assigning all the pointers (matrixes and info) needed to be able to run the Mstep
	 * */
	this->m_pointer = m;
	this->zeta_pointer = zeta;
	this->r_pointer = r;
}

double Mstep::run() {

	/*****************
	 *  M STEP
	 *
	 * */

	return 0.0000001;
}

} /* namespace mirt */
