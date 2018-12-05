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
    ifstream fin;
    ofstream fout;

    fout.open("./out.csv");
    // fin.open("../../../Lab-project-modified-datasets_20181114/AirQualityUCI/AirQualityUCI_mod.csv");
    fin.open("./in.csv");

    string line;
    vector<string> input_matrix;
    string init;
    int count = 0,x,y;
    vector<string> tmp;
    getline(fin, init);
    if(fin.is_open()) {
        while(getline(fin, line)) {
            input_matrix.push_back(line);
        }
    } else {
        cout << "Unable to open file" << endl;
        exit(0);
    }
    x = input_matrix.size();
    tmp = split(input_matrix[0],',');
    y = tmp.size();
    vector<Record> v;
    for(int i = 0;i < x;i++) {
        Record record(y, n, y - n);
        record.setRecord(input_matrix[i], n);
        v.push_back(record);
    }

    DistanceMatrix dm(x,y,v);

    fout<<dm;

    fout.close();
    fin.close();
    return 0;
}
