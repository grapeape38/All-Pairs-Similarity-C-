#include <vector>
#include <numeric>
#include <algorithm>

using V = std::vector<double>;

#ifndef VECTORS
#define VECTORS

void normalize(V &v);
void normalize(std::vector<V> &vs);
double dot(V &v1, V &v2);
void getFeatureInfo(const std::vector<V> &vecs, int size,
                    V &maxPerVec, V &maxPerFeat,
                    std::vector<int> &idxVec, std::vector<int> &idxFeat);

#endif


