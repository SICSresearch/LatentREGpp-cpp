/*
 * itemparameter.h
 *
 *  Created on: 20/04/2016
 *      Author: Milder
 */

#ifndef UTIL_ITEMPARAMETER_H_
#define UTIL_ITEMPARAMETER_H_

#include <vector>
//including optimization files from dlib library
#include <dlib/optimization.h>

namespace mirt {

// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

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

		/**
		 * Sum of all parameters of this item
		 * */
		short number_of_parameters;


	public:

		std::vector<double> alpha;
		std::vector<double> gamma;
		/**
		 * bool variable to known if the guessing parameter is being taken into account
		 * */
		bool guessing;
		/**
		 * Guesing parameter
		 * */
		double c;

		item_parameter();

		/**
		 * Receives dimension
		 * */
		item_parameter(short);

		/**
		 * Receives dimension and number of categories of the item
		 * */
		item_parameter(short, short, bool);

		static item_parameter build_item(const column_vector&, int, int);

		virtual ~item_parameter();

		std::vector<double> get_alpha();
		std::vector<double> get_gamma();

		short get_categories();
		short get_dimension();
		short get_number_of_parameters();
};

} /* namespace mirt */

#endif /* UTIL_ITEMPARAMETER_H_ */
