#pragma once
#include <vector>
#include <string>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

struct Building {
    int id;
    std::string name;
    int x;
    int y;
};

void drawCampus(const std::vector<Building>& buildings, const std::vector<std::pair<int, int>>& edges);
void drawPath(const std::vector<int>& path, const std::vector<Building>& buildings);