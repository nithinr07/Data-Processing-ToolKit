#include <vector>

#ifndef RECORD_H_
#define RECORD_H_

class Record {
    private: int _numVariables;
             int _numNumericalVariables;
             int _numNonNumericalVariables;
             std::vector<double> _featureVector; 
    public: Record(int, int, int, std::vector<double>);
            Record(const Record&);
            ~Record();
};

#endif // !RECORD_H_