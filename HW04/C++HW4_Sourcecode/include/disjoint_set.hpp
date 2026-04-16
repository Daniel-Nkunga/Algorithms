#include <vector>

class DisjointSet {
    private:
        std::vector<int> parent;
        int find(int u);
    public:
        DisjointSet(int n);
        int isOnSameSet(int u, int v);
        void join(int u, int v);
};
