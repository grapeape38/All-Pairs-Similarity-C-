#include <vector>
#include <algorithm>
#include <unordered_map>

#include "VectorList.h"

#ifndef VECTOR_FN_H
#define VECTOR_FN_H

using V = std::vector<double>;
using VI = std::vector<int>;
using SP = std::unordered_map<int,double>;
using XW = std::pair<int,double>;
using VXW = std::vector<XW>;

void normalize(V &v);
void normalize(SP &sp);

double dot(V &v1, V &v2);
double dot(VXW &v1, VXW &v2, CmpFeat &cmpF);
double dot(VXW &s, V &v);

SP makeSparse(V &v);

#endif


