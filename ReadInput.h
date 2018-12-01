#include <string>
#include <regex>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "VectorFunctions.h"

#ifndef READINPUT
#define READINPUT

void parseSparse(std::string in, SP &v, int &d);
void loadData(const char* fname, VSP &vss, int &d, bool sparse);
void loadBinaryData(const char* fname, std::vector<VI> &vs, int &d);
void loadNaiveData(const char* fname, std::vector<V> &vs);

#endif