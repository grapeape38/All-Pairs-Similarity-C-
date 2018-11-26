#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"

using V = std::vector<double>;

class AllPairs1 : public AllPairs {
    public:
        AllPairs1(VectorList &vl_, double t) 
            : AllPairs(vl_) 
        {
            for (int i = 0; i < vl.numVecs(); i++) {
                V &v = vl[i];
                std::vector<Res> R, U; 
                FindMatches(i, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                double b = 0.0;
                for (int j : vl.idxFeat()) {
                    if (v[j] != 0) {
                        b += vl.maxPerFeat[j] * v[j];
                        if (b >= t) {
                            il.add(j, i, v[j]);
                            v[j] = 0;
                        }
                    }
                }
            }
        }
        void FindMatches(int x, std::vector<Res> &R, double t) {
            V &v = vl[x];
            std::unordered_map<int, double> A;
            for (int i = 0; i < size; i++) {
                if (v[i] != 0) {
                    for (const auto &p : il[i]) {
                        int y = p.first;
                        double w = p.second;
                        A[y] += v[i] * w;
                    }
                }
            }
            for (const auto &y : A) {
                double s = y.second + dot(v, vl[y.first]);
                if (s >= t)
                    R.push_back({x, y.first, s});
            }
        }
};

