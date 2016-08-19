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
	in.import_data("datasets/Juan David/Data_CLUSTER_UNALfiltrado_final.csv", Y);
	std::cout << "Data imported" << std::endl;

	std::vector<int> cluster = {5, 14, 33, 21, 10,  9};
	dichotomous::estimation e(Y, 6, 2, 0.001, cluster, "QMCEM", 2000,
			EMPTY_INTEGER_VECTOR, "datasets/Juan David/INIVALS_DATA_CLUSTER.csv");
	e.EMAlgorithm();
	e.print_item_parameters();
	e.print_item_parameters("datasets/Juan David/Data_CLUSTER_UNALfiltrado_final-estimation.csv");
	e.MAP(true);
	e.print_latent_traits("datasets/Juan David/Data_CLUSTER_UNALfiltrado_final-LTestimation.csv");
	std::cout << "Log likelihood: " << e.log_likelihood() << std::endl;
}

void uni () {
	simulation sim;
	sim.run_single_dichotomous("datasets/unidim_data.csv", 1);
}

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(5);
	improveIO();

	uni();
	//UNAL();
}
