#include <search.hpp>

void rdfs(Graph &G, int start, int destination) {
    // YOUR CODE HERE
    int numberOfAdjacencyNodes = G.e[start].size();
    LinkedListNode<int> *p = G.e[start].getRoot();
    for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) {
        int v = p->value;
        // YOUR CODE HERE
    }
}
