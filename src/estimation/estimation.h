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
#include <map>

namespace mirt {


/*
 * Class to run the estimation process
 *
 * The main method is EMAlgorithm
 * */
class estimation {
	private:
		model model_used;
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

	public:
		estimation();

		/**
		 * This constructor receives a specific model to use
		 * and a matrix containing the answers of examinees
		 * then builds the matrix of pattern responses and its frecuency
		 * */
		estimation(model&, matrix<char>&);
		virtual ~estimation();

		/*
		 * Runs the EMAlgorithm to find out the parameters
		 * depending on what is the model used
		 * */
		void EMAlgortihm();
};

} /* namespace mirt */

#endif /* ESTIMATION_ESTIMATION_H_ */
