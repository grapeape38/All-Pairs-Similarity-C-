#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "InvList.cpp"
#include "BinVectorList.h"
#include "VectorFunctions.h"
#include "AllPairs.h"

using VI = std::vector<int>;

class AllPairsBin {
    private:
        BinVectorList bvl;
        std::vector<Res> ResList;
        InvList il;
        int size, n_can_consid;
        VI rem_size;
    public:
        AllPairsBin(BinVectorList bvl_, double t) 
        : bvl(bvl_), il(bvl_.numFeats()), size(bvl_.numFeats()),
          n_can_consid(0)
        {
            rem_size = bvl.lengths;
            for (BinVec &vec : bvl) {
                int i = vec.i;
                VI &v = vec.v;
                std::vector<Res> R, U; 
                FindMatches(vec, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                int b = 0;
                for (int &xi : v) {
                    b++;
                    if (b / bvl.lengths[i] >= t) {
                        il.add(xi, i, 1.0);
                        xi = 0;
                        rem_size[i]--;
                    }
                }
            }
        }
        void FindMatches(BinVec &vec, std::vector<Res> &R, double t) {
            int x = vec.i;
            VI &v = vec.v; 
            int remscore = bvl.lengths[x];
            double minsize = bvl.lengths[x] * t * t;
            std::unordered_map<int, double> A;
            for (int i : v) {
                il.prune(i, bvl.lengths, minsize); 
                for (const auto &p2 : il[i]) {
                    int y = p2.first;
                    if (A[y] != 0 || remscore >= minsize)
                        A[y]++;
                    remscore--;
                }
            }
            for (const auto &y : A) {
                n_can_consid++;
                int xlen = bvl.lengths[x], ylen = bvl.lengths[y.first];
                double approx = (y.second + rem_size[y.first]) /
                    std::sqrt(xlen * ylen);
                if (approx >= t) {
                    double d = (y.second + dot(bvl[x], bvl[y.first])) /
                        std::sqrt(xlen * ylen);
                    if (d >= t)
                        R.push_back({x, y.first, d});
                }
            }
        }
        void printPairs() {
            for (const Res &r : ResList) {
                std::cout << r.x << " " << r.y << " " << r.w << std::endl;
            }
            std::cout << "Number of candidates considered: " << n_can_consid
                << std::endl;
        }
};

