#include <iostream>
#include <vector>
#include <linked_list.hpp> 
#include <graph.hpp> 
#include <string>
#include <map>
#include <fstream>
#include <search.hpp>
#include <bst.hpp>
#include <avl.hpp>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

/*******************************************************************************/
//This Section is for the Grader. Do not modify this section.
// Global constant filename. For Grading purpose. Don't modify this variable.
const std::string testcases = "../HW3-testcase/testcases.txt";
const std::string map_info_testcases = "../HW3-testcase/map_info.txt";

// Function for Grading purpose. Don't modify this function.
std::string searchOnCampus(std::string start, std::string destination, std::string map_file);
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
    std::string start, destination;

    // 2. Loop exactly 'testCases' times
    for (int i = 0; i < testCases; ++i) {
        // 3. Extract the two words on each line
        if (inputFile >> start >> destination) {
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string expectedPath;
            if (std::getline(inputFile, expectedPath)) {
                // Now you can call your function and compare
                std::cout << "\n-------------------------------" << std::endl;
                std::string result = searchOnCampus(start, destination, map_info_testcases);
                
                std::cout << "Test Case " << i + 1 << ":" << std::endl;
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



bool testBST() {
    BST<int> bst;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Insert " << i << " into BST" << std::endl;
        bst.insert(i);

        std::cout << "Find " << i << ". ";  
        if (bst.find(i) != NULL && bst.find(i)->key == i)
            std::cout << "Found " << i << " in BST" << std::endl;
        else
            return false;
        
        std::cout << "Find " << i+1 << ". ";  
        if (bst.find(i+1) == NULL)
            std::cout << "Not found " << i+1 << " in BST" << std::endl;
        else
            return false;

        std::cout << std::endl;
    }

    std::cout << "Maximum value in BST: ";
    if (bst.findMaximum() == NULL || bst.findMaximum()->key != 9)
        return false;
    else
        std::cout << bst.findMaximum()->key << std::endl << std::endl;
    
    
    for (int i = 0; i < 9; ++i) {
        std::cout << "Remove " << i << " out of BST" << std::endl;
        bst.remove(i);

        std::cout << "Find " << i << ". ";  
        if (bst.find(i) == NULL) 
            std::cout << "Not found " << i << " in BST" << std::endl;
        else
            return false;

        std::cout << "Find " << i+1 << ". ";  
        if (bst.find(i+1) != NULL && bst.find(i+1)->key == i+1)
            std::cout << "Found " << i+1 << " in BST" << std::endl;
        else
            return false;
        std::cout << std::endl;
    }

    return true;
}

template<class T>
bool isAVLValid(BSTNode<T>* node, T* minKey, T* maxKey) {
    if (node == NULL) return true;

    // 1. Check BST Property
    if ((minKey && node->key < *minKey) || (maxKey && node->key > *maxKey)) {
        std::cout << "[Error] BST property violated at key: " << node->key << std::endl;
        return false;
    }

    // 2. Check Height consistency and Balance Factor
    int leftH = (node->left) ? node->left->height : -1;
    int rightH = (node->right) ? node->right->height : -1;
    
    if (node->height != std::max(leftH, rightH) + 1) {
        std::cout << "[Error] Height property mismatch at node " << node->key << std::endl;
        return false;
    }
    
    if (std::abs(leftH - rightH) > 1) {
        std::cout << "[Error] Unbalanced node found at key: " << node->key << std::endl;
        return false;
    }

    return isAVLValid(node->left, minKey, &(node->key)) && 
           isAVLValid(node->right, &(node->key), maxKey);
}

bool testAVL() {
    AVL<int> avl;
    std::cout << "--- Starting AVL Unit Test ---" << std::endl;

    // 1. Test Insertion & Balancing
    for (int i = 0; i < 10; ++i) {
        std::cout << "Insert " << i << " into AVL" << std::endl;
        avl.insert(i);

        // Print Root Height to see balancing in action
        if (avl.getRoot() != NULL) {
            std::cout << "Current Tree Height (at root): " << avl.getRoot()->height << std::endl;
        }

        std::cout << "Find " << i << ". ";  
        if (avl.find(i) != NULL && avl.find(i)->key == i)
            std::cout << "Found " << i << " in AVL" << std::endl;
        else {
            std::cout << "Failed to find " << i << std::endl;
            return false;
        }

        // Validate structure after every insert
        if (!isAVLValid<int>(avl.getRoot(), (int*)NULL, (int*)NULL)) {
            std::cout << "Structural integrity check failed!" << std::endl;
            return false;
        }
        std::cout << std::endl;
    }

    // 2. Test Maximum
    std::cout << "Maximum value in AVL: ";
    if (avl.findMaximum() == NULL || avl.findMaximum()->key != 9) {
        std::cout << "Error in findMaximum" << std::endl;
        return false;
    }
    std::cout << avl.findMaximum()->key << std::endl << std::endl;

    

    // 3. Test Removal & Rebalancing
    for (int i = 0; i < 9; ++i) {
        std::cout << "Remove " << i << " out of AVL" << std::endl;
        avl.remove(i);

        std::cout << "Find " << i << ". ";  
        if (avl.find(i) == NULL) 
            std::cout << "Not found " << i << " in AVL" << std::endl;
        else {
            std::cout << "Error: " << i << " still found in AVL" << std::endl;
            return false;
        }

        std::cout << "Find " << i+1 << ". ";  
        if (avl.find(i+1) != NULL && avl.find(i+1)->key == i+1)
            std::cout << "Found " << i+1 << " in AVL" << std::endl;
        else
            return false;

        // Check if root height decreased or rebalanced correctly
        if (avl.getRoot() != NULL) {
            std::cout << "Tree height after removal: " << avl.getRoot()->height << std::endl;
        }

        if (!isAVLValid<int>(avl.getRoot(), (int*)NULL, (int*)NULL)) {
            std::cout << "Structural integrity check failed after removal!" << std::endl;
            return false;
        }
        std::cout << std::endl;
    }

    return true;
}

std::string searchOnCampus(std::string start = "BELL", std::string destination = "HAPG", std::string map_file = "assets/map_info.txt") {
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

    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        int dx = xs[u] - xs[v];
        int dy = ys[u] - ys[v];
        int w = dx * dx + dy * dy;
        G.insertEdge(u, v, w);
    }

    std::vector<int> path = G.search(name2index[start], name2index[destination], bfs);

    std::stringstream ss;   

    ss << "Shortest path from " << start  << " to " << destination << ": " << start;
    // 2. Add the remaining nodes using your loop
    for (size_t i = 1; i < path.size(); ++i) {
        ss << " -> " << index2name[path[i]];
    }

    // 3. Convert the stream to a single string
    std::string pathString = ss.str();

    // 4. Output the final string
    std::cout << pathString << std::endl;
    std::cout << "Total Distance: " << G.distance(name2index[destination]) << std::endl;

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
    //cv::resize(image, image, cv::Size(), 0.75, 0.75);
    cv::imshow("Shortest path from " + start + " to " + destination, image);
    cv::waitKey(0);

#else
    std::cout << "You have to use OpenCV to visualize your map road\n";
#endif

    return pathString;
}
int main(int argc, char **args) {
    
    std::cout << "Perform unit test on your BST implementation" << std::endl;
    if (testBST())
        std::cout << "Your BST implementation is correct" << std::endl;
    else {
        std::cout << "Your BST implementation is incorrect" << std::endl;
        return -1;
    }

    std::cout << "Perform unit test on your AVL implementation" << std::endl;
    
    if (testAVL()) {
        std::cout << "Your AVL implementation is correct" << std::endl;
    } else {
        std::cout << "Your AVL implementation is incorrect" << std::endl;
        return -1;
    }
    

    std::cout << "\n\n";
    
    searchOnCampus("JBHT", "HAPG");

    std::cout << "\n";

    //THE FOLLOWING FUNCTION IS FOR GRADING PURPOSE. DON'T MODIFY THIS FUNCTION.
    testCases();
    
}
