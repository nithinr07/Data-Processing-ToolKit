#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include <vector>

#ifndef SIMILARITY_MATRIX_H_
#define SIMILARITY_MATRIX_H_

class SimilarityMatrix : public SymmetricSquareMatrix{
    private: int _size;
    public: SimilarityMatrix(std::vector<std::vector<double>>vec, int size):SymmetricSquareMatrix(vec), _size(size) {
                for(int i = 0;i < _size;i++) {
                    for(int j = 0;j < _size;j++) {
                        _data[i].push_back(0);
                    }
                }
            }
    // SimilarityMatrix(std::vector<std::vector<double>>data, int size):SymmetricSquareMatrix(data), _size(size) {}
            void generate_matrix(Matrix dataSet);
    friend std::ostream& operator<< (std::ostream &, const SimilarityMatrix &);
};

#endif // !SIMILARITY_MATRIX_H_