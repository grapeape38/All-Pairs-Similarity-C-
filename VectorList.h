#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>

using V = std::vector<double>;
using SP = std::unordered_map<int, double>;
using VSP = std::vector<SP>; 
using VXW = std::vector<std::pair<int,double>>;

#ifndef VECTOR_H
#define VECTOR_H

void normalize(V &v);
void normalize(SP &sp);

double dot(V &v1, V &v2);
double dot(SP &s1, SP &s2);
double dot(SP &s, V &v);

SP makeSparse(V &v);

struct Vec {
    int i;
    VXW v;
    SP s;
};

class VectorList {
    private:
        int size;
        std::vector<Vec> vecs;
        std::vector<int> index;
    public:
        using iterator = std::vector<Vec>::iterator;
        V maxPerFeat, maxPerVec; 
        std::vector<int> lengths;
        VectorList(VSP &vs, int sz);
        SP &operator[](int i) { return vecs[index[i]].s; }
        int numVecs() { return vecs.size(); };
        int numFeats() { return size; }
        iterator begin() { return vecs.begin(); }
        iterator end() { return vecs.end(); }
};

#endif


