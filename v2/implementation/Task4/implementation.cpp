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
#include <algorithm>

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
        _nonFeatureVector.push_back(tokens[i]);
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
        _values[i] = record.getFeatureVector()[i];
    }
}

/* Variance.h implementation*/
void Variance::computeVariance(std::vector<Variable> variables)
{
    for(int i = 0; i < variables.size(); i++)
    {
       Variable v = variables[i];
       std::vector<double> vals = v.get_values();
       int n = v.get_numOfValues();
       double sum = 0;
       for(int j = 0; j < n; j++)
           sum += vals[j]; 
       double mean = sum/n;
       double squareSum = 0;
       for(int j = 0; j < n; j++)
           squareSum += (vals[j] * vals[j]);
       double var = squareSum/n - (mean * mean);
       v.set_variance(var);
    }
}

double Variance::normalize(double Max, double Min, double Value)
{
    return (Value - Min) / (Max - Min);
}


std::vector<Variable> Variance::normalizedVariables(std::vector<Variable> variables)
{
    double Max = 0;
    double Min = 99999;
    int n = variables.size();
    for(int i = 0; i < n; i++)
    {
        if(variables[i].get_variance() > Max)
            Max = variables[i].get_variance();
        if(variables[i].get_variance() < Min)
            Min = variables[i].get_variance();
    }

    //Variances normalized
    for(int i = 0; i < n; i++)
    {
        Variable v = variables[i];
        double Value = v.get_variance();
        double nVar = normalize(Max, Min, Value);
        v.set_variance(nVar);
    }

    //Sorted according to normalized variances
    //std::sort(variables.begin(),variables.end(),varianceSort());
    //return variables;
    
}


