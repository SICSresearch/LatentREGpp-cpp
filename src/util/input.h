/*
 * input.h
 *
 *  Created on: 14/04/2016
 *      Author: Milder
 */

#ifndef UTIL_INPUT_H_
#define UTIL_INPUT_H_

#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "matrix.h"

namespace mirt {

template<class T>
class input {
	private:
		/**
		 * Delimiter to split each file line
		 */
		char delimiter;

	public:

		input();
		input(char);
		virtual ~input();

		/**
		 * Imports matrices from a csv
		 * */
		bool importCSV(std::string filename, matrix<T>& m);

		/**
		 * Gets the delimiter used for inputting
		 * */
		char get_delimiter() const;

		/**
		 * Sets the delimiter for inputting text matrices
		 * */
		void set_delimiter(char);
};

template<class T>
input<T>::input() {
	delimiter = ',';
}

template<class T>
input<T>::input(char delimiter) {
	this->delimiter = delimiter;
}

template<class T>
input<T>::~input() {
}

template<class T>
bool input<T>::importCSV(std::string filename, matrix<T>& m) {
	std::string line;
	std::ifstream file(filename.c_str());
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::vector<T> splitted;
			std::string::const_iterator start = line.begin();
			std::string::const_iterator end = line.end();
			std::string::const_iterator next = std::find(start, end, delimiter);
			while (next != end) {
				splitted.push_back(atoi(std::string(start, next).c_str()));
				start = next + 1;
				next = std::find(start, end, delimiter);
			}
			splitted.push_back(atoi(std::string(start, next).c_str()));
			m.add_row(&splitted);
		}
		file.close();
		return true;
	}
	return false;
}

template<class T>
char input<T>::get_delimiter() const {
	return delimiter;
}

template<class T>
void input<T>::set_delimiter(char del) {
	this->delimiter = delimiter;
}

} /* namespace mirt */

#endif /* UTIL_INPUT_H_ */
