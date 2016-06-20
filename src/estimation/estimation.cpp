/*
 * estimation.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estimation.h"

namespace irtpp {

estimation::estimation() {
	// TODO Auto-generated constructor stub

}



estimation::estimation(int themodel, matrix<char> &dataset, short d,
					   double convergence_difference) {
	/**
	 * Declaring object to allocate all data needed in estimation process
	 * */
	data = estimation_data(d);

	/**
	 * Saving pointer to the dataset
	 * */
	data.dataset = &dataset;


	/**
	 * Creating reference variables for all variables in data
	 * */
	matrix<char> &Y = data.Y;
	std::vector<int> &nl = data.nl;
	int &N = data.N;
	int &s = data.s;
	int &p = data.p;
	bool &dichotomous = data.dichotomous;
	int &G = data.G;
	std::vector<int> &categories_item = data.categories_item;
	matrix<double> &theta = data.theta;
	std::vector<double> &w = data.w;
	std::vector<matrix<double> > &r = data.r;
	std::vector<matrix<double> > &P = data.P;
	matrix<double> &pi = data.pi;
	matrix<double> &numerator = data.numerator;
	std::vector<double> &denominator = data.denominator;
	model &m = data.m;
	std::vector<matrix<int> > &X = data.X;


	//Finding the matrix of response patterns Y
	//And its frequency
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

	// Number of examinees
	N = dataset.rows();

	// Number of response patterns
	s = Y.rows();

	// Finding the number of items
	// As the matrix data is s x p
	// we can find out the number of items just seeing the size
	// of any response pattern
	p = Y.columns(0);


	//Finding the number of categories of each item and seeing if it's dichotomous
	dichotomous = false;
	for ( int j = 0; j < p; ++j ) {
		int max_category = -1;
		for ( int i = 0; i < s; ++i ) {
			if ( Y(i, j) > max_category ) max_category = Y(i, j);
			dichotomous |= Y(i, j) == 0;
		}
		categories_item.push_back(max_category);
	}

	// If it's dichotomous, we add 1 to Y
	if ( dichotomous ) {
		for ( int i = 0; i < s; ++i )
			for ( int j = 0; j < p; ++j )
				++Y(i, j);
		for ( int i = 0; i < p; ++i )
			++categories_item[i];
	}


	/**
	 * After Y, here matrix X (dichotomized matrix) is computed
	 *
	 *
	 */
	X = std::vector<matrix<int> >(s);
	for ( int l = 0; l < s; ++l ) {
		for ( int i = 0; i < p; ++i ) {
			std::vector<int> row(categories_item[i]);
			row[Y(l, i) - 1] = 1;
			X[l].add_row(row);
		}
	}

	const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40;
	G = MAX_NUMBER_OF_QUADRATURE_POINTS / (std::min(1 << (d - 1), 8));

	// Latent trait vectors are loaded
	theta = load_quadrature_points(G);

	// Weights are loaded
	w = load_weights(G);

	G = theta.rows();

	//Setting size of matrix r and P
	r = std::vector<matrix<double> >(G);
	P = std::vector<matrix<double> >(G);
	for ( int g = 0; g < G; ++g ) {
		r[g] = matrix<double>();
		P[g] = matrix<double>();
		for ( int i = 0; i < p; ++i ) {
			r[g].add_row(categories_item[i]);
			P[g].add_row(categories_item[i]);
		}
	}

	//Matrixes needed in Estep
	pi = matrix<double>(G, s);
	numerator = matrix<double>(G, s);
	denominator = std::vector<double>(s);

	//Configurations for the estimation
	m = model(themodel);
	this->convergence_difference = convergence_difference;
	this->iterations = 0;
}

estimation::estimation(int themodel, matrix<char> &dataset, short d,
					   double convergence_difference, std::vector<int> &number_of_items) {

	estimation(themodel, dataset, d, convergence_difference);

	/**
	 * Computing the items that will be pinned
	 *
	 * */
	std::set<int> &pinned_items = data.pinned_items;

	int before = 0;
	pinned_items.insert(0);
	for ( unsigned int i = 0; i < number_of_items.size() - 1; ++i ) {
		before += number_of_items[i];
		pinned_items.insert(before);
	}

	this->convergence_difference = convergence_difference;
	this->iterations = 0;
}

estimation::~estimation() {

}

void estimation::initial_values() {
	std::vector<item_parameter> &zeta = data.zeta;
	int &d = data.d;
	int &N = data.N;
	int &p = data.p;
	bool &dichotomous = data.dichotomous;
	int &G = data.G;
	std::vector<int> &categories_item = data.categories_item;
	model &m = data.m;
	matrix<char> &dataset = *data.dataset;
	std::set<int> &pinned_items = data.pinned_items;


	for ( int i = 0; i < p; ++i )
		zeta.push_back( item_parameter(m, d, categories_item[i]) );

	if ( d == 1 ) {
		if ( dichotomous ) {
			std::vector<double> alpha, gamma;
			find_initial_values(dataset, alpha, gamma);

			for ( int i = 0; i < p; ++i ) {
				item_parameter &item_i = zeta[i];

				//As there is only one alpha, item_i.alpha[0] is okay
				item_i.alpha[0] = alpha[i];
				//As there is only one gamma, item_i.gamma[0] is okay
				item_i.gamma[0] = gamma[i];

				//std::cout << i + 1 << ' ' << alpha[i] << ' ' << gamma[i] << std::endl;
			}
		}
		else {
			/**
			 * Polytomous case
			 *
			 * Here, it is necessary find dichotomous items for each polytomous item
			 * */

			for ( int i = 0; i < p; ++i ) {
				item_parameter &item_i = zeta[i];
				int mi = categories_item[i];

				matrix<char> data_dicho(N, mi - 1);
				for ( int k = 1; k < mi; ++k ) {
					for ( int j = 0; j < N; ++j )
						data_dicho(j, k - 1) = dataset(j, i) >= k + 1;
				}

				//std::cout << data << std::endl;
				//std::cout << data_dicho << std::endl;

				std::vector<double> alpha, gamma;
				find_initial_values(data_dicho, alpha, gamma);

				/**
				 * Real alpha for this item will be the average among all alphas computed
				 * */

				double a = mean(alpha);

				//As there is only one alpha, item_i.alpha[0] is okay
				item_i.alpha[0] = a;
				//As there is more than one gamma, it is necessary iterate over the number of categories
				for ( int k = 0; k < mi - 1; ++k )
					item_i.gamma[k] = gamma[k];

//				std::cout << i + 1 << ' ' << a;
//				for ( int k = 0; k < mi - 1; ++k )
//					std::cout << ' ' << gamma[k];
//				std::cout << std::endl;
			}
		}
	}

	else {

		/**
		 * If it is multidimensional
		 *
		 * here, the first item for each dimension is pinned
		 * */

		if ( dichotomous ) {
			std::vector<double> alpha, gamma;
			find_initial_values(dataset, alpha, gamma);

			for ( int i = 0; i < p; ++i ) {
				item_parameter &item_i = zeta[i];

				//As there is only one gamma, item_i.gamma[0] is okay
				item_i.gamma[0] = gamma[i];

				//std::cout << i + 1 << ' ' << gamma[i] << std::endl;
			}
		}
		else {
			/**
			 * Polytomous case
			 *
			 * Here, it is necessary find dichotomous items for each polytomous item
			 * */

			for ( int i = 0; i < p; ++i ) {
				item_parameter &item_i = zeta[i];
				int mi = categories_item[i];

				matrix<char> data_dicho(N, mi - 1);
				for ( int k = 1; k < mi; ++k ) {
					for ( int j = 0; j < N; ++j )
						data_dicho(j, k - 1) = dataset(j, i) >= k + 1;
				}

				//std::cout << data << std::endl;
				//std::cout << data_dicho << std::endl;

				std::vector<double> alpha, gamma;
				find_initial_values(data_dicho, alpha, gamma);

				//As there is more than one gamma, it is necessary iterate over the number of categories
				for ( int k = 0; k < mi - 1; ++k )
					item_i.gamma[k] = gamma[k];

//				for ( int k = 0; k < mi - 1; ++k )
//					std::cout << ' ' << gamma[k];
//				std::cout << std::endl;
			}
		}

		/**
		 * It is supposed that there are p / d items for each dimension
		 * if the user does not specify them
		 *
		 *
		 * */

		if ( pinned_items.empty() ) {
			int items_for_dimension = p / d;
			for ( int i = 0, j = 0; i < p; i += items_for_dimension, ++j ) {
				item_parameter &item = zeta[i];
				pinned_items.insert(i);
				item.alpha = std::vector<double>(item.alphas);
				item.gamma = std::vector<double>(item.gammas);
				item.alpha[j] = 1;
				if ( item.gammas > 2 ) item.gamma[(item.gammas + 1) / 2] = 1;
			}
		}

		/**
		 * If user specify the number of items for each dimension, then
		 * the first item of each dimension will be pinned
		 * */

		else {
			std::set<int>::iterator it;
			int j = 0;
			for ( it = pinned_items.begin(); it != pinned_items.end(); ++it, ++j ) {
				item_parameter &item = zeta[*it];
				item.alpha = std::vector<double>(item.alphas);
				item.alpha[j] = 1;
				item.gamma[(item.gammas) / 2] = 0;
			}
		}
	}
}


void estimation::EMAlgortihm() {
	initial_values();
	double dif;
	do {
		Estep(data);
		dif = Mstep(data);
		++iterations;
	} while ( dif > convergence_difference && iterations < MAX_ITERATIONS );
}

void estimation::print_results ( ) {
	std::vector<item_parameter> &zeta = data.zeta;
	int &d = data.d;
	int &p = data.p;

	std::cout << "Finished after " << iterations << " iterations.\n";
	for ( int i = 0; i < p; ++i ) {
		std::cout << "Item " << i + 1 << '\n';
		for ( int j = 0; j < d; ++j )
			std::cout << 'a' << j + 1 << ": " << ( zeta[i].alphas ? zeta[i].alpha[j] : 1 ) << ' ';
		for ( int j = 0; j < zeta[i].gammas; ++j )
			std::cout << 'd' << j + 1 << ": " << zeta[i].gamma[j] << ' ';
		if ( zeta[i].guessing )
			std::cout << "c: " << std::max( zeta[i].c, 0.0 );
		std::cout << '\n';
	}
}

void estimation::print_results ( std::ofstream &fout, double elapsed ) {
	std::vector<item_parameter> &zeta = data.zeta;
	int &d = data.d;
	int &p = data.p;
	model &m = data.m;

	for ( int i = 0; i < p; ++i ) {
		for ( int j = 0; j < d; ++j ) {
			if ( j ) fout << ';';
			fout << ( m.parameters != 1 ? zeta[i].alpha[j] : 1 );
		}
		for ( int j = 0; j < zeta[i].gammas; ++j ) {
			fout << ';' << zeta[i].gamma[j];
		}
		if ( zeta[i].guessing )
			fout << ';' << std::max( zeta[i].c, 0.0 );
		fout << ';' << elapsed << '\n';
	}
}

} /* namespace irtpp */
