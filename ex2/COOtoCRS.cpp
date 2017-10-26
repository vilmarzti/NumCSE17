#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <vector>

using namespace Eigen;

typedef std::vector<Eigen::Triplet<double> > T;

class MatrixCRS {
    public: 
        MatrixCRS(MatrixXd &A);
        MatrixXd get_dense();
    private:
        std::vector<int> colInd;
        std::vector<int> rowPtr;
        std::vector<double> values;

        size_t num_rows;
        size_t num_cols;
};

class MatrixCOO {
    public:
        MatrixCOO(MatrixXd &A);
        MatrixXd get_dense();
    private:
        T TripletList;
        size_t num_rows;
        size_t num_cols;
};

MatrixCRS::MatrixCRS(MatrixXd &A){
    num_cols = A.cols();
    num_rows = A.rows();

    bool first_set;
    bool empty_row = false;
    double val;
    for(size_t m=0; m<num_rows; m++){
        first_set = false;

        for(size_t n=0; n<num_cols; n++){
            val = A(m, n);

            if(val != 0){
                values.push_back(val);
                colInd.push_back(n);

                // set rowpointer for the first value in each row
                if(!first_set){
                    first_set = true;
                    rowPtr.push_back(values.size() - 1);
                }

                // add a second rowpointer as a marker for a zero column
                if(empty_row){
                    empty_row = false;
                    rowPtr.push_back(values.size() - 1);
                }
            }
        }

        // check wheter a row is empty
        if(!first_set){
            empty_row = true;
        }
    }
    rowPtr.push_back(values.size() - 1);
}

MatrixXd MatrixCRS::get_dense(){
    MatrixXd A = MatrixXd::Zero(num_rows, num_cols);
    

    int row = 0;
    // Go implicitly through all the rows
    // increase the row number whenever we go to the next few rowpointers
    for(size_t n=0; n<rowPtr.size() - 1; n++){
        int rPtr = rowPtr.at(n);
        int nextrPtr = rowPtr.at(n+1);

        // set values according to rowpointers
        for(int pos=rPtr; pos < nextrPtr; pos++ ){
            int value = values.at(pos);
            int column = colInd.at(pos);

            A(row, column) = value;
        }
        
        row += 1;
    }

    return A;
}

MatrixCOO::MatrixCOO(MatrixXd &A){
    num_cols = A.cols();
    num_rows = A.rows();
        
    for(size_t n=0; n<num_cols; n++){
        for(size_t m=0; m<num_rows; m++){

            if(A(m,n) != 0){
                TripletList.push_back(Triplet<double>(m, n, A(m,n)));
            }
        }
    }
}

MatrixXd MatrixCOO::get_dense(){
    MatrixXd A = MatrixXd::Zero(num_rows, num_cols);
    for(size_t n = 0; n< TripletList.size(); n++){
        Triplet<double> trip = TripletList.at(n);
        A(trip.row(), trip.col()) += trip.value();
    }
    
    return A;
}




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
    MatrixCRS B(A);
    MatrixXd C = A - B.get_dense();
    std::cout << C << std::endl;
}
