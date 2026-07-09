#include <graph.hpp>
#include <msort.hpp>
#include <disjoint_set.hpp>


std::vector<Edge> constructMSTKruskal(Graph &G)
{
    std::vector<Edge> edges = G.exportEdges();
    int n = G.getN();

    // Step 1: Sort all edges by weight ascending using merge sort
    msort(edges, 0, edges.size());

    std::vector<Edge> mst;
    DisjointSet djs(n);

    // Step 2: Add the cheapest edge that does not form a cycle
    for (const Edge &e : edges) {
        if (mst.size() == n - 1)
            break; // MST is complete

        if (!djs.isOnSameSet(e.u, e.v)) {
            mst.push_back(e);
            djs.join(e.u, e.v);
        }
    }

    return mst;
}
