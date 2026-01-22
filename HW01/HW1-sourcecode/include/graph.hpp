#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "linked_list.hpp"
#include "queue.hpp"

class Graph {
    private:
        int n; // Number of vertices 
        std::vector<LinkedList<int> > e; // Adjacent list 
    public:
        Graph(int n);
        ~Graph();
        void insertEdge(int u, int v, bool directed = false);
        std::vector<int> search(int start, int destination);
};

