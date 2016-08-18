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

void UNAL () {
	matrix<char> Y;
	input<char> in;
	in.import_data("datasets/Test UNAL/9D.csv", Y);
	std::cout << "Data imported from " << "datasets/Test UNAL/9D.csv" << std::endl;

	std::vector<int> cluster = {47, 12, 4, 4, 6, 4, 14, 5, 5};
	dichotomous::estimation e(Y, 9, 3, 0.001, cluster, "QMCEM", 2000,
			EMPTY_INTEGER_VECTOR, "datasets/Test UNAL/INI-9D.csv");
	e.EMAlgorithm();
	e.print_item_parameters();
	e.print_item_parameters("datasets/Test UNAL/9D-items-estimation.csv");
	e.MAP(true);
	e.print_latent_traits("datasets/Test UNAL/9D-LT-estimation.csv");
	std::cout << "Log likelihood: " << e.log_likelihood() << std::endl;
}

void uni () {
	simulation sim;
	sim.run_single_dichotomous(2, 1, "datasets/unidim_data.csv", 0.0001);
}

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(5);
	improveIO();

	uni();
}
