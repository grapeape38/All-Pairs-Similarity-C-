#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"

using V = std::vector<double>;

class AllPairs0 : public AllPairs {
    public:
        AllPairs0(VectorList vl_, double t) 
            : AllPairs(vl_)
        {
            for (int i = 0; i < vl.numVecs(); i++) {
                std::vector<Res> R, U; 
                FindMatches(i, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                for (int j = 0; j < size; j++) {
                    if (vl[i][j] != 0)
                        il.add(j, i, vl[i][j]);
                }
            }
        }
        void FindMatches(int x, std::vector<Res> &R, double t) {
            std::unordered_map<int, double> A;
            const V &v = vl[x];
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
                if (y.second >= t)
                    R.push_back({x, y.first, y.second});
            }
        }
};

