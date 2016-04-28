/*
 * mstep.h
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#ifndef ESTIMATION_MSTEP_H_
#define ESTIMATION_MSTEP_H_

#include <iostream>
#include <vector>
#include "../util/matrix.h"
#include "../model/model.h"

//including optimization files from dlib library
#include <dlib/optimization.h>

namespace mirt {

// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

/**
 * M step of the EM Algorithm
 */
class Mstep {
public:
	/**
	 * Pointer to the model used
	 * */
	model* m_pointer;

	/**
	 * Pointer to zeta, vector of item parameters
	 * */
	std::vector<item_parameter>* zeta_pointer;


	/**
	 * Pointer to the r matrix
	 *
	 * Which means:
	 * Expected number of examinees for each group g
	 * who answered category k to item i
	 * */
	std::vector<matrix<double> >* r_pointer;

	Mstep(model*, std::vector<item_parameter>*, std::vector<matrix<double> >*);

	/**
	 * Function to be maximized
	 * */
	double Qi(const column_vector&);

	/**
	 * Executes the Mstep
	 * */
	double run();
};
} /* namespace mirt */

#endif /* ESTIMATION_MSTEP_H_ */
