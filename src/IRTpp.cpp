#include <iostream>
#include "simulation/simulation.h"

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

	//compute_and_save_quadrature_points(5, 7);
	//compute_and_save_weights(5, 7);

	improveIO();
	simulation sim;

	//sim.run_single_dichotomous(2, 6, "datasets/6D-dicho-1000x60-1.csv", 0.001);
	sim.simulate(2, 4, 1, "datasets", "4D-poly-1000x100-", 1, 0.01, false, 500);

	//simulation
	//Params:
	//2PL, 1D, 100 iter, folder, filename, saves each 20 iter, dif, is data dicho?
	//sim.simulate(2, 1, 100, "datasets/1D/poly/escenario1", "1D-poly-1000x10-", 20, 0.001, false);


//	//Runs single test, with dichotomous approach
//	//2PL, 2 dimensions
//	sim.run_single(2, 2, "datasets/2D-dicho-1000x50-1.csv", 0.001, true);
//	//This is the same than above
//	sim.run_single_dichotomous(2, 2, "datasets/2D-dicho-1000x50-1.csv", 0.001);
//
//
//	//Runs single test, with polytomous approach
//	//2PL, 2 dimensions
//	sim.run_single(2, 2, "datasets/2D-dicho-1000x50-1.csv", 0.001, true);
//	//This is the same than above
//	sim.run_single_polytomous(2, 2, "datasets/2D-dicho-1000x50-1.csv", 0.001);
}
