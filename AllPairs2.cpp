#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"
#include "Vectors.h"

using V = std::vector<double>;

class AllPairs2 : public AllPairs {
    private:
        V maxPerVec, maxPerFeat, maxUnind;
        std::vector<int> sizes;
    public:
        AllPairs2(std::vector<V> &v_, int sz, double t) 
            : AllPairs(v_, sz) 
        {
            maxUnind.assign(sz, -1.1);
            sizes.assign(sz, sz);
            std::vector<int> idxVec(vecs.size()), idxFeat(sz);
            getFeatureInfo(vecs, size, maxPerVec, maxPerFeat, idxVec, idxFeat);
            for (int i : idxVec) {
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
                        b += std::min(maxPerVec[i], maxPerFeat[j]) * v[j];
                        if (b >= t) {
                            il.add(j, i, v[j]);
                            v[j] = 0;
                            sizes[i]--;
                        }
                        else {
                            maxUnind[i] = std::max(maxUnind[i], v[j]);
                        }
                    }
                }
            }
        }
        void FindMatches(int x, std::vector<Res> &R, double t) {
            V &v = vecs[x];
            std::unordered_map<int, double> A;
            double remscore = dot(v, maxPerFeat);
            //int minsize = t / maxPerVec[x];
            for (int i = 0; i < size; i++) {
                if (v[i] != 0) {
                    for (const auto &p : il[i]) {
                        int y = p.first;
                        double w = p.second;
                        if (A[y] != 0 || remscore >= t) {
                            A[y] += v[i] * w;
                        }
                    }
                    remscore -= v[i] * maxPerFeat[i];
                }
            }
            for (const auto &y : A) {
               double approx = y.second 
                    + std::min(sizes[y.first], (int)v.size())
                    * maxPerVec[x] * maxUnind[y.first];
                if (approx >= t) {
                    double s = y.second + dot(v, vecs[y.first]);
                    if (s >= t)
                        R.push_back({x, y.first, s});
                }
            }
        }
};

