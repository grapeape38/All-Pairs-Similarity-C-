#include <vector>
#include <numeric>
#include <iostream>

#include "AllPairs0.cpp"
#include "AllPairs1.cpp"
#include "AllPairs2.cpp"
#include "Vectors.h"

int main() {
    V v1 {4.0, 3.0, 2.1, 5.2}, v2 {1.2, 4.4, 5.6, 7.1}, v3 {1.2, 1.4, -1.2, 0.5};
    std::vector<V> vs {v1, v2, v3};
    normalize(vs);
    for (int i = 0; i < (int)vs.size(); i++) {
        V v1 = vs[i];
        for (int j = i+1; j < (int)vs.size(); j++) {
            V v2 = vs[j];
            std::cout << i << " " << j << " " << dot(v1, v2) << std::endl;
        }
    }
    std::cout << std::endl;
    double t = 0.3;
    AllPairs0 ap0(vs, 4, 0.2);
    AllPairs1 ap1(vs, 4, 0.2);
    AllPairs1 ap2(vs, 4, 0.2);
    ap0.printPairs();
    std::cout << std::endl;
    ap1.printPairs();
    std::cout << std::endl;
    ap2.printPairs();
    return 0;
}
