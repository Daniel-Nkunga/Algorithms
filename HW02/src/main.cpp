#include <iostream>
#include <vector>
#include <linked_list.hpp> 
#include <graph.hpp> 
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <search.hpp>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

/*******************************************************************************/
//This Section is for the Grader. Do not modify this section.
// Global constant filename. For Grading purpose. Don't modify this variable.
const std::string testcases = "../HW2-testcase/HW2_testcases.txt";
const std::string map_info_testcases = "../HW2-testcase/map_info.txt";

// Function for Grading purpose. Don't modify this function.
std::string searchOnCampus(std::string start, std::string destination, std::string algName, std::string map_file);
void testCases() {
    std::ifstream inputFile(testcases);
    
    int score = 0;

    if (!inputFile.is_open()) {
        return ;
    }

    int testCases;
    // 1. Read the number of test cases (the '4' at the top)
    if (!(inputFile >> testCases)) {
        std::cerr << "Error: Invalid file format (no test case count)." << std::endl;
        return ;
    }
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string start, destination, alg;
    
    // 2. Loop exactly 'testCases' times
    for (int i = 0; i < testCases; ++i) {
        // 3. Extract the two words on each line
        if (inputFile >> alg >>start >> destination) {
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string expectedPath;
            if (std::getline(inputFile, expectedPath)) {
                // Now you can call your function and compare
                std::cout << "\n-------------------------------" << std::endl;
                std::string result = searchOnCampus(start, destination, alg, map_info_testcases);
                
                std::cout << "Test Case " << i + 1 << ":" << alg << std::endl;
                std::cout << " Expected: " << expectedPath << std::endl;
                if (result == expectedPath) {
                    std::cout << "The strings are equal!" << std::endl;
                    score += 5;
                } else {
                    std::cout << "The strings are different." << std::endl;
                }
                std::cout << "-------------------------------" << std::endl;
            }
        } else {
            std::cerr << "Warning: Expected more lines than found in file." << std::endl;
            break;
        }
    } 
    
    std::cout<< "Total Score: " << score << " / " << testCases * 5 << std::endl;
}
// End of Grader section
/*******************************************************************************/


bool testGraph(std::string algName) {
    Graph G(6);
    G.insertEdge(0, 1);
    G.insertEdge(1, 2);
    G.insertEdge(1, 3);
    G.insertEdge(2, 4);
    G.insertEdge(4, 3);
    G.insertEdge(4, 5);

    void (*searchfn)(Graph &, int, int);
    if (algName == "bfs")
        searchfn = bfs;
    else if (algName == "dfs")
        searchfn = dfs;
    else
        searchfn = rdfs;


    std::cout << "Path from 0 to 5 by " << algName << ": " ;
    std::vector<int> path = G.search(0, 5, searchfn);
    for (int i = 0; i < path.size(); ++i) 
        std::cout << path[i] << " ";
    std::cout << "\n";
    
    return true;
}

std::string searchOnCampus(std::string start = "BELL", std::string destination = "HAPG", std::string algName = "bfs", std::string map_file = "assets/map_info.txt") {
    std::ifstream reader(map_file);
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i) {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);

    void (*searchfn)(Graph &, int, int);
    if (algName == "bfs")
        searchfn = bfs;
    else if (algName == "dfs")
        searchfn = dfs;
    else
        searchfn = rdfs;


    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        G.insertEdge(u, v);
    }

    std::vector<int> path = G.search(name2index[start], name2index[destination], searchfn);

     std::stringstream ss;

    // 1. Add the initial part of the path
    ss << "Path from " << start << " to " << destination << ": " << start;

    // 2. Add the remaining nodes using your loop
    for (size_t i = 1; i < path.size(); ++i) {
        ss << " -> " << index2name[path[i]];
    }

    // 3. Convert the stream to a single string
    std::string pathString = ss.str();

    // 4. Output the final string
    std::cout << pathString << std::endl;
    
    std::cout << "\n";

#ifdef OPENCV
   cv::Mat image = cv::imread("assets/map.png");
    for (int i = 0; i < n; ++i) {
        cv::circle(image, cv::Point(xs[i], ys[i]), 10, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, index2name[i],  cv::Point(xs[i], ys[i]-10),  cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }

    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) 
            cv::line(image, cv::Point(xs[path[i]], ys[path[i]]), cv::Point(xs[path[i-1]], ys[path[i-1]]), cv::Scalar(255, 0, 0), 4);
    }
    cv::imshow("Path from " + start + " to " + destination, image);
    std::cout << "Press ENTER on the image window to continue..." << std::endl;

    while (true) {
        // Wait for a key press
        int key = cv::waitKey(0); 

        // 13 is the ASCII code for Enter (Return)
        // Some systems might use 10, so it's safer to check both
        if (key == 13 || key == 10) {
            break; 
        }
        
        // Optional: close if 'q' or 'Esc' (27) is pressed too
        if (key == 27) break; 
    }

    cv::destroyWindow("Path from " + start + " to " + destination);

#else
    std::cout << "You have to use OpenCV to visualize your map road\n\nclear";
#endif
    return pathString;

}
int main(int argc, char **args) {
    std::string algName(args[1]);
    
    std::cout << "Perform unit test on your " << algName << " implementation" << std::endl;
    testGraph(algName);
    

    std::cout << "\n\n";
    
    searchOnCampus("JBHT", "HAPG", algName, "assets/map_info.txt");

    std::cout << "\n";

    //THE FOLLOWING FUNCTION IS FOR GRADING PURPOSE. DON'T MODIFY THIS FUNCTION.
    testCases();
    
}
