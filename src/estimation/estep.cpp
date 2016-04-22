/*
 * estep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estep.h"

namespace mirt {

/**
 * Estep of the EMAlgortihm
 *
 * */
void Estep ( model &m, std::vector<item_parameter> &zeta, matrix<char> &Y,
			 std::vector<matrix<bool> > &X, int G ) {
	/**
	 * Number of response patterns
	 * */
	int s = Y.rows();

	/**
	 * Number of items
	 * */
	int p = Y.columns(0);

	/**
	 * Probability matrix
	 *
	 * pi(g, l) with g = 1, ..., G; l = 1, ..., s
	 * 		i.e, the size of pi is
	 * 			 Number of Quadrature points X Number of response patterns
	 *
	 * pi(g, l) is the probability that a response pattern belongs to
	 * 			group g
	 * */
	matrix<double> pi(G, s);


	for ( int g = 0; g < G; ++g ) {
		for ( int l = 0; l < s; ++s ) {
			/**
			 * Computing each element of the matrix
			 * pi(g, l)
			 * */
			double pi_gl = 0;

			matrix<bool> x_l = X[l];
			for ( int i = 0; i < p; ++i ) {
				// Number of categories of this item
				int mi = zeta[i].get_categories();
				for ( int k = 0; k < mi; ++k ) {
					// here, must be Pik(theta)^x_l(i, k) * w_g
				}
			}
		}
	}
}

} /* namespace mirt */
