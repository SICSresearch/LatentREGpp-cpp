/*
 * mstep.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "mstep.h"

namespace irtpp {

/*****************************************
 * Log likelihood Function to maximize
 *
 * */

class Qi {
public:
    Qi (int n, estimation_data *d) : i(n), data(d) { }

    double operator() ( const column_vector& v ) const {
    	double value = 0;
		int mi = data->zeta[i].get_categories();
		int G = data->G;
		std::vector<matrix<double> > &P = data->P;
		std::vector<matrix<double> > &r = data->r;
		model &m = data->m;

		//Creating an item from a column_vector
		item_parameter item_i(m, data->d, mi);
		item_parameter::build_item(v, data->d, mi, item_i);
		for ( int g = 0; g < G; ++g ) {
			std::vector<double> &theta_g = *data->theta.get_pointer_row(g);
			for ( int k = 0; k < mi; ++k )
				value += r[g](i, k) * log( m.Pik(theta_g, item_i, k) );
		}
		return value;
    }

private:
    int i;
    estimation_data *data;
};


class Qi_derivative {
public:
	Qi_derivative (int n, estimation_data *d) : i(n), data(d) { }

	const column_vector operator() ( const column_vector& v ) const {
    	double tmp = 0;
		double tmp2 = 0;
		double tmp3 = 0;
		double var = 0;
		double kmax = data->zeta[i].get_categories();
		model &m = data->m;
		std::vector<matrix<double> > &r = data->r;

		//build item for each iteration
		item_parameter item_i(m, data->d, kmax);
		item_parameter::build_item(v, data->d, kmax, item_i);

		column_vector res(kmax);

		int G = data->G;
		//Lambda derivative for each item
		for (int g = 0; g < G; ++g) {
			std::vector<double> &theta_g = *data->theta.get_pointer_row(g);
			tmp3 = 0;
			for (int k = 0; k<kmax ;++k) {
				tmp3 += (((r[g](i, k))/(m.Pik(theta_g,item_i,k)))*((m.Pstar_ik(theta_g,item_i,k-1))*(1-(m.Pstar_ik(theta_g,item_i,k-1)))-(m.Pstar_ik(theta_g,item_i,k))*(1-(m.Pstar_ik(theta_g,item_i,k)))));
			}
			tmp2 += (theta_g[0]*tmp3);
		}
		res(0) = tmp2;

		tmp2 = 0;

		//k derivatives for each item
		for (int k = 0; k<kmax-1;++k) {
			for (int g = 0; g < G; ++g) {
				std::vector<double> &theta_g = *data->theta.get_pointer_row(g);

				tmp = m.Pstar_ik(theta_g,item_i,k)*(1-(m.Pstar_ik(theta_g,item_i,k)));
				tmp2 = ((-(r[g](i, k)))/(m.Pik(theta_g,item_i,k)))+(r[g](i, k+1))/(m.Pik(theta_g,item_i,k+1));

				var += tmp*tmp2;
			}
			res(k+1) = var;
			var = 0;
		}
		return res;
    }

private:
    int i;
    estimation_data *data;
};

/**********************************
 *  M STEP						  *
 *								  *
 **********************************/

double Mstep(estimation_data &data) {
	double max_difference = 0.0;

	int &p = data.p;
	int &d = data.d;
	model &m = data.m;
	std::vector<item_parameter> &zeta = data.zeta;
	std::set<int> &pinned_items = data.pinned_items;

	/**
	 * Log likelihood must be optimized for every item
	 * */
	for ( int i = 0; i < p; ++i ) {
		/**
		 * If it is multidimensional and this is one of the pinned items
		 * i.e the first item of a dimension
		 * this item is just skipped
		 * */
		if ( d > 1 && pinned_items.count(i) ) continue;

		/**
		 * Starting point where optimization will start
		 * */
		column_vector starting_point(zeta[i].get_number_of_parameters());
		int j = 0;
		for ( int k = 0; k < zeta[i].alphas; ++k, ++j )
			starting_point(j) = zeta[i].alpha[k];
		for ( int k = 0; k < zeta[i].gammas; ++k, ++j )
			starting_point(j) = zeta[i].gamma[k];
		if ( zeta[i].guessing ) starting_point(j) = zeta[i].c;

		/**
		 *	Calling BFGS from dlib to optimize Qi with explicit derivatives (Log likelihood)
		 * */

		/**
		 * If the dimension is 1, the optimization is done with explicit derivatives
		 * */
		if ( d == 1 ) {
			if ( m.parameters < 3 ) {
				dlib::find_max(dlib::bfgs_search_strategy(),
											   dlib::objective_delta_stop_strategy(1e-4),
											   Qi(i, &data),
											   Qi_derivative(i, &data),starting_point,-1);
			} else {
				dlib::find_max_using_approximate_derivatives(dlib::lbfgs_search_strategy(6),
											   dlib::objective_delta_stop_strategy(1e-4),
											   Qi(i, &data),
											   starting_point,-1);
			}
		} else {
			dlib::find_max_using_approximate_derivatives(dlib::bfgs_search_strategy(),
						   dlib::objective_delta_stop_strategy(1e-4),
						   Qi(i, &data),starting_point,-1);
		}

		//Computing difference of current item
		double dif = 0.0;

		j = 0;
		for ( int k = 0; k < zeta[i].alphas; ++k, ++j ) {
			dif = std::max(dif, std::abs(zeta[i].alpha[k] - starting_point(j)));

			//Updating new value for alpha k
			zeta[i].alpha[k] = starting_point(j);
		}

		for ( int k = 0; k < zeta[i].gammas; ++k, ++j ) {
			dif = std::max(dif, std::abs(zeta[i].gamma[k] - starting_point(j)));

			//Updating new value for gamma k
			zeta[i].gamma[k] = starting_point(j);
		}

		if ( zeta[i].guessing ) {
			dif = std::max(dif, std::abs(zeta[i].c - starting_point(j)));
			zeta[i].c = starting_point(j);
		}

		max_difference = std::max(max_difference, dif);
	}

	return max_difference;
}

} /* namespace irtpp */

