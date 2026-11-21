class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int maxSum = INT_MIN;
        int currentSum = 0;
        int n = nums.size();
 
        for (int i = 0; i < n; i++) {
            currentSum += nums[i];
 
            if (i >= k) {
                currentSum -= nums[i - k];
            }
 
            if (i >= k - 1) {
                maxSum = max(maxSum, currentSum);
            }
        }
 
        return static_cast<double>(maxSum) / k;
    }
};