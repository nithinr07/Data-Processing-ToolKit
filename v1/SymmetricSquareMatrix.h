#include "Matrix.h"

#ifndef SYMMETRIC_SQUARE_MATRIX_H_
#define SYMMETRIC_SQUARE_MATRIX_H_
class SymmetricSquareMatrix : public Matrix {
    private: 
    public: SymmetricSquareMatrix(int nodes): Matrix(nodes,nodes){}
            SymmetricSquareMatrix(const SymmetricSquareMatrix&);
            ~SymmetricSquareMatrix();
            double getElementOfMatrix(int,int);
};

#endif // !SYMMETRIC_SQUARE_MATRIX_H_
