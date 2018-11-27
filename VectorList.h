#include <vector>
#include <algorithm>
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
};

struct CmpFeat {
    VI featCount;
    CmpFeat(int sz) : featCount(sz) {}
    bool operator()(const XW &p1, const XW &p2) {
        return featCount[p1.first] > featCount[p2.first] ||
            (featCount[p1.first] == featCount[p2.first] && p1.first < p2.first);
    };
};

class DataList {
    protected:
        int size;
        std::vector<int> index;
        std::vector<Vec> vecs;
    public:
        using iterator = std::vector<Vec>::iterator;
        V maxPerFeat, maxPerVec; 
        VI lengths;
        CmpFeat cmpF;
        DataList(int numV, int sz) : size(sz), index(numV), cmpF(sz), lengths(sz) {}
        VXW &operator[](int i) { return vecs[index[i]].v; }
        int numVecs() { return vecs.size(); };
        int numFeats() { return size; }
        iterator begin() { return vecs.begin(); }
        iterator end() { return vecs.end(); }
};

class VectorList : public DataList {
    public:
        VectorList(VSP &vs, int sz);
};

class BinVectorList : public DataList {
    public:
        BinVectorList(std::vector<VI> &vs, int sz);
};

#endif


