#include "../v1/SymmetricSquareMatrix.h"
#include "../v1/Matrix.h"
#include "../v1/Record.h"

#include <iostream>
#include <vector>
#include <algorithm> 
#include <iterator>

using namespace std;

void Matrix::addRecord(Record record) {
    _data.push_back(record);
}

void Record::setFeatureVector(std::vector<double> newFeatureVector){
    _featureVector = newFeatureVector;
}

double SymmetricSquareMatrix::getElementOfMatrix(int i, int j){
    vector<double> feature = getData(i).getFeatureVector();
    return feature[j];
}

vector<int> minDegReorder(SymmetricSquareMatrix &inputMatrix, vector<int> permutation, vector<int> reqPermutation){
    if(permutation.size() == 1){
        reqPermutation.push_back(permutation[0]);
        return reqPermutation;
    }
    vector<int> newPermutation;
    vector<double> degreeSum;
    int rows = inputMatrix.getNumRows();
    SymmetricSquareMatrix ssm(rows-1);
    for(int i = 0; i < rows; i++){
        double sum = 0.0;
        for(int j = 0; j < rows; j++){
            if(i != j){
                cout << "blah"<< i << "," << j << endl;
                sum += inputMatrix.getElementOfMatrix(i,j);
            }
        }
        degreeSum.push_back(sum);
    }
    vector<double>:: iterator it;
    it = min_element(degreeSum.begin(), degreeSum.end());
    int index = it - degreeSum.begin();
    for(int i = 0; i < rows; i++){
        if(i != index){
            Record r(rows-1,0,rows-1);
            vector<double> newFeatureVector;
            vector<double> inputFeatureVector = inputMatrix.getData(i).getFeatureVector();
            for(int j = 0; j < rows; j++){
                if(j != index){
                    newFeatureVector.push_back(inputFeatureVector[j]);
                }
            }
            r.setFeatureVector(newFeatureVector);
            ssm.addRecord(r);
        }
    }

    for(int i = 0; i < rows; i++){
        if(i != index) newPermutation.push_back(permutation[i]);
    }
        
    reqPermutation.push_back(permutation[index]);    
    return minDegReorder(ssm,newPermutation,reqPermutation);
}

int main(){
    SymmetricSquareMatrix ssm(3);
    Record r(3,0,3);
    Record r1(3,0,3);
    Record r2(3,0,3);
    vector<double> newFeatureVector;
    newFeatureVector.push_back(0.2);
    newFeatureVector.push_back(0.2);
    newFeatureVector.push_back(0.4);
    r.setFeatureVector(newFeatureVector);
    vector<double> newFeatureVector2;
    newFeatureVector2.push_back(0.2);
    newFeatureVector2.push_back(0.5);
    newFeatureVector2.push_back(0.1);
    r1.setFeatureVector(newFeatureVector2);
    vector<double> newFeatureVector3;
    newFeatureVector3.push_back(0.4);
    newFeatureVector3.push_back(0.1);
    newFeatureVector3.push_back(0.7);
    r2.setFeatureVector(newFeatureVector3);
    ssm.addRecord(r);
    ssm.addRecord(r1);
    ssm.addRecord(r2);
    vector<int> perm;
    perm.push_back(0);
    perm.push_back(1);
    perm.push_back(2);
    vector<int> req;
    cout << ssm.getElementOfMatrix(0,0) << endl;
    req = minDegReorder(ssm,perm,req);
    for(int i = 0; i < 3; i++){
        cout << req[i] << endl;
    }
    return 0;
}