#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"

using V = std::vector<double>;

class AllPairs2 : public AllPairs {
    private:
        std::vector<int> rem_size;
        V maxUnind;
    public:
        AllPairs2(VectorList &vl_, double t) 
            : AllPairs(vl_) 
        {
            maxUnind.assign(size, -1.1);
            rem_size = vl.lengths;
            for (int i : vl.idxFeat()) {
                V &v = vl[i];
                std::vector<Res> R, U; 
                FindMatches(i, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                double b = 0.0;
                for (int j : vl.idxVec()) {
                    if (v[j] != 0) {
                        b += std::min(vl.maxPerVec[i], vl.maxPerFeat[j]) * v[j];
                        if (b >= t) {
                            il.add(j, i, v[j]);
                            v[j] = 0;
                            rem_size[i]--;
                        }
                        else {
                            maxUnind[i] = std::max(maxUnind[i], v[j]);
                        }
                    }
                }
            }
        }
        void FindMatches(int x, std::vector<Res> &R, double t) {
            V &v = vl[x];
            std::unordered_map<int, double> A;
            double remscore = dot(v, vl.maxPerFeat);
            int minsize = t / vl.maxPerVec[x];
            for (int i = 0; i < size; i++) {
                if (v[i] != 0) {
                    il.prune(i, vl.lengths, minsize);
                    for (const auto &p : il[i]) {
                        int y = p.first;
                        double w = p.second;
                        if (A[y] != 0 || remscore >= t) {
                            A[y] += v[i] * w;
                        }
                    }
                    remscore -= v[i] * vl.maxPerFeat[i];
                }
            }
            for (const auto &y : A) {
               double approx = y.second 
                    + std::min(rem_size[y.first], vl.lengths[x])
                    * vl.maxPerVec[x] * maxUnind[y.first];
                if (approx >= t) {
                    double s = y.second + dot(v, vl[y.first]);
                    if (s >= t)
                        R.push_back({x, y.first, s});
                }
            }
        }
};

