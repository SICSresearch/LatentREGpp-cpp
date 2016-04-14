#include <iostream>
#include "util/matrix.h"

using namespace mirt;
using std::cout;


/**
 * MIRTpp main
 * Main function used to test classes and implemented
 * algorithm.
 */
int main() {
	//temporary tests
	matrix<int> m1(4, 5);
	m1.print();

	std::vector<int> v;
	v.push_back(3);
	v.push_back(2);
	v.push_back(3);
	matrix<int> m2;
	m2.add_row(v);
	m2.add_row(v);
	m2.print();

	int *t = new int[2];
	t[0] = 5;
	t[1] = 3;
	matrix<int> m3;
	m3.add_row(t, 2);
	m3.add_row(t, 2);
	m3.add_element(6);
	m3.print();
	delete t;
}
