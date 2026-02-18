/*
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2

*/

/*
This problem is Subarray Sum Equals K. To remember this at a glance, think of it as the "Prefix Sum Scavenger Hunt." Instead of checking every possible subarray, you look backward to see how many times you've seen a "matching" sum before.

1. The Strategy: The Gap Method
The core idea relies on a simple mathematical observation:
If the sum from the start to your current position is curSum, and you want to find a subarray that sums to k, you just need to know if there was a previous point where the sum was curSum - k.

Subarray Sum=Current Prefix Sum−Previous Prefix Sum
Prefix Sum: As you walk through the array, keep a running total (curSum).

The Map: Use an unordered_map to store how many times each prefix sum has occurred.

The Lookback: At each step, check the map: "How many times did I have a sum of curSum - k earlier?" Every time it happened, it means a subarray ending now sums to k.

2. Key Code Components
sums[curSum - k]

This is your target. If your current sum is 10 and you want a subarray of 7, you are looking for a moment in the past where the sum was 3.

If the map says you've seen the sum 3 three different times, you just found 3 new subarrays that satisfy the condition.

if(curSum == k) ans++

This handles the case where the subarray starts exactly from index 0.

Pro-tip: Many developers simplify this by initializing the map with sums[0] = 1 before the loop starts. This removes the need for this if check!

sums[curSum]++

After checking for the target, you "save" your current sum in the notebook (map) so future elements can use it as a reference.
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> sums;
        int curSum = 0;
        int ans = 0;
        for(int i=0;i<nums.size();i++)
        {
            curSum+=nums[i];
            if(sums.find(curSum-k)!=sums.end())
            {
                ans+=sums[curSum-k];
            }
            if(curSum == k)ans++;
            sums[curSum]++;
        }
        return ans;
    }
};