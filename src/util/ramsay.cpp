/*
 * squarem.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: Milder
 */

#include "squarem.h"

namespace irtpp {

void ramsay(std::vector<item_parameter> zeta[ZETA_STEP],
		std::set<int> &pinned) {

	double dx2, dx, d2x2, num = 0, den = 0, accel = 0;
	int p = zeta[0].size();

	for ( int i = 0; i < p; ++i ) {
		if ( pinned.count(i) ) continue;
		for ( int j = 0; j < zeta[0][i].size(); ++j ) {
			dx = zeta[2][i](j) - zeta[1][i](j);
			dx2 = zeta[1][i](j) - zeta[0][i](j);
			d2x2 = dx - dx2;

			num += dx * dx;
			den += d2x2 * d2x2;
		}
	}

	accel = std::max(1 - sqrt(num / den), MINIMUM_ACCEL);

	for ( int i = 0; i < p; ++i ) {
		if ( pinned.count(i) ) continue;
		for ( int j = 0; j < zeta[0][i].size(); ++j ) {
//			std::cout << zeta[2][i](j) << ' ';
			zeta[2][i](j) = (1 - accel) * zeta[2][i](j) + accel * zeta[1][i](j);
//			std::cout << zeta[2][i](j) << std::endl;
		}
	}
}

} /* namespace irtpp */
