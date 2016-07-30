/*
 * estimation.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "../../dicho-multi/estimation/estimation.h"

namespace irtpp {

namespace dichomulti {

estimation::estimation(int themodel, matrix<char> &dataset, short d,
					   double convergence_difference,
					   std::string quadrature_technique,
					   int quadrature_points,
					   std::vector<int> number_of_items,
					   std::string custom_initial_values_filename ) {
	/**
	 * Object to allocate all data needed in estimation process
	 * */
	data = estimation_data(d);
	data.dataset = &dataset;

	//-------------------------------------------------------------------------------------

	//Model to be used
	model &m = data.m;

	//Number of examinees
	int &N = data.N;

	//Number of items
	int &p = data.p;

	//Number of response patterns (s <= N)
	int &s = data.s;

	//Matrix of response patterns. Its size is s x p
	matrix<char> &Y = data.Y;

	//Frequency of each pattern
	std::vector<int> &nl = data.nl;

	//Number of quadrature points
	int &G = data.G;

	//Matrix r. Needed in Estep and Mstep
	matrix<double> &r = data.r;

	/**
	 * Probability matrix P
	 *
	 * P_gi
	 *
	 * P_gi means the probability that an individual has selected the correct answer
	 *
	 *
	 * The purpose of this matrix is to allocate the value of P_gi
	 * to avoid recompute them while matrix Pi and r are computed in EStep
	 * */
	matrix<double> &P = data.P;

	//Matrix pi
	matrix<double> &pi = data.pi;
	//f
	std::vector<double> &f = data.f;
	//Matrix correct that has been answered correctly
	matrix<int> &correct = data.correct;

	//-------------------------------------------------------------------------------------


	//Matrix of response patterns and their frequency
	std::map<std::vector<char>, int> freq;
	for ( int i = 0; i < dataset.rows(); ++i )
		++freq[dataset.get_row(i)];

	Y = matrix<char>();
	nl = std::vector<int>();

	std::map<std::vector<char>, int>::iterator it;
	for ( it = freq.begin(); it != freq.end(); ++it ) {
		Y.add_row(it->first);
		nl.push_back(it->second);
	}

	N = dataset.rows();
	s = Y.rows();
	p = Y.columns(0);

	correct = matrix<int>(s);
	for ( int l = 0; l < s; ++l )
		for ( int i = 0; i < p; ++i )
			if ( Y(l, i) )
				correct.add_element(l, i);

	if ( quadrature_technique == SOBOL_QUADRATURE )
		sobol_quadrature(quadrature_points);
	else
		gaussian_quadrature();

	//Builds r and P matrixes
	P = matrix<double>(G, p);
	pi = matrix<double>(G, s);
	r = matrix<double>(G, p);
	f = std::vector<double>(G);

	//Pinned items in multidimensional case (the first of each dimension)
	std::set<int> &pinned_items = data.pinned_items;


	//Number of items size MUST be equal to the number of dimensions
	if ( number_of_items.size() == d ) {
		int pinned = 0;
		for ( unsigned int i = 0; i < number_of_items.size(); ++i ) {
			pinned_items.insert(pinned);
			pinned += number_of_items[i];
		}
	}

	//Configurations for the estimation
	m = model(themodel);
	this->convergence_difference = convergence_difference;
	this->iterations = 0;
	this->custom_initial_values_filename = custom_initial_values_filename;
}


void estimation::sobol_quadrature (int g) {
	//Dimension
	int &d = data.d;

	//Number of quadrature points
	int &G = data.G;

	//Latent trait vectors
	matrix<double> &theta = data.theta;

	//Weights
	std::vector<double> &w = data.w;

	input<double> in(' ');
	std::stringstream ss;
	ss << "data/sobol" << d << ".data";
	in.importData(ss.str(), theta);

	G = g;

	w = std::vector<double>(G, 1.0);
}

void estimation::gaussian_quadrature () {
	//Dimension
	int &d = data.d;

	//Number of quadrature points
	int &G = data.G;

	//Latent trait vectors
	matrix<double> &theta = data.theta;

	//Weights
	std::vector<double> &w = data.w;

	/**
	 * Number of quadrature points (G) is computed based on
	 * MAX_NUMBER_OF_QUADRATURE_POINTS and dimension of the problem, in this way
	 *
	 *
	 * G will be in 1dimension = 40 ---> 40^1 = 40
	 * 				2dimension = 20 ---> 20^2 = 400
	 * 				3dimension = 10 ---> 10^3 = 1000
	 * 				> 4dimension = 5 ---> 5^d
	 * */

	// Latent trait vectors loaded from file
	theta = load_quadrature_points(d);

	// Weights loaded from file
	w = load_weights(d);

	G = theta.rows();
}

void estimation::load_initial_values ( std::string filename ) {
	matrix<double> mt;
	input<double> in(',');
	in.importData(filename, mt);

	//Dimension
	int &d = data.d;
	//Parameters of the items
	std::vector<item_parameter> &zeta = data.zeta[0];
	//Number of items
	int &p = data.p;
	//Model used in the problem
	model &m = data.m;

	zeta = std::vector<item_parameter>(p);
	int total_parameters = m.parameters == 1 ? 1 : m.parameters - 1 + d;

	for ( int i = 0; i < p; ++i ) {
		zeta[i] = item_parameter(total_parameters);
		for ( int j = 0; j < total_parameters; ++j )
			zeta[i](j) = mt(i, j);
	}

	//Items that will not be estimated
	std::set<int> &pinned_items = data.pinned_items;

	if ( pinned_items.empty() ) {
		int items_for_dimension = p / d;
		for ( int i = 0, j = 0; i < p; i += items_for_dimension, ++j )
			pinned_items.insert(i);
	}
}

void estimation::initial_values() {
	//Parameters of the items
	std::vector<item_parameter> &zeta = data.zeta[0];
	//Dimension
	int &d = data.d;
	//Number of examinees
	int &p = data.p;
	//Model used in the problem
	model &m = data.m;
	//Matrix of answers of the examinees
	matrix<char> &dataset = *data.dataset;

	zeta = std::vector<item_parameter>(p);
	int total_parameters = m.parameters == 1 ? 1 : m.parameters - 1 + d;

	for ( int i = 0; i < p; ++i ) {
		zeta[i] = item_parameter(total_parameters);
		for ( int j = 0; j < total_parameters; ++j )
			zeta[i](j) = 1.0;
	}

	if ( d == 1 ) {
		std::vector<double> alpha, gamma;
		find_initial_values(dataset, alpha, gamma);

		for ( int i = 0; i < p; ++i ) {
			item_parameter &item_i = zeta[i];

			if ( m.parameters > 1 ) {
				item_i(0) = alpha[i];
				item_i(1) = gamma[i];
				if ( m.parameters == 3 ) item_i(2) = -1.1;
			} else {
				item_i(0) = gamma[i];
			}
		}
	} else {
		std::vector<double> alpha, gamma;
		find_initial_values(dataset, alpha, gamma);

		for ( int i = 0; i < p; ++i ) {
			item_parameter &item_i = zeta[i];

			if ( m.parameters < 3 ) item_i(item_i.size() - 1) = gamma[i];
			else {
				item_i(item_i.size() - 2) = gamma[i];
				item_i(item_i.size() - 1) = -1.1;
			}
		}

		//Items that will not be estimated
		std::set<int> &pinned_items = data.pinned_items;

		if ( pinned_items.empty() ) {
			int items_for_dimension = p / d;
			for ( int i = 0, j = 0; i < p; i += items_for_dimension, ++j )
				pinned_items.insert(i);
		}

		int j = 0;
		for ( auto pinned : pinned_items ) {
			item_parameter &item = zeta[pinned];
			for ( int h = 0; h < d; ++h )
				item(h) = 0;
			item(j) = 1;
			++j;
		}
	}
}

void estimation::EMAlgortihm() {
	if ( custom_initial_values_filename == NONE || custom_initial_values_filename == BUILD ) initial_values();
	else load_initial_values(custom_initial_values_filename);
	double dif = 0.0;
	iterations = 0;
	int current;
	do {
		current = iterations % ZETA_STEP;
		Estep(data, current);

		if ( iterations > 0 && current == 2 ) {
			ramsay(data.zeta, data.pinned_items);
			//squarem(data.zeta, data.pinned_items);
		}

		dif = Mstep(data, current);
		++iterations;
		std::cout << "Iteration: " << iterations << " \tMax-Change: " << dif << std::endl;
	} while ( dif > convergence_difference && iterations < MAX_ITERATIONS );
}

void estimation::print_results ( ) {
	std::vector<item_parameter> &zeta = data.zeta[iterations % ZETA_STEP];
	int &p = data.p;
	model &m = data.m;

	std::cout << "Finished after " << iterations << " iterations.\n";

	bool guessing_parameter = m.parameters == 3;
	for ( int i = 0; i < p; ++i ) {
		std::cout << "Item " << i + 1 << '\n';
		for ( int j = 0; j < zeta[i].size() - guessing_parameter; ++j )
			std::cout << zeta[i](j) << ' ';
		if ( guessing_parameter ) {
			double c = zeta[i](zeta[i].size() - 1);
			std::cout << 1.0 / (1.0 + exp(-c));
		}
		std::cout << '\n';
	}
}

void estimation::print_results ( std::ofstream &fout, double elapsed ) {
	std::vector<item_parameter> &zeta = data.zeta[iterations % ZETA_STEP];
	int &d = data.d;
	int &p = data.p;
	model &m = data.m;

	bool guessing_parameter = m.parameters == 3;
	for ( int i = 0; i < p; ++i ) {
		for ( int j = 0; j < zeta[i].size() - guessing_parameter; ++j ) {
			if ( j ) fout << ';';
			fout << zeta[i](j);
		}
		if ( guessing_parameter ) {
			double c = zeta[i](zeta[i].size() - 1);
			fout << 1.0 / (1.0 + exp(-c));
		}
		fout << ';' << iterations << ';' << elapsed << '\n';
	}
}

estimation::~estimation() {

}

} /* namespace dichomulti */

} /* namespace irtpp */
