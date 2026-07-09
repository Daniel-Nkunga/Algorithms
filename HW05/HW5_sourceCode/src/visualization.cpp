#include "../include/visualization.hpp"
#include <iostream>

void drawCampus(const std::vector<Building>& buildings, const std::vector<std::pair<int, int>>& edges) {
#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    if (image.empty()) image = cv::Mat(800, 1200, CV_8UC3, cv::Scalar(255, 255, 255));
    for (const auto& edge : edges) {
        cv::line(image, cv::Point(buildings[edge.first].x, buildings[edge.first].y),
                 cv::Point(buildings[edge.second].x, buildings[edge.second].y), cv::Scalar(200, 200, 200), 2);
    }
    for (const auto& b : buildings) {
        cv::circle(image, cv::Point(b.x, b.y), 10, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, b.name, cv::Point(b.x, b.y - 10), cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }
    cv::imshow("Campus Map", image);
    cv::waitKey(0);
#else
    std::cout << "OpenCV disabled. Building count: " << buildings.size() << "\n";
#endif
}

void drawPath(const std::vector<int>& path, const std::vector<Building>& buildings) {
#ifdef OPENCV
    cv::Mat image = cv::imread("assets/map.png");
    if (image.empty()) return;
    for (size_t i = 1; i < path.size(); ++i) {
        cv::line(image, cv::Point(buildings[path[i-1]].x, buildings[path[i-1]].y),
                 cv::Point(buildings[path[i]].x, buildings[path[i]].y),  cv::Scalar(255, 0, 0), 4);
    }
    for (const auto& b : buildings) {
        cv::circle(image, cv::Point(b.x, b.y), 10, cv::Scalar(255, 0, 0), -1);
        cv::putText(image, b.name, cv::Point(b.x, b.y - 10), cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
    }
    cv::imshow("Calculated Path", image);
    while (true) {
        int key = cv::waitKey(0);
        if (key == 13 || key == 10 || key == 27) break; 
    }
    cv::destroyAllWindows();
#endif
}