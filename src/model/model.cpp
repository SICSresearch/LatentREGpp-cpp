/*
 * model.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "model.h"

namespace mirt {

model::model() {
	// TODO Auto-generated constructor stub

}

model::model(int parameters) {
	this->parameters = parameters;
}

double model::Pstar_ik(std::vector<double> &theta, item_parameter &parameters, int k) {
	/**
	 * Base cases
	 *
	 * Because of implementation indexes start from 0 and theory from 1
	 * It's necessary subtract 1
	 * */

	if ( k == -1 ) return 1;
	if ( k == parameters.get_categories() - 1 ) return 0;

	if ( this->parameters == 1 ) {

	}
	if ( this->parameters == 2 ) {
		/**
		 * 2PL Approach
		 *
		 *
		 *
		 * */

		/**
		 * Dimensions
		 * */
		short d = parameters.get_dimension();

		/**
		 * Initialized with gamma_k value
		 * */
		double eta = parameters.gamma[k];

		//Computing dot product
		for ( short i = 0; i < d; ++i )
			eta += parameters.alpha[i] * theta[i];

		/**
		 * Equation (82) from Doc1
		 * */
		return 1.0 / (1.0 + std::exp(-eta));
	}
	/**
	 * 3PL Approach
	 *
	 * */

	return 1;
}

double model::Pik(std::vector<double> &theta, item_parameter &parameters, int k) {
	// TODO Should be loaded from file
	/**
	 * Equation (86) from Doc1
	 *
	 * */
	static const double LOWER_BOUND_ = 1e-08;
	static const double UPPER_BOUND_ = 0.999999;

	double P_ik = Pstar_ik(theta, parameters, k - 1) - Pstar_ik(theta, parameters, k);

	P_ik = std::max(P_ik, LOWER_BOUND_);
	P_ik = std::min(P_ik, UPPER_BOUND_);
	return P_ik;
}

model::~model() {
	// TODO Auto-generated destructor stub
}

} /* namespace mirt */
