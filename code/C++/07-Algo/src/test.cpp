//
// Created by Cheng Sun on 2023/7/30.
//


#include "../include/library.h"

class Solution {
public:
    static int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size());
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < cost.size(); i++) {
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        }
        return min(dp[cost.size() - 1], dp[cost.size() - 2]);
    }
};

int main() {
    int a[] = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<int> cost(a, a + sizeof(a) / sizeof(int));
    Solution solution;
    cout << solution.minCostClimbingStairs(cost) << endl;
}