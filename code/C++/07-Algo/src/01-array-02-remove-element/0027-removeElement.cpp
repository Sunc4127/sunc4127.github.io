//
// Created by Cheng Sun on 2023/7/30.
//
#include "../../include/library.h"

// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            if (val != nums[right]) {
                nums[left++] = nums[right];
            }
        }
        return left;
    }
};

int main() {
    vector<int> nums = {0,1,2,2,3,0,4,2};
    int target = 2;
    Solution solution;
    cout << solution.removeElement(nums, target) << endl;
}