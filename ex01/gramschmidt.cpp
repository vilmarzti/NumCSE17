////
//// Copyright (C) 2016 SAM (D-MATH) @ ETH Zurich
//// Author(s): lfilippo <filippo.leonardi@sam.math.ethz.ch>
//// Contributors: tille, jgacon, dcasati
//// This file is part of the NumCSE repository.
////
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

VectorXd _projection(VectorXd u, VectorXd v){
    VectorXd projection;
    double size = u.transpose().dot(v) / u.squaredNorm();
    projection = u*size;
    return projection;
}
/* \brief Performs Gram-Schidt orthonormalization
 * Given a matrix $\mathbf{A}$ of linearly independent columns,
 * returns the result of a Gram-Schmidt orthonormalization.
 * Unstable GS algorithm: output is prone to cancellation issues.
 * \param[in] $\mathbf{A}$ Matrix of linearly independent columns
 * \return Matrix with ONB of $span(a_1, \cdots, a_n)$ as columns
 */
MatrixXd gram_schmidt(const MatrixXd & A) {
    // We create a matrix Q with the same size and data of A
    MatrixXd Q(A);
    size_t size = Q.cols();

    for(size_t x=0; x < size; x++) {
        VectorXd v = Q.col(x);
        VectorXd proj(v.size());

        for(int n=0; n<x; n++){
            proj += _projection(Q.col(n), v);
        }

        Q.col(x) = v - proj;
    }

    for(size_t x=0; x <size; x++){
        Q.col(x).normalize();
    }

    return Q;
}


int main(void) {
    // Orthonormality test
    unsigned int n = 9;
    MatrixXd A = MatrixXd::Random(n,n);
    // TODO: use gramschmidt to compute orthonormalization of
    // the matrix $\mathbf{A}$.
    MatrixXd Q = gram_schmidt(A);
    for(int x=0; x<n; x++){
        std::cout << x << std::endl;
        for(int y=0; y<n; y++){
            double a = Q.col(x).transpose().dot(Q.col(y));
            if(a <= std::numeric_limits<double>::epsilon()){
                a = 0;
            }
            else{
                std::cout << a <<std::endl;
            }
        }

        std::cout <<std::endl;
    }
}
