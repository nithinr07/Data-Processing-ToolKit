#include "../../Matrix.h"
#include "DistanceMatrix.h"
#include "../../Record.h"
#include "../Task1/WordDelimitedBy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <bits/time.h>
#include <string>
#include <cstdlib>

// using namespace std;
double EucledianDistance(Record &x, Record &y)
{
	double ans = 0.0;
	for(int i = 0; i < x.getNumNumericVariables() ; i++)
	{
		ans+=(x.getFeatureVector()[i]-y.getFeatureVector()[i])*(x.getFeatureVector()[i]-y.getFeatureVector()[i]);
	}
	ans = pow(ans,1.0/2);
	return ans;
}
double Normalize(double Min,double Max,double Value)
{
	return (Value - Min)/(Max - Min);
}
// template <typename T>
bool NormalizedDisComp::operator()(Record &r1,Record &r2)
{
	double val1 = EucledianDistance(r1,_avg);
	double val2 = EucledianDistance(r2,_avg);
	val1 = Normalize(0.0,1.0,val1);	
	val2 = Normalize(0.0,1.0,val2);	
	return val1<val2;
}

// template<typename T>
DistanceMatrix::DistanceMatrix(int M,int N,std::vector<Record> data) : Matrix(M,N,data)
{
	indices = std::vector<int>(M);
	indexOrdering = std::vector<int>();
	_distanceMatrix = std::vector<std::vector<double>>(M);
	for(int i = 0; i < M ; i++)
		_distanceMatrix[i] = std::vector<double>(M);

	if(data.size()>0)	
	hypotheticalAverageRecord = *(new Record(data[0].getNumVariables(),data[0].getNumNonNumericVariables(),data[0].getNumNumericVariables()));

	std::vector<double> v;
	for(int i = 0; i < data.size(); i++)
	{
		v.push_back(0.0);
		for(int j = 0 ; j < data[i].getNumNumericVariables() ; j++)
		{
			v[i] += data[i].getFeatureVector()[j];
		}	
	}

	for(int i = 0; i < data.size(); i++)
	{
		/*
			storing the indices
		*/
		int ind = 0;
		while(!(data[i] == data[ind])) ind++;
		indices[i] = ind;

		v[i] = v[i]/data.size(); 
	}	

	hypotheticalAverageRecord.setFeatureVector(v);
	std::sort(data.begin(), data.end(),NormalizedDisComp(hypotheticalAverageRecord));
	
	for(int i = 0; i < M ;i++)
		indexOrdering.push_back(indices[i]);

	for(int i = 0; i < M ;i++)
	{
		for(int j = 0; j < M ; j++)
		{
			_distanceMatrix[i][j] = EucledianDistance(data[i],data[j]);
		}
	}
}

void DistanceMatrix::printReordering()
{
	for(int i : indexOrdering)
	{
		std::cout << i << " ";
	}
	std::cout<<std::endl;
}

std::ostream& operator<< (std::ostream &os, DistanceMatrix &dm) 
{
	for(auto i : dm._distanceMatrix)
	{
		for(auto j : i)
		{
			os << j <<" ";
		}
		os << std::endl;
	}
	return os;
}
/*

int main(int argc, char const *argv[])
{
	std::vector<Record> v;
	Record r1(3,0,3,{" "},{1.1,2.2,3.3});
	Record r2(3,0,3,{" "},{1.2,2.3,3.4});
	Record r3(3,0,3,{" "},{1.3,2.4,3.5});
	// v.push_back({1.1,2.2,3.3});
	// v.push_back({1.2,2.3,3.4});
	// v.push_back({1.3,2.4,3.5});
	v.push_back(r1);
	v.push_back(r2);
	v.push_back(r3);
	DistanceMatrix d(3,3,v);
	// d.printReordering();
	std::cout<<d;
    return 0;
}

*/