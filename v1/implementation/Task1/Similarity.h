#include <vector>
#include <cmath>

#ifndef SIMILARITY_H_
#define SIMILARITY_H_

class Similarity {
    private : 
    public : Similarity() {}
             double compute_pairwise_similarity(std::vector<double>, std::vector<double>);
};

#endif // !SIMILARITY_H_