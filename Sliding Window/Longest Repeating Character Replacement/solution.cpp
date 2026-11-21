class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int maxLength = 0;
        int maxCount = 0;
        int left = 0;
        int freq[26] = {0};
 
        for (int i = 0 ; i < n ; i++) {
            freq[s[i] - 'A']++;
 
            maxCount = max(maxCount, freq[s[i] - 'A']);
 
            if (i - left + 1 - maxCount > k) {
                freq[s[left] - 'A']--;
                left++;
            }
 
            maxLength = max(maxLength, i - left + 1);
        }
 
        return maxLength;
    }
};