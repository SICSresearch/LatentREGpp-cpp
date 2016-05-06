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

void simulate_dicho_multi ( int start, int end ) {
	std::ofstream report_parameters, report_times;
	std::stringstream ss;
	ss << "datasets/dicho-multi-tests/escenario1/estimation" << start << "-" << end << ".txt";
	std::string parameters = ss.str();
	ss.str("");
	ss << "datasets/dicho-multi-tests/escenario1/times" << start << "-" << end << ".txt";
	std::string times = ss.str();
	report_parameters.open(parameters.c_str());
	report_times.open(times.c_str());

	report_parameters.precision(4);
	report_times.precision(4);

	const std::string base_name = "datasets/dicho-multi-tests/escenario1/dicho-multi";
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

		e.EMAlgortihm();

		clock_t stop = clock();
		double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

		report_parameters << "ITERATION " << i << '\n';
		e.print_results(report_parameters);
		report_parameters << "\n\n";

		report_times << "ITERATION " << i << " - " << elapsed << "s." << '\n';

		cout << "Iteration " << i << " - " << elapsed << "s." << '\n';
	}

	report_parameters.close();
	report_times.close();
}

void simulate_dicho_multi ( int iterations ) {
	for ( int i = 13; i <= iterations; i += 10 ) {
		simulate_dicho_multi(i, i + 9);
	}
}

int main() {
	cout.setf(std::ios_base::fixed);
	//cout.precision(5);

	improveIO();
	simulate_dicho_multi(100);
}
