#include "../../SymmetricSquareMatrix.h"
#include "../../Matrix.h"
#include "../../Record.h"
#include "Similarity.h"
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

void Record::setRecord(std::string data, int n) {
    std::istringstream iss(data);
    std::vector<std::string> tokens{std::istream_iterator<WordDelimitedBy<','>>{iss}, std::istream_iterator<WordDelimitedBy<','>>{}}; 
    for(int i = 0;i < n;i++) {
        _nonFeatureVector.push_back(tokens[i]);
    }
    for(int i = 0;i < _numNumericalVariables;i++) {
        _featureVector.push_back(stod(tokens[i + n]));
    }
}

void Matrix::addRecord(Record &record) {
    _data.push_back(record);
}

double Similarity::compute_pairwise_similarity(std::vector<double> A, std::vector<double> B) {
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
        for(unsigned int i = 0u; i < A.size(); ++i) {
            dot += A[i] * B[i] ;
            denom_a += A[i] * A[i];
            denom_b += B[i] * B[i];
        }
    return dot / (sqrt(denom_a) * sqrt(denom_b));    
}

SymmetricSquareMatrix Similarity::generate_similarity_matrix(std::vector<Cluster> clusters) {
    // SymmetricSquareMatrix ssm;
}

void KMeans::compute_centroids() {
    int count = 0;
    while(count != _K) {
        int id = rand() % (_dataSet.numRows() + 1);
        if(_centroids.count(id) == 0) {
            std::vector<double> entry = _dataSet.getData(id).getFeatureVector();
            _centroids[id] = entry;
            count++;
            Cluster cluster;
            cluster.set_id(id);
            cluster.set_centralValues(entry);
            add_cluster(cluster);
        }
    }
}

Cluster KMeans::get_cluster_by_id(int id) {
    Cluster cluster;
    for(int i = 0;i < _clusters.size();i++) {
        if(_clusters[i].get_id() == id) 
            cluster = _clusters[i];
    }
    return cluster;
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
        Cluster cluster = get_cluster_by_id(id);
        cluster.update_centralValue(i, average);
    }
}

void KMeans::process(int maxIterations) {
    Similarity cosine_similarity;
    for(int i = 0;i < _dataSet.numRows();i++) {
        double dissimilarity = 0.0;
        int id = -1;
        std::map<int, std::vector<double>>::iterator it;
        for(it = _centroids.begin(); it != _centroids.end(); it++) {
            double value = 1.0 - cosine_similarity.compute_pairwise_similarity(_dataSet.getData(i).getFeatureVector(), it -> second);
            if(dissimilarity > value) {
                dissimilarity = value;
                id = it -> first;
            }
        }
        for(int j = 0;j < _clusters.size();j++) {
            if(id == _clusters[j].get_id()) {
                Vector data(_dataSet.getData(i));
                data.set_cluster_id(id);
                _clusters[j].add_vector(data);
                update_centroid(id, _clusters[j].get_size(), data.getFeatureVector());
            }
        }
    }
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
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << vector._clusterId;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Cluster& cluster) {
    os << cluster._id << "\t" << cluster._vectors << "\t" << cluster._centralValues;
    return os;
}

std::ostream& operator<<(std::ostream& os, const KMeans& kmeans) {
    for(int i = 0;i < kmeans._K;i++) {
        os << kmeans._clusters[i] << std::endl;
    }
    os << std::endl;
    return os;
}