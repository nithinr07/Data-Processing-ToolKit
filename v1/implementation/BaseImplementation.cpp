#include "../Matrix.h"
#include "../Record.h"
#include "./Task1/WordDelimitedBy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <bits/time.h>
#include <string>
#include <cstdlib>


// Implementation of Matrix Class

Matrix::Matrix(int R , int C , std::vector<Record> _datain ): _numRows(R), _numCols(C) {

  _data = std::vector<Record>(_datain);

}

Matrix::Matrix(): _numRows(0), _numCols(0) {

	_data = {};

}

// Matrix::~Matrix() {

// 	for (int i = 0; i < _data.size(); ++i)
// 		_data[i].~Record();

//     _data.clear();
//   _numRows = 0 ; _numCols = 0 ;
// }

Matrix::Matrix(Matrix& m) :
  _numRows(m._numRows), _numCols(m._numCols){
  _data = std::vector<Record>(m._data);
}

void Matrix::addRecord(Record &record) {
    _data.push_back(record);
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(os, ","));
  }
  return os;
}

std::ostream& operator<< (std::ostream& os, Matrix& m)
 {
    for(int i = 0;i < m._numRows;i++) {
        os << m.getData(i).getNonFeatureVector() << m.getData(i).getFeatureVector();
        os << std::endl;
    }
    return os;
//   int nr = m._numRows ;
//   int nc = m._numCols ;
//   os << nr << " " << nc << std::endl;
//   for (int i = 0; i < nr; i++) {
//       os << m._data[i]<< " " ;
//   }
//   return os;
}


// Implementation of Record Class

Record::Record(int y, int n, int N, std::vector<std::string> nonFeatureVector, std::vector<double> featureVector):
        _numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) 
{
	_nonFeatureVector = std::vector<std::string>(nonFeatureVector);
	_featureVector = std::vector<double>(featureVector);
}

Record::Record(const Record &r) {
	_numVariables = r._numVariables;
	_numNumericalVariables = r._numNumericalVariables;
	_numNonNumericalVariables = r._numNonNumericalVariables;

	_nonFeatureVector = std::vector<std::string>(r._nonFeatureVector);
	_featureVector = std::vector<double>(r._featureVector);
}

// Record::~Record()
// {
// 	_nonFeatureVector.clear();
// 	_featureVector.clear();
// 	_numNumericalVariables = 0;
// 	_numVariables = 0;
// 	_numNonNumericalVariables = 0;
// }

std::ostream& operator<< (std::ostream &os, Record &r)
{
    for(int i = 0;i < r._featureVector.size();i++)
    {
        os << r._featureVector[i] << " ";
    }
    os << std::endl;
    return os;
}

template<char delimiter>
std::istream& operator>>(std::istream& is, WordDelimitedBy<delimiter>& output)
{
   std::getline(is, output, delimiter);
   return is;
}

void Record::setRecord(std::string data, int n) {
    std::istringstream iss(data);
    std::vector<std::string> tokens{std::istream_iterator<WordDelimitedBy<','>>{iss}, std::istream_iterator<WordDelimitedBy<','>>{}}; 
    for(int i = 0;i < n;i++) {
        _nonFeatureVector.push_back(tokens[i]);
    }
    for(int i = 0;i < _numNumericalVariables;i++) {
        _featureVector.push_back(stod(tokens[i + n]));
    }
}

void Record::setFeatureVector(std::vector<double> &fv)
{
	_featureVector = fv;
}

bool Record::operator==(Record &r1)
{
	return (r1.getFeatureVector()==getFeatureVector())&&(r1.getNonFeatureVector()==getNonFeatureVector());

}
void Record::operator=(const Record &r)
{
	_numVariables = r._numVariables;
	_numNumericalVariables = r._numNumericalVariables;
	_numNonNumericalVariables = r._numNonNumericalVariables;

	_nonFeatureVector = std::vector<std::string>(r._nonFeatureVector);
	_featureVector = std::vector<double>(r._featureVector);
}

//---------------------Record End
