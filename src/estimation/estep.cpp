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
			 std::vector<matrix<int> > &X, int G ) {
	// Latent trait vectors are loaded
	static matrix<double> theta = load_quadrature_points(G);
	// Weights are loaded
	static std::vector<double> w = load_weights(G);

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
			double pi_gl = 1;

			/**
			 * Just supporting polytomic case
			 * */
			matrix<int> &x_l = X[l];
			for ( int i = 0; i < p; ++i ) {
				double t = 1;

				// Number of categories of this item
				int mi = zeta[i].get_categories();
				for ( int k = 0; k < mi; ++k ) {
					if ( x_l(i, k) ) {
						std::vector<double> theta_i = theta.get_row(i);
						t *= m.Pik(theta_i, zeta[i], k) * w[g];
					} else
						t *= w[g];
				}

				pi_gl *= t;
			}
		}
	}
}

} /* namespace mirt */
