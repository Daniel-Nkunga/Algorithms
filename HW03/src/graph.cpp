#include <graph.hpp>



Graph::Graph(int n) {
    this->n = n;
    this->e = std::vector<LinkedList<std::pair<int, int> > >(n, LinkedList<std::pair<int, int> >());
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
    this->dist = std::vector<int>(n, 1000000000LL);
}

int &Graph::distance(int u) {
    return this->dist[u];
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


void Graph::insertEdge(int u, int v, int w, bool directed) {
    this->e[u].insert(std::pair<int, int>(v, w));
    if (not directed)
        this->e[v].insert(std::pair<int, int>(u, w));
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
