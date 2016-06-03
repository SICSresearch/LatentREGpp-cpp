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

/**
 * Model to be used
 * */
model m;
/**
 * Dimension of the data
 * */
short d;
/**
 * Number of items
 * */
int p;
/**
 * Number of response patterns
 * */
int s;

/**
 * Number of examinees
 * */
int N;

/**
 * Vector of parameters
 * */
std::vector<item_parameter> zeta;

/**
 * Y , s x p, matrix of pattern responses.
 *
 * where s is the number of patterns s <= N (N, number of examinees)
 * p is the number of items
 * */
matrix<char> Y;

/**
 * Dichotomized matrix
 * */
std::vector<matrix<int> > X;

/**
 * nl, frequencies of each pattern allocated in Y
 * */
std::vector<int> nl;

// Latent trait vectors
matrix<double> theta;

// Weights
std::vector<double> w;

//Matrix r
std::vector<matrix<double> > r;

const int MAX_NUMBER_OF_QUADRATURE_POINTS = 40;
/**
 * Defining the number of quadrature points
 *
 * As max number of quadrature points is 40
 *
 * G will be in 1dimension = 40
 * 				2dimension = 20
 * 				3dimension = 10
 * 				> 4dimension = 5
 * */
int G;

/**
 * Probability matrix P
 *
 * P_gik
 *
 * P_gik means the probability that an individual has selected the category k
 * to item i and belongs to group g
 *
 *
 * The purpose of this matrix is to allocate the value of P_gik
 * to avoid recompute them while numerators and denominators in Estep are computed
 * */
std::vector<matrix<double> > P;

/**
 * Variable to know if data is dichotomous
 *
 * */
bool dichotomous;

/**
 * For multidimensional case
 *
 * set that contains what are the items that have to be pinned
 * */
std::set<int> pinned_items;

/**
 * Matrix of probabilities pi, denominators vector and matrix of numerators
 * needed in Estep
 * */
matrix<double> numerator;
std::vector<double> denominator;
matrix<double> pi;


estimation::estimation(int themodel, matrix<char> &data, short d,
					   double convergence_difference) {
	// Setting the dimension
	irtpp::d = d;

	//Finding the matrix of response patterns Y
	//And its frequency
	std::map<std::vector<char>, int> freq;
	for ( int i = 0; i < data.rows(); ++i )
		++freq[data.get_row(i)];

	Y = matrix<char>();
	nl = std::vector<int>();

	std::map<std::vector<char>, int>::iterator it;
	for ( it = freq.begin(); it != freq.end(); ++it ) {
		Y.add_row(it->first);
		nl.push_back(it->second);
	}

	// Number of examinees
	N = data.rows();

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

	// If it's dichotomous, we add 1 to data
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
	irtpp::m = model(themodel);
	this->convergence_difference = convergence_difference;
	this->iterations = 0;

	initial_values();
}

estimation::estimation(int themodel, matrix<char> &data, short d,
					   double convergence_difference, std::vector<int> &number_of_items) {
	/**
	 * Computing the items that will be pinned
	 *
	 * */

	int before = 0;
	pinned_items.insert(0);
	for ( unsigned int i = 0; i < number_of_items.size() - 1; ++i ) {
		before += number_of_items[i];
		pinned_items.insert(before);
	}

	estimation(themodel, data, d, convergence_difference);

	this->convergence_difference = convergence_difference;
	this->iterations = 0;
}

estimation::~estimation() {

}

void estimation::initial_values() {
	zeta = std::vector<item_parameter>();

	for ( int i = 0; i < p; ++i )
		zeta.push_back( item_parameter(m, d, categories_item[i]) );

	/**
	 * If it is multidimensional
	 *
	 * here, the first item for each dimension is pinned
	 * */
	if ( d > 1 ) {
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
	double dif;
	do {
		Estep();
		dif = Mstep2();
		++iterations;
		std::cout << iterations << ' ' << dif << std::endl;
	} while ( dif > convergence_difference );
}

void estimation::print_results ( ) {
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
