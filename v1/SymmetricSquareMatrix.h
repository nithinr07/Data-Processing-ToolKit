#include <vector>

#ifndef SYMMETRIC_SQUARE_MATRIX_H_
#define SYMMETRIC_SQUARE_MATRIX_H_
class SymmetricSquareMatrix : public Matrix {
    private: std::vector<std::vector<double>> _data;
    public: SymmetricSquareMatrix(int nodes): Matrix(nodes,nodes){}
            SymmetricSquareMatrix(const SymmetricSquareMatrix&);
            ~SymmetricSquareMatrix();
            double getElementOfMatrix(int, int);
};

#endif // !SYMMETRIC_SQUARE_MATRIX_H_
