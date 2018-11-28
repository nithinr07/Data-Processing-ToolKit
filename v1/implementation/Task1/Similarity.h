#include "../../Record.h"

#include <vector>
#include <cmath>

#ifndef SIMILARITY_H_
#define SIMILARITY_H_

class Similarity {
    private : Record _record1, _record2; 
    public : double compute_pairwise_similarity();
};

#endif // !SIMILARITY_H_