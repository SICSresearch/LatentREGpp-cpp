/*
 * estep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estep.h"

//Includes for testing
#include "../../test/pimatrixtest.h";

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

	/**
	 * Computing pi matrix
	 * */
	for ( int g = 0; g < G; ++g ) {
		for ( int l = 0; l < s; ++l ) {
			/**
			 * Computing each element of the matrix
			 * pi(g, l)
			 * */

			//std::cout << "Computing pi(" << g << ' ' << l << ") " << std::endl;

			double &pi_gl = pi(g, l);

			double numerator = 1;

			matrix<int> &x_l = X[l];
			for ( int i = 0; i < p; ++i ) {
				double product = 1;

				// Number of categories of this item
				int mi = zeta[i].get_categories();
				for ( int k = 0; k < mi; ++k ) {
					if ( x_l(i, k) ) {
						std::vector<double> theta_i = theta.get_row(i);
						product *= m.Pik(theta_i, zeta[i], k);
						//std::cout << i << ' ' << k << ' ' << m.Pik(theta_i, zeta[i], k) << std::endl;
					}
					product *= w[g];
				}

				numerator *= product;
			}

			double denominator = 0;

			for ( int h = 0; h < G; ++h ) {
				double product1 = 1;

				for ( int i = 0; i < p; ++i ) {
					double product2 = 1;

					// Number of categories of this item
					int mi = zeta[i].get_categories();
					for ( int k = 0; k < mi; ++k ) {
						if ( x_l(i, k) ) {
							std::vector<double> theta_i = theta.get_row(i);
							product2 *= m.Pik(theta_i, zeta[i], k);
						}
						product2 *= w[h];
					}

					product1 *= product2;
				}

				denominator += product1;
			}

			//std::cout << numerator << ' ' << denominator << std::endl;

			pi_gl = numerator / denominator;
			//std::cout << pi_gl << std::endl;
		}
	}

	std::cout.precision(4);
	//std::cout << "Pi matrix" << std::endl;
	//std::cout << pi << std::endl;
	std::cout << test_pi(pi) << std::endl;
}

} /* namespace mirt */
