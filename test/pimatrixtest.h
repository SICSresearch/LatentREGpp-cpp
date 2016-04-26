/*
 * pimatrixtest.h
 *
 *  Created on: 25/04/2016
 *      Author: Milder
 */

#ifndef TEST_PIMATRIXTEST_H_
#define TEST_PIMATRIXTEST_H_

#include "../src/util/matrix.h"

namespace mirt {

	/**
	 * Tests the sum if each columns of pi matrix is equals to 1
	 * */
	bool test_pi ( matrix<double> &pi );
}



#endif /* TEST_PIMATRIXTEST_H_ */
