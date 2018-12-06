#include "../../Record.h"
#include "../../Matrix.h"

#include <iostream>
#include <vector>

#ifndef VARIABLE_H_
#define VARIABLE_H_ 

class Variable
{
    private: int _varIndex;
             int _numOfValues;
             double _variance;
             double _mean;
             std::vector<double> _values;

             
    public: 
            Variable(){}
            Variable(int n){_varIndex = n; }
            void setVariable(int, Matrix&);
            int get_varIndex() { return _varIndex; }
            void set_varIndex(int in) { _varIndex = in;}
            double get_variance() const { return _variance; }
            void set_variance(double var) { _variance = var; }
            double get_mean() const { return _mean; }
            void set_mean(double x) { _mean = x; }
            void set_numOfValues(int n){ _numOfValues = n; }
            int get_numOfValues() { return _numOfValues; }
            int get_size() { return _values.size(); }
            void set_values(std::vector<double> values) { _values = values; }
            std::vector<Variable> normalizedVariables(std::vector<Variable>);
            std::vector<double> get_values() { return _values; }




    friend std::ostream& operator<<(std::ostream&, const Variable&);


};

bool operator<(const Variable &v1, const Variable &v2);

#endif //VARIABLE_H_

