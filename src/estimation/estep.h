/*
 * estep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_ESTEP_H_
#define ESTIMATION_ESTEP_H_

#include <iostream>
#include "../model/model.h"
#include "../util/matrix.h"
#include "../util/quadraturepoints.h"

namespace mirt {

/**
 * Estep of the EMAlgortihm
 *
 * */
class Estep {
private:

	/**
	 * Pointer to the model used
	 * */
	model* m_pointer;

	/**
	 * Pointer to zeta, vector of item parameters
	 * */
	std::vector<item_parameter>* zeta_pointer;

	/**
	 * Pointer to the matrix Y, response patters matrix
	 * */
	matrix<char>* Y_pointer;

	/**
	 * Pointer to dichotomized matrix X
	 * */
	std::vector<matrix<int> >* X_pointer;

	/**
	 * Pointer to the frequency of each response pattern
	 * */
	std::vector<int>* nl_pointer;

	/**
	 * Number of nodes [quadrature points]
	 * */
	int G;

	/**
	 * Number of examinees
	 * */
	int N;

	/**
	 * Pointer to the r matrix
	 *
	 * Which means:
	 * Expected number of examinees for each group g
	 * who answered category k to item i
	 * */
	std::vector<matrix<double> >* r_pointer;

	/**
	 * Pointer to Latent trait vectors
	 * */
	matrix<double>* theta_pointer;

	/**
	 * Pointer to weights of latent trait
	 * */
	std::vector<double>* w_pointer;

public:

    Estep(model*, std::vector<item_parameter>*, matrix<char>*,
		   std::vector<matrix<int> >*, std::vector<int>*, int, int,
		   std::vector<matrix<double> >*, matrix<double>*, std::vector<double>*);

    /**
     * Executes the Estep
     * */
	void run();
};
} /* namespace mirt */

#endif /* ESTIMATION_ESTEP_H_ */
