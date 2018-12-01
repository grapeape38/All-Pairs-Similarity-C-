#include <vector>
#include <cstddef>

#ifndef INVLIST
#define INVLIST

class InvList {
    private:
        std::vector<std::pair<int,double>> items;
        int fp;
    public:
        InvList() : fp(0) {}
        int size() { return items.size(); }
        void add(int x, double w) {
            items.push_back({x, w});
        }
        void prune(std::vector<int> &lens, double minsize) {
            if (items.size()) {
                while (fp < items.size() && 
                        lens[items[fp].first] < minsize) {
                    fp++;
                }
                if (fp == items.size()) {
                    items.clear();
                    fp = 0;
                }
            }
        }
        std::pair<int,double> &operator[](int i) { return items[i + fp]; }
        using const_iterator = std::vector<std::pair<int,double>>::const_iterator;
        const_iterator begin() { return items.begin() + fp; }
        const_iterator end() { return items.end(); }
};

#endif
