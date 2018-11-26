#include <vector>
#include <string>

#ifndef RECORD_H_
#define RECORD_H_

class Record {
    private: int _numVariables;
             int _numNonNumericalVariables;
             int _numNumericalVariables;
             std::vector<std::string> _nonFeatureVector; 
             std::vector<double> _featureVector;
    public: Record(int y, int n, int N):_numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) {}
            Record(int, int, int, std::vector<std::string>, std::vector<double>);
            Record(const Record&);
            ~Record();
            void setRecord(std::string, int);
};

#endif // !RECORD_H_