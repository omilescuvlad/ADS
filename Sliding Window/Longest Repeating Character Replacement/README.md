# Longest Repeating Character Replacement

This is [LeetCode 424: Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/description/).

Given a string `s` and a number `k`, the goal is to find the longest substring I can turn into one repeated letter using at most `k` replacements.

## My approach

I use a sliding window and keep a count of each letter inside it. The cheapest way to make the whole window match is to keep whichever letter already appears the most and change the rest.

For example, `AABAB` has three `A`s and two `B`s. I can make it all `A`s with two changes, or all `B`s with three. So the minimum is `5 - 3 = 2`.

## Counting the letters

Whenever I add a letter on the right, I update its counter and check whether it sets a new record:

```cpp
freq[s[i] - 'A']++;
maxCount = max(maxCount, freq[s[i] - 'A']);
```

Say the window is `AAA` and I add a `B`. Since `'B' - 'A'` is `1`, I increment `freq[1]`, B's counter. A's counter is still `3`. The next line compares the old record of `3` with B's new count of `1`, so `maxCount` stays at `3`.

**Each letter has its own counter. `maxCount` stores just the number.** In `AAAB`, the change would be `B` to `A`, but all I need to calculate is `4 - 3 = 1`. The problem asks for the longest length, so there's no need to perform the swap or store which letter set the record.

## Moving the window

```cpp
if (i - left + 1 - maxCount > k) {
    freq[s[left] - 'A']--;
    left++;
}
```

`i - left + 1` gives me the window length, including both ends. I subtract `maxCount` and check the result against `k`. If it's over budget, I decrement the counter for the letter on the left and move `left` forward. Exactly `k` changes are allowed, which is why I use `>`.

I leave `maxCount` alone when a letter leaves the window. For example, with `k = 1`, `AABA` is a valid window of length 4. Adding a `B` gives me `AABAB`, so the check gives `5 - 3 = 2` and I drop the leftmost `A`.

That leaves `ABAB`, which actually takes two changes. `maxCount` is still `3` from `AABA`, and the window is still only 4 letters long. I already found a valid window of that length. To grow past 4, I need a new record of four matching letters in the current window.

```cpp
maxLength = max(maxLength, i - left + 1);
```

I update the best length after deciding whether to move `left`. Each iteration adds one letter and removes at most one, so the window either grows by one or stays the same size.

## Sliding window takeaway

I start by defining what makes a window valid. Here, the actual number of changes needed is **the window length minus the count of its most common letter**. I can update the letter counts as characters enter and leave the window, so I never have to recount the whole substring.

Time complexity is `O(n)`. Extra space is `O(1)` because I only need 26 letter counters.