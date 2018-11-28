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
             std::map<int, vector<double>> _centroids;
    public: KMeans(int, Matrix);
            void compute_centroids();
            void process();
};

#endif // !K_MEANS_H_
