#include<iostream>
#include <queue>
#include "ReorderingSSM.h"
using namespace std;

ReorderingSSM::ReorderingSSM(SymmetricSquareMatrix _matrix):_matrix(_matrix){

}
void ReorderingSSM::sparsification(){
    for(int i=0;i<_matrix.getNumRows();i++){
        for(int j=0;j<_matrix.getNumColums();j++){
            if(_matrix.getElementOfMatrix(i,j) < 0.75) _matrix.setElementOfMatrix(i,j,0.0);
            else _matrix.setElementOfMatrix(i,j,1.0);
        }
    }
}

vector<int> ReorderingSSM::CuthillMchee(){
    sparsification();
    queue<int> Q;
    vector<int> R;

}