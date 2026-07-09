#include "../include/graph.hpp"
#include "../include/linked_list.hpp"
#include "../include/queue.hpp"
#include <algorithm>

Graph::Graph(int nodes) : n(nodes) {
    adj.resize(n);
    // Adjacency Matrix initialized to INF for Floyd-Warshall compatibility
    adjMatrix.assign(n, std::vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) adjMatrix[i][i] = 0;
}

void Graph::insertEdge(int u, int v) {
    adj[u].insert(v);
    adj[v].insert(u); // Assuming undirected for campus map
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

std::vector<int> Graph::search(int start, int end) {
    if (start == end) return {start};
    
    Queue<int> q;
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);
    
    q.push(start);
    visited[start] = true;
    
    while(!q.empty()) {
        int u = q.pop();
        if(u == end) break;
        
        LinkedListNode<int>* curr = adj[u].getRoot();
        while(curr) {
            if(!visited[curr->value]) {
                visited[curr->value] = true;
                parent[curr->value] = u;
                q.push(curr->value);
            }
            curr = curr->next;
        }
    }
    
    std::vector<int> path;
    for(int v = end; v != -1; v = parent[v]) path.push_back(v);
    std::reverse(path.begin(), path.end());
    
    if(path.size() == 1 && path[0] != start) return {}; // No path found
    return path;
}

// Helper for algorithms.cpp
std::vector<std::vector<int>> Graph::getDistanceMatrix() {
    return adjMatrix;
}