/*
 * estimation.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef DICHOMULTI_ESTIMATION_ESTIMATION_H_
#define DICHOMULTI_ESTIMATION_ESTIMATION_H_

#include "../../util/initial_values.h"
#include "../../util/matrix.h"
#include "../../util/input.h"
#include "../../util/quadraturepoints.h"
#include "../../util/constants.h"
#include "../../util/squarem.h"
#include "../../util/ramsay.h"

#include <map>
#include <cmath>

#include "../estimation/estep.h"
#include "../estimation/mstep.h"
#include "../model/model.h"
#include "../type/estimationdata.h"

namespace irtpp {

namespace dichomulti {
/**
 * Max number of iterations of EMAlgorithm
 * */
const int MAX_ITERATIONS = 500;

const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40;

/*
 * Class to set up and run the estimation process
 *
 * The main method is EMAlgorithm
 * */

class estimation {
	private:

		/**
		 * Counts the actual number of iterations
		 * */
		short iterations;

		/**
		 * Epsilon to stop the EMAlgorithm
		 * */
		double convergence_difference;

		std::string custom_initial_values_filename;

	public:
		/**
		 * Saves all data needed in the estimation process
		 * */
		estimation_data data;

		/**
		 * Receives:
		 * 	1. A specific model to use -> [1, 3] that means 1PL, 2PL, or 3PL
		 *  2. A matrix containing the answers of examinees
		 *  3. The dimension of the problem
		 *	4. The epsilon (convergence difference) that the algoritm will use
		 *		as a criterion to stop
		 *
		 *	Optional parameters:
		 *		quadrature_technique: [GAUSSIAN_QUADRATURE, SOBOL_QUADRATURE]
		 *		quadrature_points: 	  Custom number of quadrature points
		 *		cluster: 			  Vector that contains the number of item for each dimension
		 *		custom_initial_values_filename:		  Custom initial values filename
		 *
		 *  Then it sets up all the data needed to start the estimation process
		 *
		 * */
		estimation(int, matrix<char>&, short, double,
						std::string quadrature_technique = GAUSSIAN_QUADRATURE,
						int quadrature_points = DEFAULT_SOBOL_POINTS,
						std::vector<int> cluster = std::vector<int>(),
						std::string custom_initial_values_filename = NONE );

		virtual ~estimation();

		/**
		 * Finds the initial values for every parameter of the items to start the estimation
		 * */
		void initial_values();

		/**
		 * Loads the initial values for every parameter of the items to start the estimation
		 * from file
		 * */
		void load_initial_values(std::string);

		void sobol_quadrature (int);

		void gaussian_quadrature ();

		/*
		 * Runs the EMAlgorithm to find out the parameters
		 * */
		void EMAlgortihm();

		/**
		 * Prints the results
		 * Values of the estimated parameters
		 * */
		void print_results();

		/**
		 * Prints the results to a specific output stream,
		 * including time elapsed in ms
		 * */
		void print_results(std::ofstream &, double);
};

}

} /* namespace irtpp */

#endif /* ESTIMATION_ESTIMATION_H_ */
