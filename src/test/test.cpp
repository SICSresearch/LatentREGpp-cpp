/*
 * pi_matrix_test.cpp
 *
 *  Created on: 25/04/2016
 *      Author: Milder
 */

#include "test.h"
#include <iostream>

namespace mirt {

	bool test_pi ( matrix<double> &pi ) {
		const double MIN = 0.999;

		bool correct = true;
		for ( int j = 0; j < pi.columns(0); ++j ) {
			double sum = 0;
			for ( int i = 0; i < pi.rows(); ++i )
				sum += pi(i, j);
			correct &= sum >= MIN;
		}

		return correct;
	}

	bool test_r ( std::vector<matrix<double> > &r, int N, int p ) {
		double sum = 0;
		for ( int i = 0; i < r.size(); ++i )
			for ( int j = 0; j < r[i].rows(); ++j )
				for ( int k = 0; k < r[i].columns(j); ++k )
					sum += r[i](j, k);
		//std::cout << N << ' ' << p << ' ' << sum << std::endl;

		const double eps = 1e-5;
		return N * p == int(sum + eps);
	}

}



