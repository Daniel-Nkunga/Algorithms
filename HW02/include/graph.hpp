#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <linked_list.hpp>
#include <queue.hpp>

class Graph {
    private:
        int n; // Number of vertices 
        std::vector<LinkedList<int> > e; // Adjacent list 
        std::vector<int> traces;
        std::vector<bool> visited;
    public:
        Graph(int n);
        ~Graph();
        void insertEdge(int u, int v, bool directed = false);
        
        void reset();

        bool isVisited(int u);
        void setVisited(int u);
        
        int trace(int u);
        void setTrace(int u, int v);

        std::vector<int> search(int start, int destination, void (*searchfn)(Graph&, int, int));

        friend void bfs(Graph &G, int start, int destination);
        friend void dfs(Graph &G, int start, int destination);
        friend void rdfs(Graph &G, int start, int destination);

};

