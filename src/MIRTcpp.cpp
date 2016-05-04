#include <iostream>
#include "util/matrix.h"
#include "util/input.h"
#include "estimation/estimation.h"
#include "util/quadraturepoints.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <set>

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
	cout.precision(5);

//	std::freopen("log.txt", "w", stdout);

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
	in.importData("datasets/un_math.csv", Y);
	std::cout << "Data imported" << std::endl;

	clock_t start = clock();

	/**
	 * Estimation with
	 * 	Model: 1PL, 2PL, 3PL
	 * 	Y matrix as dataset
	 * 	N dimension
	 * 	0.001 as convergence difference
	 *
	 * 	If it is multidimensional you can specify the number of items for dimension
	 * 	using a vector
	 * */

	//Multidimensional example
//	std::vector<int> number_of_items;
//	number_of_items.push_back(15);
//	number_of_items.push_back(15);
//
//	estimation e(2, Y, 2, 0.001, number_of_items);

	//Unidimensional
	estimation e(2, Y, 1, 0.001);
	e.EMAlgortihm();

	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

	e.print_results();
	cout << "Time elapsed: " << elapsed << " ms." << '\n';
}
