#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"
#include "Vectors.h"

using V = std::vector<double>;

class AllPairs1 : public AllPairs {
    public:
        AllPairs1(std::vector<V> &v_, int sz, double t) 
            : AllPairs(v_, sz) 
        {
            V maxPerVec, maxPerFeat;
            std::vector<int> idxVec(vecs.size()), idxFeat(sz);
            getFeatureInfo(vecs, size, maxPerVec, maxPerFeat, idxVec, idxFeat);
            for (int i = 0; i < (int)vecs.size(); i++) {
                V &v = vecs[i];
                std::vector<Res> R, U; 
                FindMatches(i, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                double b = 0.0;
                for (int j : idxFeat) {
                    if (v[j] != 0) {
                        b += maxPerFeat[j] * v[j];
                        if (b >= t) {
                            il.add(j, i, v[j]);
                            v[j] = 0;
                        }
                    }
                }
            }
        }
        void FindMatches(int x, std::vector<Res> &R, double t) {
            V &v = vecs[x];
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
                double s = y.second + dot(v, vecs[y.first]);
                if (s >= t)
                    R.push_back({x, y.first, s});
            }
        }
};

