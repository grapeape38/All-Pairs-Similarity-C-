#include <vector>
#include <numeric>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <chrono>

#include "ReadInput.h"
#include "AllPairs0.cpp"
#include "AllPairs1.cpp"
#include "AllPairs2.cpp" 
#include "AllPairsBin.cpp"
#include "VectorList.h"

void computeNaive(std::vector<V> &vs, double t) {
    /*test output*/
    std::cout << "Computing Naively" << std::endl;
    std::vector<Res> ResList;
    for (int i = 0; i < (int)vs.size(); i++) {
        V v1 = vs[i];
        for (int j = i+1; j < (int)vs.size(); j++) {
            V v2 = vs[j];
            double d = dot(v1, v2);
            if (d >= t) {
                ResList.push_back({i, j, d});
            }
        }
    }
    for (auto &r : ResList) {
        std::cout << r.x << " " << r.y << " " << r.w << std::endl;
    }
}
void parseFlags(int argc, char *argv[], int &type, double &t, bool &sparse) {
  char c;
  std::stringstream ss;
  while ((c = getopt(argc, argv, "012bnspt:")) != -1)
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
        case 'n':
            type = 4;
            break;
        case 'p':
            type = 5;
            break;
        case 's':
            sparse = true;
            break;
        default:
            abort ();
      }
}

using namespace std::chrono;
inline double timeDiff(high_resolution_clock::time_point &prev) {
        auto c = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(c - prev);
        return time_span.count();
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
    parseFlags(argc, argv, type, t, sparse);
    if (optind >= argc) {
        std::cout << "Usage: filename -<type> (0/1/2) -t <threshold>";
        return 0;
    }
    std::cout << "type: " << type << " threshold: " << t << std::endl;
    if (type == 4) {
        std::vector<V> vs;
        loadNaiveData(argv[optind], vs);
        computeNaive(vs, t);
        return 0;
    }
    AllPairs *ap = nullptr;
    auto now = high_resolution_clock::now();
    if (type != 3) {
        VSP vss;
        loadData(argv[optind], vss, d, sparse);
        VectorList vl(vss, d);
        double t_d = timeDiff(now);
        std::cout << "Took " << t_d << " seconds to read and preprocess input.\n";
        now = high_resolution_clock::now();
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
        loadBinaryData(argv[optind], vs, d);
        BinVectorList bvl(vs, d);
        double t_d = timeDiff(now);
        std::cout << "Took " << t_d << " seconds to read and preprocess input.\n";
        now = high_resolution_clock::now();
        ap = new AllPairsBin(bvl, t);
    }
    if (ap != nullptr)
        ap->printPairs();
    double t_d = timeDiff(now);
    std::cout << "Took " << t_d << " seconds to run All Pairs.\n";
    delete ap;
    return 0;
}
