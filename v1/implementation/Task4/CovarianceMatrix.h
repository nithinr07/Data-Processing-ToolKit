#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "Variance.h"

#include <iostream>
#include <fstream>
#include <vector>

#ifndef COVARIANCE_MATRIX_H_
#define COVARIANCE_MATRIX_H_

class CovarianceMatrix : public Matrix
{  
    private:
        std::vector<std::vector<double>> _elements;
        int _size;

    public: 
        CovarianceMatrix(){}
        
        //double computeCovariance(Variable, Variable);
        void computeVariance(std::vector<Variable>);
        std::vector<Variable> normalizedVariables(std::vector<Variable>);
        double normalize(double, double, double);
        void normalizeMatrix(std::vector<std::vector<double>>);
        std::vector<std::vector<double>> get_elements() { return _elements; }
        std::vector<std::vector<double>> generate_matrix(std::vector<Variable>);
    friend std::ostream& operator<< (std::ostream &, CovarianceMatrix &) ;

};

#endif //COVARIANCE_MATRIX_H_
