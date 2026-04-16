#ifndef TOPOLOGICALSORT_HPP
#define TOPOLOGICALSORT_HPP

#include <vector>
#include "graph.hpp"

// Returns topological order or empty vector if graph is cyclic
std::vector<int> topologicalSort(Graph& graph);

#endif // TOPOLOGICALSORT_HPP
