#include "../v1/SymmetricSquareMatrix.h"
#include "../v1/Matrix.h"
#include "../v1/Record.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>

using namespace std;

template<char delimiter>
class WordDelimitedBy : public string
{};

template<char delimiter>
istream& operator>>(istream& is, const WordDelimitedBy<delimiter>& output)
{
   getline(is, output, delimiter);
   return is;
}

int get_row_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<WordDelimitedBy<','>>{iss}, istream_iterator<WordDelimitedBy<','>>{}};
    return stoi(tokens.at(0));
}

int get_col_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<WordDelimitedBy<','>>{iss}, istream_iterator<WordDelimitedBy<','>>{}};
    return stoi(tokens.at(1)); 
}

double compute_pairwise_similarity(Record record1, Record record2) {
    vector<double> A = record1.getFeatureVector();
    vector<double> B = record2.getFeatureVector();
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
         for(unsigned int i = 0u; i < record1.getNumNumericVariables(); ++i) {
            dot += A[i] * B[i] ;
            denom_a += A[i] * A[i] ;
            denom_b += B[i] * B[i] ;
        }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;    
}

void Record::setRecord(string data, int n) {
    istringstream iss(data);
    vector<string> tokens{istream_iterator<WordDelimitedBy<';'>>{iss}, istream_iterator<WordDelimitedBy<';'>>{}}; 
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

int main(int argc, char **argv) {
    int n = stoi(argv[1]);
    ifstream inputFile;
    inputFile.open("../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI.csv");
    string line;
    vector<string> input_matrix;
    string init;
    getline(inputFile, init);
    int count = 0;
    if(inputFile.is_open()) {
        while(getline(inputFile, line)) {
            input_matrix.push_back(line);
        }
        inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(0);
    }
    int x = get_row_size(init);
    int y = get_col_size(init);
    Matrix matrix(x, y);
    for(int i = 0;i < x;i++) {
        Record record(y, n, y - n);
        record.setRecord(input_matrix[i], n);
        matrix.addRecord(record);
    }
    inputFile.close();
    return 0;
}