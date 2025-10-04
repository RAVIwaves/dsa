/*
    Problem:
        11. Container With Most Water
        https://leetcode.com/problems/container-with-most-water
    Solution:
        Author: Ravi Lahare
        Date: 2025-10-04
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // partitioning problem into two subproblems 1.left bar is bigger 2.right bar is bigger
    int maxArea_v1(vector<int>& height) {
        int ans = maxAreaLeftBarBigger(height);
        reverse(height.begin(), height.end());
        ans = max(ans, maxAreaLeftBarBigger(height));
        return ans;
    }

    // container with left bar bigger, iterating for right bar and selecting leftmost bigger bar
    int maxAreaLeftBarBigger(vector<int>& height)
    {
        vector<int> leftTowersHeight, leftTowerIndex;
        int maxAns = 0;
        leftTowersHeight.push_back(height[0]);
        leftTowerIndex.push_back(0);
        for(int i=1 ; i<height.size() ; i++) {
            if(height[i]<=leftTowersHeight.back()) {
                int ind = lower_bound(leftTowersHeight.begin(), leftTowersHeight.end(), height[i]) - leftTowersHeight.begin();
                maxAns = max(maxAns, (i - leftTowerIndex[ind]) * height[i]);
            }
            else {
                leftTowersHeight.push_back(height[i]);
                leftTowerIndex.push_back(i);
            }
        }
        return maxAns;
    }

    // two pointer approach
    int maxArea_v2(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;
        while(left < right) {
            int currentArea = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, currentArea);
            if(height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }
};

int32_t main() {
    ios::sync_with_stdio(0), cin.tie(0); // for fast IO
    Solution s = Solution();

    vector<vector<int>> testCases = {
        {1,8,6,2,5,4,8,3,7},
        {1,1}
    };
    vector<int> expectedOutputs = {49, 1};

    for(int i=0 ; i<testCases.size() ; i++) {
        int result = s.maxArea_v2(testCases[i]);
        cout << "Test Case " << i+1 << ": ";
        if(result == expectedOutputs[i])
            cout << "Passed\n";
        else
            cout << "Failed (Expected " << expectedOutputs[i] << ", Got " << result << ")\n";
    }
    return 0;
}