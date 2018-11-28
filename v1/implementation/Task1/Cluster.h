#include "Vector.h"

#ifndef CLUSTER_H_
#define CLUSTER_H_

class Cluster {
    private: int id;
             std::vector<double> centralValues;
             std::vector<Vector> vectors; 
    public: Cluster();
};

#endif // !CLUSTER_H_