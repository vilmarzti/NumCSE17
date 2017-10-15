#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

// Point (c)

void solve_blockLU(const MatrixXd &R,
				   const VectorXd &u,
				   const VectorXd &v,
				   const VectorXd &b,
				   VectorXd &x){
    size_t size = R.cols();
    VectorXd zero = VectorXd::Zero(size)
    VectorXd uR   = u.transpose().dot(R.inverse());

    MatrixXd L << MatrixXd::Identity(size, size) << zero
               << uR << 1;

    MatrixXd U << R << v 
               << zero.transpose() << uR.dot(v);

    VectorXd y = L.inverse().dot(b);
    x = U.inverse().dot(y);
}


void solve_blockGauss(const MatrixXd &R,
				  	  const VectorXd &u,
				      const VectorXd &v,
				      const VectorXd &b,
				      VectorXd &x)
{
	// TODO
}

int main() {

}
