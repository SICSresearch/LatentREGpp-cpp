/*
 * estep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estep.h"

//Includes for testing
#include "../test/test.h"

namespace mirt {

/**
 * Estep of the EMAlgortihm
 *
 * */

void Estep ( ) {
	/*********************************
	 *  E STEP
	 *
	 *********************************/

	/**
	 * Probability matrix pi
	 *
	 * pi(g, l) with g = 1, ..., G; l = 1, ..., s
	 * 		i.e, the size of pi is
	 * 			 Number of Quadrature points X Number of response patterns
	 *
	 * pi(g, l) is the probability that a response pattern belongs to
	 * 			group g
	 * */
	static matrix<double> pi(G, s);

	/**
	 * Computing and saving the values of denominators
	 * in pi(g, l) equation to avoid recompute them
	 * */
	static std::vector<double> denominators(s);

	for ( int l = 0; l < s; ++l ) {
		double &denominator = denominators[l] = 0;
		for ( int h = 0; h < G; ++h ) {
			double product = 1;
			std::vector<double> &theta_h = *theta.get_pointer_row(h);
			for ( int i = 0; i < p; ++i )
				product *= m.Pik(theta_h, zeta[i], Y(l, i) - 1);
			denominator += product * w[h];
		}
	}

	/**
	 * Computing pi matrix
	 * */
	for ( int g = 0; g < G; ++g ) {
		for ( int l = 0; l < s; ++l ) {
			/**
			 * Computing each element of the matrix
			 * pi(g, l)
			 * */
			double &pi_gl = pi(g, l);
			std::vector<double> &theta_g = *theta.get_pointer_row(g);

			double numerator = 1;
			for ( int i = 0; i < p; ++i )
				numerator *= m.Pik(theta_g, zeta[i], Y(l, i) - 1);

			//Now multiply by the weight of node g and divide by denominator previously computed
			pi_gl = numerator * w[g] / denominators[l];
		}
	}

	//Asserting pi correctness
	bool pi_ok = test_pi(pi);
	assert(("Each column of pi matrix must sum 1.0", pi_ok));

	/**
	 * Expected number of examinees for each group g
	 * who answered category k to item i
	 *
	 * Matrix r
	 * */
	for ( int g = 0; g < G; ++g ) {
		for ( int i = 0; i < p; ++i ) {
			r[g].reset_row(i);
			for ( int l = 0; l < s; ++l ) {
				int k = Y(l, i) - 1;
				r[g](i, k) += nl[l] * pi(g, l);
			}
		}
	}

	//Asserting r correctness
	bool r_ok = test_r(r, N, p);
	assert(("Sum of elements in r must be N x p", r_ok));
}

} /* namespace mirt */
