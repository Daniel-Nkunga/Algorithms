#pragma once
#include <string>
#include <vector>

std::vector<int> rabinKarpSearch(std::string pattern, std::string text);
void floydWarshall(int V, std::vector<std::vector<int>>& dist);
int solveTSP(int mask, int pos, int n, const std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& dp);