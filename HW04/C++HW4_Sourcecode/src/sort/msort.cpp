#include <vector>
#include <msort.hpp>
#include <graph.hpp>

template <typename T>
void merge(std::vector<T> &array, int l, int m, int r) {
   // YOUR CODE HERE
}

template <typename T>
void msort(std::vector<T> &array, int l, int r) {
    // YOUR CODE HERE
}

// Explicit instantiation for Edge to satisfy the linker for Kruskal's algorithm
template void msort<Edge>(std::vector<Edge> &array, int l, int r);
// Explicit instantiation for int for unit testing
template void msort<int>(std::vector<int> &array, int l, int r);