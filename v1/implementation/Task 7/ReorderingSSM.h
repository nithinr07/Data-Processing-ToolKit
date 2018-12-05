#include<iostream>
#include<vector>
#include "../../SymmetricSquareMatrix.h"
using namespace std;

#ifndef Reordering_S_S_M_H_
#define Reordering_S_S_M_H_

class ReorderingSSM {
    private:
        SymmetricSquareMatrix _matrix;

    public:
        // Constructor and Destructor
        ReorderingSSM(SymmetricSquareMatrix );
        ReorderingSSM(){}
        ~ReorderingSSM();
        //copy constructor
        ReorderingSSM(ReorderingSSM &);

        // class methods
        vector<int> CuthillMckee();
        vector<int> ReverseCuthillMckee();
        void sparsification();
        vector<double> degreeGenerator();

        //getters and Setters
        int getNumRows(){
            return _matrix.getNumRows();
        }
        int getNumRowsColums(){
            return _matrix.getNumColums();
        }
        double getMatrixDataAt(int i,int j){
            return _matrix.getElementOfMatrix(i,j);
        }

        void setMatrixDataAt(int i,int j,double data){
            _matrix.setElementOfMatrix(i,j,data);
        }

};
#endif // !Reordering_S_S_M_H_
