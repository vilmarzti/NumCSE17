#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>

using namespace Eigen;

class MatrixCOO {
	// TODO: implement COO data structures, conversion to CRS and to/from dense Eigen matrix.
	// The level of abstraction is left to your choice:
	// you can delete this and use raw vectors;
	// (recommended) you can implement this as a wrapper and consider
	// only matrices with entries of the double type;
	// you can implement this as a template class.
	// The same for conversions:
	// you can work directly with the raw vectors;
	// (recommended) you can implement functions toCRS and toDense for your wrappers;
	// you can overload operator= for implicit/explicit conversion.
    //
    public:
        MatrixCOO toCOO(MatrixXd &A);
    private:
        std::vector<Eigen::Triplet<double>> TripletList;
};


MatrixCOO::MatrixCOO(std::vector<Eigen::Triplet<double>> T){
    TripletList = T;
};

MatrixCOO MatrixCOO::toCOO(MatrixXd &A){
    size_t num_cols = A.cols();
    size_t num_rows = A.rows();
    std::vector<Eigen::triplet<double>> Tlist;

    for(size_t n=0;n<num_rows;n++){
        for(size_t m=0;m<num_cols;m++){
            if(A(m,n) != 0){
                Tlist.push(Triplet(m, n, A(m,n)));
            }
        }
    }
    return MatrixCOO(Tlist);
};



class MatrixCRS {
	// TODO: implement CRS data structures, conversion to COO and to/from dense Eigen matrix.
};

int main() {
	MatrixXd A(18,17);
	A<< 2,-1, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   -1, 4,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0,
 		0,-1, 3,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
 		0, 0,-1, 3, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       -1,-1, 0, 0, 4, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0,
 		0, 0, 0,-1, 0, 0, 0, 4, 0, 0,-1, 0, 0, 0, 0, 0,-1,
 		0, 0, 0, 0,-1, 0, 0, 0, 4, 0, 0,-1,-1, 0, 0, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 4,-1, 0, 0,-1,-1, 0,-1,
 		0, 0, 0, 0, 0, 0, 0,-1, 0,-1, 3, 0, 0, 0,-1, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 2,-1, 0, 0, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0,-1, 4,-1, 0, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0,-1, 3,-1, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 0, 0,-1, 3, 0, 0,
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 		0,-1, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,-1,
 		0, 0,-1,-1, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 0,-1, 5;
	
	// TODO: test correctness of implementend conversion methods on A
}
