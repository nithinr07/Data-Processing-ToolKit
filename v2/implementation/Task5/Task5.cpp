#include "../../SymmetricSquareMatrix.h"

#include<iostream>
#include<vector>
#include <math.h>
using namespace std;

vector<double> norm(vector<double> xrand) {
    int n = xrand.size();
    vector <double> xnew(n);
    // getting the norm of eigen vector
    double normal = 0;
    for(int i = 0;i < n; i++){
        normal += xrand[i]*xrand[i];
    }
    normal = sqrt(normal);

    // normalisation
    for(int i = 0;i < n; i++){
        xnew[i] = xrand[i]/normal;
    }
    return xnew;
}

vector<double> orthogonalize(vector<double> xcurr,vector<double> xprev) {
    int n = xcurr.size();
    
    double normal = 0;
    vector <double> xnew(n);
    
    for(int i = 0; i < n; i++) {
        normal += xcurr[i]*xprev[i]; 
    }

    for(int i = 0; i < n; i++) {
        xnew[i] = xcurr[i] - normal*xprev[i]; 
    }


    return xnew;

}

void eig(vector <vector <double> > A,int p,vector <vector <double> > &eigen_vectors ,vector<double> &eigen_values) {
    int n = A.size();

    const double E = 0.0001;
    double condition;
    double normal,normalearlier;


    // for loop for finding all the eigen values and vectors
    for(int loop = 0; loop < p; loop++) {
        
        
        vector <double> xrand(n); // random vector init
        for(int i = 0;i < n; i++) {
            xrand[i] = 1;
        }

        xrand = norm(xrand);
        vector <double> xcurr(n); 
  
        do {
            normalearlier = normal;
            normal = 0;
            // random vector init
            
            for(int i = 0;i < n; i++){
                xcurr[i] = xrand[i];
            }

            for(int j = 0 ; j <= loop - 1; j++) {
                vector <double> xprev = eigen_vectors[j];
                xcurr = orthogonalize(xcurr,xprev);
            }

            // 
            for(int i = 0;i < n; i++) {
                xrand[i] = 0;
                for(int j = 0; j < n; j++) {
                    xrand[i] += A[i][j]*xcurr[j];
                }
                    
            }

            for(int i = 0;i < n; i++){
                normal += xrand[i]*xrand[i];
            }
            normal = sqrt(normal);
            
            xrand = norm(xrand);


            for(int i = 0; i < n; i++) {
                condition += xcurr[i]*xrand[i];
            }



        }while(fabs(normal - normalearlier) > 0.000001);

    eigen_vectors.push_back(xrand);
    eigen_values.push_back(normal);

    // for(int i = 0; i < n; i++) {
    //             cout<< xrand[i] << " ";
    //         }
    //         cout <<endl;

    //         cout << normal << endl;

    } // end of finding all eigen values and vectors
    
};

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
    SymmetricSquareMatrix ssm(v);

    eig(ssm.get_data(),p,eigen_vectors,eigen_values);

    for(int i = 0; i < eigen_vectors.size(); i++) {
        for(int j = 0; j < eigen_vectors[i].size(); j++) {
            cout << eigen_vectors[i][j] << " " ;
        }
        cout << endl;
    }

    for(int i = 0; i < eigen_values.size(); i++) {
        cout << eigen_values[i] << " ";
    }

    cout << endl;


    return 0;
}
