/*
 * squarem.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: Milder
 */

#include "squarem.h"

namespace irtpp {

double norm ( item_parameter &it ) {
	double sum = 0;
	for ( auto x : it )
		sum += x * x;
	return std::sqrt(sum);
}

void squarem ( std::vector<item_parameter> zeta[ZETA_STEP], std::set<int> &pinned ) {
	int p = zeta[0].size();
	double r, v, alpha;
	for ( int i = 0; i < p; ++i ) {
		if ( pinned.count(i) ) continue;
		for ( int j = 0; j < zeta[0][i].size(); ++j ) {
			r = zeta[1][i](j) - zeta[0][i](j);
			v = zeta[2][i](j) - zeta[1][i](j) - r;

			alpha = - std::abs(r) / std::abs(v);
			std::cout << "alpha: " << alpha << std::endl;
			alpha = std::min(alpha, -1.0);


			//std::cout << zeta[2][i](j) << ' ';

			zeta[2][i](j) = zeta[0][i](j) - alpha * (2 * r - alpha * v);

			//std::cout << zeta[2][i](j) << std::endl;
		}
	}
}

} /* namespace irtpp */
