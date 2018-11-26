#include <iostream>
#include <vector>
#include "InvList.cpp"

#ifndef ALLPAIRS_H
#define ALLPAIRS_H

using V = std::vector<double>;

struct Res {
    int x, y;
    double w;
    bool operator<(const Res &r2) {
        return x < r2.x || (x == r2.x && y < r2.y);
    }
};

class AllPairs {
    protected:
        std::vector<V> vecs;
        std::vector<Res> ResList;
        InvList il;
        int size;
    public:
        AllPairs(std::vector<V> v, int sz) 
            : vecs(v), size(sz), il(sz) {}
        virtual void FindMatches(int x, std::vector<Res> &R, double t) = 0;
        void printPairs() {
            for (const Res &r : ResList) {
                std::cout << r.x << " " << r.y << " " << r.w << std::endl;
            }
        }
};

#endif
