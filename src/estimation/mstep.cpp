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
			item_parameter item_i = item_parameter::build_item(v, d, mi);
			value += r[g](i, k) * log( m.Pik(theta_g, item_i, k) );
		}
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

	/**
	 * New vector of parameters
	 * */
	std::vector<item_parameter> new_zeta;

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

		/**
		 *	Calling bfgs from dlib to optimize Qi
		 * */
		dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
													 dlib::objective_delta_stop_strategy(1e-7),
		                                             Qi,
													 starting_point, -1);

		std::cout << "Optimized: \n"<< starting_point << std::endl;

		new_zeta.push_back(item_parameter::build_item(starting_point, d, zeta[i].get_categories()));

		//Computing difference of current item
		double current_difference = 0.0;
		for ( int i = 0; i < zeta[i].alpha.size(); ++i )
			current_difference = std::max(current_difference,
										  std::abs(zeta[i].alpha[j] - new_zeta[i].alpha[j]));
		for ( int i = 0; i < zeta[i].gamma.size(); ++i )
			current_difference = std::max(current_difference,
										  std::abs(zeta[i].gamma[j] - new_zeta[i].gamma[j]));

		max_difference = std::max(max_difference, current_difference);
		std::cout << "Difference between zeta's i " << current_difference << std::endl;
	}



	zeta = new_zeta;
	return 0.000001;
}

} /* namespace mirt */

