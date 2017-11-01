#include <iostream>

#include <Eigen/Dense>

using namespace Eigen;

/* @brief 
 * @param[in] z An $n$-dimensional vector containing one side of input data
 * @param[in] c An $n$-dimensional vector containing the other side of input data
 * @param[out] x The vector of parameters $(\alpha,\beta)$, intercept and slope of the line fitted
 */
VectorXd lsqEst(const VectorXd &z, const VectorXd &c)
{
    // Initialization
	int n = z.size();
    assert( z.size() == c.size() && "z and c must have same size");
    std::cout << c.size() << std::endl;

	VectorXd x(2);
    MatrixXd A(n, 2);

    double z1;
    double z2;
    for(int j=0; j < n; j++){
        A(j, 0) = z(j);

        if(j==0){
            z1 = 0;
        }else{
            z1 = z(j-1);
        }

        if(j==n-1){
            z2 = 0;
        }else{
            z2 = z(j+1);
        }
        
        A(j, 1) = z1 + z2;
    }

        
    x = (A.transpose() * A).ldlt().solve(A.transpose() * c);
	return x;
}

int main() {
    // Initialization
    unsigned int n = 10;
    VectorXd z(n), c(n);
    for(size_t i=0; i<n; ++i) {
		z(i) = i+1;
		c(i) = n-i;
	}

	VectorXd x = lsqEst(z, c);

	std::cout << "alpha = " << x(0) << std::endl;
	std::cout << "beta = "  << x(1) << std::endl;
}
