#include <vector>
#include <cstddef>

using IList = std::vector<std::pair<int,double>>;

#ifndef INVLIST
#define INVLIST

class InvList { 
    private:
        std::vector<IList> lists;
        //std::vector<int> fp;
        int size;
    public:
        InvList(int sz) : size(sz) {
            lists.assign(sz,IList());
            //fp.assign(sz,0);
        }
        void add(int i, int x, double w) {
            lists[i].push_back({x, w});
        }
        /*void prune(int i, std::vector<int> &sz, double minsize) {
            while (fp[i] < lists[i].size() && 
                    sz[lists[i][fp[i]].first] < minsize) {
                fp++;
            }
        }*/
        IList operator[](size_t i) const { 
            return lists[i];
            //return lists[i+fp[i]];
        };
};

#endif
