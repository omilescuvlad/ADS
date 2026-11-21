# Maximum Average Subarray I

This is [LeetCode 643: Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/).

Given an array `nums` and a number `k`, the goal is to find the highest average among all groups of exactly `k` consecutive elements.

## My approach

I use a fixed-size sliding window. Every window has the same number of elements, so the biggest sum also gives me the biggest average. I keep track of the best sum and divide by `k` once at the end.

## Building the first window

At each index, I add the new element with `currentSum += nums[i]`. With `k = 4`, the first full window covers indices `0` through `3`. That's why I only compare sums once `i` reaches `k - 1`.

```cpp
if (i >= k - 1) {
    maxSum = max(maxSum, currentSum);
}
```

I start `maxSum` at `INT_MIN` so a negative sum can still become the best one. Starting at `0` would give me the wrong answer if every window had a negative sum.

## Moving the window

Once I have a full window, adding a new element means one has to leave. I already have the previous window's sum, so I can reuse it by adding the new rightmost element and subtracting the old leftmost one.

```cpp
if (i >= k) {
    currentSum -= nums[i - k];
}
```

Here's how I get **`i - k`**. The new window ends at `i`, so its first index is `i - k + 1`. The element I need to remove is one spot before that, at `i - k`.

For example, with `[1, 12, -5, -6, 50, 3]` and `k = 4`, the first window is `[1, 12, -5, -6]` and its sum is `2`.

When `i` reaches `4`, `50` comes in. The new window starts at index `1`, so the `1` at index `0` leaves. The new sum is `2 + 50 - 1 = 51`. On the next slide, `3` comes in and `12` leaves, giving me `51 + 3 - 12 = 42`.

The best sum is `51`, so the answer is `51 / 4 = 12.75`. I use `static_cast<double>(maxSum) / k` to keep the decimal part.

## Sliding window takeaway

When I see **exactly `k` consecutive elements**, I check what changes when the window moves one spot. Here, `k - 1` elements stay the same, so I only have to account for the one coming in and the one going out.

Time complexity is `O(n)` because I make one pass through the array. Extra space is `O(1)` because I only store a few variables.
