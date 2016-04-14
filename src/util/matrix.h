/*
 * matrix.h
 *
 *  Created on: 14/04/2016
 *      Author: Milder
 */

#ifndef UTIL_MATRIX_H_
#define UTIL_MATRIX_H_

#include <vector>
#include <iostream>

namespace mirt {

/*
 * Class matrix
 * */

template<class T>
class matrix {
	private:
		std::vector<std::vector<T> > data;

	public:
		matrix();
		/**
		 * Creates a new matrix with size rows * cols
		 * */
		matrix(int rows, int cols);

		/**
		 * Creates a new matrix specifying only the number of rows
		 * rows can be added after using add_row(std::vector) method
		 * */
		matrix(int cols);

		/**
		 * Adds a new row to the current matrix
		 * */
		void add_row(std::vector<T> &new_row);
		void add_row(T* new_row, int size);
		/**
		 * Adds an empty row
		 * */
		void add_row();

		/**
		 * Adds an element to the last row
		 * */
		void add_element(T e);

		// Temporary method to prints the matrix
		/**
		 * Prints the matrix
		 * */
		void print();
		virtual ~matrix();
};




template<class T>
matrix<T>::matrix(int rows) {
	data = std::vector<std::vector<T> >(rows);
}

template<class T>
matrix<T>::matrix() {}

template<class T>
matrix<T>::~matrix() {}

template<class T>
matrix<T>::matrix(int rows, int cols) {
	data = std::vector<std::vector<T> >(rows, std::vector<T>(cols));
}

template<class T>
void matrix<T>::add_row(std::vector<T> &new_row) {
	data.push_back(new_row);
}

template<class T>
void matrix<T>::add_row(T* new_row, int size) {
	data.push_back(std::vector<T>(new_row, new_row + size));
}

template<class T>
void matrix<T>::add_row() {
	data.push_back(std::vector<T>());
}

template<class T>
void matrix<T>::add_element(T e) {
	data.back().push_back(e);
}

template<class T>
void matrix<T>::print() {
	for ( int i = 0; i < data.size(); ++i ) {
		for ( int j = 0; j < data[i].size(); ++j )
			std::cout << data[i][j] << ' ';
		std::cout << '\n';
	}
}

} /* namespace mirt */

#endif /* UTIL_MATRIX_H_ */
