---
title: Sortinig_algorithms
date: 2021-11-07 12:20:40
permalink: /pages/ad7681/
categories:
  - data_Structure_and_Algorithm
tags:
  - 
---
-   冒泡排序的总体时间复杂度为O(N^2)

```java
int[] bubbleSort(int[] nums) {
    int N = nums.length;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
    return nums;
}
```



---





