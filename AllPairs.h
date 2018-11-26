#include <iostream>
#include <vector>

#include "InvList.cpp"
#include "VectorList.h"

#ifndef ALLPAIRS_H
#define ALLPAIRS_H

struct Res {
    int x, y;
    double w;
    bool operator<(const Res &r2) {
        return x < r2.x || (x == r2.x && y < r2.y);
    }
};

class AllPairs {
    protected:
        VectorList vl;
        std::vector<Res> ResList;
        InvList il;
        int size;
    public:
        AllPairs(VectorList vl_) 
            : vl(vl_), size(vl_.numFeats()), il(vl_.numFeats()) {}
        virtual void FindMatches(int x, std::vector<Res> &R, double t) = 0;
        void printPairs() {
            for (const Res &r : ResList) {
                std::cout << r.x << " " << r.y << " " << r.w << std::endl;
            }
        }
};

#endif
