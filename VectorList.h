#include <vector>
#include <unordered_map>

using V = std::vector<double>;
using VI = std::vector<int>;
using SP = std::unordered_map<int, double>;
using VSP = std::vector<SP>; 
using XW = std::pair<int,double>;
using VXW = std::vector<XW>;

#ifndef VECTOR_H
#define VECTOR_H

struct Vec {
    int i;
    VXW v;
    SP s;
};

class VectorList {
    private:
        int size;
        std::vector<int> index;
        std::vector<Vec> vecs;
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


