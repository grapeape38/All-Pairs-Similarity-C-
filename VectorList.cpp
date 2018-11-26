#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#include "VectorList.h"

using V = std::vector<double>;
using SP = std::unordered_map<int,double>;
using XW = std::pair<int,double>;
using VXW = std::vector<std::pair<int,double>>;

void normalize(V &v) {
    double s = std::sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
    V res(v.size());
    std::transform(v.begin(), v.end(), res.begin(),
            [&](double d) { return d / s; });
    v = std::move(res);
}

void normalize(SP &s) {
    double sum = 0.0;
    for (const auto &p : s)
        sum += p.second*p.second;
    double len = std::sqrt(sum);
    for (auto &p : s)
        p.second /= len;
}

double dot(V &v1, V &v2) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}

double dot(SP &s1, SP &s2) {
    double ret = 0.0;
    if (s1.size() > s2.size()) std::swap(s1,s2);
    for (const auto &p : s1) {
        if (s2[p.first]) ret += p.second * s2[p.first];
    }
    return ret;
}

double dot(SP &s, V &v) {
    double ret = 0.0;
    for (const auto &p : s) 
        ret += p.second * v[p.first];
    return ret;
}

SP makeSparse(V &v) {
    SP s;
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i]) s[i] = v[i];
    }
    return s;
}

VectorList::VectorList(VSP &vs, int sz)
    : size(sz), lengths(sz), index(vs.size())
{
    std::vector<int> featCount(size);
    maxPerFeat.assign(size, -1.1);
    maxPerVec.assign(vs.size(), -1.1);
    for (int x = 0; x < (int)vs.size(); x++) {
        const SP &v = vs[x];
        for (const auto &p : v) { 
            featCount[p.first]++;
            lengths[x]++;
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

