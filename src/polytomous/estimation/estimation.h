/**
 * estimation.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef POLYTOMOUS_ESTIMATION_ESTIMATION_H_
#define POLYTOMOUS_ESTIMATION_ESTIMATION_H_

#include "estep.h"
#include "mstep.h"

#include "../model/model.h"

#include "../../util/matrix.h"
#include "../../util/input.h"
#include "../../util/quadraturepoints.h"
#include "../../util/initial_values.h"
#include "../../util/constants.h"

#include "../type/estimationdata.h"

#include <map>
#include <cmath>

namespace irtpp {

namespace polytomous {

const int MAX_ITERATIONS = 500; /**< Max number of iterations of EMAlgorithm*/
const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40; /**< Max number of quadrature points*/

/**
 * Class to set up and run the estimation process
 * in polytomous models
 *
 * The main method is EMAlgorithm
 */
class estimation {
	private:

		short iterations; /**< Counts the actual number of iterations*/
		double convergence_difference; /**< Epsilon to stop the EMAlgorithm*/
		std::string custom_initial_values_filename; /**< path with custom initial values*/

	public:

		estimation_data data; /**< Saves all data needed in the estimation process*/

		/**
		 * Receives:
		 * 	1. A specific model to use -> [1, 3] that means 1PL, 2PL, or 3PL
		 *  2. A matrix containing the answers of examinees
		 *  3. The dimension of the problem
		 *	4. The epsilon (convergences difference) that the algoritm will use
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
		 * @param themodel model to use 1PL, 2PL or 3PL.
		 * @param dataset a matrix data type char template with data to estimate parameters.
		 * @param d the dimension.
		 * @param convergence_difference epsilon convergence difference.
		 * @param quadrature_technique string. it can be Gaussian or Sobol.
		 * @param quadrature_technique if Sobol. Number of points to use.
		 * @param cluster a std vector integer template with number of items for each dimension.
		 * @param custom_initial_values_filename string with path for custom initial_values. Default is none.
		 */
		estimation(int, matrix<char>&, unsigned int, double,
				std::string quadrature_technique = GAUSSIAN_QUADRATURE,
				int quadrature_points = DEFAULT_SOBOL_POINTS,
				std::vector<int> cluster = std::vector<int>(),
				std::string custom_initial_values_filename = NONE );

		/**
		 * Destructor for estimation class.
		 */
		virtual ~estimation();

		/**
		 * Finds the initial values for every parameter of the items to start the estimation.
		 * it is called if custom_initial_values_filename is none by default.
		 * @see custom_initial_values_filename
		 */
		void initial_values();

		/**
		 * Loads the initial values for every parameter of the items to start the estimation
		 * from file. It is call if custom_initial_values_filename has a value different to none.
		 * @param filename string with path for initial values.
		 * @see custom_initial_values_filename
		 */
		void load_initial_values(std::string);

		/**
		 * Sobol quadrature, receives the number of points to use.
		 * @param g the number of points.
		 */
		void sobol_quadrature (int);

		/**
		 * gaussian_quadrature. By default max points to use is 40.
		 */
		void gaussian_quadrature ();

		/**
		 * Runs the EMAlgorithm to find out the parameters.
		 */
		void EMAlgortihm();

		/**
		 * Prints the results values of the estimated parameters.
		 */
		void print_results();

		/**
		 * Prints the results to a specific output stream, including time elapsed in ms.
		 * @param fout the ofstream object from std library.
		 * @param elapsed a double with time elpased in EM estimation.
		 */
		void print_results(std::ofstream &, double);
};

}

} /* namespace irtpp */

#endif /* ESTIMATION_ESTIMATION_H_ */
