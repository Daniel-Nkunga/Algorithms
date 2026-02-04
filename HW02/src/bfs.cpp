#include <search.hpp>

void bfs(Graph &G, int start, int destination) {
    Queue<int> queue;
    G.reset();
    // YOUR CODE HERE
    while (!queue.empty()) {
        int u = queue.pop();
        // YOUR CODE HERE
        int numberOfAdjacencyNodes = G.e[u].size();
        LinkedListNode<int> *p = G.e[u].getRoot();
        for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) {
            int v = p->value;
            // YOUR CODE HERE
        }
    }
}
