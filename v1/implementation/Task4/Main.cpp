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
    inputFile.open("../../../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI_mod.csv");
    //inputFile.open("../Task1/input.csv");
    outputFile.open("output.csv");
    string line;
    vector<string> input_matrix;
    if(inputFile.is_open()) {
        getline(inputFile, line);
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
    std::vector<Variable> variables;
    for(int i = 0; i < (y-n); i++)
    {
        Variable v(i);
        v.set_numOfValues(x);
        std::vector<double> values;
        for(int j = 0; j < x; j++)
        {
            Record record = matrix.getData(j);
            std::vector<double> temp = record.getFeatureVector();   
            values.push_back(temp[i]);
        }
        v.set_values(values);
        variables.push_back(v);
    }

    Variance var;
    CovarianceMatrix cm;
    //Variable v1;
    var.computeVariance(variables);
    var.normalizedVariables(variables);
    //for(int i = 0; i < variables.size(); i++){
    //    for(int j = 0; j < variables[i].get_numOfValues(); j++){
    //        printf("%lf ",variables[i].get_values()[j]);}
    //printf("\n");
    //}

    std::vector<std::vector<double>> CM = cm.generate_matrix(variables);
    for(int i = 0; i < CM.size(); i++)
    {
        for(int j = 0; j < CM.size(); j++)
        {
            printf("%lf ",CM[i][j]);
        }
        printf("\n");
    }
    cm.normalizeMatrix(CM);

    vector<int> ordering = var.ordering(variables);

    outputFile<<cm;
    outputFile.close();
    return 0; 
}

