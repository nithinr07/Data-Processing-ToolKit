#include<iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "ReorderingSSM.h"
using namespace std;

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
for(int i=0;i<v.size();i++)out<<v[i]<<' ';return out;}

vector<double> CommaSeparation(string init){
    stringstream ss(init);
    vector<double> token;
    double i;
    while(ss >> i){
        token.push_back(i);
        if(ss.peek() == ',') ss.ignore();
    }
    return token;
}


int main(){
    int num_rows;
    vector<vector<double>> data;
    // for(int i=0;i<num_rows;i++){
    //     vector <double> datai;
    //     for(int j=0;j<num_rows;j++) datai.push_back(0.8);
    //     data.push_back(datai);
    // }

    // data[0] = {0.0,0.78,0.79,0.8,0.23};
    // data[1] = {0.9,0.0,0.43,0.771,0.702};
    // data[2] = {0.82,0.0,0.6,0.79,0.34};
    // data[3] = {0.8,0.8,0.8,0.0,0.8};
    // data[4] = {0.54,0.97,0.12,0.78,0.0};  



    string line;
    ifstream  input;
    input.open("../Task1/similarity.csv");
    if(input.is_open()){
        while(getline(input, line)) {
            data.push_back(CommaSeparation(line));
        }
        input.close();
    } 
    else{
        cout << "Unable to open file" << endl;
        exit(0);
    }
    SymmetricSquareMatrix matrix(data);
    ReorderingSSM m(matrix);
    vector<int> r = m.ReverseCuthillMckee();
    cout << r << endl;
    return 0;
}