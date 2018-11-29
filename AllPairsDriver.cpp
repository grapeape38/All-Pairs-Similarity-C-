#include <vector>
#include <numeric>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "ReadInput.h"
#include "AllPairs0.cpp"
#include "AllPairs1.cpp"
#include "AllPairs2.cpp"
#include "AllPairsBin.cpp"
#include "VectorList.h"

void printNaive(std::vector<V> &vs) {
    /*test output*/
    for (int i = 0; i < (int)vs.size(); i++) {
        V v1 = vs[i];
        for (int j = i+1; j < (int)vs.size(); j++) {
            V v2 = vs[j];
            std::cout << i << " " << j << " " << dot(v1, v2) << std::endl;
        }
    }
}
void parseFlags(int argc, char *argv[], int &type, int &d, double &t, bool &sparse) {
  char c;
  std::stringstream ss;
  while ((c = getopt(argc, argv, "012bst:d:")) != -1)
    switch (c)
      {
        case '0':
            type = 0;
            break;
        case '1':
            type = 1;
            break;
        case '2':
            type = 2;
            break;
        case 'b':
            type = 3;
            break;
        case 'd':
            ss << optarg;
            ss >> d;
            break;
        case 't':
            ss << optarg;
            ss >> t;
            break;
        case 's':
            sparse = true;
            break;
        default:
            abort ();
      }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: filename -<type> (0/1/2) -t <threshold>";
        return 0;
    }
    int type = 2;
    double t = 0.5;
    int d = 0;
    bool sparse = false;
    parseFlags(argc, argv, type, d, t, sparse);
    if (optind >= argc) {
        std::cout << "Usage: filename -<type> (0/1/2) -t <threshold>";
        return 0;
    }
    std::cout << "type: " << type << " threshold: " << t << std::endl;
    AllPairs *ap = nullptr;
    if (t != 3) {
        VSP vss;
        loadData(argv[optind], vss, d, false);
        VectorList vl(vss, d);
        switch(type) {
            case 0: 
                ap = new AllPairs0(vl, t);
                break;
            case 1:
                ap = new AllPairs1(vl, t);
                break;
            default: 
                ap = new AllPairs2(vl, t);
        }
    }
    else {
        std::vector<VI> vs;
        loadBinaryData(argv[optind], vs);
        BinVectorList bvl(vs, d);
        ap = new AllPairsBin(bvl, t);
    }
    if (ap != nullptr)
        ap->printPairs();
    delete ap;
    return 0;
}
