#include "../../Matrix.h"
#include "Vector.h"

#ifndef CLUSTER_H_
#define CLUSTER_H_

class Cluster {
    private: int _id;
             std::vector<double> _centralValues;
             std::vector<Vector> _vectors; 
    public: Cluster() {}
            void set_id(int id) { _id = id; }
            void set_centralValues(std::vector<double> centralValues) { _centralValues = centralValues; }
};

#endif // !CLUSTER_H_