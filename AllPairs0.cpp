#include <algorithm>
#include <vector>
#include <unordered_map>

#include "AllPairs.h"
#include "VectorFunctions.h"

using V = std::vector<double>;
using VXW = std::vector<std::pair<int,double>>;

class AllPairs0 : public AllPairs {
    public:
        AllPairs0(VectorList &vl_, double t) 
            : AllPairs(vl_)
        {
            for (Vec &vec : vl) {
                int i = vec.i;
                std::vector<Res> R, U; 
                FindMatches(vec, R, t);
                std::set_union(ResList.begin(), ResList.end(),
                        R.begin(), R.end(),
                        std::back_inserter(U));
                ResList = std::move(U);
                const VXW &v = vec.v;
                for (const auto &p : v) {
                    il.add(p.first, i, p.second);
                }
            }
        }
        void FindMatches(Vec &vec, std::vector<Res> &R, double t) {
            int x = vec.i;
            VXW &v = vec.v;
            std::unordered_map<int, double> A;
            for (const auto &p : v) {
                int i = p.first;
                double w = p.second;
                for (const auto &p2 : il[i]) {
                    int y = p2.first;
                    double w2 = p2.second;
                    A[y] += w * w2;
                }
            }
            for (const auto &y : A) {
                n_can_consid++;
                if (y.second >= t)
                    R.push_back({x, y.first, y.second});
            }
        }
};

