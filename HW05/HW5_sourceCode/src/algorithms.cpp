#include "../include/algorithms.hpp"
#include <algorithm>

std::vector<int> rabinKarpSearch(std::string pattern, std::string text) {
    std::vector<int> matches;
 
    int patLen  = pattern.size();
    int textLen = text.size();
 
    if (patLen == 0 || patLen > textLen) return matches;
 
    // Hash parameters
    const long long BASE = 31;
    const long long MOD  = 1e9 + 9;
 
    // Precompute BASE^(patLen-1) % MOD for rolling the window
    long long highPow = 1;
    for (int i = 0; i < patLen - 1; ++i)
        highPow = (highPow * BASE) % MOD;
 
    // Lambda: map a character to a non-zero integer value
    auto charVal = [](char c) -> long long { return c - 'A' + 1; };
 
    // Compute hash of the pattern and the first window of text
    long long patHash  = 0;
    long long winHash  = 0;
    for (int i = 0; i < patLen; ++i) {
        patHash = (patHash * BASE + charVal(pattern[i])) % MOD;
        winHash = (winHash * BASE + charVal(text[i]))    % MOD;
    }
 
    // Slide the window across the text
    for (int i = 0; i <= textLen - patLen; ++i) {
        // Hash match → verify character by character to rule out collisions
        if (winHash == patHash) {
            if (text.substr(i, patLen) == pattern)
                matches.push_back(i);
        }
 
        // Roll the hash forward (skip on the last iteration)
        if (i < textLen - patLen) {
            winHash = (winHash - charVal(text[i]) * highPow % MOD + MOD) % MOD;
            winHash = (winHash * BASE + charVal(text[i + patLen]))        % MOD;
        }
    }
 
    return matches;
}

void floydWarshall(int V, std::vector<std::vector<int>>& dist) {
    // For each intermediate vertex k, relax every (i, j) pair
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            // Skip rows where i→k is already unreachable to avoid overflow
            if (dist[i][k] >= 1e8) continue;
            for (int j = 0; j < V; ++j) {
                if (dist[k][j] >= 1e8) continue;
                int candidate = dist[i][k] + dist[k][j];
                if (candidate < dist[i][j])
                    dist[i][j] = candidate;
            }
        }
    }
}

int solveTSP(int mask, int pos, int n,
             const std::vector<std::vector<int>>& dist,
             std::vector<std::vector<int>>& dp) {
 
    // Base case: all cities visited → return cost of going back to city 0
    int fullMask = (1 << n) - 1;
    if (mask == fullMask) {
        return (dist[pos][0] >= 1e8) ? 1e8 : dist[pos][0];
    }
 
    // Return cached result if available
    if (dp[mask][pos] != -1) return dp[mask][pos];
 
    int best = 1e8; // Represents "infinity" / no valid tour found yet
 
    // Try every unvisited city as the next destination
    for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue;        // already visited
        if (dist[pos][next] >= 1e8)  continue;   // no direct edge
 
        int newMask  = mask | (1 << next);
        int subCost  = solveTSP(newMask, next, n, dist, dp);
 
        if (subCost < 1e8) {
            int totalCost = dist[pos][next] + subCost;
            best = std::min(best, totalCost);
        }
    }
 
    dp[mask][pos] = best;
    return best;
}