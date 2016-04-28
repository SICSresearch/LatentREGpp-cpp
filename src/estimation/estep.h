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

namespace mirt {


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
 * Number of response patterns
 * */
extern int s;

/**
 * Number of examinees
 * */
extern int N;

/**
 * Vector of parameters
 * */
extern std::vector<item_parameter> zeta;

/**
 * Y , s x p, matrix of pattern responses.
 *
 * where s is the number of patterns s <= N (N, number of examinees)
 * p is the number of items
 * */
extern matrix<char> Y;

/**
 * Dichotomized matrix
 * */
extern std::vector<matrix<int> > X;

/**
 * nl, frequencies of each pattern allocated in Y
 * */
extern std::vector<int> nl;

// Latent trait vectors
extern matrix<double> theta;

// Weights
extern std::vector<double> w;

extern const int MAX_NUMBER_OF_QUADRATURE_POINTS;
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

/**
 * Estep of the EMAlgortihm
 *
 * */
void Estep();

} /* namespace mirt */

#endif /* ESTIMATION_ESTEP_H_ */
