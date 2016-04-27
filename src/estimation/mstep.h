/*
 * mstep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_MSTEP_H_
#define ESTIMATION_MSTEP_H_

#include <iostream>
#include <vector>
#include "../util/matrix.h"
#include "../model/model.h"

namespace mirt {
	/**
 	 * M step of the EM Algorithm
	 */
	double Mstep(model&, std::vector<item_parameter>&, std::vector<matrix<double> >&);

} /* namespace mirt */

#endif /* ESTIMATION_MSTEP_H_ */
