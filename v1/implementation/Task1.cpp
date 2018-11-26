#include "./SymmetricSquareMatrix.h"
#include "./Matrix.h"
#include "./Record.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

int get_row_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return stoi(tokens.at(0));
}

int get_col_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return stoi(tokens.at(1)); 
}

void Record::setRecord(string data, int n) {
    istringstream iss(data);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}}; 
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
    inputFile.open("input.txt");
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