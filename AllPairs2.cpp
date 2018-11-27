#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"
#include "VectorFunctions.h"

using V = std::vector<double>;
using VXW = std::vector<std::pair<int,double>>;

class AllPairs2 : public AllPairs {
    private:
        std::vector<int> rem_size;
        V maxUnind;
    public:
        AllPairs2(VectorList vl_, double t) 
            : AllPairs(vl_) 
        {
            maxUnind.assign(size, -1.1);
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
                double b = 0.0;
                for (auto &p : v) {
                    int j = p.first;
                    double w = p.second;
                    b += std::min(vl.maxPerVec[i], vl.maxPerFeat[j]) * w;
                    if (b >= t) {
                        il.add(j, i, w);
                        p.second = 0;
                        rem_size[i]--;
                    }
                    else {
                        maxUnind[i] = std::max(maxUnind[i], w);
                    }
                }
            }
        }
        void FindMatches(Vec &vec, std::vector<Res> &R, double t) {
            int x = vec.i;
            VXW &v = vec.v;
            std::unordered_map<int, double> A;
            double remscore = dot(v, vl.maxPerFeat);
            int minsize = t / vl.maxPerVec[x];
            for (const auto &p1 : v) {
                int i = p1.first;
                double w = p1.second;
                il.prune(i, vl.lengths, minsize);
                for (const auto &p2 : il[i]) {
                    int y = p2.first;
                    double w2 = p2.second;
                    if (A[y] != 0 || remscore >= t) {
                        A[y] += w * w2;
                    }
                }
                remscore -= w * vl.maxPerFeat[i];
            }
            for (const auto &y : A) {
               n_can_consid++;
               double approx = y.second 
                    + std::min(rem_size[y.first], vl.lengths[x])
                    * vl.maxPerVec[x] * maxUnind[y.first];
                if (approx >= t) {
                    double s = y.second + dot(v, vl[y.first], vl.cmpF);
                    if (s >= t)
                        R.push_back({x, y.first, s});
                }
            }
        }
};

