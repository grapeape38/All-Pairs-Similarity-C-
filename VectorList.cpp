#include <vector>
#include <unordered_map>
#include <algorithm>

#include "VectorList.h"

VectorList::VectorList(VSP &vs, int sz)
    : size(sz), lengths(sz), index(vs.size())
{
    std::vector<int> featCount(size);
    maxPerFeat.assign(size, -1.1);
    maxPerVec.assign(vs.size(), -1.1);
    for (int x = 0; x < (int)vs.size(); x++) {
        const SP &v = vs[x];
        lengths[x] = v.size();
        for (const auto &p : v) { 
            featCount[p.first]++;
            maxPerFeat[p.first] = std::max(maxPerFeat[p.first], p.second);
            maxPerVec[x] = std::max(maxPerVec[x], p.second);
        }
        VXW vx(v.begin(), v.end());
        vecs.push_back(Vec {x, vx, v});
    }
    auto cmpFeat =
        [&](XW p1, XW p2) {
            return featCount[p1.first] > featCount[p2.first];
        };
    auto cmpVec =
        [&](const Vec &v1, const Vec &v2) { 
            return maxPerVec[v1.i] > maxPerVec[v2.i];
        };
    for (int x = 0; x < (int)vecs.size(); x++) 
        std::sort(vecs[x].v.begin(), vecs[x].v.end(), cmpFeat);
    std::sort(vecs.begin(), vecs.end(), cmpVec);
    for (int x = 0; x < (int)vecs.size(); x++) 
        index[vecs[x].i] = x;
}

