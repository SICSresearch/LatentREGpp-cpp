/*
 * model.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <cmath>
#include <cassert>
#include "../util/itemparameter.h"

//including optimization files from dlib library
#include <dlib/optimization.h>

namespace mirt {

// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

class item_parameter;
class model;

/*
 * Model class
 * It represents what is the model approach to use
 * Might be 1PL, 2PL, 3PL
 * */

/**
 * Variable to know if data is dichotomous
 *
 * */
extern bool dichotomous;
extern model m;

class model {

public:
	/**
	 * Number of parameters of the model
	 * */
	int parameters;

	model();

	/**
	 * This receives 1, 2 or 3. Depending on the model to use
	 * */
	model(int);
	virtual ~model();

	/**
	 * Probability in dichotomous case
	 * */
	double Pstar_ik(std::vector<double>&, item_parameter&, int k);

	/**
	 * This method computes the probability that a response pattern U_l has the category k to item
	 * i, given that its latent trait vector theta, and the item paramters
	 * */
	double Pik(std::vector<double>&, item_parameter&, int k);
};

} /* namespace mirt */

#endif /* MODEL_MODEL_H_ */
