#include <vector>

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
    private: int _numRows;
             int _numCols;
             std::vector <double, double> _data;
    public: Matrix();
            Matrix(const Matrix&);
            ~Matrix();
};

#endif // !MATRIX_H_