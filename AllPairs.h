#include <iostream>
#include <vector>

#include "InvList.cpp"
#include "VectorList.h"

#ifndef ALLPAIRS_H
#define ALLPAIRS_H

struct Res {
    int x, y;
    double w;
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
        void printPairs() {
            for (const Res &r : ResList) {
                std::cout << r.x << " " << r.y << " " << r.w << std::endl;
            }
            std::cout << "Number of candidates considered: " << n_can_consid
                << std::endl;
        }
};

#endif
