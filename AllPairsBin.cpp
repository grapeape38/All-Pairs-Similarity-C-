#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "VectorFunctions.h"
#include "AllPairs.h"

using VI = std::vector<int>;
using VXW = std::vector<std::pair<int,double>>;

class AllPairsBin : public AllPairs {
    private:
        VI rem_size;
    public:
        AllPairsBin(BinVectorList bvl_, double t)
            : AllPairs(bvl_)
        {
            rem_size = vl.lengths;
            for (Vec &vec : vl) {
                int i = vec.i;
                VXW &v = vec.v;
                std::vector<Res> R, U; 
                FindMatches(vec, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                int b = 0;
                for (auto &p : v) {
                    int j = p.first;
                    b++;
                    if (b / vl.lengths[i] >= t) {
                        il[j].add(i, 1.0);
                        p.second = 0;
                        rem_size[i]--;
                    }
                }
            }
        }
        void FindMatches(Vec &vec, std::vector<Res> &R, double t) {
            int x = vec.i;
            VXW &v = vec.v; 
            int remscore = vl.lengths[x];
            double minsize = vl.lengths[x] * t * t;
            std::unordered_map<int, double> A;
            for (const auto &p : v) {
                int i = p.first;
                il[i].prune(vl.lengths, minsize); 
                for (const auto &p2 : il[i]) {
                    int y = p2.first;
                    if (A[y] != 0 || remscore >= minsize)
                        A[y]++;
                    remscore--;
                }
            }
            for (const auto &y : A) {
                n_can_consid++;
                int xlen = vl.lengths[x], ylen = vl.lengths[y.first];
                double approx = (y.second + rem_size[y.first]) /
                       std::sqrt(xlen * ylen);
                if (approx >= t) {
                    double d = (y.second + dot(vl[x], vl[y.first], vl.cmpF)) / 
                        std::sqrt(xlen * ylen);
                    if (d >= t)
                        R.push_back({x, y.first, d});
                }
            }
        }
};

