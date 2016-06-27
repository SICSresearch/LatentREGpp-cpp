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
#include "../model/model.h"
#include "../../util/matrix.h"

#include <dlib/optimization.h>

namespace irtpp {

namespace multidichotomous {

typedef dlib::matrix<double,0,1> item_parameter;

class estimation_data {
public:
	matrix<char> *dataset;
	int d;
	matrix<char> Y;
	std::vector<int> nl;
	int N;
	int s;
	int p;
	int G;
	matrix<double> theta;
	std::vector<double> w;
	matrix<double> r;
	matrix<double> P;
	matrix<double> pi;
	std::vector<double> f;
	std::set<int> pinned_items;
	std::vector<item_parameter> zeta;
	model m;

	estimation_data(int);
	estimation_data();
	virtual ~estimation_data();
};

}

} /* namespace irtpp */

#endif /* UTIL_ESTIMATIONDATA_H_ */
