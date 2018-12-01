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
        std::vector<double> computeVariances(std::vector<Variable>);
        std::vector<Variable> normalized_variables();
        

};

#endif //VARIANCE_H_
