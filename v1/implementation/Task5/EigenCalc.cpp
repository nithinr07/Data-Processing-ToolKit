#include "EigenCalc.h"

// constructor
EigenCalc::EigenCalc(std::vector <std::vector <double> > data) {
    ssm = SymmetricSquareMatrix(data);
}


// copy constructor
// EigenCalc::EigenCalc(const EigenCalc& ec) {
//     ssm = SymmetricSquareMatrix(ec.ssm);
//     _eigen_vectors = ec._eigen_vectors;
//     _eigen_values = ec._eigen_values;
    
// };


// eigen vector calculation
void EigenCalc::eig(int p) {
        int n = ssm.getNumRows();

    const double E = 0.0001;
    double condition;
    double normalisation,normearlier;


    // for loop for finding all the eigen values and vectors
    for(int loop = 0; loop < p; loop++) {
        
        
        vector <double> xrand(n); // random vector init
        for(int i = 0;i < n; i++) {
            xrand[i] = 1;
        }

        xrand = norm(xrand);
        vector <double> xcurr(n); 
  
        do {
            normearlier = normalisation;
            normalisation = 0;
            
            for(int i = 0;i < n; i++){
                xcurr[i] = xrand[i];
            }

            for(int j = 0 ; j <= loop - 1; j++) {
                vector <double> xprev = _eigen_vectors[j];
                xcurr = orthogonalize(xcurr,xprev);
            }

            for(int i = 0;i < n; i++) {
                xrand[i] = 0;
                for(int j = 0; j < n; j++) {
                    xrand[i] += ssm.getElementOfMatrix(i,j)*xcurr[j];
                }
                    
            }

            for(int i = 0;i < n; i++){
                normalisation += xrand[i]*xrand[i];
            }
            normalisation = sqrt(normalisation);
            
            xrand = norm(xrand);


            for(int i = 0; i < n; i++) {
                condition += xcurr[i]*xrand[i];
            }



        }while(fabs(normalisation - normearlier) > 0.000001);

    _eigen_vectors.push_back(xrand);
    _eigen_values.push_back(normalisation);

    } // end of finding all eigen values and vectors
};


// calculation norm
vector<double> EigenCalc::norm(vector<double> xrand) {
    int n = xrand.size();
    vector <double> xnew(n);
    // getting the norm of eigen vector
    double normalisation = 0;
    for(int i = 0;i < n; i++){
        normalisation += xrand[i]*xrand[i];
    }
    normalisation = sqrt(normalisation);

    // normalisation
    for(int i = 0;i < n; i++){
        xnew[i] = xrand[i]/normalisation;
    }
    return xnew;

};

// calculation to remove the previous largesteigen value
vector<double> EigenCalc::orthogonalize(vector<double> xcurr,vector<double> xprev) {
    int n = xcurr.size();
    
    double normalisation = 0;
    vector <double> xnew(n);

    for(int i = 0; i < n; i++) {
        normalisation += xcurr[i]*xprev[i]; 
    }

    for(int i = 0; i < n; i++) {
        xnew[i] = xcurr[i] - normalisation*xprev[i]; 
    }

    return xnew;
};
// printing 
ostream& operator<<( ostream &os, EigenCalc const &ec) {
    os << "Eigen Vectors" << endl;
    for(int i = 0; i < ec._eigen_vectors.size(); i++) {
        for(int j = 0; j < ec._eigen_vectors[i].size(); j++) {
            os << ec._eigen_vectors[i][j] << " " ;
        }
        os << endl;
    }
    os << "Eigen Values" << endl;
    for(int i = 0; i < ec._eigen_values.size(); i++) {
        os << ec._eigen_values[i] << " ";
    }

    os << endl;


    return os;
}
