#include <iostream>
#include <vector>
#include <graph.hpp>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <hsort.hpp>
#include <msort.hpp>
#include <topologicalsort.hpp>
#include <algorithm>
#include "rbtree.hpp"
#include <stdexcept> // Required for std::runtime_error and std::out_of_range

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

// --- UNIT TEST FUNCTIONS ---

bool testSort(int sort)
{
    std::vector<int> data;
    int n = 20;
    for (int i = 0; i < n; ++i)
        data.push_back(rand() % 50);

    std::cout << "Original array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    if (sort == 0) {
        heapSort(data);
    } else if (sort == 1) {
        msort(data, 0, data.size());
    } else {
        std::cout << "Invalid sort type!" << std::endl;
        return false;
    }

    std::cout << "Sorted array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return std::is_sorted(data.begin(), data.end());
}

#if PRIM || KRUSKAL
bool testMST(int algo)
{
    Graph G(6);
    G.insertEdge(0, 1, 1);
    G.insertEdge(1, 2, 2);
    G.insertEdge(1, 3, 3);
    G.insertEdge(2, 4, 4);
    G.insertEdge(4, 3, 5);
    G.insertEdge(4, 5, 6);

    std::vector<Edge> tree;
    if (algo == 1)
    {
        tree = constructMSTPrim(G);
    }
    else if (algo == 2)
    {
        tree = constructMSTKruskal(G);
    }

    int totalCost = 0;
    for (int i = 0; i < tree.size(); ++i)
    {
        totalCost += tree[i].w;
    }
   std::cout << "Total Cost of Minimum Spanning Tree: " << totalCost << std::endl;

    return true;
}

void mstOnCampus(int algo)
{
    std::ifstream reader("assets/map_info.txt");
    if (!reader.is_open()) {
        std::cout << "Error: Could not open assets/map_info.txt" << std::endl;
        return;
    }
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i)
    {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        reader >> u >> v;
        int dx = xs[u] - xs[v];
        int dy = ys[u] - ys[v];
        int w = (int)sqrt(dx * dx + dy * dy);
        G.insertEdge(u, v, w);
    }

    std::vector<Edge> tree;
    if (algo == 1)
    {
        tree = constructMSTPrim(G);
    }
    else if (algo == 2)
    {
        tree = constructMSTKruskal(G);
    }

    int totalCost = 0;
    for (int i = 0; i < tree.size(); ++i)
    {
        totalCost += tree[i].w;
    }

    std::cout << "Total Cost of Minimum Spanning Tree: " << totalCost << std::endl;

#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    if (image.empty()) {
        std::cout << "Error: Could not load assets/map.png" << std::endl;
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        cv::circle(image, cv::Point(xs[i], ys[i]), 5, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, index2name[i], cv::Point(xs[i], ys[i] - 10), cv::FONT_HERSHEY_DUPLEX, 0.4, cv::Scalar(255, 0, 0), 1);
    }
    for (int i = 0; i < tree.size(); ++i)
    {
        int u = tree[i].u;
        int v = tree[i].v;
        cv::line(image, cv::Point(xs[u], ys[u]), cv::Point(xs[v], ys[v]), cv::Scalar(255, 0, 0), 4);
    }
    cv::imshow("Minimum Spanning Tree", image);
    cv::waitKey(0);
#else
    std::cout << "You have to use OpenCV to visualize your map\n";
#endif
}
#endif

#ifdef DIJKSTRA
bool testShortestPath()
{
    Graph G(6);
    G.insertEdge(0, 1, 1);
    G.insertEdge(1, 2, 2);
    G.insertEdge(1, 3, 3);
    G.insertEdge(2, 4, 4);
    G.insertEdge(4, 3, 5);
    G.insertEdge(4, 5, 6);

    int startNode = 0;
    int destNode = 5;

    std::vector<int> path = G.search(startNode, destNode);

    // HANDLE FALSE: Check if the path is empty or unreachable
    if (path.empty()) {
        std::cout << "Path from " << startNode << " to " << destNode << ": NO PATH FOUND" << std::endl;
        return false; 
    }

    // Additional check: If the path doesn't end at the destination, it's invalid
    if (path.back() != destNode) {
        std::cout << "Pathfinding error: Destination not reached." << std::endl;
        return false;
    }

    std::cout << "Path from " << startNode << " to " << destNode << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
    }
    std::cout << std::endl;

    return true;
}

void searchOnCampus(std::string start = "BELL", std::string destination = "HAPG")
{
    std::ifstream reader("assets/map_info.txt");
    if (!reader.is_open()) return;
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i)
    {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        reader >> u >> v;
        int dx = xs[u] - xs[v];
        int dy = ys[u] - ys[v];
        int w = (int)sqrt(dx * dx + dy * dy);
        G.insertEdge(u, v, w);
    }

    std::vector<int> path = G.search(name2index[start], name2index[destination]);

    std::cout << "Path from " << start << " to " << destination << ": ";
    for (int i = 0; i < path.size(); ++i) {
        std::cout << index2name[path[i]] << (i == (int)path.size() - 1 ? "" : " -> ");
    }
    std::cout << "\n";

#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    if (image.empty()) return;
    for (int i = 0; i < n; ++i)
    {
        cv::circle(image, cv::Point(xs[i], ys[i]), 5, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, index2name[i], cv::Point(xs[i], ys[i] - 10), cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }
    for (int i = 1; i < (int)path.size(); ++i)
    {
        cv::line(image, cv::Point(xs[path[i]], ys[path[i]]), cv::Point(xs[path[i - 1]], ys[path[i - 1]]), cv::Scalar(255, 0, 0), 4);
    }
    cv::imshow("Path from " + start + " to " + destination, image);
    cv::waitKey(0);
#else
    std::cout << "You have to use OpenCV to visualize your map road\n";
#endif
}
#endif

// --- COMBINED ALGORITHM DEMO ---



void combinedAlgorithmDemo()
{
    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- STARTING INTEGRATED ALGORITHM STACK DEMO ---" << std::endl;
    std::cout << "==========================================================" << std::endl;

    try {
        // 1. Red-Black Tree (Storage & Retrieval)
        RedBlackTree buildingDB;
        buildingDB.insert(0, 100, 100); 
        buildingDB.insert(1, 200, 300); 
        buildingDB.insert(2, 400, 150); 
        std::cout << "[Step 1] RB-Tree: Coordinates stored for Buildings 0, 1, and 2." << std::endl;

        RBNode* b0 = buildingDB.search(0);
        RBNode* b1 = buildingDB.search(1);
        RBNode* b2 = buildingDB.search(2);

        // HANDLE FALSE: Validation check for Tree Retrieval
        if (!b0 || !b1 || !b2) {
            throw std::runtime_error("RB-Tree Error: One or more buildings could not be retrieved.");
        }

        std::cout << " -> Found Building " << b0->data << " at (" << b0->x << ", " << b0->y << ")" << std::endl;
        std::cout << " -> Found Building " << b1->data << " at (" << b1->x << ", " << b1->y << ")" << std::endl;
        std::cout << " -> Found Building " << b2->data << " at (" << b2->x << ", " << b2->y << ")" << std::endl;

        // 2. Graph Construction with Dynamic Weights
        Graph G(3);
        int d01 = (int)sqrt(pow(b1->x - b0->x, 2) + pow(b1->y - b0->y, 2));
        int d12 = (int)sqrt(pow(b2->x - b1->x, 2) + pow(b2->y - b1->y, 2));
        int d02 = (int)sqrt(pow(b2->x - b0->x, 2) + pow(b2->y - b0->y, 2));

        G.insertEdge(0, 1, d01);
        G.insertEdge(1, 2, d12);
        G.insertEdge(0, 2, d02);
        
        std::cout << "\n[Step 2] Graph: Edges created with Euclidean weights:" << std::endl;
        std::cout << " -> Edge (0,1) weight: " << d01 << std::endl;
        std::cout << " -> Edge (1,2) weight: " << d12 << std::endl;
        std::cout << " -> Edge (0,2) weight: " << d02 << std::endl;

        // 3. Kruskal's MST (Optimization)
#ifdef KRUSKAL
        std::cout << "\n[Step 3] Kruskal: Constructing Minimum Spanning Tree..." << std::endl;
        // Pass by reference is safer (ensure your signature was updated in graph.hpp)
        std::vector<Edge> mst = constructMSTKruskal(G);
        
        if (mst.empty()) {
            throw std::runtime_error("Kruskal Error: MST could not be formed (Graph may be disconnected).");
        }

        int mstCost = 0;
        for (const auto& edge : mst) {
            std::cout << " -> Added Edge (" << edge.u << "," << edge.v << ") w:" << edge.w << std::endl;
            mstCost += edge.w;
        }
        std::cout << "Total MST Cost: " << mstCost << std::endl;
#endif

        // 4. Dijkstra's (Navigation)
#ifdef DIJKSTRA
        std::cout << "\n[Step 4] Dijkstra: Calculating shortest path from 0 to 2..." << std::endl;
        std::vector<int> path = G.search(0, 2);

        // HANDLE FALSE: Check if destination was reached
        if (path.empty() || path.back() != 2) {
            throw std::runtime_error("Dijkstra Error: No path found between specified nodes.");
        }

        std::cout << " -> Shortest Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        std::cout << std::endl;
#endif

        // 5. Heap Sort (Ranking/Analytics)
        std::vector<int> congestion = {85, 12, 44, 98, 30};
        std::cout << "\n[Step 5] HeapSort: Sorting traffic congestion scores..." << std::endl;
        std::cout << " -> Original: 85 12 44 98 30" << std::endl;
        heapSort(congestion);
        std::cout << " -> Sorted:   ";
        for (int score : congestion) std::cout << score << " ";
        std::cout << std::endl;

    } 
    catch (const std::out_of_range& e) {
        std::cerr << "\n[CRITICAL MEMORY ERROR]: " << e.what() << " (Check vector indices)" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\n[ALGORITHM LOGIC ERROR]: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[UNKNOWN EXCEPTION]: " << e.what() << std::endl;
    }

    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- INTEGRATED DEMO COMPLETE ---" << std::endl;
    std::cout << "==========================================================" << std::endl;
}// --- MAIN EXECUTION ---

int main(int argc, char **args)
{
    std::cout << "Perform unit test on heap sort" << std::endl;
    if (testSort(0))
        std::cout << "Your sorting implementation is correct\n" << std::endl;
    else
    {
        std::cout << "Your sorting implementation is incorrect\n" << std::endl;
        return 1;
    }

    std::cout << "Perform unit test on Merge sort" << std::endl;
    if (testSort(1))
        std::cout << "Your sorting implementation is correct\n" << std::endl;
    else
    {
        std::cout << "Your sorting implementation is incorrect\n" << std::endl;
        return 1;
    }  
    
    std::cout << std::endl << "Perform unit test on Topological sort" << std::endl;
    Graph g(6);
    g.insertEdge(5, 0, 1, true); 
    g.insertEdge(5, 2, 1, true); 
    g.insertEdge(4, 0, 1, true); 
    g.insertEdge(4, 1, 1, true); 
    g.insertEdge(2, 3, 1, true); 
    g.insertEdge(3, 1, 1, true); 

    std::vector<int> result = topologicalSort(g);
    std::cout << "Topological Sort: ";
    for (int node : result) std::cout << node << " ";
    std::cout << std::endl;
    if (result.size() == 6) {
        std::cout << "Topological Sort implementation is correct." << std::endl;
    } else {
        std::cout << "Topological Sort implementation is incorrect. Not all nodes processed." << std::endl;
        return 1;
    }

#ifdef PRIM
    
    std::cout << "Perform unit test of the Prim's algorithm" << std::endl;
    testMST(1);
    std::cout << std::endl;
    mstOnCampus(1);
#endif

#ifdef KRUSKAL
    std::cout << std::endl << "Perform unit test of the Kruskal's algorithm" << std::endl;
    testMST(2);
    std::cout << std::endl;
    mstOnCampus(2);
#endif

#ifdef DIJKSTRA
    std::cout << std::endl << "Perform unit test of the Dijkstra algorithm" << std::endl;
    testShortestPath();
    std::cout << std::endl;
    searchOnCampus("SAEF", "GRAD");
#endif

#ifdef INTEGRATED
    std::cout << std::endl << "Perform unit test of the Red-Black Tree" << std::endl;
    combinedAlgorithmDemo();
#endif

    return 0;
}