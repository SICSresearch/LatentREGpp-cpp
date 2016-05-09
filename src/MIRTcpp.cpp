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
 * And saves estimations each 20 iterations
 *
 *	Receives the number of iterations, the folder where the datasets will be loaded and estimation saved
 *	and the name which each file of estimation will be saved
 * */
void simulate ( int iterations, std::string folder, std::string name ) {
	for ( int i = 1; i <= iterations; i += 20 ) {
		simulate(i, i + 19, folder, name);
	}
}

int main() {
	cout.setf(std::ios_base::fixed);
	//cout.precision(5);

	improveIO();
	simulate(100, "datasets/dicho-multi-tests/escenario2", "dicho-multi");
}
