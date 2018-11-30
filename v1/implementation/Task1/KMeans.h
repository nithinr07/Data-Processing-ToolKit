#include "Cluster.h"
#include "../../Matrix.h"

#include <vector>
#include <map>

#ifndef K_MEANS_H_
#define K_MEANS_H_

class KMeans {
    private: int _K;
             Matrix _dataSet;
             std::vector<Cluster> _clusters;
             std::map<int, std::vector<double>> _centroids;
    public: KMeans(int, Matrix);
            void compute_centroids();
            void process(int);
            void add_cluster(Cluster cluster) { _clusters.push_back(cluster); }
            void update_centroid(int, int, std::vector<double>);
            Cluster get_cluster_by_id(int);
};

#endif // !K_MEANS_H_
