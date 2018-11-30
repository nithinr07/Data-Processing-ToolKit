#include "../../SymmetricSquareMatrix.h"
#include <iostream>
#include <vector>

#ifndef MinDegreeReordering_H_
#define MinDegreeReordering_H_

class MinDegreeReordering {
    private:
        SymmetricSquareMatrix _matrix;
        std::vector<int> _permutation;

    public:
        MinDegreeReordering(SymmetricSquareMatrix &);
        MinDegreeReordering(){}
        // ~MinDegreeReordering(){};
        std::vector<int> minDegReorder(SymmetricSquareMatrix &, std::vector<int>);        
        
};

#endif // !MinDegreeReordering_H_