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
#include "../util/itemparameter.h"
#include <cmath>
#include <cstdlib>

//including optimization files from alglib library
#include <alglib/stdafx.h>
#include <alglib/optimization.h>

namespace irtpp {

extern double C;


extern model m;
/**
 * Dimension of the data
 * */
extern short d;
/**
 * Number of items
 * */
extern int p;

/**
 * Vector of parameters
 * */
extern std::vector<item_parameter> zeta;

// Latent trait vectors
extern matrix<double> theta;

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
extern int G;

/**
 * Matrix r
 *
 * Expected number of examinees in group g
 * that answered category k to item i
 * */
extern std::vector<matrix<double> > r;
//Varaiable to know the current item
extern int i;

/**
 * For multidimensional case
 *
 * set that contains what are the items that have to be pinned
 * */
extern std::set<int> pinned_items;


// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

/**
 * M step of the EM Algorithm
 */
double Mstep();
double Mstep2();

	/**
	 * Function to be maximized
	 * */

} /* namespace irtpp */

#endif /* ESTIMATION_MSTEP_H_ */
