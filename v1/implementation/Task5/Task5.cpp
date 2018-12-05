#include "EigenCalc.h"

#include<iostream>
#include<vector>
#include <math.h>
using namespace std;


int main() {
    int n,p;
    cin >>  n >> p;
    vector <vector<double> > eigen_vectors;
    vector <double> eigen_values;

    vector<vector<double> > v(n, vector<double>(n,1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }
    EigenCalc ec(v);
    ec.eig(p);
    cout << ec;
}
