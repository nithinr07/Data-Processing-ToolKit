#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include <vector>

#ifndef SIMILARITY_MATRIX_H_
#define SIMILARITY_MATRIX_H_

class SimilarityMatrix : public SymmetricSquareMatrix{
    private: 
    public: SimilarityMatrix(std::vector<std::vector<double>>data):SymmetricSquareMatrix(data) {}
            void generate_matrix(Matrix dataSet);
    friend std::ostream& operator<< (std::ostream &, const SimilarityMatrix &);
};

#endif // !SIMILARITY_MATRIX_H_