/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
*/

/*
At each index if the characters in both the strings are same then move -1 in both and add +1 to the value.
IF it is not equal you can either move ind1 back or ind2 back and calculate the max.
*/

class Solution {
public:
    int calc(string& text1, string& text2,int ind1,int ind2,map<pair<int,int>,int>& dp)
    {
        if(ind1<0 || ind2<0)return 0;
        if(dp.find({ind1,ind2})!=dp.end())return dp[{ind1,ind2}];
        if(text1[ind1] == text2[ind2])return (dp[{ind1,ind2}] = 1+calc(text1,text2,ind1-1,ind2-1,dp));
        return (dp[{ind1,ind2}] = max(calc(text1,text2,ind1-1,ind2,dp),calc(text1,text2,ind1,ind2-1,dp)));
    }
    int longestCommonSubsequence(string text1, string text2) {
        map<pair<int,int>,int> dp;
        return calc(text1,text2,text1.size()-1,text2.size()-1,dp);
    }
};