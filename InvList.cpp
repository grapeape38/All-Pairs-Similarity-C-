#include <vector>
#include <cstddef>

using IList = std::vector<std::pair<int,double>>;

#ifndef INVLIST
#define INVLIST

class InvList { 
    private:
        std::vector<IList> lists;
        std::vector<int> fp;
    public:
        InvList(int sz) : lists(sz), fp(sz) {}
        void add(int i, int x, double w) {
            lists[i].push_back({x, w});
        }
        void prune(int i, std::vector<int> &lens, double minsize) {
            while (fp[i] < lists[i].size() && 
                    lens[lists[i][fp[i]].first] < minsize) {
                fp[i]++;
            }
            if (fp[i] >= lists[i].size() / 2) {
                IList il(lists[i].size() - fp[i] + 1);
                std::copy(lists[i].begin() + fp[i], lists[i].end(), il.begin());
                lists[i] = std::move(il);
            }
        }
        IList operator[](size_t i) const { 
            //return lists[i];
            return lists[i + fp[i]];
        };
};

#endif
