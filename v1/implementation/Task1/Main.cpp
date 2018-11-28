#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "WordDelimitedBy.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <bits/time.h>

using namespace std;

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

int main(int argc, char **argv) {
    srand(time(NULL));
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