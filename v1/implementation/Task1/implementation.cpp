#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "Similarity.h"
#include "SimilarityMatrix.h"
#include "WordDelimitedBy.h"
#include "KMeans.h"
#include "Cluster.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <vector>

template<char delimiter>
std::istream& operator>>(std::istream& is, WordDelimitedBy<delimiter>& output)
{
   std::getline(is, output, delimiter);
   return is;
}

KMeans::KMeans(int K, Matrix dataSet):_K(K), _dataSet(dataSet) {}

double Similarity::compute_pairwise_similarity(std::vector<double> A, std::vector<double> B) {
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
        for(unsigned int i = 0u; i < A.size(); ++i) {
            dot += A[i] * B[i] ;
            denom_a += A[i] * A[i];
            denom_b += B[i] * B[i];
        }
    return dot / (sqrt(denom_a) * sqrt(denom_b));    
}

void SimilarityMatrix::generate_matrix(Matrix dataSet) {
    Similarity cosine_similarity;
    for(int i = 0;i < dataSet.numRows();i++) {
        for(int j = 0;j < dataSet.numRows();j++) {
            double value = cosine_similarity.compute_pairwise_similarity(dataSet.getData(i).getFeatureVector(), dataSet.getData(j).getFeatureVector());
            _data[i][j] = value;
        } 
    }
}

void KMeans::compute_centroids() {
    // std::cout << _dataSet;
    int count = 0;
    while(count != _K) {
        int id = (int)rand() % (_dataSet.numRows());
        // std::cout << id << std::endl;
        if(_centroids.count(id) == 0) {
            std::vector<double> entry = _dataSet.getData(id).getFeatureVector();
            _centroids[id] = entry;
            count++;
            // Cluster cluster(entry);
            Cluster cluster;
            cluster.set_id(id);
            for(int i = 0;i < entry.size();i++) {
                // std::cout << entry[i] << " ";
                cluster.set_centralValues(entry[i]);
            }
            // std::cout << std::endl;
            add_cluster(cluster);
        }
    }
}

Cluster& KMeans::get_cluster_by_id(int id) {
    // Cluster cluster;
    for(int i = 0;i < _clusters.size();i++) {
        if(_clusters[i].get_id() == id) 
            return _clusters[i];
    }
    // return cluster;
    
}

void KMeans::update_centroid(int id, int clusterSize, std::vector<double> entry) {
    std::map<int, std::vector<double>>::iterator it;
    // std::vector<double>::iterator it1;
    it = _centroids.find(id);
    std::vector<double> currentCentroid = it -> second;
    for(int i = 0;i < entry.size();i++) {
        double sum = 0.0;
        double average = 0.0;
        sum = currentCentroid[i] * (clusterSize - 1) + entry[i];
        average = sum / clusterSize;
        currentCentroid[i] = average;
        get_cluster_by_id(id).update_centralValue(i, average);
        // cluster.update_centralValue(i, average);
        // std::cout << get_cluster_by_id(id);
    }
}

void KMeans::process() {
    compute_centroids();
    Similarity cosine_similarity;
    int recordNum = 0;
    for(int i = 0;i < _dataSet.numRows();i++) {
        double dissimilarity = 1.0;
        int id = -1;
        recordNum = -1;
        std::map<int, std::vector<double>>::iterator it;
        for(it = _centroids.begin(); it != _centroids.end(); it++) {
            double value = 1.0 - cosine_similarity.compute_pairwise_similarity(_dataSet.getData(i).getFeatureVector(), it -> second);
            // std::cout << value << std::endl;
            if(dissimilarity > value) {
                dissimilarity = value;
                id = it -> first;
                recordNum = i;
            }
        }
        for(int j = 0;j < _clusters.size();j++) {
            // std::cout << id << "   " << _clusters[j].get_id() << std::endl;
            if(id == _clusters[j].get_id()) {
                // _dataSet.getData(recordNum).addToFeatureVector((double)j);
                Vector data(_dataSet.getData(i));
                data.set_cluster_id(j);
                _clusters[j].add_vector(data);
                update_centroid(id, _clusters[j].get_size(), data.getFeatureVector());
                break;
            }
        }
    }
    // std::cout << _dataSet; 
    // for(int i = 0;i < maxIterations -1;i++) {
    //     for(int i = 0;i < _dataSet.numRows();i++) {
    //         int id = 
    //         std::map<int, std::vector<double>>::iterator it;
    //         for(it = _centroids.begin(); it != _centroids.end(); it++) {
    //             double dissimilarity1 = 1 - cosine_similarity.compute_pairwise_similarity(_dataSet.getData(i).getFeatureVector(), it -> second);

    //         }
    //     }
    // }
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
  if ( !v.empty() ) {
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(os, ","));
  }
  return os;
}

// std::ostream& operator<<(std::ostream& os, Matrix& m) {
//     for(int i = 0;i < m._numRows;i++) {
//         os << m.getData(i).getNonFeatureVector() << m.getData(i).getFeatureVector();
//         os << std::endl;
//     }
//     return os;
// }

std::ostream& operator<<(std::ostream& os,const SimilarityMatrix& sm) {
    for(int i = 0;i < sm._size;i++) {
        for(int j = 0;j < sm._size;j++) {
            if(j < sm._size-1)
                os << sm._data[i][j] << ",";
            else
                os << sm._data[i][j];
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    std::vector<double> newVec(vector._featureVector.begin(), vector._featureVector.begin() + vector._featureVector.size() - 1);
    os << vector._nonFeatureVector << newVec << vector._clusterId;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Cluster& cluster) {
    for(int i = 0;i < cluster._vectors.size();i++) {
        if(i < cluster._vectors.size()-1)
            os << cluster._vectors[i] << std::endl;
        else
            os << cluster._vectors[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const KMeans& kmeans) {
    for(int i = 0;i < kmeans._K;i++) {
        if(i < kmeans._K - 1)
            os << kmeans._clusters[i] << std::endl;
        else
            os << kmeans._clusters[i];
    }
    return os;
}