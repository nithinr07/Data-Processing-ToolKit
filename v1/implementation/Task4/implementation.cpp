#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "../Task1/WordDelimitedBy.h"
#include "Variable.h"
#include "Variance.h"
#include "CovarianceMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <vector>
#include <algorithm>


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
       v.set_mean(mean);
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

bool operator<(const Variable &v1, const Variable &v2)
{
    return v1.get_variance() < v2.get_variance();
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
    std::sort(variables.begin(), variables.end());

    return variables;
     
}

/*CovarianceMatrix implementation*/
double computeCovariance(Variable v1, Variable v2)
{
    std::vector<double> val1 = v1.get_values();
    std::vector<double> val2 = v2.get_values();
    double mean1 = v1.get_mean();
    double mean2 = v2.get_mean();
    int n = v1.get_numOfValues();
    
    double sum = 0;
    for(int i = 0; i < n; i++)
        sum += (v1.get_values()[i]-mean1)*(v2.get_values()[i]-mean2); 
    double cov = sum/(n-1);   
    return cov;
}

std::vector<std::vector<double>> CovarianceMatrix::generate_matrix(std::vector<Variable> variables)
{
    std::vector<std::vector<double>> elements; //(variables.size(),std::vector<double>( variables[0].get_numOfValues()));
    for(int i = 0; i < variables.size(); i++)
    {
        std::vector<double> temp;
        for(int j = 0; j < variables.size(); j++)
        {
            temp.push_back(0.0);
        }
        elements.push_back(temp);
    }

    for(int i = 0; i < variables.size(); i++)
    {
        for(int j = 0; j < variables.size(); j++)
        {
            if(i == j)
            {
                elements[i][j] = variables[i].get_variance();
            }
            else
            {
                elements[i][j] = computeCovariance(variables[i], variables[j]);
            }
        }
    }
    return elements;
}

void CovarianceMatrix::normalizeMatrix(std::vector<std::vector<double>> elements)
{
    double max = 0;
    Variance var;
    for(int i = 0; i < elements.size(); i++)
    {
        for(int j = 0; j < elements.size(); j++)
        {
            if(elements[i][j] > max)
                max = elements[i][j];
        }
    }
    double min = 999999;
    for(int i = 0; i < elements.size(); i++)
    {
        for(int j = 0; j < elements.size(); j++)
        {
            if(elements[i][j] < min)
                min = elements[i][j];
        }
    }
    for(int i = 0; i < elements.size(); i++)
    {
        for(int j = 0; j < elements.size(); j++)
            elements[i][j] = var.normalize(max, min, elements[i][j]);
    }    
}


std::vector<int> Variance::ordering(std::vector<Variable> variables)
{
    std::reverse(variables.begin(), variables.end());
    std::vector<int> ordering;
    for(int i = 0; i < variables.size(); i++)
    {   
        int in = variables[i].get_varIndex();
        ordering.push_back(in);
    }

    return ordering;
}

std::ostream& operator<< (std::ostream &os, CovarianceMatrix &cm) 
{
	for(auto i : cm.get_elements())
	{
		for(auto j : i)
		{
			os << j <<",";
		}
		os << std::endl;
	}
	return os;
}
