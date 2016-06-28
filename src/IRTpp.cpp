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

	improveIO();
	simulation sim;

	//simulation
	//Params:
	//2PL, 1D, 100 iter, folder, filename, saves each 20 iter, dif, is data dicho?
	sim.simulate(2, 1, 100, "datasets/1D/poly/escenario1", "1D-poly-1000x10-", 20, 0.001, false);


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
