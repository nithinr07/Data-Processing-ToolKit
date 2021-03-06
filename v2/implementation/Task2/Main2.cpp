#include "../../Matrix.h"
#include "../../Record.h"
#include "DistanceMatrix.h"
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

template<char delimiter>
istream& operator>>(istream &is, WordDelimitedBy<delimiter> &output)
{
    /*
        this part is pending!!
    */
    vector<string> v={};
    stringstream ss;
    string s;
    is >> s;
    while(getline(ss,s,delimiter))
    {
        v.push_back(s);
    }
    is.clear();
    for(auto i :v)
        is>>i;
   // getline(is, output, delimiter);
   return is;
}

int get_row_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<WordDelimitedBy<','>>{iss}, istream_iterator<WordDelimitedBy<','>>{}};
    return stoi(tokens.at(0));
}

int get_col_size(string init) {
    istringstream iss(init);
    vector<string> tokens{istream_iterator<WordDelimitedBy<','>>{iss}, istream_iterator<WordDelimitedBy<','>>{}};
    return stoi(tokens.at(1)); 
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int n = stoi(argv[1]);
    ifstream inputFile;

    ofstream fout;
    fout.open("out.csv");
    // inputFile.open("../../../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI_mod.csv");
    inputFile.open("./in.csv");
    string line;
    vector<string> input_matrix;
    string init;
    getline(inputFile, init);
    int count = 0;
    if(inputFile.is_open()) {
        while(getline(inputFile, line)) {
            input_matrix.push_back(line);
            // printf("%s\n","------" );
            std::cout<<line<<std::endl;
            
        }
        // inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(0);
    }
    int x = input_matrix.size();
    vector<string> tmp=split(input_matrix[0],',');
    int y = tmp.size();
    vector<Record> v ={};
    for(int i = 0;i < x;i++) {
        Record record(y, n, y - n);
    // printf("%d %d\n",x,y );
        record.setRecord(input_matrix[i], n);
        v.push_back(record);
        // dm.Matrix::addRecord(record);
    }
    DistanceMatrix dm(x,y,v);

    fout<<dm;
    fout.close();
    inputFile.close();
    return 0;
}
