#include <vector>
#include <numeric>
#include <algorithm>

#include "VectorList.h"

using V = std::vector<double>;

void normalize(V &v) {
    double s = std::accumulate(v.begin(), v.end(), 0.0);
    V res(v.size());
    std::transform(v.begin(), v.end(), res.begin(),
            [&](double d) { return d / s; });
    v = std::move(res);
}

double dot(V &v1, V &v2) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}

VectorList::VectorList(std::vector<V> &vs, int sz)
    : vecs(vs), size(sz), descFeatureIdx(sz), descVecIdx(vecs.size()), lengths(sz)
{
    std::iota(descFeatureIdx.begin(), descFeatureIdx.end(), 0);
    std::iota(descVecIdx.begin(), descVecIdx.end(), 0);
    std::vector<int> featCount(size);
    maxPerFeat.assign(size, -1.1);
    maxPerVec.assign(vecs.size(), -1.1);
    for (int x = 0; x < (int)vecs.size(); x++) {
        const V &v = vecs[x];
        for (int i = 0; i < size; i++) {
            if (v[i] != 0) {
                featCount[i]++;
                lengths[x]++;
                maxPerFeat[i] = std::max(maxPerFeat[i], v[i]);
                maxPerVec[x] = std::max(maxPerVec[x], v[i]);
            }
        }
    }
    auto cmpFeat = [&](int i, int j) { return featCount[i] > featCount[j]; };
    auto cmpVec = [&](int i, int j) { return maxPerVec[i] > maxPerVec[j]; };
    std::sort(descFeatureIdx.begin(), descFeatureIdx.end(), cmpFeat);
    std::sort(descVecIdx.begin(), descVecIdx.end(), cmpVec);
}

