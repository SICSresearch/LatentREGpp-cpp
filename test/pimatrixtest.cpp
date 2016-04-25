/*
 * pi_matrix_test.cpp
 *
 *  Created on: 25/04/2016
 *      Author: Milder
 */

#include "pimatrixtest.h"

namespace mirt {

	bool test_pi ( matrix<double> &pi ) {
		const double MIN = 0.9999;

		bool correct = true;
		for ( int i = 0; i < pi.rows(); ++i ) {
			double sum = 0;
			for ( int j = 0; j < pi.columns(i); ++j )
				sum += pi(i, j);
			correct &= sum >= MIN;
		}

		return correct;
	}

}



