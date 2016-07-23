/*
 * simulation.cpp
 *
 *  Created on: 1/06/2016
 *      Author: Milder
 */

#include "simulation.h"
#define START_CLOCK		double start = omp_get_wtime();
#define END_CLOCK		double stop = omp_get_wtime();
#define REPORT_TIME     double elapsed = stop - start;\
						std::cout << "Time elapsed: " << elapsed << "s." << '\n';


namespace irtpp {

simulation::simulation() {
	// TODO Auto-generated constructor stub

}

void simulation::simulate ( int model, int d, int start, int end, std::string folder,
							std::string name, double dif, bool dicho,
							std::string quadrature_technique, int G, std::vector<int> cluster,
							std::string custom_initial ) {

	std::ofstream report_parameters;
	std::stringstream ss;
	ss << folder << "/estimation-" << name << '-' << start << '-' << end;
	if ( quadrature_technique == SOBOL_QUADRATURE ) ss << "-G=" << G << ".csv";

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

		if ( dicho ) {
			START_CLOCK
			dichomulti::estimation e(model, Y, d, dif, quadrature_technique, G, cluster, custom_initial);
			e.EMAlgortihm();

			END_CLOCK
			REPORT_TIME
			e.print_results(report_parameters, elapsed);
		} else {
			START_CLOCK
			polytomous::estimation e(model, Y, d, dif, quadrature_technique, G, cluster, custom_initial);
			e.EMAlgortihm();

			END_CLOCK
			REPORT_TIME
			e.print_results(report_parameters, elapsed);
		}
	}

	report_parameters.close();
}

void simulation::simulate ( int model, int d, int iterations, std::string folder,
							std::string name, int interval, double dif, bool dicho,
							std::string quadrature_technique, int G,
							std::vector<int> cluster, std::string custom_initial) {
	for ( int i = 1; i <= iterations; i += interval ) {
		simulate(model, d, i, i + interval - 1, folder, name, dif, dicho,
				 quadrature_technique, G, cluster, custom_initial);
	}
}

void simulation::run_single ( int model, int d, std::string filename, double dif, bool dicho,
							   std::string quadrature_technique, int G, std::vector<int> cluster,
							   std::string custom_initial ) {
	if ( dicho ) run_single_dichotomous(model, d, filename, dif, quadrature_technique, G, cluster, custom_initial );
	else		 run_single_polytomous(model, d, filename, dif, quadrature_technique, G, cluster, custom_initial );
}

void simulation::run_single_polytomous ( int model, int d, std::string filename, double dif,
										std::string quadrature_technique, int G, std::vector<int> cluster,
									    std::string custom_initial ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	polytomous::estimation e(model, Y, d, dif, quadrature_technique, G, cluster, custom_initial);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}

void simulation::run_single_dichotomous ( int model, int d, std::string filename, double dif,
										  std::string quadrature_technique, int G, std::vector<int> cluster,
										  std::string custom_initial ) {
	matrix<char> Y;
	input<char> in(';');
	in.importData(filename, Y);
	std::cout << "Data imported" << std::endl;

	START_CLOCK

	dichomulti::estimation e(model, Y, d, dif, quadrature_technique, G, cluster, custom_initial);
	e.EMAlgortihm();

	END_CLOCK

	e.print_results();
	REPORT_TIME
}

simulation::~simulation() {
	// TODO Auto-generated destructor stub
}

} /* namespace irtpp */
