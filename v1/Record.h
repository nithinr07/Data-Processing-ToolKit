#include <vector>
#include <string>

#ifndef RECORD_H_
#define RECORD_H_
class Record {
    protected: int _numVariables;
             int _numNonNumericalVariables;
             int _numNumericalVariables;
             std::vector<std::string> _nonFeatureVector; 
             std::vector<double> _featureVector;
    public: 

            Record()
            {
                _nonFeatureVector = std::vector<std::string>();
                _featureVector = std::vector<double>();
            }

            ~Record() {}

            Record(int y, int n, int N):_numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) 
            {
                _nonFeatureVector = std::vector<std::string>();
                _featureVector = std::vector<double>();
            }
            Record(int, int, int, std::vector<std::string>, std::vector<double>);


            Record(const Record&);
            // ~Record();

            /*
                set functions
            */
            void setRecord(std::string, int);
            void setFeatureVector(std::vector<double> &);
            void addToFeatureVector(double value) { _featureVector.push_back(value); }
            /*
                get functions
            */
            int getNumNumericVariables() { return _numNumericalVariables; } 
            int getNumNonNumericVariables() { return _numNonNumericalVariables; }
            int getNumVariables() { return _numVariables; } 
            std::vector<double> getFeatureVector() { return _featureVector; }
            std::vector<std::string> getNonFeatureVector() { return _nonFeatureVector; }

            /*
                operators overloaded
            */
            bool operator==(Record &r1);
            void operator=(const Record &r);

            friend std::ostream& operator<< (std::ostream &, Record &) ;

};

#endif // !RECORD_H_
