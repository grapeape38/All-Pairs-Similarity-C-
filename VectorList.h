#include <vector>
#include <numeric>
#include <algorithm>

using V = std::vector<double>;

#ifndef VECTOR_H
#define VECTOR_H

void normalize(V &v);
double dot(V &v1, V &v2);

class VectorList {
    private:
        int size;
        std::vector<V> vecs;
        std::vector<int> descFeatureIdx, descVecIdx;
    public:
        V maxPerFeat, maxPerVec; 
        std::vector<int> lengths;
        VectorList(std::vector<V> &vs, int sz);
        const std::vector<int> &idxFeat() { return descFeatureIdx; }
        const std::vector<int> &idxVec() { return descVecIdx; }
        V &operator[](int i) { return vecs[i]; }
        int numVecs() { return vecs.size(); };
        int numFeats() { return size; }
};

#endif


