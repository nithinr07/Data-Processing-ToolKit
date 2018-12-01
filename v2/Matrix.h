#include "Record.h"

#include <vector>
#include <iostream>

#ifndef Matrix_H_
#define Matrix_H_


class Matrix{
 protected:
    int _numRows, _numCols ;
    std::vector<Record> _data;
  
 public:
  Matrix() ; // constructor //
  Matrix(int numRows, int numCols):_numRows(numRows), _numCols(numCols) {}
//   ~Matrix()  ; // destructor //
  Matrix(Matrix&) ; // copy constructor //
  Matrix(int, int, std::vector<Record>);

  void addRecord(Record &);
  Record getData(int i){ return _data[i]; }

  friend std::ostream& operator<< (std::ostream &, Matrix &) ;

  // getters //
  int numRows() { return _numRows ; }
  int numCols() { return _numCols ; }
  
} ;


#endif
