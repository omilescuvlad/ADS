# 643. Maximum Average Subarray I

[View the problem on LeetCode](https://leetcode.com/problems/maximum-average-subarray-i/)

## Problem

Given an integer array `nums` and an integer `k`, find the largest average among all groups of exactly `k` consecutive elements.

The array has between 1 and 100,000 elements, `k` is between 1 and the length of the array, and each element is between −10,000 and 10,000. The answer is accepted if its absolute error is less than 10⁻⁵.

## Solution

Every window has the same length, so the window with the largest sum also has the largest average. We can keep track of the largest sum and divide by `k` at the end.

The loop adds `nums[i]` to the running sum on every iteration. Once the window is full, adding a new element means the leftmost element has to leave. This is the part of the code that removes it.

```cpp
if (i >= k) {
    currentSum -= nums[i - k];
}
```

For example, when `k = 4` and `i = 4`, the new window covers indices 1 through 4. The element at index `i - k`, which is `0`, is the one that leaves.

The check `i >= k - 1` controls when the sum counts toward the answer. With `k = 4`, the first complete window ends at index 3. The first removal happens one iteration later, at index 4.

## Example

With `[1, 12, -5, -6, 50, 3]` and `k = 4`, the first window has a sum of 2. When 50 enters and 1 leaves, the sum becomes 51. On the next slide, 3 enters and 12 leaves, so the sum drops to 42. The largest sum is 51, which gives an average of 12.75.

## Complexity Analysis

- **Time complexity `O(n)`**. The algorithm makes one pass through the array and updates the sum in constant time at each step.
- **Auxiliary space `O(1)`**. The algorithm uses a fixed number of variables and does not store a separate copy of the window.

## Takeaway

When a problem asks about exactly `k` consecutive elements, check whether you can reuse the previous window's result. Here, adding the incoming element and subtracting the outgoing one gives you the next sum without adding up all `k` elements again.