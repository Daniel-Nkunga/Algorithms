#include <search.hpp>
#include <avl.hpp>

void bfs(Graph &G, int start, int destination) {
    // We use AVL for O(log n) efficiency to keep the priority queue balanced
    AVL<std::pair<int, int> > priorityQueue;

    G.reset();
    G.distance(start) = 0;
    
    // Insert initial node (distance, index)
    priorityQueue.insert(std::pair<int, int>(G.distance(start), start));
    G.setTrace(start, -1);

    while (true) {
        // --- UPDATED: Get the node with the SHORTEST distance ---
        BSTNode<std::pair<int, int>>* minNode = priorityQueue.findMinimum();
        
        if (minNode == NULL) break;

        std::pair<int, int> current = minNode->key;
        priorityQueue.remove(current);

        // Optimization: If we found a better way to 'u' already, skip this stale entry
        if (current.first > G.distance(current.second)) continue;

        int u = current.second;
        int dist = current.first;

        G.setVisited(u);

        if (u == destination) break;

        int numberOfAdjacencyNodes = G.e[u].size();
        LinkedListNode<std::pair<int, int> > *p = G.e[u].getRoot();
        for (int i = 0; i < numberOfAdjacencyNodes; i++, p = p->next) {
            int v = p->value.first;
            int weight = p->value.second;

            if (G.isVisited(v)) continue;

            // Relaxation Step
            if (dist + weight < G.distance(v)) {
                G.distance(v) = dist + weight;
                priorityQueue.insert(std::pair<int, int>(G.distance(v), v));
                G.setTrace(v, u);   
            }
        }
    }
}