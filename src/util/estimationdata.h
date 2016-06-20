/*
 * estimationdata.h
 *
 *  Created on: 20/06/2016
 *      Author: Milder
 */

#ifndef UTIL_ESTIMATIONDATA_H_
#define UTIL_ESTIMATIONDATA_H_
#include <vector>
#include <set>
#include "matrix.h"
#include "itemparameter.h"

namespace irtpp {

class estimation_data {
public:
	matrix<char> *dataset;
	int d;
	matrix<char> Y;
	std::vector<int> nl;
	int N;
	int s;
	int p;
	bool dichotomous;
	int G;
	std::vector<int> categories_item;
	matrix<double> theta;
	std::vector<double> w;
	std::vector<matrix<double> > r;
	std::vector<matrix<double> > P;
	matrix<double> pi;
	matrix<double> numerator;
	std::vector<double> denominator;
	std::vector<matrix<int> > X;
	std::set<int> pinned_items;
	std::vector<item_parameter> zeta;
	model m;

	estimation_data(int);
	estimation_data();
	virtual ~estimation_data();
};

} /* namespace irtpp */

#endif /* UTIL_ESTIMATIONDATA_H_ */
