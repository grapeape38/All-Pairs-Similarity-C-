#include <vector>
#include <numeric>
#include <iostream>

#include "AllPairs0.cpp"
#include "AllPairs1.cpp"
#include "AllPairs2.cpp"
#include "VectorList.h"

int main() {
    V v1 {4.0, 0.0, 2.1, 5.2}, v2 {1.2, 4.4, 0.0, 7.1}, v3 {1.2, 0.0, -1.2, 0.5};
    std::vector<V> vs {v1, v2, v3};
    for (V &v : vs)
        normalize(v);

    /*test output*/
    for (int i = 0; i < (int)vs.size(); i++) {
        V v1 = vs[i];
        for (int j = i+1; j < (int)vs.size(); j++) {
            V v2 = vs[j];
            std::cout << i << " " << j << " " << dot(v1, v2) << std::endl;
        }
    }

    std::vector<SP> vss;
    for (V &v : vs) {
        SP s = makeSparse(v);
        vss.push_back(s);
    }
    VectorList vl(vss, 4);
    std::cout << std::endl;
    double t = 0.3;
    AllPairs0 ap0(vl, t);
    AllPairs1 ap1(vl, t);
    AllPairs1 ap2(vl, t);
    ap0.printPairs();
    std::cout << std::endl;
    ap1.printPairs();
    std::cout << std::endl;
    ap2.printPairs();
    return 0;
}
