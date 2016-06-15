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
#include "../model/model.h"
#include "initial_values.h"
#include "matrix.h"

namespace irtpp {

// Necessary typedef to be able to maximize using dlib
typedef dlib::matrix<double,0,1> column_vector;

//Necesary for using cesandoval BFGS
typedef std::vector<double> Parameter;
typedef void* Info;
typedef std::vector<double> (*Function)(Parameter params, Info info);

class model;

class item_parameter {
	private:
		/**
		 * Sum of all parameters of this item
		 * */
		short number_of_parameters;


	public:

		std::vector<double> alpha;
		std::vector<double> gamma;

		/**
		 * Number of alphas
		 * */
		short alphas;
		/**
		 * Number of categories of this item
		 * */
		short gammas;

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


		static void build_item(const column_vector&, int, int, item_parameter&);

		/**
		 * Receives dimension and number of categories of the item
		 * */
		item_parameter(model&, short, short);
		item_parameter(matrix<char> &Y, model&, short, short);

		virtual ~item_parameter();

		std::vector<double> get_alpha();
		std::vector<double> get_gamma();

		void add_single_alpha(double a);
		void add_single_gamma(double d);

		short get_categories();
		short get_dimension();
		short get_number_of_parameters();
};

} /* namespace irtpp */

#endif /* UTIL_ITEMPARAMETER_H_ */
