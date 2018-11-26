#include <vector>
#include <numeric>
#include <algorithm>

#include "Vectors.h"

using V = std::vector<double>;

void normalize(V &v) {
    double s = std::accumulate(v.begin(), v.end(), 0.0);
    V res(v.size());
    std::transform(v.begin(), v.end(), res.begin(),
            [&](double d) { return d / s; });
    v = std::move(res);
}

void normalize(std::vector<V> &vs) {
    for (V &v : vs)
        normalize(v);
}

double dot(V &v1, V &v2) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}

void getFeatureInfo(const std::vector<V> &vecs, int size,
                    V &maxPerVec, V &maxPerFeat,
                    std::vector<int> &idxVec, std::vector<int> &idxFeat)
{
    maxPerVec.assign(vecs.size(), -1.1);
    maxPerFeat.assign(size, -1.1);
    std::iota(idxVec.begin(), idxVec.end(), 0);
    std::iota(idxFeat.begin(), idxFeat.end(), 0);
    std::vector<int> featCount(size);
    for (int x = 0; x < (int)vecs.size(); x++) {
        const V &v = vecs[x];
        for (int i = 0; i < size; i++) {
            if (v[i] != 0) {
                featCount[i]++;
                maxPerFeat[i] = std::max(maxPerFeat[i], v[i]);
                maxPerVec[x] = std::max(maxPerVec[x], v[i]);
            }
        }
    }
    auto cmpFeat = [&](int i, int j) { return featCount[i] > featCount[j]; };
    auto cmpVec = [&](int i, int j) { return maxPerVec[i] > maxPerVec[j]; };
    sort(idxFeat.begin(), idxFeat.end(), cmpFeat);
    sort(idxVec.begin(), idxVec.end(), cmpVec);
}


