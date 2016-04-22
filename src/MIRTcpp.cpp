#include <iostream>
#include "util/matrix.h"
#include "util/input.h"
#include "model/twopl.h"
#include "estimation/estimation.h"
#include "util/quadraturepoints.h"
#include <fstream>

using namespace mirt;
using std::cout;

/**
 * MIRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */

int main() {
	compute_and_save_quadrature_points("data/quadrature10_in.data", 2);

	matrix<char> Y;
	input<char> in(';');
	in.importData("test/dataset01.csv", Y);

	cout << Y << '\n';

	model model_chosen = twopl();
	estimation e(model_chosen, Y, 1, 10, 0.001);
}
