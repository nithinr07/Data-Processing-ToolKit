#include<iostream>
#include <queue>
#include "ReorderingSSM.h"
#include<bits/stdc++.h>
using namespace std;

vector<double> globalDegree;

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

vector<int> ReorderingSSM::CuthillMchee(){
    vector<double> degrees = degreeGenerator();
    ::globalDegree = degrees;
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