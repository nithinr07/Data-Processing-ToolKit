#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "Similarity.h"
#include "WordDelimitedBy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <vector>

template<char delimiter>
std::istream& operator>>(std::istream& is, WordDelimitedBy<delimiter>& output)
{
   std::getline(is, output, delimiter);
   return is;
}

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

void Matrix::addRecord(Record record) {
    _data.push_back(record);
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