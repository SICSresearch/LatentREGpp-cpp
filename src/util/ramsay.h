/*
 * squarem.h
 *
 *  Created on: Jul 28, 2016
 *      Author: Milder
 */

#ifndef UTIL_RAMSAY_H_
#define UTIL_RAMSAY_H_

#include <dlib/optimization.h>
#include "constants.h"
#include <vector>
#include <cmath>
#include <set>

namespace irtpp {

typedef dlib::matrix<double,0,1> item_parameter; /**< data type from dlib library*/

/**
 * Ramsay is an accelerate method for EM algorithm.
 * @params zeta a vector with previous zeta values z0,z1,z2 calculated in EM algorithm.
 * @params pinned a set with int template that contains items that won't be estimated, pass by reference.
 */
void ramsay ( std::vector<item_parameter> zeta[ACCELERATION_PERIOD], std::set<int> &pinned );


} /* namespace irtpp */

#endif /* UTIL_SQUAREM_H_ */
