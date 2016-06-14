/*
 * initial_values.cpp
 *
 *  Created on: 13/06/2016
 *      Author: Milder
 */

#include "initial_values.h"
#include <cmath>
#include <boost/math/distributions/normal.hpp>

namespace irtpp {

	template <class T>
	inline double mean ( std::vector<T> &v ) {
		double sum = 0;
		for ( int i = 0; i < v.size(); ++i )
			sum += v[i];
		return sum / double(v.size());
	}

	template <class T>
	inline double sd ( std::vector<T> &v ) {
		double m = mean(v), sum = 0;
		for ( int i = 0; i < v.size(); ++i )
			sum += (m - v[i]) * (m - v[i]);
		return std::sqrt(sum/v.size());
	}

	void compute_biserial_correlation(matrix<char> &Y, std::vector<double> &ro) {
		int n = Y.rows(),
			p = Y.columns(0);

		std::vector<double> scores(n);
		for ( int i = 0; i < n; ++i )
			for ( int j = 0; j < p; ++j )
				if ( Y(i, j) == 1 )
					++scores[i];

		//vector of biserial correlation
		ro = std::vector<double>(p);
		//Standard deviation of scores vector
		double sn = sd(scores);

		double nn1 = n * (n - 1);
		for ( int i = 0; i < p; ++i ) {

			double n1 = 0, n0 = 0, m0 = 0, m1 = 0;
			for ( int j = 0; j < n; ++j )
				if ( Y(j, i) == 1 ) {
					++n1;
					m1 += scores[j];
				} else {
					++n0;
					m0 += scores[j];
				}

			m0 /= n0;
			m1 /= n1;
			ro[i] = ((m1 - m0)/ sn ) * std::sqrt( n1 * n0 / nn1 );
		}
	}

	void compute_alphas(std::vector<double> &p, std::vector<double> &a) {
		a = std::vector<double>(p.size());
		for ( int i = 0; i < p.size(); ++i ) {
			double p2 = p[i] * p[i];
			double temp = p[i] * std::sqrt(p2 + 4);
			a[i] = std::max(p2 + temp, p2 - temp) / 2.0;
		}
	}

	void compute_gammas(matrix<char> &Y, std::vector<double> &a, std::vector<double> &p, std::vector<double> &d) {
		std::vector<double> b(p.size());
		boost::math::normal dist(0.0, 1.0);

		for ( int i = 0; i < p.size(); ++i ) {
			int right_answers = 0;
			for ( int j = 0; j < Y.rows(); ++j )
				if ( Y(j, i) == 1 )
					++right_answers;

			double pi = double(right_answers) / double(Y.rows());
			double q = quantile(dist, pi);

			b[i] = -q / p[i];
		}

		d = std::vector<double>(b.size());
		for ( int i = 0; i < a.size(); ++i )
			d[i] = -a[i] * b[i];
	}

} // irtpp



