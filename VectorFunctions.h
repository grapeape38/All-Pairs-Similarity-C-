#include <vector>
#include <algorithm>
#include <unordered_map>

#ifndef VECTOR_FN_H
#define VECTOR_FN_H

using V = std::vector<double>;
using VI = std::vector<int>;
using SP = std::unordered_map<int, double>;

void normalize(V &v);
void normalize(SP &sp);

double dot(V &v1, V &v2);
int dot(VI &v1, VI &v2);
double dot(SP &s1, SP &s2);
double dot(SP &s, V &v);

SP makeSparse(V &v);

#endif


