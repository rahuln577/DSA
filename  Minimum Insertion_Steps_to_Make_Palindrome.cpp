/*
Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

 

Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.
*/
/*
1. The Strategy: Total Length Minus LPSEvery character that is already part of the Longest Palindromic Subsequence (LPS) doesn't need a partner added. Only the characters outside the LPS need corresponding insertions to balance out the palindrome.Find LPS Length: Compute LCS between s and reverse(s) (which equals LPS(s)).Calculate Insertions:$$\text{Minimum Insertions} = \text{Total Length} - \text{LPS}(s)$$
*/
class Solution {
public:
    int minInsertions(string s) {
        string s2{s};
        reverse(s2.begin(),s2.end());
        vector<vector<int>> dp(s.size()+1,vector<int>(s.size()+1,0));
        for(int i=1;i<=s.size();i++)
        {
            for(int j=1;j<=s.size();j++)
            {
                if(s[i-1] == s2[j-1])
                {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    continue;
                }
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return (s.size()-dp[s.size()][s.size()]);
    }
};