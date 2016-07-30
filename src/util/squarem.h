/*
 * squarem.h
 *
 *  Created on: Jul 28, 2016
 *      Author: Milder
 */

#ifndef UTIL_SQUAREM_H_
#define UTIL_SQUAREM_H_

#include <dlib/optimization.h>
#include "constants.h"
#include <vector>
#include <cmath>
#include <set>

namespace irtpp {

typedef dlib::matrix<double,0,1> item_parameter;

void squarem ( std::vector<item_parameter> zeta[ZETA_STEP], std::set<int> &pinned );


} /* namespace irtpp */

#endif /* UTIL_SQUAREM_H_ */
