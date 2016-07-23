/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "mstep.h"

namespace irtpp {

namespace polytomous {

Qi::Qi (int i, estimation_data *d) : i(i), data(d) { }

double Qi::operator() ( const column_vector& item_i ) const {
	//Value of Qi
	double value = 0;
	//Number of categories
	int mi = data->categories_item[i];
	//Number of quadrature points
	int G = data->G;
	//Matrix r
	std::vector<matrix<double> > &r = data->r;
	//Model used
	model &m = data->m;
	//Latent trait vectors
	matrix<double> &theta = data->theta;

	for ( int g = 0; g < G; ++g ) {
		std::vector<double> &theta_g = *theta.get_pointer_row(g);
		for ( int k = 0; k < mi; ++k )
			value += r[g](i, k) * log( m.Pik(theta_g, item_i, i, k) );
	}

	return value;
}

Qi_derivative::Qi_derivative (int i, estimation_data *d) : i(i), data(d) { }

const column_vector Qi_derivative::operator() ( const column_vector& item_i ) const {
	double tmp = 0;
	double tmp2 = 0;
	double tmp3 = 0;
	double var = 0;
	double kmax = data->categories_item[i];
	//Model used
	model &m = data->m;
	//Matrix r
	std::vector<matrix<double> > &r = data->r;

	//Latent trait vectors
	matrix<double> &theta = data->theta;

	column_vector res(kmax);

	int G = data->G;
	//Lambda derivative for each item
	for (int g = 0; g < G; ++g) {
		std::vector<double> &theta_g = *theta.get_pointer_row(g);
		tmp3 = 0;
		for (int k = 0; k<kmax ;++k) {
			tmp3 += (((r[g](i, k))/(m.Pik(theta_g,item_i,i,k)))*((m.Pstar_ik(theta_g,item_i,i,k-1))*(1-(m.Pstar_ik(theta_g,item_i,i,k-1)))-(m.Pstar_ik(theta_g,item_i,i,k))*(1-(m.Pstar_ik(theta_g,item_i,i,k)))));
		}
		tmp2 += (theta_g[0]*tmp3);
	}
	if(m.parameters>1)
		res(0) = tmp2;

	tmp2 = 0;

	//k derivatives for each item
	for (int k = 0; k<kmax-1;++k) {
		for (int g = 0; g < G; ++g) {
			std::vector<double> &theta_g = *theta.get_pointer_row(g);

			tmp = m.Pstar_ik(theta_g,item_i,i,k)*(1-(m.Pstar_ik(theta_g,item_i,i,k)));
			tmp2 = ((-(r[g](i, k)))/(m.Pik(theta_g,item_i,i,k)))+(r[g](i, k+1))/(m.Pik(theta_g,item_i,i,k+1));

			var += tmp*tmp2;
		}
		if (m.parameters>1)
			res(k+1) = var;
		else
			res(k) = var;
		var = 0;
	}
	return res;
}

double Mstep(estimation_data &data) {
	double max_difference = 0.0;

	int &p = data.p;
	int &d = data.d;
	std::vector<item_parameter> &zeta = data.zeta;
	std::set<int> &pinned_items = data.pinned_items;
	/**
	 * Log likelihood must be optimized for every item
	 * */

	#pragma omp parallel for schedule(dynamic)
	for ( int i = 0; i < p; ++i ) {
		/**
		 * If it is multidimensional and this is one of the pinned items
		 * i.e the first item of a dimension
		 * this item is just skipped
		 * */
		if ( pinned_items.count(i) ) continue;

		column_vector &item_i = zeta[i];
		column_vector before = item_i;

		/**
		 *	Calling BFGS from dlib to optimize Qi with explicit derivatives (Log likelihood)
		 * */

		/**
		 * If the dimension is 1, the optimization is done with explicit derivatives
		 * */
		if ( d == 1 ) {
			dlib::find_max(dlib::bfgs_search_strategy(),
										   dlib::objective_delta_stop_strategy(1e-5),
										   Qi(i, &data),
										   Qi_derivative(i, &data),item_i,-1);
		} else {
			dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
						   dlib::objective_delta_stop_strategy(1e-5),
						   Qi(i, &data),item_i,-1);
		}

		//Computing difference of current item
		for ( int j = 0; j < before.size(); ++j )
			max_difference = std::max(max_difference, std::abs(before(j) - item_i(j)));
	}

	return max_difference;
}

}

} /* namespace irtpp */

