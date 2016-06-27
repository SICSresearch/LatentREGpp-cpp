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
#include "../polytomous/estimation/estimation.h"
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

	/**
	 * Helper function to simulate a specific range of the total number of iterations
	 * 		range -> [start, end], where 1 <= start <= iterations
	 * 									 1 <= end <= iterations
	 * 									 start <= end
	 *
	 * Should be called from
	 * 		void simulate ( int model, int d, int iterations, std::string folder, std::string name, int interval );
	 *
	 * 		and it's called iterations/interval times
	 * */
	void simulate ( int model, int d, int start, int end, std::string folder, std::string name );

	/**
	 * Simulates the number of iterations
	 *
	 * And saves estimations each 'interval' iterations
	 *
	 *	Receives the model to be used and dimension of the problem,
	 *	number of iterations, the folder where the datasets will be loaded and estimation saved
	 *	and the prefix of files allocated in 'folder'
	 *
	 *
	 *	Example:
	 *		Model: 2PL
	 *		Dimension: 2
	 *		Iterations: 100
	 *		Folder where data is: "datasets/dicho-multi-tests/escenario2"
	 *		Prefix of files in folder: "dicho-multi"
	 *		Saves each 20 iterations.
	 *
	 *
	 *		simulate(2, 2, 100, "datasets/dicho-multi-tests/escenario2", "dicho-multi", 20);
	 *
	 * */
	void simulate ( int model, int d, int iterations, std::string folder, std::string name, int interval );

	/**
	 * Runs a single unidimensional test
	 * Receives the model to use
	 * 			the filename of the dataset
	 * 			the convergence difference to use
	 * */
	void run_single_unidimensional ( int, std::string, double );

	/**
	 * Runs a single multidimensional test
	 * Receives the model to use
	 * 			the filename of the dataset
	 * 			the dimension
	 * 			the convergence difference to use
	 * */
	void run_single_multidimensional ( int, std::string, int d, double );

	/**
	 * Runs a single multidimensional test
	 * Receives the model to use
	 * 			the filename of the dataset
	 * 			the dimension
	 * 			the convergence difference to use
	 * 			the number of items of each dimension
	 * */
	void run_single_multidimensional ( int, std::string, int d, double, std::vector<int>& );
	simulation();
	virtual ~simulation();
};

} /* namespace irtpp */

#endif /* SIMULATION_SIMULATION_H_ */
