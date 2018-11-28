#include <vector>
#include <map>

#include "Cluster.h"

#ifndef K_MEANS_H_
#define K_MEANS_H_

class KMeans {
    private: int K;
             std::vector<Cluster> clusters;
             std::map<int, double> centroids;
    public: KMeans();
            void compute_centroids();
            void process();
};

#endif // !K_MEANS_H_
