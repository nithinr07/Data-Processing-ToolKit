#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "../Task1/WordDelimitedBy.h"
#include "CovarianceMatrix.h"
#include "Variable.h"
#include "Variance.h"


#include <iostream>
#include <vector>
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
    ifstream inputFile;
    ofstream outputFile;
    //inputFile.open("../../../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI_mod.csv");
    inputFile.open("../Task1/input.csv");
    outputFile.open("output.csv");
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
    //std::vector<std::vector<double>> sample = {{0,0,0,0},{1,1,1,1},{2,2,2,2}};
    std::vector<Variable> variables(y-n);
    for(int i = 0; i < (y-n); i++)
        variables[i].setVariable(i,matrix);

    Variance var;
    CovarianceMatrix cm;
    Variable v1;
    var.computeVariance(variables);
    var.normalizedVariables(variables);
    std::vector<std::vector<double>> CM = cm.generate_matrix(variables);
    cm.normalizeMatrix(CM);
    vector<int> ordering = var.ordering(variables);

    outputFile<<cm;
    outputFile.close();
    return 0; 
}

