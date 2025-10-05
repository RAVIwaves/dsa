/*
    Problem:
        417. Pacific Atlantic Water Flow
        https://leetcode.com/problems/pacific-atlantic-water-flow
    Solution:
        Author: Ravi Lahare
        Date: 2025-10-05
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // multisource bfs: solution for individual ocean then combine results
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> ans, visited(n, vector<int>(m, 0));
        queue<array<int,2>> pq, aq;
        array<int,4> di = {0,1,0,-1};
        array<int,4> dj = {1,0,-1,0};
        for(int i=0 ; i<n ; i++) {
            pq.push({i,0});
            visited[i][0] = 1;
        }
        for(int j=1 ; j<m ; j++) {
            pq.push({0,j});
            visited[0][j] = 1;
        }
        while(!pq.empty()) {
            auto [i,j] = pq.front();
            pq.pop();
            for(int d=0 ; d<4 ;d++) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if(ni>=0 && ni<n && nj>=0 && nj<m && visited[ni][nj]==0 && heights[ni][nj]>=heights[i][j]) {
                    visited[ni][nj] = 1;
                    pq.push({ni,nj});
                }
            }
        }
        for(int i=0 ; i<n ; i++) {
            aq.push({i,m-1});
            visited[i][m-1] += 1;
            visited[i][m-1] *= -1;
        }
        for(int j=0 ; j<m-1 ; j++) {
            aq.push({n-1,j});
            visited[n-1][j] += 1;
            visited[n-1][j] *= -1;
        }
        while(!aq.empty()) {
            auto [i,j] = aq.front();
            aq.pop();
            for(int d=0 ; d<4 ;d++) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if(ni>=0 && ni<n && nj>=0 && nj<m && visited[ni][nj]>=0 && heights[ni][nj]>=heights[i][j]) {
                    visited[ni][nj] += 1;
                    visited[ni][nj] *= -1;
                    aq.push({ni,nj});
                }
            }
        }
        for(int i=0 ; i<n ; i++)
            for(int j=0 ; j<m ; j++)
                if(visited[i][j] == -2)
                    ans.push_back({i,j});
        return ans;
    }
};

int32_t main() {
    ios::sync_with_stdio(0), cin.tie(0); // for fast IO
    Solution s = Solution();

    vector<vector<vector<int>>> testCases = {
        {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}},
        {{1}}
    };
    vector<vector<vector<int>>> expectedOutputs = {
        {{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0}},
        {{0,0}}
    };

    for(int i=0 ; i<testCases.size() ; i++) {
        vector<vector<int>> result = s.pacificAtlantic(testCases[i]);
        cout << "Test Case " << i+1 << ": ";
        sort(result.begin(), result.end());
        sort(expectedOutputs[i].begin(), expectedOutputs[i].end());
        if(result == expectedOutputs[i])
            cout << "Passed\n";
        else
            cout << "Failed\n";
    }
    return 0;
}