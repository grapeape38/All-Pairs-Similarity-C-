#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#include "VectorFunctions.h"
#include "VectorList.h"


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

double dot(VXW &v1, VXW &v2, CmpFeat &cmpF) {
    int i = 0, j = 0;
    double ret = 0.0;
    while (i < (int)v1.size() && j < (int)v2.size()) {
        if (v1[i].first == v2[j].first) {
            ret += v1[i].second * v2[j].second;
            i++;
            j++;
        }
        else if (cmpF(v1[i], v2[j])) i++;
        else j++;
    }
    return ret;
}

double dot(VXW &s, V &v) {
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


