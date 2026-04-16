#include <graph.hpp>
#include <queue>


struct EdgeKeyComparison
{
    constexpr bool operator()(const Edge &a, const Edge &b) const noexcept
    {
        return a.w > b.w;
    }
};

std::vector<int> searchShortestPath(Graph &G, int start, int destination)
{
    // std::priority_queue<Edge, std::vector<Edge>, EdgeKeyComparison> heap;
    //  If you want to use heap to optimize the minimum searching, you can use heap defined as above
    //       Insert: heap.push(Edge(u, -1, distance));
    //       Get Minimum: top = heap.top(); u = top.u; distance = top.w;
    //       Remove top: heap.pop(); (this function usually goes after the get minimum method)

    std::vector<int> path;

    // YOUR CODE HERE


    return path;
}
