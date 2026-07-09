#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "../include/graph.hpp" 
#include "../include/algorithms.hpp"
#include "../include/visualization.hpp"

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

int main() {
    // 1. Load Map Data
    std::string map_file = "assets/map_info.txt";
    std::ifstream reader(map_file);
    if (!reader.is_open()) {
        std::cerr << "Error: Could not open " << map_file << std::endl;
        return -1;
    }

    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<Building> buildings;

    for (int i = 0; i < n; ++i) {
        int id, x, y;
        std::string name;
        reader >> id >> name >> x >> y;
        name2index[name] = id;
        index2name[id] = name;
        buildings.push_back({id, name, x, y});
    }

    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        G.insertEdge(u, v); // Populates both AdjList and AdjMatrix
    }
    reader.close();

    // 2. Rabin-Karp: Identify a destination building by keyword
    std::cout << "\n========================================================" << std::endl;
    std::cout << "   ALGORITHM 1: SMART CAMPUS DIRECTORY SEARCH" << std::endl;
    std::cout << "========================================================" << std::endl;
    
    std::string search_query = "HILL";
    std::string campus_catalogue = "BELL_JBHT_HILL_WJWH_HAPG";
    
    std::cout << "Action: Scanning campus database for: [" << search_query << "]" << std::endl;
    std::cout << "Method: Rabin-Karp Rolling Hash (Digital Fingerprinting)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    std::vector<int> found = rabinKarpSearch(search_query, campus_catalogue);
    
    if (!found.empty()) {
        std::cout << "STATUS: Success! Building identified." << std::endl;
        for (int pos : found) {
            // Visualize where the match is in the string
            std::cout << "Location: Found '" << search_query << "' at position " << pos << " in the record." << std::endl;
            std::cout << "Visual: " << campus_catalogue << std::endl;
            std::cout << "        " << std::string(pos, ' ') << "^^^^" << std::endl;
        }
    } else {
        std::cout << "STATUS: Building not found." << std::endl;
        std::cout << "Check spelling or update the campus catalogue." << std::endl;
        return -1;
    }
    std::cout << "--------------------------------------------------------" << std::endl;

    // 3. Floyd-Warshall: Pre-calculate all shortest paths on campus
    std::cout << "\n========================================================" << std::endl;
    std::cout << "   ALGORITHM 2: CAMPUS-WIDE NAVIGATION CALCULATOR" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << "Status: Analyzing all possible walking routes..." << std::endl;

    std::vector<std::vector<int>> distMatrix = G.getDistanceMatrix();
    floydWarshall(n, distMatrix);
    
    std::cout << "Success: Shortest paths between all buildings calculated." << std::endl;
    std::cout << "\nHow to read the table below:" << std::endl;
    std::cout << "- The numbers represent the minimum number of 'steps' between buildings." << std::endl;
    std::cout << "- 'INF' means there is currently no connected path between those two buildings." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    // Header Row with Building Names
    std::cout << "FROM \\ TO\t";
    for(int i=0; i<5 && i<n; ++i) {
        // Truncate name to 4 letters for a clean table look
        std::string shortName = index2name[i].substr(0, 4);
        std::cout << shortName << "\t";
    }
    std::cout << "\n" << std::string(60, '-') << std::endl;
    
    // Data Rows
    for (int i = 0; i < 5 && i < n; i++) {
        std::string rowName = index2name[i].substr(0, 4);
        std::cout << rowName << " |     \t";
        
        for (int j = 0; j < 5 && j < n; j++) {
            if (distMatrix[i][j] >= 1e8) { // Checking against our 'Infinity'
                std::cout << "--- \t"; 
            } else if (i == j) {
                std::cout << "0 \t"; // Staying put
            } else {
                std::cout << distMatrix[i][j] << " \t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Example: To get from " << index2name[0] << " to " << index2name[1] 
              << ", it takes " << distMatrix[0][1] << " connection(s)." << std::endl;

    // 4. TSP: Find the optimal tour for a mission (visit first 4 buildings)
    std::cout << "\n========================================================" << std::endl;
    std::cout << "   ALGORITHM 3: EFFICIENT CAMPUS TOUR PLANNER (TSP)" << std::endl;
    std::cout << "========================================================" << std::endl;
    
    int tourSize = 4; // Number of buildings to include in the tour
    if (n >= tourSize) {
        std::cout << "Mission: Visit " << tourSize << " locations and return to start with minimum walking." << std::endl;
        std::cout << "Target Stops: ";
        for(int i = 0; i < tourSize; ++i) {
            std::cout << index2name[i] << (i < tourSize - 1 ? " -> " : " -> [Return]");
        }
        std::cout << std::endl;

        std::cout << "Status: Solving the 'Traveling Salesperson' puzzle..." << std::endl;

        // DP with Bitmasking initialization
        std::vector<std::vector<int>> tspDP((1 << tourSize), std::vector<int>(tourSize, -1));
        int optimalCost = solveTSP(1, 0, tourSize, distMatrix, tspDP);
        
        std::cout << "--------------------------------------------------------" << std::endl;
        std::cout << "RESULT: Optimal route identified." << std::endl;
        std::cout << "Total Walking Distance: " << optimalCost << " connections." << std::endl;
        std::cout << "Efficiency: This is the shortest possible path out of all " 
                  << tourSize << "! potential combinations." << std::endl;
    } else {
        std::cout << "Notice: Map size too small for a multi-stop tour optimization." << std::endl;
        return -1;
    }
    std::cout << "========================================================" << std::endl;

    // 5. Visualization (Optional OpenCV)
#ifdef OPENCV
    std::cout << "Displaying Campus Map..." << std::endl;
    //drawCampus(buildings, {}); // Draws the base map nodes
    
    // Example: Highlight the path found by BFS from BELL (0) to HAPG (4)
    std::vector<int> missionPath = G.search(0, 4);
    drawPath(missionPath, buildings);
#else
    std::cout << "OpenCV not enabled. Run 'make OPENCV=1' to see the map." << std::endl;
#endif

    return 0;
}