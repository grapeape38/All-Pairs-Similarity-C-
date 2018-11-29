#include "ReadInput.h"

void parseSparse(std::string in, SP &v) {
    std::regex e {"(\\d):(\\d(\\.\\d*)?)"} ;
    std::sregex_iterator rit(in.begin(), in.end(), e);
    std::sregex_iterator rend;
    while (rit != rend) {
        std::smatch m = *rit;
        std::string first = m[1], second = m[2];
        int i = std::stoi(first);
        double w = std::stod(second);
        v[i] = w;
        ++rit;
    }
}

void loadBinaryData(const char* fname, std::vector<VI> &vs) {
    std::ifstream ifs(fname);
    std::string line;
    while (getline(ifs, line)) {
        std::stringstream ss(line);
        VI fts;
        int x; 
        while (ss >> x)
            fts.push_back(x);
        vs.push_back(fts);
    }
    ifs.close();
}

void loadSparseData(const char* fname, VSP &vss) {
    std::ifstream ifs(fname);
    std::string line;
    while (getline(ifs, line)) {
        SP sp;
        parseSparse(line, sp);
        normalize(sp);
        vss.push_back(sp);
   }
   ifs.close();
}

void loadData(const char* fname, VSP &vss, int &d, bool sparse) {
    if (sparse) {
        loadSparseData(fname, vss);
        return;
    }
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
    d = d ? d : vs[0].size();
    ifs.close();
}


