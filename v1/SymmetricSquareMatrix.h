#ifndef SYMMETRIC_SQUARE_MATRIX_H_
#define SYMMETRIC_SQUARE_MATRIX_H_

template <typename T>
class SymmetricSquareMatrix : public Matrix {
    private: 
    public: SymmetricSquareMatrix(int, int);
            SymmetricSquareMatrix(const SymmetricSquareMatrix&);
            ~SymmetricSquareMatrix();
};

#endif // !RECORD_H_