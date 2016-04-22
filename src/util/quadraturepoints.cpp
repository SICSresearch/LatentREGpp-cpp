/*
 * quadraturepoints.cpp
 *
 *  Created on: 22/04/2016
 *      Author: Milder
 */

#include "quadraturepoints.h"
#include "input.h"
#include "matrix.h"

namespace mirt {

	void compute_latent_trait ( std::vector<double> &q, int r,
								std::vector<double> &current_trait,
								std::vector<bool> &used,
				  	  	  	    matrix<double> &latent_trait ) {
		if ( r == 0 ) {
			latent_trait.add_row(current_trait);
			return;
		}
		for ( size_t i = 0; i < q.size(); ++i ) {
				current_trait.push_back(q[i]);
				compute_latent_trait(q, r - 1, current_trait, used, latent_trait);
				current_trait.pop_back();
		}
	}

	void compute_and_save_quadrature_points(std::string filename, int d) {
		matrix<double> temp;
		input<double> in(' ');
		//Quadrature points loaded from file
		in.importData(filename, temp);
		//Saving them as a vector
		std::vector<double> q;
		for ( int i = 0; i < temp.rows(); ++i )
			for ( int j = 0; j < temp.columns(i); ++j )
				q.push_back(temp(i, j));
		/**
		 * Here the latent trait vectors are computed
		 * using a backtracking approach
		 * */

		//latent trait vectors
		matrix<double> latent_trait;
		//current latent trait vector, it starts void
		std::vector<double> current_trait;
		//vector of used
		std::vector<bool> used(q.size());

		//computing latent trait vector for the given dimension
		compute_latent_trait(q, d, current_trait, used, latent_trait);

		std::cout << "Latent trait vectors. Total[" << latent_trait.rows() << "]\n";
		for ( int i = 0; i < latent_trait.rows(); ++i ) {
			std::cout << '[';
			for ( int j = 0; j < latent_trait.columns(i); ++j ) {
				if (j) std::cout << ", ";
				std::cout << latent_trait(i, j);
			}
			std::cout << "]\n";
		}
	}

}


