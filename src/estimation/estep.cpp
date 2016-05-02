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

/**********************************
 *  E STEP						  *
 *								  *
 **********************************/

void Estep ( ) {
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
	 * Computing and saving the values of numerators and denominators
	 * for pi(g, l) equation to avoid recompute them
	 *
	 * As you can see in pi(g, l) equation [7 from Doc], denominators are the same by columns
	 *
	 * So, here numerators for each position in pi are computed
	 * and the denominators are the summation of numerators by columns
	 *
	 * */
	static matrix<double> numerator(G, s);
	static std::vector<double> denominator(s);

	for ( int l = 0; l < s; ++l ) {
		double &denonimator_l = denominator[l] = 0;
		for ( int g = 0; g < G; ++g ) {
			/**
			 * Computing numerator for (g, l) position
			 * */
			double &numerator_gl = numerator(g, l) = 1;
			std::vector<double> &theta_g = *theta.get_pointer_row(g);

			/**
			 * Here, P_gik is requested to the model
			 *
			 * Using X (dichotomized matrix) to compute the numerator is NOT efficient
			 * because most of numbers in X[l](i) are zero
			 * 		Example:
			 * 			If an individual answered category 3 for an item with 5 categories
			 *			X[l](i) will be:
			 * 				0 0 1 0 0
			 *
			 *			As you are computing (Pik(theta_g))^x_lik, when k = 1, 2, 4, 5 x_lik is 0
			 *			and the result for (Pik(theta_g))^x_lik is 1,
			 *			so it's possible to obtain the value for k that is really important
			 *			i.e when k = 3.
			 *			It's possible to do this using the matrix of response patterns
			 *
			 * 			k = Y(l, i)
			 *
			 * 			And because of indexes start in 0:
			 *
			 * 			k = Y(l, i) - 1
			 *
			 * */
			for ( int i = 0; i < p; ++i )
				numerator_gl *= m.Pik(theta_g, zeta[i], Y(l, i) - 1);
			numerator_gl *= w[g];

			/**
			 * As denominator for a response pattern l is the summation over the latent traits
			 * here numerator(g, l) is added to denominator[l]
			 * */
			denonimator_l += numerator_gl;
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
			pi(g, l) = numerator(g, l) / denominator[l];
		}
	}

	//Asserting pi correctness
//	bool pi_ok = test_pi(pi);
//	assert(("Each column of pi matrix must sum 1.0", pi_ok));

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
//	bool r_ok = test_r(r, N, p);
//	assert(("Sum of elements in r must be N x p", r_ok));
}

} /* namespace mirt */
