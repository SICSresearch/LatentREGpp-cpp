#include <iostream>
#include "util/matrix.h"
#include "util/input.h"
#include <fstream>

using namespace mirt;
using std::cout;

/**
 * MIRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */
int main() {

	/*
	 * Example of how to read a matrix from a csv
	 * saving the values as int
	 *
	 * matrix and input have to have the same type
	 * */
	matrix<short> Y;
	input<short> in(';');
	in.importCSV("test/dataset01.csv", Y);
	cout << Y << '\n';
}
