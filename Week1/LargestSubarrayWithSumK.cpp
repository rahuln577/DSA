/*
Given an array arr[] containing integers and an integer k, your task is to find the length of the longest subarray where the sum of its elements is equal to the given value k. If there is no subarray with sum equal to k, return 0.

Examples:

Input: arr[] = [10, 5, 2, 7, 1, -10], k = 15
Output: 6
Explanation: Subarrays with sum = 15 are [5, 2, 7, 1], [10, 5] and [10, 5, 2, 7, 1, -10]. The length of the longest subarray with a sum of 15 is 6.
Input: arr[] = [-5, 8, -14, 2, 4, 12], k = -5
Output: 5
Explanation: Subarrays with sum = -5 are [-5] and [-5, 8, -14, 2, 4]. The length of the longest subarray with a sum of -5 is 5.
Input: arr[] = [10, -10, 20, 30], k = 5
Output: 0
Explanation: No subarray with sum = 5 is present in arr[].
*/

/*
The Strategy

Imagine walking down a path, keeping a running total (Prefix Sum) of the steps you've taken.

The Goal: You want to find two points where the difference between their totals is exactly k.

The Map: You carry a notebook (presum). Every time you reach a new total, you write down: "I reached total X at step i." 3. The Check: At every step, you ask: "Have I ever seen a total equal to CurrentSum - k before?"

If yes, the section between that old spot and your current spot adds up to k.

The Rule: Only record a sum the first time you see it. This keeps the subarray as long as possible.

The Logic Flow

Action	Why?
sum += arr[i]	Update your running total.
if(sum == k)	If the total from the very beginning is k, the length is just i+1.
m[sum - k]	Check the map for the "needed" previous sum to make the gap equal k.
if(not found) save	Store the current sum only if it's new (greedy for length).
Quick Example (k=5)

Array: [1, 2, 3, -1, 1]

Sum = 1. Map: {1:0}

Sum = 3. Map: {1:0, 3:1}

Sum = 6. Search for 6 - 5 = 1. Found at index 0. Length = 2−0=2.

Sum = 5. sum == k is true. Length = 3+1=4. (Updated)

Sum = 6. Already in map. Ignore (keep index 2 for max length).
*/

class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        // code here
        int ans = 0;
        long long sum=0;
        unordered_map<int,int> presum;
        for(int i=0;i<arr.size();i++)
        {
            sum+=arr[i];
            if(sum == k)ans=max(ans,i+1);
            if(presum.find(sum-k)!=presum.end())
            {
                ans = max(ans,i-m[sum-k]);
            }
            if(presum.find(sum) == presum.end())
            presum[sum] = i;
        }
        return ans;
    }
};