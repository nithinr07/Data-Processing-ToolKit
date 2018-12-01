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
             std::vector<double> _values;

             
    public: Variable(){}
            void setVariable(int, Matrix);
            int get_varIndex() { return _varIndex; }
            void set_varIndex(int in) { _varIndex = in;}
            double get_variance() { return _variance; }
            void set_variance(double var) { _variance = var; }
            int get_numOfValues() { return _numOfValues; }
            int get_size() { return _values.size(); }
            void set_values(std::vector<double> values) { _values = values; }
            std::vector<double> get_values() { return _values; }

    friend std::ostream& operator<<(std::ostream&, const Variable&);


};

class varianceSort
{
    inline bool operator() (const Variable& v1, const Variable& v2)
    {
        return (v1.get_variance() < v2.get_variance());
    }
};

#endif //VARIABLE_H_

