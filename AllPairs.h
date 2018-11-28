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
        DataList vl;
        std::vector<Res> ResList;
        std::vector<InvList> il;
        int size, n_can_consid;
    public:
        AllPairs(DataList vl_) 
            : vl(vl_), size(vl_.numFeats()), il(vl_.numFeats()),
              n_can_consid(0) {}
        virtual void FindMatches(Vec &vec, std::vector<Res> &R, double t) = 0;
        void printPairs() {
            for (const Res &r : ResList) {
                std::cout << r.x << " " << r.y << " " << r.w << std::endl;
            }
            std::cout << "Number of candidates considered: " << n_can_consid
                << std::endl;
        }
};

#endif
