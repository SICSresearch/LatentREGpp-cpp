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

	//sim.run_single_unidimensional(1, "datasets/LSAT7.csv", 0.0001);
	sim.run_single_multidimensional(2, "datasets/2D/poly/escenario1/2D-poly-1000x50-1.csv", 2, 0.001);
}
