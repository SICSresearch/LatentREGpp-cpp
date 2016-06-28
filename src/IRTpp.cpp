#include <iostream>
//#include "simulation/simulation.h"

//#include "util/quadraturepoints.h"

#include "util/input.h"
#include "util/matrix.h"
#include "multi-dichotomous/estimation/estimation.h"

#define START_CLOCK		clock_t start = clock();
#define END_CLOCK		clock_t stop = clock();
#define REPORT_TIME     double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;\
						std::cout << "Time elapsed: " << elapsed << " ms." << '\n';

using namespace irtpp;
using std::cout;

/**
 * IRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */

inline void improveIO () {
	std::ios_base::sync_with_stdio(0);
	//std::cin.tie(0); std::cout.tie(0);
}

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(5);

	improveIO();
//	simulation sim;
//
////	compute_and_save_quadrature_points(40, 1);
////	compute_and_save_quadrature_points(20, 2);
////	compute_and_save_quadrature_points(10, 3);
////	compute_and_save_quadrature_points(5, 4);
////	compute_and_save_quadrature_points(5, 5);
////	compute_and_save_quadrature_points(5, 6);
////	compute_and_save_weights(40, 1);
////	compute_and_save_weights(20, 2);
////	compute_and_save_weights(10, 3);
////	compute_and_save_weights(5, 4);
////	compute_and_save_weights(5, 5);
////	compute_and_save_weights(5, 6);
//
////	sim.run_single_unidimensional(2, "datasets/1D/poly/escenario1/1D-poly-1000x10-1.csv", 0.01);
//	sim.run_single_multidimensional(2, "datasets/2D-dicho-1000x50-1.csv", 2, 0.001);

	std::string filename = "datasets/2D-dicho-1000x50-1.csv";
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	multidichotomous::estimation e(2, Y, 2, 0.001);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}
