/*
 * model.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "model.h"

namespace irtpp {

namespace multidichotomous {

model::model() {
	// TODO Auto-generated constructor stub

}

model::model(int parameters) {
	this->parameters = parameters;
}

double model::P(std::vector<double> &theta, item_parameter &parameters) {
	if ( this->parameters == 1 ) {
		/**
		 * 1PL Approach
		 *
		 * */

		//Initialized with gamma_k value
		double eta = parameters(0);

		//Computing dot product
		for ( short i = 0; i < theta.size(); ++i )
			eta += 1 * theta[i]; //no alpha in this model

		return 1.0 / (1.0 + std::exp(-eta));
	}
	if ( this->parameters == 2 ) {
		/**
		 * 2PL Approach
		 * */

		//Initialized with gamma value
		double eta = parameters(parameters.size() - 1);

		//Computing dot product
		for ( short i = 0; i < theta.size(); ++i )
			eta += parameters(i) * theta[i];

		return 1.0 / (1.0 + std::exp(-eta));
	}
	//TODO 3PL

	return 0.5;
}

model::~model() {
	// TODO Auto-generated destructor stub
}

}

} /* namespace irtpp */
