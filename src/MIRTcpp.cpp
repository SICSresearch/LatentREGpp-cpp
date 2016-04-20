#include <iostream>
#include "util/matrix.h"
#include "util/input.h"
#include "model/twopl.h"
#include "estimation/estimation.h"
#include <fstream>

using namespace mirt;
using std::cout;

/**
 * MIRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */

int main() {
	matrix<char> Y;
	input<char> in(';');
	in.importCSV("test/dataset01.csv", Y);

	cout << Y << '\n';

	model model_chosen = twopl();
	estimation e(model_chosen, Y, 1, 10, 0.001);
}
