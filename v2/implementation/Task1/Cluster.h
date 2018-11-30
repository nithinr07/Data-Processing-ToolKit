#include "../../Matrix.h"
#include "Vector.h"

#include <vector>
#include <map>

#ifndef CLUSTER_H_
#define CLUSTER_H_

class Cluster {
    private: int _id;
             std::vector<double> _centralValues;
             std::vector<Vector> _vectors; 
    public: Cluster() {}
            int get_id() { return _id; }
            void set_id(int id) { _id = id; }
            int get_size() { return _vectors.size(); }
            void set_centralValues(std::vector<double> centralValues) { _centralValues = centralValues; }
            void update_centralValue(int i, double value) { _centralValues[i] = value; }
            void add_vector(Vector data) { _vectors.push_back(data); }
    friend std::ostream& operator<<(std::ostream&, const Cluster&);

};

#endif // !CLUSTER_H_