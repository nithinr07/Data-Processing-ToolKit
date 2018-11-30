#include "MinDegreeReordering.h"

using namespace std;

int main(){
    vector<vector<double>> data;
    vector<double> newFeatureVector;
    newFeatureVector.push_back(0.2);
    newFeatureVector.push_back(0.2);
    newFeatureVector.push_back(0.4);
    data.push_back(newFeatureVector);
    vector<double> newFeatureVector2;
    newFeatureVector2.push_back(0.2);
    newFeatureVector2.push_back(0.5);
    newFeatureVector2.push_back(0.1);
    data.push_back(newFeatureVector2);
    vector<double> newFeatureVector3;
    newFeatureVector3.push_back(0.4);
    newFeatureVector3.push_back(0.1);
    newFeatureVector3.push_back(0.7);
    data.push_back(newFeatureVector3);

    SymmetricSquareMatrix ssm(data);
    vector<int> perm;
    perm.push_back(0);
    perm.push_back(1);
    perm.push_back(2);
    vector<int> req;

    MinDegreeReordering mdr(ssm);

    cout << ssm.getElementOfMatrix(0,0) << endl;
    req = mdr.minDegReorder(ssm,perm);
    for(int i = 0; i < 3; i++){
        cout << req[i] << endl;
    }
    return 0;
}