#include <iostream>
#include <eigen3/Eigen/Dense>
#include <chrono>

using namespace Eigen;

class MatrixCOO { // re-use the class you implemented in exercise 2.4
				  // or delete this and work with raw vectors
	
	// Point (b)
	MatrixCOO mult_naive (MatrixCOO &A, MatrixCOO &B) {
		MatrixCOO result;
		// TODO
		return result;
	}

	// Point (d)
	// if you prefer,you can overload operator*
	MatrixCOO mult_efficient (MatrixCOO &A, MatrixCOO &B) {
		MatrixCOO result;
		// TODO
		return result;
	}
};

int main() {
	// Point (f)
	// TODO
}
