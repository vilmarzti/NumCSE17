//// 
//// Copyright (C) 2016 SAM (D-MATH) @ ETH Zurich
//// Author(s): lfilippo <filippo.leonardi@sam.math.ethz.ch> 
//// Contributors: tille, jgacon, dcasati
//// This file is part of the NumCSE repository.
////
#include <iostream>
#include <iomanip>

#include <Eigen/Dense>
#include <mgl2/mgl.h>
#include "timer.h"

using namespace Eigen;

/* @brief Build an "arrow matrix" and compute A*A*y
 * Given vectors $a$ and $d$, returns A*A*x in $y$, where A is built from a, d
 * @param[in] d An n-dimensional vector
 * @param[in] a An n-dimensional vector
 * @param[in] x An n-dimensional vector
 * @param[out] y The vector y = A*A*x
 */
void arrow_matrix_2_times_x(const VectorXd &d, const VectorXd &a,
                            const VectorXd &x, VectorXd &y) {
    assert(d.size() == a.size() && a.size() == x.size() &&
           "Vector size must be the same!");
    int n = d.size();

    VectorXd d_head = d.head(n-1);
    VectorXd a_head = a.head(n-1);
    MatrixXd d_diag = d_head.asDiagonal();

    MatrixXd A(n, n);

    A << d_diag,             a_head,
         a_head.transpose(), d(n-1);

    y = A*A*x;
}

/* @brief Build an "arrow matrix"
 * Given vectors $a$ and $b$, returns A*A*x in $y$, where A is build from a,d
 * @param[in] d An n-dimensional vector
 * @param[in] a An n-dimensional vector
 * @param[in] x An n-dimensional vector
 * @param[out] y The vector y = A*A*x
 */
void efficient_arrow_matrix_2_times_x(const VectorXd &d,
                                      const VectorXd &a,
                                      const VectorXd &x,
                                      VectorXd &y) {
    assert(d.size() == a.size() && a.size() == x.size() &&
         "Vector size must be the same!");
    int n = d.size();

    // Split A into 4 Different Blocks
    //
    //     D  |  a
    // A = -  -  - 
    //     aT |  d
    // And use block multiplications to efficiently calculate y
    //
    // y = (y_head, y_tail) = AAx

    VectorXd d_head = d.head(n-1);
    VectorXd a_head = a.head(n-1);
    VectorXd x_head = x.head(n-1);

    double aTX  = a_head.transpose().dot(x_head);
    VectorXd DX = d_head.cwiseProduct(x_head);

    VectorXd DDX = d_head.cwiseProduct(DX);
    VectorXd Dax = d_head.cwiseProduct(a_head) * x(n-1);
    VectorXd aaX = a_head * aTX;
    VectorXd adx = a_head * d(n-1) * x(n-1);

    VectorXd y_head = DDX + Dax + aaX + adx;

    double aDx = a_head.transpose().dot(DX);
    double aax = a_head.squaredNorm() * x(n-1);
    double daX = aTX * d(n-1);
    double ddx = d(n-1) * d(n-1) * x(n-1);

    double y_tail = aDx + aax + daX + ddx;

    y << y_head, y_tail;
}

/* \brief Compute the runtime of arrow matrix multiplication.
 * Repeat tests 10 times, and output the minimal runtime
 * amongst all times. Test both the inefficient and the efficient
 * versions.
*/
void runtime_arrow_matrix() {
    for(int x=4; x<1024; x = x*2){
        Timer t1, t2;
        VectorXd a(x);
        VectorXd d(x);
        VectorXd vx(x);
        VectorXd yi;

        a.setRandom();
        d.setRandom();
        vx.setRandom();

        for(int n=0; n<5; n++){
            // naive test
            t1.start();
            arrow_matrix_2_times_x(a, d, vx, yi);
            t1.stop();

            // efficient test
            t2.start();
            efficient_arrow_matrix_2_times_x(a, d, vx, yi);
            t2.stop();
        }

        std::cout << "Size " << x << std::endl;
        std::cout << "Naive min:" << t1.min() << std::endl;
        std::cout << "Effic min:" << t2.min() << std::endl;
        std::cout << std::endl;

    }

}


int main(void) {
    // Test vectors
    VectorXd a(5);
    a << 1., 2., 3., 4., 5.;
    VectorXd d(5);
    d <<1., 3., 4., 5., 6.;
    VectorXd x(5);
    x << -5., 4., 6., -8., 5.;
    VectorXd yi;

    // Run both functions
    arrow_matrix_2_times_x(a,d,x,yi);
    VectorXd ye(yi.size());
    efficient_arrow_matrix_2_times_x(a,d,x,ye);

    // Compute error
    double err = (yi - ye).norm();

    // Output error
    std::cout << "--> Correctness test." << std::endl;
    std::cout << "Error: " << err << std::endl;

    // Print out runtime
    std::cout << "--> Runtime test." << std::endl;
    runtime_arrow_matrix();

    // Final test: exit with error if error is too big
    double eps = std::numeric_limits<double>::denorm_min();
    exit(err < eps);
}
