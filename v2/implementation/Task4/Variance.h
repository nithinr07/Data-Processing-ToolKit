#include "../../Matrix.h"
#include "../../Record.h"

#include <vector>
#include <cmath>

#ifndef VARIANCE_H_
#define VARIANCE_H_

class Variance
{
    private: std::vector<double> _variances;

    public:
        Variance(){}
        void computeVariance(std::vector<Variable>);
        double normalize(double, double, double);
        std::vector<Variable> normalizedVariables(std::vector<Variable>);
        

};

#endif //VARIANCE_H_
