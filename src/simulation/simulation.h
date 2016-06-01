/*
 * simulation.h
 *
 *  Created on: 1/06/2016
 *      Author: Milder
 */

#ifndef SIMULATION_SIMULATION_H_
#define SIMULATION_SIMULATION_H_

#include <iostream>
#include "../util/matrix.h"
#include "../util/input.h"
#include "../estimation/estimation.h"
#include "../util/quadraturepoints.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include <set>

namespace irtpp {

class simulation {
public:
	void simulate ( int start, int end, std::string folder, std::string name );
	void simulate ( int iterations, std::string folder, std::string name, int interval );
	void run_single_unidimensional ( int, std::string, double );
	void run_single_multidimensional ( int, std::string, int d, double );
	void run_single_multidimensional ( int, std::string, int d, double, std::vector<int>& );
	simulation();
	virtual ~simulation();
};

} /* namespace irtpp */

#endif /* SIMULATION_SIMULATION_H_ */
