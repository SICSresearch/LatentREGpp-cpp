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
#include <set>

namespace irtpp {

class simulation {
public:
	void simulate ( int start, int end, std::string folder, std::string name );
	void simulate ( int iterations, std::string folder, std::string name, int interval );
	void run_single_dicho_uni ( );
	simulation();
	virtual ~simulation();
};

} /* namespace irtpp */

#endif /* SIMULATION_SIMULATION_H_ */
