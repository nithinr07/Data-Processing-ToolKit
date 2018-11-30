#include <vector>
#include <string>

#ifndef RECORD_H_
#define RECORD_H_
// template<typename T>
class Record {
    private: int _numVariables;
             int _numNonNumericalVariables;
             int _numNumericalVariables;
             std::vector<std::string> _nonFeatureVector; 
             std::vector<double> _featureVector;
    public: 
            Record(){
                printf("%s\n","called" );
                _nonFeatureVector = *(new std::vector<std::string>);
                _featureVector = *(new std::vector<double>);
            }
            Record(int y, int n, int N):_numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) {
                _nonFeatureVector = *(new std::vector<std::string>());
                _featureVector = *(new std::vector<double>());
            }
            Record(int, int, int, std::vector<std::string>, std::vector<double>);
            // Record(const Record&);
            // ~Record();
            void setRecord(std::string, int);
            int getNumNumericVariables() { return _numNumericalVariables; }
            int getNumNonNumericVariables() { return _numNonNumericalVariables; }
            int getNumVariables() { return _numVariables; }
            void setFeatureVector(std::vector<double> &);
            std::vector<double> getFeatureVector() { return _featureVector; }
            std::vector<std::string> getNonFeatureVector() { return _nonFeatureVector; }
            bool operator==(Record &r1);
            friend std::ostream& operator<< (std::ostream &, Record &) ;

};

#endif // !RECORD_H_