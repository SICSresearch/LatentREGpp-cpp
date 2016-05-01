/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "mstep.h"

namespace mirt {

int i;

double Qi (const column_vector& v) {
	/**
	 * Computing value of Qi function
	 * */
	double value = 0;
	for ( int g = 0; g < G; ++g ) {
		std::vector<double> &theta_g = *theta.get_pointer_row(g);

		int mi = zeta[i].get_categories();
		//Creating an item from a column_vector
		item_parameter item_i = item_parameter::build_item(v, d, mi);

		for ( int k = 0; k < mi; ++k )
			value += r[g](i, k) * log( m.Pik(theta_g, item_i, k) );
	}
	return value;
}

// TODO Include derivates
const column_vector Qi_derivative (const column_vector& m) {

}

double Mstep() {
	/*********************************
	 *  M STEP
	 *
	 *********************************/

	double max_difference = 0.0;

	// Iterate over the number of items
	for ( i = 0; i < p; ++i ) {
		//Creating starting point
		column_vector starting_point(zeta[i].get_number_of_parameters());
		int j = 0;
		for ( int k = 0; k < d; ++k, ++j )
			starting_point(j) = zeta[i].alpha[k];
		for ( unsigned int k = 0; k < zeta[i].gamma.size(); ++k, ++j )
			starting_point(j) = zeta[i].gamma[k];
		if ( zeta[i].guessing ) starting_point(j) = zeta[i].c;


		/**
		 *	Calling bfgs from dlib to optimize Qi
		 * */
		dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
													 dlib::objective_delta_stop_strategy(1e-4),
		                                             Qi,
													 starting_point, -1);


		//Computing difference of current item
		double dif = 0.0;

		j = 0;
		for ( int k = 0; k < d; ++k, ++j ) {
			dif = std::max(dif, std::abs(zeta[i].alpha[k] - starting_point(j)));

			//Updating new value for alpha
			zeta[i].alpha[k] = starting_point(j);
		}

		for ( unsigned int k = 0; k < zeta[i].gamma.size(); ++k, ++j ) {
			dif = std::max(dif, std::abs(zeta[i].gamma[k] - starting_point(j)));

			//Updating new value for alpha
			zeta[i].gamma[k] = starting_point(j);
		}

		if ( j == starting_point.size() ) {
			dif = std::max(dif, std::abs(zeta[i].c - starting_point(j)));
			zeta[i].c = starting_point(j);
		}

		max_difference = std::max(max_difference, dif);
	}

	return max_difference;
}

} /* namespace mirt */

