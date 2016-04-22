/*
 * model.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include "../util/itemparameter.h"

namespace mirt {

/*
 * Model class
 * It represents what is the model approach to use
 * Might be 1PL, 2PL, 3PL
 * */
class model {
public:
	model();
	virtual ~model();

	/**
	 * This method computes the probability that a response pattern U_l has the category k to item
	 * i, given that its latent trait vector theta, and the item paramters
	 * */
	double Pik(std::vector<double>&, item_parameter&, int k);
};

} /* namespace mirt */

#endif /* MODEL_MODEL_H_ */
