#include "Matrix.h"

#ifndef SYMMETRIC_SQUARE_MATRIX_H_
#define SYMMETRIC_SQUARE_MATRIX_H_
class SymmetricSquareMatrix : public Matrix {
    private: 
    public: SymmetricSquareMatrix(int, int);
            SymmetricSquareMatrix(const SymmetricSquareMatrix&);
            ~SymmetricSquareMatrix();
};

#endif // !RECORD_H_