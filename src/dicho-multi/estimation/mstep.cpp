/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "../../dicho-multi/estimation/mstep.h"

namespace irtpp {

namespace dichomulti {

Qi::Qi (int i, estimation_data *d) : i(i), data(d) { }

double Qi::operator() ( const item_parameter& item_i ) const {
	//Value of Qi
	double value = 0;
	//Number of quadrature points
	int G = data->G;
	//Matrix P
	matrix<double> &P = data->P;
	//Matrix r
	matrix<double> &r = data->r;
	//Model used
	model &m = data->m;
	//Latent trait vectors
	matrix<double> &theta = data->theta;
	//f
	std::vector<double> &f = data->f;

	for ( int g = 0; g < G; ++g ) {
		std::vector<double> &theta_g = *theta.get_pointer_row(g);
		double P_gi = m.P(theta_g, item_i);
		value += r(g, i) * log(P_gi) + (f[g] - r(g, i)) * log(1 - P_gi);
	}

	return value;
}

double Mstep(estimation_data &data, double epsilon) {
	double max_difference = 0.0;

	int &p = data.p;
	int &d = data.d;
	std::vector<item_parameter> &zeta = data.zeta;
	std::set<int> &pinned_items = data.pinned_items;
	std::vector<bool> &active_items = data.active_items;
	int &active_items_count = data.active_items_count;

	/**
	 * Log likelihood must be optimized for every item
	 * */

	int off = 0;

	#pragma omp parallel for schedule(dynamic) reduction(+:off)
	for ( int i = 0; i < p; ++i ) {
		/**
		 * If it is multidimensional and this is one of the pinned items
		 * i.e the first item of a dimension
		 * this item is just skipped
		 * */
		if ( pinned_items.count(i) ) continue;

		//If this item is not active is also skipped
		if ( !active_items[i] ) continue;

		item_parameter before = zeta[i];

		//Calling BFGS from dlib to optimize Qi with approximate derivatives (Log likelihood)
		dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
					   dlib::objective_delta_stop_strategy(1e-7),
					   Qi(i, &data), zeta[i], -1);

		//Computing difference of current item
		double max_difference_i = 0.0;
		for ( int j = 0; j < before.size(); ++j )
			max_difference_i = std::max(max_difference_i, std::abs(before(j) - zeta[i](j)));

		max_difference = std::max(max_difference, max_difference_i);

		if ( max_difference_i < epsilon ) {
			active_items[i] = false;
			++off;
		}
	}

	if ( active_items_count != p - d && active_items_count == off ) {
		active_items.assign(p, true);
		active_items_count -= off;
		std::cout << "Turning off: " << off << " Active: " << active_items_count << std::endl;
		active_items_count = p - d;
		std::cout << "Turning on all items, active: " << active_items_count << std::endl;
		max_difference = Mstep(data, epsilon);
	} else {
		active_items_count -= off;
		std::cout << "Turning off: " << off << " Active: " << active_items_count << std::endl;
	}

	return max_difference;
}

}

} /* namespace irtpp */

