#include "MinDegreeReordering.h"
#include <iostream>
#include <algorithm> 
#include <iterator>

using namespace std;

MinDegreeReordering::MinDegreeReordering(SymmetricSquareMatrix &_matrix):_matrix(_matrix){}

vector<int> MinDegreeReordering::minDegReorder(SymmetricSquareMatrix &inputMatrix, vector<int> initialPermutation){
    if(initialPermutation.size() == 1){
        _permutation.push_back(initialPermutation[0]);
        return _permutation;
    }
    vector<int> newPermutation;
    vector<double> degreeSum;
    int rows = inputMatrix.getNumRows();

    for(int i = 0; i < rows; i++){
        double sum = 0.0;
        for(int j = 0; j < rows; j++){
            if(i != j){
                sum += inputMatrix.getElementOfMatrix(i,j);
            }
        }
        degreeSum.push_back(sum);
    }

    vector<double>:: iterator it;
    it = min_element(degreeSum.begin(), degreeSum.end());
    int index = it - degreeSum.begin();

    vector<vector<double>> data;
    for(int i = 0; i < rows; i++){
        if(i != index){
            vector<double> data_row;
            for(int j = 0; j < rows; j++){
                if(j != index){
                    data_row.push_back(inputMatrix.getElementOfMatrix(i,j));
                }
            }
            data.push_back(data_row);
        }
    }

    for(int i = 0; i < rows; i++){
        if(i != index) newPermutation.push_back(initialPermutation[i]);
    }
        
    SymmetricSquareMatrix ssm(data);
    _permutation.push_back(initialPermutation[index]);    
    return minDegReorder(ssm,newPermutation);
}
