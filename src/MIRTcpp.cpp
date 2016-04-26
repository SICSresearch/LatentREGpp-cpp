#include <iostream>
#include "util/matrix.h"
#include "util/input.h"
#include "estimation/estimation.h"
#include "util/quadraturepoints.h"
#include <fstream>
#include <cstdlib>

using namespace mirt;
using std::cout;

/**
 * MIRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */

inline void improveIO () {
	std::ios_base::sync_with_stdio(0);
	//std::cin.tie(0); std::cout.tie(0);
}

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(25);

//	compute_and_save_quadrature_points(40, 1);
//	compute_and_save_weights(40, 1);
//
//	compute_and_save_quadrature_points(20, 2);
//	compute_and_save_weights(20, 2);
//
//	compute_and_save_quadrature_points(10, 3);
//	compute_and_save_weights(10, 3);
//
//	compute_and_save_quadrature_points(5, 4);
//	compute_and_save_weights(5, 4);

	improveIO();

	matrix<char> Y;
	input<char> in(';');
	in.importData("test/dataset02.csv", Y);

	cout << "Data\n";
	cout << Y << std::endl;

	estimation e(2, Y, 1, 0.001);
	e.EMAlgortihm();
}
