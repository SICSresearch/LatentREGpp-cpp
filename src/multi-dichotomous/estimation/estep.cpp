/*
 * estep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estep.h"

namespace irtpp {

namespace multidichotomous {

void Estep ( estimation_data &data ) {
	//Number of items
	int &p = data.p;
	//Number of response patterns
	int &s = data.s;
	//Number of quadrature points
	int &G = data.G;
	//Model used
	model &m = data.m;
	//Matrix of response patterns
	matrix<char> &Y = data.Y;
	//Frequency of each pattern
	std::vector<int> &nl = data.nl;
	//Latent trait vectors
	matrix<double> &theta = data.theta;
	//Weights
	std::vector<double> &w = data.w;
	//Vector of parameters of the items
	std::vector<item_parameter> &zeta = data.zeta;

	//pi matrix
	matrix<double> &pi = data.pi;

	/**
	 * Probability matrix P
	 * */
	matrix<double> &P = data.P;

	//r matrix
	matrix<double> &r = data.r;
	r.reset();

	/**
	 * Computing each element of matrix P
	 * P_gi
	 * */
	for ( int g = 0; g < G; ++g ) {
		std::vector<double> &theta_g = *theta.get_pointer_row(g);
		for ( int i = 0; i < p; ++i )
			P(g, i) = m.P(theta_g, zeta[i]);
	}

	for ( int l = 0; l < s; ++l ) {
		double denonimator_l = 0;
		for ( int g = 0; g < G; ++g ) {
			pi(g, l) = w[g];
			for ( int i = 0; i < p; ++i ) {
				if ( Y(l, i) )
					pi(g, l) *= P(g, i);
				else
					pi(g, l) *= 1 - P(g, i);
			}
			/**
			 * As denominator for a response pattern l is the summation over the latent traits
			 * here pi(g, l) is added to denominator_l
			 * */
			denonimator_l += pi(g, l);
		}

		for ( int g = 0; g < G; ++g ) {
			pi(g, l) /= denonimator_l;

			for ( int i = 0; i < p; ++i )
				r(g, i) += nl[l] * pi(g, l);
		}
	}

	//Asserting pi correctness
	bool pi_ok = test_pi(pi);
	assert(("Each column of pi matrix must sum 1.0", pi_ok));

	//Asserting r correctness
	bool r_ok = test_r(r, data.N, p);
	assert(("Sum of elements in r must be N x p", r_ok));
}

}

} /* namespace irtpp */
