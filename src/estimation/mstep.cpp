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
double Mstep::Qi ( const column_vector& v ) {
	/**
	 * Creating reference variables to data needed
	 *
	 * m (model used)
	 * zeta (parameters info)
	 * matrix r (computed in Estep)
	 * */
	model &m = *m_pointer;
	std::vector<item_parameter> &zeta = *zeta_pointer;
	std::vector<matrix<double> > &r = *r_pointer;
	matrix<double> &theta = *theta_pointer;

	/**
	 * Computing value of Qi function
	 * */

	double value = 0;
	for ( int g = 0; g < G; ++g ) {
		int mi = zeta[i].get_categories();
		for ( int k = 0; k < mi; ++k ) {
			std::vector<double> theta_g = theta.get_row(g);
			value += r[g](i, k) * log( m.Pik(theta_g, v, k) );
		}
	}

	return value;
}

Mstep::Mstep(model* m, std::vector<item_parameter>* zeta, std::vector<matrix<double> >* r, int G, int p, matrix<double> *theta ) {
	/**
	 * Assigning all the pointers (matrixes and info) needed to be able to run the Mstep
	 * */
	this->m_pointer = m;
	this->zeta_pointer = zeta;
	this->r_pointer = r;
	this->theta_pointer = theta;

	this->G = G;
	this->p = p;
}

double Mstep::run() {
	// Obtaining reference of zeta
	std::vector<item_parameter> &zeta = *zeta_pointer;

	/*****************
	 *  M STEP
	 *
	 * */

	// Iterate over the number of items
	for ( i = 0; i < p; ++i ) {
		column_vector starting_point(zeta[i].get_number_of_parameters());
//		starting_point = 4, 8;
//
//		dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
//                									 dlib::objective_delta_stop_strategy(1e-7),
//													 Qi, starting_point, -1);
	}


	return 0.0000001;
}

} /* namespace mirt */
