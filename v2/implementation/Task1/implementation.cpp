#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "Similarity.h"
#include "../Task1/WordDelimitedBy.h"
#include "KMeans.h"
#include "../Task2/DistanceMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <vector>

// Implementation of Matrix Class

Matrix::Matrix(int R , int C , std::vector<Record> _data ): _numRows(R), _numCols(C) {
  _data = *(new std::vector<Record>)  ;
  for (int i = 0 ; i < _numRows ; i++) {
    _data[i] = *(new Record()) ;
    }
}

Matrix::Matrix(): _numRows(0), _numCols(0) {
  _data = *(new std::vector<Record>)  ;
}

Matrix::~Matrix() {
    _data.clear();
  _numRows = 0 ; _numCols = 0 ;
}

Matrix::Matrix(Matrix& m) :
  _numRows(m._numRows), _numCols(m._numCols){
  _data = *(new std::vector<Record>)  ;
  for (int i = 0 ; i < _numRows ; i++) {
    _data[i] = *(new Record()) ;
    }
    
        
  for (int i = 0; i < _numRows; i++) 
      _data[i] = m._data[i];
}

void Matrix::addRecord(Record record) {
    _data.push_back(record);
}

std::ostream& operator<< (std::ostream& os, Matrix& m)
 {

  int nr = m._numRows ;
  int nc = m._numCols ;
  os << nr << " " << nc << std::endl;
  for (int i = 0; i < nr; i++) {
      os << m._data[i]<< " " ;
  }
  return os;
}

std::ostream& operator<< (std::ostream &os, Record &r)
{
    for(auto i : r.getFeatureVector())
    {
        os << i << " ";
    }
    os << std::endl ;
    return os;
}

template<char delimiter>
std::istream& operator>>(std::istream& is, WordDelimitedBy<delimiter>& output)
{
   std::getline(is, output, delimiter);
   return is;
}

// Implementation of Record Class
void Record::setRecord(std::string data, int n) {
    std::istringstream iss(data);
    std::vector<std::string> tokens{std::istream_iterator<WordDelimitedBy<';'>>{iss}, std::istream_iterator<WordDelimitedBy<';'>>{}}; 
    for(int i = 0;i < n;i++) {
        _nonFeatureVector.push_back(tokens[i]);
    }
    for(int i = 0;i < _numNumericalVariables;i++) {
        _featureVector.push_back(stod(tokens[i + n]));
    }
}

Record(int y, int n, int N, std::vector<std::string> nonFeatureVector, std::vector<double> featureVector):
        _numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) {
{
                _nonFeatureVector = *(new std::vector<std::string>(nonFeatureVector));
                _featureVector = *(new std::vector<double>(featureVector));

}


double Similarity::compute_pairwise_similarity() {
    std::vector<double> A = _record1.getFeatureVector();
    std::vector<double> B = _record2.getFeatureVector();
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
        for(unsigned int i = 0u; i < _record1.getNumNumericVariables(); ++i) {
            dot += A[i] * B[i] ;
            denom_a += A[i] * A[i];
            denom_b += B[i] * B[i];
        }
    return dot / (sqrt(denom_a) * sqrt(denom_b));    
}

void KMeans::compute_centroids() {
    int count = 0;
    while(count != _K) {
        int id = rand() % (_dataSet.getNumRows() + 1);
        if(_centroids.count(id) == 0) {
            std::vector<double> entry = _dataSet.getData(id).getFeatureVector();
            _centroids[id] = entry;
            count++;
        }
    }
}

void KMeans::process() {
    
}

// Implementation of NormalizedDisComp

