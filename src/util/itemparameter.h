/*
 * itemparameter.h
 *
 *  Created on: 20/04/2016
 *      Author: Milder
 */

#ifndef UTIL_ITEMPARAMETER_H_
#define UTIL_ITEMPARAMETER_H_

#include <vector>

namespace mirt {

class item_parameter {
	private:
		/**
		 * Dimension
		 * */
		short d;
		/**
		 * Number of categories of this item
		 * */
		short categories;

		std::vector<double> alpha;
		std::vector<double> gamma;
	public:
		item_parameter();

		/**
		 * Receives dimension and number of categories of the item
		 * */
		item_parameter(short, short);
		virtual ~item_parameter();

		std::vector<double> get_alpha();
		std::vector<double> get_gamma();
};

} /* namespace mirt */

#endif /* UTIL_ITEMPARAMETER_H_ */
