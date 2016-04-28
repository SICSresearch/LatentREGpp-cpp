/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "mstep.h"

namespace mirt {

double C = 100000.0;
int i;

double Qi (const column_vector& v) {
	/**
	 * Computing value of Qi function
	 * */
	double value = 0;
	for ( int g = 0; g < G; ++g ) {
		int mi = zeta[i].get_categories();
		for ( int k = 0; k < mi; ++k ) {
			std::vector<double> theta_g = theta.get_row(g);
			value += r[g](i, k) * log( m.Pik(theta_g, v, k, d, mi) );
		}
	}

	return value;
}

double Mstep() {
	/*****************
	 *  M STEP
	 *
	 * */

	// Iterate over the number of items
	for ( i = 0; i < p; ++i ) {
		//Creating starting point
		column_vector starting_point(zeta[i].get_number_of_parameters());
		int j = 0;
		for ( int k = 0; k < zeta[i].alpha.size(); ++k, ++j )
			starting_point(j) = zeta[i].alpha[k];
		for ( int k = 0; k < zeta[i].gamma.size(); ++k, ++j )
			starting_point(j) = zeta[i].gamma[k];
		if ( zeta[i].guessing ) starting_point(j) = zeta[i].c;

		//Calling bfgs from dlib to optimize Qi
		dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
													 dlib::objective_delta_stop_strategy(1e-7),
		                                             Qi,
													 starting_point, -1);

		std::cout << "Optimized: \n"<< starting_point << std::endl;
	}

	return 0.0000001;
}

} /* namespace mirt */

