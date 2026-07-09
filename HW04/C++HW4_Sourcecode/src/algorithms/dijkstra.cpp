#include <graph.hpp>
#include <queue>
#include <climits>

struct EdgeKeyComparison
{
    constexpr bool operator()(const Edge &a, const Edge &b) const noexcept
    {
        return a.w > b.w;
    }
};

std::vector<int> searchShortestPath(Graph &G, int start, int destination)
{
    int n = G.getN();
    std::vector<Edge> edges = G.exportEdges();

    std::priority_queue<Edge, std::vector<Edge>, EdgeKeyComparison> heap;

    std::vector<int> path;

    // Step 1: Initialize distances to infinity and traces to -1
    G.reset();
    for (int i = 0; i < n; i++)
        G.distance(i) = INT_MAX;

    G.distance(start) = 0;
    heap.push(Edge(start, -1, 0));

    // Step 2: Process new nodes
    while (!heap.empty()) {
        Edge top = heap.top();
        heap.pop();

        int u = top.u;

        // Skip if we already finalized this node
        if (G.isVisited(u))
            continue;
        G.setVisited(u);

        // Early exit: once we pop the destination it has its final shortest distance
        if (u == destination)
            break;

        // Relax all edges adjacent to u
        for (const Edge &e : edges) {
            int v   = -1;
            if      (e.u == u) v = e.v;
            else if (e.v == u) v = e.u; // undirected: check both directions
            else continue;

            if (!G.isVisited(v) && G.distance(u) != INT_MAX &&
                G.distance(u) + e.w < G.distance(v))
            {
                G.distance(v) = G.distance(u) + e.w;
                G.setTrace(v, u); // remember how to get to start
                heap.push(Edge(v, -1, G.distance(v)));
            }
        }
    }

    // Step 3: Reconstruct path by walking traces back from destination to start
    if (G.distance(destination) == INT_MAX)
        return path; // destination unreachable

    for (int cur = destination; cur != start; cur = G.trace(cur)) {
        path.push_back(cur);
        if (G.trace(cur) == -1) // no valid path
            return {};
    }
    path.push_back(start);

    // Reverse to get path from start
    std::reverse(path.begin(), path.end());

    return path;
}