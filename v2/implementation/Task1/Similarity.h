#include "../../SymmetricSquareMatrix.h"
#include "Cluster.h"

#include <vector>
#include <cmath>

#ifndef SIMILARITY_H_
#define SIMILARITY_H_

class Similarity {
    private : 
    public : Similarity() {}
             double compute_pairwise_similarity(std::vector<double>, std::vector<double>);
             SymmetricSquareMatrix generate_similarity_matrix(std::vector<Cluster>);
};

#endif // !SIMILARITY_H_