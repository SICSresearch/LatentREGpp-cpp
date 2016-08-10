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
	std::cin.tie(0); std::cout.tie(0);
}

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(5);
	improveIO();

	matrix<char> Y;
	input<char> in(';');
	in.importData("datasets/2D-1000x40.csv", Y);
	std::cout << "Data imported from " << "datasets/2D-1000x40.csv" << std::endl;

	dichomulti::estimation e(Y, 2, 2, 0.0001, EMPTY_INTEGER_VECTOR, "QMCEM", 300);
	e.EMAlgortihm();
	e.print_item_parameters();
	e.print_item_parameters("datasets/2D-1000x40-estimation.csv");
	e.EAP(true);
	e.print_latent_traits("datasets/2D-1000x40-LT-G=300-EAP.csv");
	e.MAP(true);
	e.print_latent_traits("datasets/2D-1000x40-LT-G=300-MAP.csv");
	std::cout << e.log_likelihood() << std::endl;
}
