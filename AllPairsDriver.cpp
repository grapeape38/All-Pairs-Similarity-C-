#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

#include "AllPairs0.cpp"
#include "AllPairs1.cpp"
#include "AllPairs2.cpp"
#include "AllPairsBin.cpp"
#include "VectorFunctions.h"
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

VectorList loadData(const char* fname, int nf, bool sparse) {
    std::ifstream ifs(fname);
    std::string line;
    /*
    if (binary) {
        std::vector<VI> vs;
        while (getline(ifs, line)) {
            std::stringstream ss(line);
            VI fts;
            int x; 
            while (ss >> x)
                fts.push_back(x);
            vs.push_back(fts);
        }
        return BinVectorList(vs, nf);
    }*/
    std::vector<V> vs;
    while (getline(ifs, line)) {
        std::stringstream ss(line);
        V fts;
        double x; 
        while (ss >> x)
            fts.push_back(x);
        vs.push_back(fts);
    }
    VSP vss;
    for (V &v : vs) {
        normalize(v);
        vss.push_back(makeSparse(v));
    }
    printNaive(vs);
    std::cout << std::endl;
    int sz = nf ? nf : vs[0].size();
    return VectorList(vss, sz);
}

void parseFlags(int argc, char *argv[], int &type, double &t) {
  char c;
  std::stringstream ss;
  while ((c = getopt(argc, argv, "012bt")) != -1)
    switch (c)
      {
        case '0':
            type = 0;
            break;
        case '1':
            type = 1;
            break;
        case 'b':
            type = 3;
            break;
        case 't':
            ss << optarg;
            ss >> t;
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
    bool binary = false;
    parseFlags(argc, argv, type, t);
    AllPairs *ap = nullptr;
    if (t != 3) {
        VectorList vl = loadData(argv[1], 0, false);
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
    if (ap != nullptr)
        ap->printPairs();
    delete ap;
    return 0;
}
