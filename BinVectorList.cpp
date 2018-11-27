#include <vector>
#include <algorithm>

#include "BinVectorList.h"

BinVectorList::BinVectorList(std::vector<VI> &vs, int sz)
    : size(sz), lengths(sz), index(vs.size())
{
    std::vector<int> featCount(size);
    for (int x = 0; x < (int)vs.size(); x++) {
        const VI &v = vs[x];
        lengths[x] = v.size();
        for (int i : v) 
            featCount[i]++;
        vecs.push_back({x, v});
    }
    auto cmpFeat =
        [&](int i, int j) {
            return featCount[i] > featCount[j];
        };
    auto cmpLen =
        [&](const BinVec &v1, const BinVec &v2) { 
            return lengths[v1.i] < lengths[v2.i];
        };
    for (int x = 0; x < (int)vecs.size(); x++) 
        std::sort(vecs[x].v.begin(), vecs[x].v.end(), cmpFeat);
    std::sort(vecs.begin(), vecs.end(), cmpLen);
    for (int x = 0; x < (int)vecs.size(); x++) 
        index[vecs[x].i] = x;
}

