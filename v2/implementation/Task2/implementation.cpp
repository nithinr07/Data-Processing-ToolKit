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

using namespace std;
// template <typename T>
// Implementation of Matrix Class

Matrix::Matrix(int R , int C , std::vector<Record> _data ): _numRows(R), _numCols(C) {
  _data = *(new std::vector<Record>)  ;
  for (int i = 0 ; i < _numRows ; i++) {
    _data[i] = *(new Record()) ;
    }
}

Matrix::Matrix(): _numRows(0), _numCols(0) {
  _data = *(new std::vector<Record>)  ;
}

Matrix::~Matrix() {
    _data.clear();
  _numRows = 0 ; _numCols = 0 ;
}

Matrix::Matrix(Matrix& m) :
  _numRows(m._numRows), _numCols(m._numCols){
  _data = *(new std::vector<Record>)  ;
  for (int i = 0 ; i < _numRows ; i++) {
    _data[i] = *(new Record()) ;
    }
    
        
  for (int i = 0; i < _numRows; i++) 
      _data[i] = m._data[i];
}

void Matrix::addRecord(Record &record) {
    _data.push_back(record);
}

std::ostream& operator<< (std::ostream& os, Matrix& m)
 {

  int nr = m._numRows ;
  int nc = m._numCols ;
  os << nr << " " << nc << std::endl;
  for (int i = 0; i < nr; i++) {
      os << m._data[i]<< " " ;
  }
  return os;
}

std::ostream& operator<< (std::ostream &os, Record &r)
{
    for(auto i : r.getFeatureVector())
    {
        os << i << " ";
    }
    os << std::endl ;
    return os;
}

template<char delimiter>
std::istream& operator>>(std::istream& is, WordDelimitedBy<delimiter>& output)
{
   std::getline(is, output, delimiter);
   return is;
}

// Implementation of Record Class
vector<string> _split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
void Record::setRecord(std::string data, int n) {
    // std::istringstream iss(data);
    // std::vector<std::string> tokens{std::istream_iterator<WordDelimitedBy<';'>>{iss}, std::istream_iterator<WordDelimitedBy<';'>>{}}; 
    std::vector<std::string> tokens = _split(data,',');
    // cout<<tokens.size()<<" "<<data<<endl;
    for(int i = 0;i < n;i++) {
        _nonFeatureVector.push_back(tokens[i]);
    // printf("%s\n","here" );
    }
    for(int i = 0;i < _numNumericalVariables;i++) {
        _featureVector.push_back(stod(tokens[i + n]));
    }
}

Record::Record(int y, int n, int N, std::vector<std::string> nonFeatureVector, std::vector<double> featureVector):
        _numVariables(y), _numNonNumericalVariables(n), _numNumericalVariables(N) 
{
                _nonFeatureVector = *(new std::vector<std::string>(nonFeatureVector));
                _featureVector = *(new std::vector<double>(featureVector));

}

void Record::setFeatureVector(std::vector<double> &fv)
{
	_featureVector = fv;
}

bool Record::operator==(Record &r1)
{
	return (r1.getFeatureVector()==getFeatureVector())&&(r1.getNonFeatureVector()==getNonFeatureVector());

}
//---------------------Record End
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
	_distanceMatrix = *(new std::vector<std::vector<double>>(M));
	indices = *(new std::vector<int>(M));
	for(int i = 0; i < M ; i++)
	{
		_distanceMatrix[i] = *(new std::vector<double>(M));
	}
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
		// std::cout<< data[i]<<" "<<ind<<"\n";
		v[i] = v[i]/data.size(); 
	}	

	hypotheticalAverageRecord.setFeatureVector(v);
	std::sort(data.begin(), data.end(),NormalizedDisComp(hypotheticalAverageRecord));
	indexOrdering = *(new std::vector<int>());
	for(int i = 0; i < M ;i++)
	{
		indexOrdering.push_back(indices[i]);
	}
	for(int i = 0; i < M ;i++)
	{
		for(int j = 0; j < M ; j++)
		{
			_distanceMatrix[i][j] = EucledianDistance(data[i],data[j]);
		}
	}
}

// template <typename T>
DistanceMatrix::~DistanceMatrix()
{
	hypotheticalAverageRecord.~Record();
	this->~Matrix();
}
// template <typename T>
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

// int main(int argc, char const *argv[])
// {
// 	std::vector<Record> v;
// 	Record r1(3,0,3,{" "},{1.1,2.2,3.3});
// 	Record r2(3,0,3,{" "},{1.2,2.3,3.4});
// 	Record r3(3,0,3,{" "},{1.3,2.4,3.5});
// 	// v.push_back({1.1,2.2,3.3});
// 	// v.push_back({1.2,2.3,3.4});
// 	// v.push_back({1.3,2.4,3.5});
// 	v.push_back(r1);
// 	v.push_back(r2);
// 	v.push_back(r3);
// 	DistanceMatrix d(3,3,v);
// 	// d.printReordering();
// 	std::cout<<d;
//     return 0;
// }