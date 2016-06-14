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

	sim.run_single_unidimensional(2, "datasets/1D/poly/escenario3/1D-poly-5000x20-1.csv", 0.001);
}
