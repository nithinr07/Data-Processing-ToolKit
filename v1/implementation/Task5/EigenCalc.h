#include "../../SymmetricSquareMatrix.h"

#include<iostream>
#include<vector>
#include <math.h>
using namespace std;

#ifndef EigenCalc_H
#define EigenCalc_H

class EigenCalc {
    public:
        // constructor
        EigenCalc(std::vector <std::vector <double> > data);

        // destructor
        ~EigenCalc() {};

        // copy constructors
        EigenCalc(const EigenCalc&);

        // eigen vector calculation
        void eig(int p);
        // print the eigen values and vectors
        friend ostream& operator<<( ostream &os, EigenCalc const &ec);


    protected:
        // calculation norm
        vector<double> norm(vector<double>);
        // orthogonolize
        vector<double> orthogonalize(vector<double> ,vector<double>);



    private:
        SymmetricSquareMatrix ssm;
        std::vector <std::vector<double> > _eigen_vectors;
        std::vector <double> _eigen_values;






};

#endif