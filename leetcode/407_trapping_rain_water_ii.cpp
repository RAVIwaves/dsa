/*
    Problem:
        407. Trapping Rain Water II
        https://leetcode.com/problems/trapping-rain-water-ii
    Solution:
        Author: Ravi Lahare
        Date: 2025-10-03
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // iteration method until no changes occur(stable state)
    int trapRainWater_v1(vector<vector<int>>& heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();
        vector<vector<int>> water(n, vector<int>(m, INT_MAX));
        for(int i = 0; i < n; i++) {
            water[i][0] = heightMap[i][0];
            water[i][m-1] = heightMap[i][m-1];
        }
        for(int j = 0; j < m; j++) {
            water[0][j] = heightMap[0][j];
            water[n-1][j] = heightMap[n-1][j];
        }
        bool changed = true;
        while (changed) {
            changed = false;
            for(int i=1 ; i<n-1 ; i++)
                for(int j=1 ; j<m-1 ; j++) {
                    int prevWater = water[i][j];
                    water[i][j] = max(min({water[i][j-1], water[i][j+1], water[i-1][j], water[i+1][j]}), heightMap[i][j]);
                    if(water[i][j] != prevWater) changed = true;
                }
        }
        int ans = 0;
        for(int i=0 ; i<n ; i++)
            for(int j=0 ; j<m ; j++)
                ans += water[i][j] - heightMap[i][j];
        return ans;
    }

    // priority queue + BFS method
    int trapRainWater_v2(vector<vector<int>>& heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();
        if(n<3 || m<3) return 0;
        vector<vector<bool>> visited(n, vector<bool>(m, 0)); 
        priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
        int ans = 0;
        vector<int> di = {0, 0, 1, -1};
        vector<int> dj = {1, -1, 0, 0};
        for(int i=0 ; i<n ; i++) {
            pq.push({heightMap[i][0], i, 0});
            pq.push({heightMap[i][m-1], i, m-1});
            visited[i][0] = true;
            visited[i][m-1] = true;
        }
        for(int j=1 ; j<m-1 ; j++) {
            pq.push({heightMap[0][j], 0, j});
            pq.push({heightMap[n-1][j], n-1, j});
            visited[0][j] = true;
            visited[n-1][j] = true;
        }
        while(!pq.empty()) {
            auto [h, i, j] = pq.top(); pq.pop();
            for(int d=0 ; d<4 ; d++) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if(ni >= 0 && ni < n && nj >= 0 && nj < m && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    if(heightMap[ni][nj] < h) ans += h - heightMap[ni][nj];
                    {heightMap[ni][nj] = max(heightMap[ni][nj], h);}
                    pq.push({heightMap[ni][nj], ni, nj});
                }
            }
        }
        return ans;
    }
};

int32_t main() {
    ios::sync_with_stdio(0), cin.tie(0); // for fast IO
    Solution s = Solution();

    vector<vector<vector<int>>> testCases = {
        {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}},
        {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}}  
    };
    vector<int> expectedOutputs = {4, 10};

    for(int i=0 ; i<testCases.size() ; i++) {
        int result = s.trapRainWater_v2(testCases[i]);
        cout << "Test Case " << i+1 << ": ";
        if(result == expectedOutputs[i])
            cout << "Passed\n";
        else
            cout << "Failed (Expected " << expectedOutputs[i] << ", Got " << result << ")\n";
    }
    return 0;
}