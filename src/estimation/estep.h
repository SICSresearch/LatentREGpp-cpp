/*
 * estep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTEP_H_
#define ESTIMATION_ESTEP_H_

#include <iostream>
#include "../model/model.h"
#include "../util/matrix.h"
#include "../util/quadraturepoints.h"

namespace mirt {

/**
 * Estep of the EMAlgortihm
 *
 * */
void Estep(model&, std::vector<item_parameter>&, matrix<char>&,
		   std::vector<matrix<int> >&, std::vector<int>&, int, int,
		   std::vector<matrix<double> >&);

} /* namespace mirt */

#endif /* ESTIMATION_ESTEP_H_ */
