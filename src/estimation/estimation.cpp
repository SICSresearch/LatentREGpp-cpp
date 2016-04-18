/*
 * estimation.cpp
 *
 *  Created on: 13/04/2016
 *      Author: Milder
 */

#include "estimation.h"

namespace mirt {

estimation::estimation() {
	// TODO Auto-generated constructor stub

}

estimation::estimation(model &m, matrix<char> &data) {
	model_used = m;
	std::map<std::vector<char>, int> freq;
	for ( int i = 0; i < data.rows(); ++i )
		++freq[data.get_row(i)];

	std::map<std::vector<char>, int>::iterator it;
	for ( it = freq.begin(); it != freq.end(); ++it ) {
		Y.add_row(it->first);
		nl.push_back(it->second);
	}
}

estimation::~estimation() {
	// TODO Auto-generated destructor stub
}



} /* namespace mirt */
