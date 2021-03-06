// #include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <vector>
#include<algorithm>
#include <map>

#ifndef DistanceMatrix_H_
#define DistanceMatrix_H_

// template<typename T>
class DistanceMatrix : Matrix
{
private:
	Record hypotheticalAverageRecord;
	// std::map<Record,int> indices;
	std::vector<int> indexOrdering,indices;
	std::vector<std::vector<double>> _distanceMatrix;
public:
    DistanceMatrix(){}
    ~DistanceMatrix();
    DistanceMatrix(int M,int N,std::vector<Record> data);
    Record getAvgRecord()
    {
    	return hypotheticalAverageRecord;
    }
   	// outputs on to terminal
    void printReordering();
    /*
		outputs to a csv file
    */
    void printDistanceMatrix();
	friend std::ostream& operator<< (std::ostream &, DistanceMatrix &) ;
};
double EucledianDistance( Record &x, Record &y);

/*
comparator class 
*/
class NormalizedDisComp{

	public:
	    double Normalize(double Min,double Max,double Value)
    	{
    		return (Value - Min)/(Max - Min);
    	}
    	Record _avg;
		NormalizedDisComp(Record &avg)
		{
			_avg = avg;
		}
		~NormalizedDisComp(){}
		bool operator()(Record &r1,Record &r2);
};

#endif // DistanceMatrix_H_
