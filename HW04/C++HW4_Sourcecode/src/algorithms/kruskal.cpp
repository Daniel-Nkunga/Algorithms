#include <graph.hpp>
#include <msort.hpp>
#include <disjoint_set.hpp>


std::vector<Edge> constructMSTKruskal(Graph &G)
{
    std::vector<Edge> edges = G.exportEdges(); // Graph's edges
    // DisjointSet djs(G.n);
    // Use Disjoint Set to check whether two vertices are on the same set
    // Usage: Check djs.isOnSameSet(u, v); Check is u and v is on the same set or not
    //              djs.join(u, v); Join sets of u and v into the same set

    std::vector<Edge> mst;
    DisjointSet djs(G.getN());
    // YOUR CODE HERE


    return mst;
}
