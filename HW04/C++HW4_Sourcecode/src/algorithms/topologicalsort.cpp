#include "topologicalsort.hpp"
#include <queue>

std::vector<int> topologicalSort(Graph& graph) {
    int n = graph.getN();

    // Initialize in-degree array (number of incoming edges for each vertex)
    std::vector<int> inDegree(n, 0);
    std::vector<Edge> edges = graph.exportEdges();

    // Count incoming edges for each vertex
    for (const Edge& e : edges) {
        inDegree[e.v]++;
    }

    // Seed queue with all vertices that have no incoming edges
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0)
            q.push(i);
    }

    // BFS: process each node, reduce neighbors' in-degrees
    std::vector<int> result;
    result.reserve(n);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (const Edge& e : edges) {
            if (e.u == node) {
                inDegree[e.v]--;
                if (inDegree[e.v] == 0)
                    q.push(e.v);
            }
        }
    }

    // If not all nodes were visited, a cycle exists
    if ((int)result.size() != n)
        return {};

    return result;
}