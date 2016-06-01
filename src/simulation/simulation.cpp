/*
 * simulation.cpp
 *
 *  Created on: 1/06/2016
 *      Author: Milder
 */

#include "simulation.h"
#define START_CLOCK		clock_t start = clock();
#define END_CLOCK		clock_t stop = clock();
#define REPORT_TIME     double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;\
						std::cout << "Time elapsed: " << elapsed << " ms." << '\n';


namespace irtpp {

void simulation::simulate ( int start, int end, std::string folder, std::string name ) {
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

		START_CLOCK

		estimation e(2, Y, 2, 0.001);
		e.EMAlgortihm();

		END_CLOCK
		REPORT_TIME

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
void simulation::simulate ( int iterations, std::string folder, std::string name, int interval ) {
	for ( int i = 1; i <= iterations; i += interval ) {
		simulate(i, i + interval - 1, folder, name);
	}
}

void simulation::run_single_unidimensional ( int model, std::string filename, double dif ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	estimation e(model, Y, 1, dif);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}

void simulation::run_single_multidimensional ( int model, std::string filename, int d, double dif ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	estimation e(model, Y, d, dif);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}

void simulation::run_single_multidimensional ( int model, std::string filename, int d, double dif, std::vector<int> &items ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	estimation e(model, Y, d, dif, items);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}


simulation::simulation() {
	// TODO Auto-generated constructor stub

}

simulation::~simulation() {
	// TODO Auto-generated destructor stub
}

} /* namespace irtpp */
