#include <vector>
#include <unordered_map>

#include "AllPairs.h"
#include "VectorFunctions.h"

using V = std::vector<double>;
using VXW = std::vector<std::pair<int,double>>;

class AllPairs1 : public AllPairs {
    public:
        AllPairs1(VectorList &vl_, double t) 
            : AllPairs(vl_) 
        {
            for (Vec &vec : vl) {
                int i = vec.i;
                VXW &v = vec.v;
                FindMatches(vec, t);
                double b = 0.0;
                for (auto &p : v) {
                    int j = p.first;
                    double w = p.second;
                    b += vl_.maxPerFeat[j] * w;
                    if (b >= t) {
                        il[j].add(i, w);
                        p.second = 0;
                    }
                }
            }
        }
        void FindMatches(Vec &vec, double t) {
            int x = vec.i;
            VXW &v = vec.v; 
            std::unordered_map<int, double> A;
            for (const auto &p1 : v) {
                int i = p1.first;
                double w = p1.second;
                for (const auto &p2 : il[i]) {
                    int y = p2.first;
                    double w2 = p2.second;
                    A[y] += w * w2;
                }
            }
            for (const auto &y : A) {
                n_can_consid++;
                double s = y.second + dot(v, vl[y.first], vl.cmpF);
                if (s >= t)
                    ResList.push_back({x, y.first, s});
            }
        }
};

