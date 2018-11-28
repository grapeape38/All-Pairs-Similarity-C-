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

void loadBinaryData(const char* fname, VSP &vss, int &nf, bool sparse) {
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
}

void loadData(const char* fname, VSP &vss, int &nf, bool sparse) {
    std::ifstream ifs(fname);
    std::string line;
    std::vector<V> vs;
    while (getline(ifs, line)) {
        std::stringstream ss(line);
        V fts;
        double x; 
        while (ss >> x)
            fts.push_back(x);
        if (fts.size())
            vs.push_back(fts);
    }
    for (V &v : vs) {
        normalize(v);
        SP sp = makeSparse(v);
        if (sp.size())
            vss.push_back(sp);
    }
    //printNaive(vs);
    //std::cout << std::endl;
    nf = vs[0].size();
    ifs.close();
}

void parseFlags(int argc, char *argv[], int &type, double &t) {
  char c;
  std::stringstream ss;
  while ((c = getopt(argc, argv, "012bt:f:")) != -1)
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
        case 't':
            ss << optarg;
            ss >> t;
            break;
        default:
            abort ();
      }
}

void dummyTest() {
    V v1 {4.0, 0.0, 2.1, 5.2}, v2 {1.2, 4.4, 0.0, 7.1}, v3 {1.2, 0.0, -1.2, 0.5};
    std::vector<V> vs {v1, v2, v3};
    for (V &v : vs)
        normalize(v);
    std::vector<SP> vss;
    for (V &v : vs) {
        SP s = makeSparse(v);
        vss.push_back(s);
    }
    VectorList vl(vss, 4); 
    AllPairs1 ap(vl, 0.2);
    ap.printPairs();
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
    if (optind >= argc) {
        std::cout << "Usage: filename -<type> (0/1/2) -t <threshold>";
        return 0;
    }
    std::cout << "type: " << type << " threshold: " << t << std::endl;
    AllPairs *ap;
    if (t != 3) {
        int sz = 10;
        VSP vss;
        loadData(argv[optind], vss, sz, false);
        VectorList vl(vss, sz);
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
