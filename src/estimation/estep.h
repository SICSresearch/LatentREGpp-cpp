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
 * Probability matrix P
 *
 * P_gik
 *
 * P_gik means the probability that an individual has selected the category k
 * to item i and belongs to group g
 *
 *
 * The purpose of this matrix is to allocate the value of P_gik
 * to avoid recompute them while numerators and denominators are computed
 * */
extern std::vector<matrix<double> > P;

/**
 * Probability matrix pi
 *
 * pi(g, l) with g = 1, ..., G; l = 1, ..., s
 * 		i.e, the size of pi is
 * 			 Number of Quadrature points X Number of response patterns
 *
 * pi(g, l) is the probability that a response pattern belongs to
 * 			group g
 * */
extern matrix<double> pi;

/**
 * Matrix of numerators and vector of denominators
 * used to avoid recompute values while pi is built
 * */
extern matrix<double> numerator;
extern std::vector<double> denominator;


/**
 * Estep of the EMAlgortihm
 *
 * */
void Estep();

} /* namespace mirt */

#endif /* ESTIMATION_ESTEP_H_ */
