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
#include "../util/itemparameter.h"
#include "../util/estimationdata.h"
#include <cmath>
#include <set>

//including optimization files from dlib library
#include <dlib/optimization.h>

namespace irtpp {

// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

/**
 * M step of the EM Algorithm
 */
double Mstep(estimation_data&);

	/**
	 * Function to be maximized
	 * */

} /* namespace irtpp */

#endif /* ESTIMATION_MSTEP_H_ */
