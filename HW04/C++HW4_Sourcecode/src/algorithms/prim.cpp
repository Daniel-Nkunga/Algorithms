#include <graph.hpp>
#include <msort.hpp>
#include <disjoint_set.hpp>
#include <queue>

struct EdgeKeyComparison
{
    constexpr bool operator()(const Edge &a, const Edge &b) const noexcept
    {
        return a.w > b.w;
    }
};


std::vector<Edge> constructMSTPrim(Graph &G)
{
    std::vector<Edge> edges = G.exportEdges();
    int n = G.getN();

    std::priority_queue<Edge, std::vector<Edge>, EdgeKeyComparison> heap;

    std::vector<Edge> mst;
    std::vector<bool> inMST(n, false);

    // Step 1: Add all edges to the heap
    inMST[0] = true;
    for (const Edge &e : edges) {
        if (e.u == 0 || e.v == 0)
            heap.push(e);
    }

    // Step 2: Choose the cheapest edge
    while (!heap.empty() && (int)mst.size() < n - 1) {
        Edge top = heap.top();
        heap.pop();

        // Determine which endpoint is the new vertex being added
        int next = -1;
        if  (!inMST[top.v])      next = top.v;
        else if (!inMST[top.u])  next = top.u;
        else continue; // Avoid cycles

        // Add this edge to the MST and mark the new vertex
        inMST[next] = true;
        mst.push_back(top);

        // Expand the frontier
        for (const Edge &e : edges) {
            if ((e.u == next && !inMST[e.v]) ||
                (e.v == next && !inMST[e.u]))
                heap.push(e);
        }
    }

    return mst;
}
