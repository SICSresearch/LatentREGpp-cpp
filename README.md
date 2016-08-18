# IRTpp-multidimensional-cpp

### Item Response Theory software

IRT package for multidimensional polytomous models.

## Usage

Necessary to load a matrix object where dataset is allocated.
This operation is performed by an `input` object.
```cpp
matrix<char> Y;
input<char> in;
in.importData("datasets/admission_test.csv", Y);
```
`admission_test.csv` will look like:
```
1;0;1; ... ;0;1
0;1;0; ... ;1;1
.
.
.
1;1;1; ... ;0;0
```
In dichotomous case, or with positive integers in polytomous case.

### Item parameters estimation

Estimations are perfomed by `dichotomous::estimation` class for unidimensional or multidimensional dichotomous cases, and unidimensional or multidimensional polytomous cases by `polytomous::estimation`.

Simple estimation<br>
Just with dataset and dimension.
```cpp
dichotomous::estimation e(Y, 7);
e.EMAlgorithm();
e.print_item_parameters();
```
Or more customized configurations for the estimation.<br>
Dataset, dimension, item type `[1PL, 2PL, 3PL]`, epsilon for EM convergence:
```cpp
dichotomous::estimation e(Y, 7, 2, 0.0001);
```
Dataset, dimension, item type, EM epsilon, size cluster (amount of items by dimension), quadrature technique, amount of quadrature points, individuals' weights, custom initial values for item parameters:
```cpp
std::vector<int> size_cluster = {20, 20, 15};
dichotomous::estimation e(Y, 7, 2, 0.001, size_cluster, "QMCEM", 2000, individual_weights,
"datasets/initial_values_admission_test.csv");
```
For <b>latent traits</b> estimation you can use expected a priori or maximum a posteriori approaches.
```cpp
e.EAP(true);
e.MAP(true);
e.print_latent_traits();
```
Send `true` will estimate by individuals and `false` by patterns.
If you have item parameters estimation you can load it and then estimate latent traits.
```cpp
e.load_initial_values("datasets/admission_test_estimation.csv");
e.MAP(true);
```
Both, item parameters and latent traits estimation can be saved to files.
```cpp
e.print_item_parameters("datasets/admission_test_estimation.csv");
e.print_latent_traits("datasets/admission_test_LTestimation.csv");
```
<b>Log likelihood</b> can be obtained calling `e.log_likelihood()`.
```cpp
std::cout << e.log_likelihood() << '\n';
```
