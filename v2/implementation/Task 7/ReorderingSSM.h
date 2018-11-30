#include<iostream>
#include<vector>
#include "../../SymmetricSquareMatrix.h"
using namespace std;

#ifndef Reordering_S_S_M_H_
#define Reordering_S_S_M_H_

class ReorderingSSM {
    private:
        SymmetricSquareMatrix _matrix;

    public:
        ReorderingSSM(SymmetricSquareMatrix );
        ReorderingSSM(){}
        ~ReorderingSSM(){};
        vector<int> CuthillMchee();
        void sparsification();
        
        
};
#endif // !Reordering_S_S_M_H_
