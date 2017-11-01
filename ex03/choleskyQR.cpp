#include <iostream>
#include <limits>

#include <Eigen/Dense>
#include <Eigen/QR>

using namespace Eigen;

/* @brief QR decomposition from Cholesky decomposition
 * @param[in] A An $m \times n$ matrix
 * @param[out] R The upper triangular matrix from the QR decomposition of $A$
 * @param[out] Q The orthogonal matrix from the QR decomposition of $A$
 */
void CholeskyQR(const MatrixXd & A, MatrixXd & R, MatrixXd & Q) {
	
	//TODO
	
}

MatrixXd CholeskyDecomp(const MatrixXd &A, int step){
    int size = A.rows();
    MatrixXd L = MatrixXd::Identity(size, size);
    MatrixXd A_prime; 

    if(step == size){
        return L;
    }

    return L * CholeskyDecomp(A_prime, n + 1);
}

/* @brief Direct QR decomposition
 * @param[in] A An $m \times n$ matrix
 * @param[out] R The upper triangular matrix from the QR decomposition of $A$
 * @param[out] Q The orthogonal matrix from the QR decomposition of $A$
 */
void DirectQR(const MatrixXd & A, MatrixXd & R, MatrixXd & Q) {
	
	//TODO
	
}

int main() {
	size_t m = 3;
	size_t n = 2;
    
	MatrixXd A(m,n);
	double epsilon = std::numeric_limits<double>::denorm_min();
	A << 3, 5, 1, 9, 7, 1;
  //A << 1, 1, 0.5*epsilon, 0, 0, 0.5*epsilon;
	std::cout << "A =" << std::endl << A << "\n" << std::endl;
    
	MatrixXd R, Q;

	CholeskyQR(A, R, Q);
	std::cout << "From Cholesky: R =" << std::endl << R << "\n" << std::endl;
	std::cout << "From Cholesky: Q =" << std::endl << Q << "\n" << std::endl;
    
	DirectQR(A, R, Q);
	std::cout << "Direct QR: R =" << std::endl << R << "\n" << std::endl;
	std::cout << "Direct QR: Q =" << std::endl << Q << std::endl;

}
