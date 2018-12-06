#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "WordDelimitedBy.h"
#include "KMeans.h"
#include "SimilarityMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <bits/time.h>

using namespace std;

template<char delimiter>
istream& operator>>(istream& is, WordDelimitedBy<delimiter>& output)
{
   getline(is, output, delimiter);
   return is;
}

int get_col_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<WordDelimitedBy<','>>{iss}, istream_iterator<WordDelimitedBy<','>>{}};
    return tokens.size(); 
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int n = stoi(argv[1]);
    int k = stoi(argv[2]);
    ifstream inputFile;
    ofstream outputFile1;
    ofstream outputFile2;
    ofstream outputFile3;
    inputFile.open("../../../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI_mod.csv");
    // inputFile.open("input.csv");
    outputFile1.open("kmeans.csv");
    outputFile2.open("similarity.csv");
    outputFile3.open("records.csv");
    string ignore;
    getline(inputFile, ignore);
    string line;
    vector<string> input_matrix;
    if(inputFile.is_open()) {
        while(getline(inputFile, line)) {
            input_matrix.push_back(line);
        }
        inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(0);
    }
    int x = input_matrix.size();
    int y = get_col_size(input_matrix[0]);
    Matrix matrix;
    matrix.setRows(x);
    matrix.setCols(y);
    for(int i = 0;i < x;i++) {
        Record record(y, n, y - n);
        record.setRecord(input_matrix[i], n);
        matrix.addRecord(record);
    }
    vector<vector<double>> data(x);
    SimilarityMatrix sm(data, x);
    sm.generate_matrix(matrix);
    outputFile2 << sm;
    KMeans kmeans(k, matrix);
    kmeans.process();
    outputFile1 << kmeans << endl;
    // outputFile3 << kmeans.getDataSet();
    // SimilarityMatrix sm(data, x);
    // sm.generate_matrix(matrix);
    // outputFile2 << sm;
    inputFile.close();
    outputFile1.close();
    outputFile2.close();
    outputFile3.close();
    return 0;
}