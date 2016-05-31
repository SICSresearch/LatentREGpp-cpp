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

using namespace irtpp;
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

void simulate ( int start, int end, std::string folder, std::string name ) {
	std::ofstream report_parameters;
	std::stringstream ss;
	ss << folder << "/estimation" << start << "-" << end << ".csv";
	std::string parameters = ss.str();
	report_parameters.open(parameters.c_str());
	report_parameters.precision(4);

	ss.str("");
	ss << folder << "/" << name;
	const std::string base_name = ss.str();
	for ( int i = start; i <= end; ++i ) {
		matrix<char> Y;
		input<char> in(';');

		std::stringstream ss;
		ss << base_name << i << ".csv";

		std::string file_name = ss.str();
		in.importData(file_name, Y);
		std::cout << file_name << " imported" << std::endl;

		clock_t start = clock();

		//Multidimensional configuration
		std::vector<int> number_of_items;
		number_of_items.push_back(25);
		number_of_items.push_back(25);
		estimation e(2, Y, 2, 0.001, number_of_items);

		//Unidimensional configuration
		//estimation e(2, Y, 1, 0.001);

		e.EMAlgortihm();

		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

		//e.print_results();
		std::cout << elapsed << "s." << std::endl;
		e.print_results(report_parameters, elapsed);
	}

	report_parameters.close();
}

/**
 * Simulates the number of iterations
 *
 * And saves estimations each 'interval' iterations
 *
 *	Receives the number of iterations, the folder where the datasets will be loaded and estimation saved
 *	and the name with each file of estimation will be saved
 *
 *
 *	Example:
 *		simulate(100, "datasets/dicho-multi-tests/escenario2", "dicho-multi", 20);
 * */
void simulate ( int iterations, std::string folder, std::string name, int interval ) {
	for ( int i = 1; i <= iterations; i += interval ) {
		simulate(i, i + interval - 1, folder, name);
	}
}

void run_single_dicho_uni ( ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData("datasets/LSAT7.csv", Y);
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

int main() {
	cout.setf(std::ios_base::fixed);
	cout.precision(3);

	improveIO();
	run_single_dicho_uni();
}
