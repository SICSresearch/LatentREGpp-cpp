/*
 * estimation.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTIMATION_H_
#define ESTIMATION_ESTIMATION_H_

#include "../model/model.h"
#include "../util/matrix.h"
#include "../util/itemparameter.h"
#include <map>
#include <cmath>

namespace mirt {


/*
 * Class to run the estimation process
 *
 * The main method is EMAlgorithm
 * */
class estimation {
	private:
		model model_used;
		short iterations;
		/**
		 * Dimension of the data
		 * */
		short d;

		/**
		 * Number of items
		 * */
		int p;

		/**
		 * Number of nodes
		 * Number of Quadrature points
		 * */
		int G;

		/**
		 * Number of response patterns
		 * */
		int s;
		double convergence_difference;
		std::vector<item_parameter> zeta;
		/**
		 * Y , s x p, matrix of pattern responses.
		 *
		 * where s is the number of patterns s <= N (N, number of examinees)
		 * p is the number of items
		 * */
		matrix<char> Y;

		/**
		 * nl, frequencies of each pattern allocated in Y
		 * */
		std::vector<int> nl;

		/**
		 * vector to allocate the number of categories of each item
		 * */
		std::vector<int> categories_item;

		/**
		 * Probability matrix
		 *
		 * pi(g, l) with g = 1, ..., G; l = 1, ..., s
		 * 		i.e, the size of pi is
		 * 			 Number of Quadrature points X Number of response patterns
		 *
		 * pi(g, l) is the probability that a response pattern belongs to
		 * 			group g
		 * */
		matrix<double> pi;

	public:
		estimation();

		/**
		 * This constructor receives a specific model to use
		 * and a matrix containing the answers of examinees
		 *
		 * Optional parameters are number of iterations
		 * and convergence difference (between an iteration and before)
		 *
		 * If convergence difference is not defined its default value is 0.0001
		 * If number of iterations is not defined its default value is -1
		 * 		which means that the EMalgorithm does not take into account
		 * 		iterations, it finishes when the convergence difference is reached
		 *
		 *
		 *
		 * Then it builds the matrix of pattern responses and its frequency
		 * */
		estimation(model&, matrix<char>&, short, short, double);
		virtual ~estimation();

		void initial_values();
		/*
		 * Runs the EMAlgorithm to find out the parameters
		 * depending on what is the model used
		 * */
		void EMAlgortihm();
};

} /* namespace mirt */

#endif /* ESTIMATION_ESTIMATION_H_ */
