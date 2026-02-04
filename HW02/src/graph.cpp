#include <graph.hpp>

Graph::Graph(int n) {
    this->n = n;
    this->e = std::vector<LinkedList<int> >(n, LinkedList<int>());
    this->reset();
}

Graph::~Graph() {
    this->e.clear();
    this->traces.clear();
    this->visited.clear();
}

void Graph::reset() {
    this->visited = std::vector<bool>(n, false);
    this->traces = std::vector<int>(n, -1);
}

bool Graph::isVisited(int u) {
    return this->visited[u];
}

void Graph::setVisited(int u) {
    this->visited[u] = true;
}
        
int Graph::trace(int u) {
    return this->traces[u];
}

void Graph::setTrace(int u, int v) {
    this->traces[u] = v;
}


void Graph::insertEdge(int u, int v, bool directed) {
    this->e[u].insert(v);
    if (not directed)
        this->e[v].insert(u);
}

std::vector<int> Graph::search(int start, int destination, void (*searchfn)(Graph &, int, int)) {
    searchfn(*this, start, destination); 
    std::vector<int> path;
    int u = destination;
    while (u != -1) {
        path.push_back(u);
        u = this->trace(u);
    }

    std::reverse(path.begin(), path.end());

    return path;
}
