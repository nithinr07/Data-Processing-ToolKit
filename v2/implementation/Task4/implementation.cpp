#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "../Task1/WordDelimitedBy.h"
#include "Variable.h"
#include "Variance.h"

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

/*Record.h implementation*/
void Record::setRecord(std::string data, int n) 
{
    std::istringstream iss(data);
    std::vector<std::string> tokens{std::istream_iterator<WordDelimitedBy<','>>{iss}, std::istream_iterator<WordDelimitedBy<','>>{}};
    for(int i = 0;i < n;i++)
        _NonFeatureVector.push_back(tokens[i]);
    for(int i = 0;i < _numNumericalVariables;i++)
        _featureVector.push_back(stod(tokens[i + n]));
}

/*Matrix.h implementation*/
void Matrix::addRecord(Record &record)
{
    _data.push_back(record);
}

/* Variable.h implementation*/
void Variable::setVariable(int varIndex, Matrix input)
{
    _varIndex = varIndex;
    _numOfValues = input.numRows();
    for(int i = 0; i < _numOfValues; i++)
    {
        Record record = input.getData(i);
        _values[i] = record.getFeatureVector().get(i);
    }
}

/* Variance.h implementation*/
std::vector<double> Variance::computeVariances(std::vector<Variable> variables)
{
    for(int i = 0; i < variables.size(); i++)
    {
       Variable v = variables.get(i);
       std::vector<double> vals = v.get_values();
       int n = v.get_numOfValues();
       double sum = 0;
       for(int j = 0; j < n; j++)
           sum += vals.get(j); 
       double mean = sum/n;
       double squareSum = 0;
       for(int j = 0; j < n; j++)
           squareSum += (vals.get(j) * vals.get(j));
       double var = squareSum/n - (mean * mean);
       v.set_variance(var);
    }
}


