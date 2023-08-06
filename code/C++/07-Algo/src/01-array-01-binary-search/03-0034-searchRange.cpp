//
// Created by Cheng Sun on 2023/7/30.
//
#include "../../include/library.h"

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1; // 定义target在左闭右闭的区间里，[left, right]
        while (left <= right) { // 当left==right，区间[left, right]依然有效
            int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
            if (nums[middle] > target) {
                right = middle - 1; // target 在左区间，所以[left, middle - 1]
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，所以[middle + 1, right]
            } else { // nums[middle] == target
                return middle;
            }
        }
        // 最后循环退出的时候，left指向的肯定是比target第一个大的
        return left;
    }
};

int main() {
    vector<int> nums = {-1,0,3,5,9,12};
    int target = 9;
    Solution solution;
    cout << solution.searchInsert(nums, target) << endl;
}