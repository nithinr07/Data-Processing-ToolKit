#include "Record.h"

#include <vector>

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
    private: int _numRows;  
             int _numCols;
             std::vector<Record> _data;
    public: Matrix(int M, int N):_numRows(M), _numCols(N) {} 
            Matrix(int, int, std::vector<Record>);
            // Matrix(const Matrix&);
            // ~Matrix();
            void addRecord(Record&);
            Record getData(int i){ return _data[i]; }
            int numRows() { return _numRows; }
            int numCols() { return _numCols; }
};

#endif // !MATRIX_H_