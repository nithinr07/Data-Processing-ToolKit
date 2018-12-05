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
        CovarianceMatrix(std::vector<std::vector<double>> elements)
        {
            _elements = elements;
            _size = elements.size();
        }
        
        CovarianceMatrix generate_matrix(std::vector<Variable>);
        double computeCovariance(Variable, Variable);
        void computeVariance(std::vector<Variable>);
        double normalize(double, double, double);
        void normalizeMatrix();
        std::vector<std::vector<double>> get_elements() { return _elements; }
};

#endif //COVARIANCE_MATRIX_H_
