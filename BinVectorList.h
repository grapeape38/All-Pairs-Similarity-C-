#include <vector>
#include <unordered_map>

using VI = std::vector<int>;

#ifndef BIN_VECTOR_H
#define BIN_VECTOR_H

struct BinVec {
    int i;
    VI v;
};

class BinVectorList {
    private:
        int size;
        VI index;
        std::vector<BinVec> vecs;
    public:
        using iterator = std::vector<BinVec>::iterator;
        VI lengths;
        BinVectorList(std::vector<VI> &vs, int sz);
        VI &operator[](int i) { return vecs[index[i]].v; }
        int numVecs() { return vecs.size(); };
        int numFeats() { return size; }
        iterator begin() { return vecs.begin(); }
        iterator end() { return vecs.end(); }
};

#endif


