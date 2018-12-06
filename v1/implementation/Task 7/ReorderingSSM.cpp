#include<iostream>
#include <queue>
#include "ReorderingSSM.h"
#include<bits/stdc++.h>
using namespace std;

vector<double> globalDegree;

//constructor and Destructor
ReorderingSSM::ReorderingSSM(SymmetricSquareMatrix _matrix):_matrix(_matrix){

}
ReorderingSSM::~ReorderingSSM(){

}
//Copy constructor
ReorderingSSM::ReorderingSSM(ReorderingSSM & old_matrix){
    if(_matrix.getNumRows() == old_matrix.getNumRows()){
        for(int i=0;i<old_matrix.getNumRows();i++){
            for(int j=0;j<old_matrix.getNumRowsColums();j++){
                _matrix.setElementOfMatrix(i,j,old_matrix.getMatrixDataAt(i,j));
            }
        }
    }
}
//methods of class  
void ReorderingSSM::sparsification(){
    for(int i=0;i<_matrix.getNumRows();i++){
        for(int j=0;j<_matrix.getNumColums();j++){
            if(_matrix.getElementOfMatrix(i,j) < 0.75) _matrix.setElementOfMatrix(i,j,0.0);
            else _matrix.setElementOfMatrix(i,j,1.0);
        }
    }
}
vector<double> ReorderingSSM::degreeGenerator(){
    vector<double> degrees;
    for (int i = 0; i < _matrix.getNumRows(); i++){
        double count = 0;
        for (int j = 0; j < _matrix.getNumColums(); j++){
            count += _matrix.getElementOfMatrix(i, j);
        }
        degrees.push_back(count);
    }
    return degrees;
}

int findIndex(vector<pair<int,double>> a,int x){
    for(int i=0;i<a.size();i++) if(a[i].first == x) return i;
    return -1;
}

bool compareDegree(int i,int j){
    return ::globalDegree[i] - ::globalDegree[j];
}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
for(int i=0;i<v.size();i++)out<<v[i]<<' ';return out;}

vector<int> ReorderingSSM::CuthillMckee(){
    vector<double> degrees = degreeGenerator();
    ::globalDegree = degrees;
    cout << degrees << endl;
    sparsification();
    queue<int> Q;
    vector<int> R;
    vector<pair<int,double>> notVisited;
    for(int i=0;i<degrees.size();i++) notVisited.push_back(make_pair(i,degrees[i]));
    while(notVisited.size()){
        int minNodeIndex=0;
        for(int i=0;i<notVisited.size();i++) if(notVisited[i].second < notVisited[minNodeIndex].second) minNodeIndex = i;
        Q.push(notVisited[minNodeIndex].first);
        notVisited.erase(notVisited.begin() + findIndex(notVisited, notVisited[Q.front()].first));
        while(!Q.empty()){
            vector<int> toSort;
            for(int i=0;i<_matrix.getNumColums();i++){
                if(i!=Q.front() && _matrix.getElementOfMatrix(Q.front(), i) == 1 && findIndex(notVisited, i)!=-1){
                    toSort.push_back(i);
                    notVisited.erase(notVisited.begin() + findIndex(notVisited, i));
                }
            }
            sort(toSort.begin(), toSort.end(), compareDegree);
            for(int i=0;i<toSort.size();i++) Q.push(toSort[i]);
            R.push_back(Q.front());
            Q.pop();
        }
    }
    return R;
}


vector<int> ReorderingSSM::ReverseCuthillMckee(){
    vector<int> cuthill = CuthillMckee();
    int n = cuthill.size();
    if(n%2 == 0) n -= 1;
    n = n/2;
    for(int i=0;i<=n;i++){
        int j = cuthill[cuthill.size()-1-i];
        cuthill[cuthill.size()-1-i] = cuthill[i];
        cuthill[i] = j;
    }
    return cuthill;
}