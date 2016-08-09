/*
 * constants.h
 *
 *  Created on: Jul 22, 2016
 *      Author: Milder
 */

#ifndef UTIL_CONSTANTS_H_
#define UTIL_CONSTANTS_H_

#include <string>

//including optimization files from dlib library
#include <dlib/optimization.h>

namespace irtpp {

	typedef dlib::matrix<double,0,1> optimizer_vector; /**< data type from dlib library*/

	const int MAX_ITERATIONS = 500; /**< Max number of iterations of EMAlgorithm*/
	const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40; /**< Max number of quadrature points*/

	const std::string GAUSSIAN_QUADRATURE = "Gaussian";
	const std::string SOBOL_QUADRATURE = "Sobol";
	const int DEFAULT_SOBOL_POINTS = 2000;

	const std::string NONE = "None";
	const std::string BUILD = "Build";

	const std::string ONEPL = "1PL";
	const std::string TWOPL = "2PL";
	const std::string THREEPL = "3PL";

	const std::vector<int> EMPTY_INTEGER_VECTOR = std::vector<int>();

	const double LOWER_BOUND_ = 1e-08;
	const double UPPER_BOUND_ = 0.999999;

	const int ACCELERATION_PERIOD = 3;
	const double MINIMUM_ACCEL = -5.0;

	const double PI = std::acos(-1);
}


#endif /* UTIL_CONSTANTS_H_ */
