#pragma once
#include <vector>
#include <string>
#include "linked_list.hpp"

class Graph {
private:
    int n;                                   // Number of nodes
    std::vector<LinkedList<int>> adj;        // Adjacency list for BFS search
    std::vector<std::vector<int>> adjMatrix; // Adjacency matrix for DP algorithms

public:
    // Constructor
    Graph(int nodes);

    // HW1/Project 1 style methods
    void insertEdge(int u, int v);
    std::vector<int> search(int start, int end);

    // HW5 specific methods
    void addEdge(int u, int v, int weight);
    std::vector<std::vector<int>> getDistanceMatrix();
};