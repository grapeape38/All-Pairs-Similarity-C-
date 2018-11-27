#include "VectorList.h"

VectorList::VectorList(VSP &vs, int sz)
    : DataList(vs.size(), sz)
{
    maxPerFeat.assign(size, -1.1);
    maxPerVec.assign(vs.size(), -1.1);
    for (int x = 0; x < (int)vs.size(); x++) {
        const SP &v = vs[x];
        lengths[x] = v.size();
        for (const auto &p : v) { 
            cmpF.featCount[p.first]++;
            maxPerFeat[p.first] = std::max(maxPerFeat[p.first], p.second);
            maxPerVec[x] = std::max(maxPerVec[x], p.second);
        }
        VXW vx(v.begin(), v.end());
        vecs.push_back(Vec {x, vx});
    }
    auto cmpVec =
        [&](const Vec &v1, const Vec &v2) { 
            return maxPerVec[v1.i] > maxPerVec[v2.i];
        };
    for (int x = 0; x < (int)vecs.size(); x++) 
        std::sort(vecs[x].v.begin(), vecs[x].v.end(), cmpF);
    std::sort(vecs.begin(), vecs.end(), cmpVec);
    for (int x = 0; x < (int)vecs.size(); x++) 
        index[vecs[x].i] = x;
}

BinVectorList::BinVectorList(std::vector<VI> &vs, int sz)
    :  DataList(vs.size(), sz)
{
    for (int x = 0; x < (int)vs.size(); x++) {
        const VI &v = vs[x];
        VXW vx;
        lengths[x] = v.size();
        for (int i : v) {
            cmpF.featCount[i]++;
            vx.push_back({i, 1.0});
        }
        vecs.push_back({x, vx});
    }
    auto cmpLen =
        [&](const Vec &v1, const Vec &v2) { 
            return lengths[v1.i] < lengths[v2.i];
        };
    for (int x = 0; x < (int)vecs.size(); x++) 
        std::sort(vecs[x].v.begin(), vecs[x].v.end(), cmpF);
    std::sort(vecs.begin(), vecs.end(), cmpLen);
    for (int x = 0; x < (int)vecs.size(); x++) 
        index[vecs[x].i] = x;
}

