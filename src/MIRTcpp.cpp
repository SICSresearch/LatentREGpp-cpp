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

void simulation100iterations()
{
	for (int var = 30; var < 99; var++) {
		input<char> in(';');
		//output<char> out(';');
		matrix<char> Y;

		std::string inFile= "C:/Users/Jhonatan/Desktop/Test poli-uni escenario 2/dataset";
		std::string extension = ".csv";

		std::stringstream ss;
		ss<<inFile<<var+1<<extension;

		std::string file = ss.str();

		in.importData(file, Y);
		std::cout << "Data imported" << std::endl;
		std::cout <<Y.rows()<<" "<<Y.columns(0)<<std::endl;
		clock_t start = clock();
		//Unidimensional

		std::cout<<"ITERACION: "<<var+1<<std::endl;

		estimation e(2, Y, 1, 0.001);

		e.EMAlgortihm();

		clock_t stop = clock();
		double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

		std::string outFile = "C:/Users/Jhonatan/Desktop/Test poli-uni escenario 2/ResultsDataSet";

		std::stringstream sss;
		sss<<outFile<<var+1<<extension;

		std::string oFile = sss.str();

		e.print_results();
		e.exportData(oFile,elapsed);
		cout << "Time elapsed: " << elapsed << " ms." << '\n';
	}

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

	/*
	matrix<char> Y;
	input<char> in(';');
	in.importData("C:/Users/Jhonatan/Desktop/Tests poli-uni/dataset5.csv", Y);
	std::cout << "Data imported" << std::endl;

	clock_t start = clock();

	**
	 * Estimation with
	 * 	Model: 1PL, 2PL, 3PL
	 * 	Y matrix as dataset
	 * 	N dimension
	 * 	0.001 as convergence difference
	 *
	 * 	If it is multidimensional you can specify the number of items for dimension
	 * 	using a vector
	 * *


	//Multidimensional example
	std::vector<int> number_of_items;
	number_of_items.push_back(4);
	number_of_items.push_back(4);
	number_of_items.push_back(3);
	//estimation e(2, Y, 3, 0.001, number_of_items);


	//Unidimensional
	estimation e(2, Y, 1, 0.001);


	e.EMAlgortihm();

	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

	e.print_results();
	e.exportData("C:/Users/Jhonatan/Desktop/Tests poli-uni/ResultsDataSet5.csv",elapsed);
	cout << "Time elapsed: " << elapsed << " ms." << '\n'; */

	simulation100iterations();
	//simulation();

}
