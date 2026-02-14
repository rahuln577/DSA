/*
This is Kadane’s Algorithm. To remember it at a glance, think of it as the "Fresh Start" rule: if your current debt (negative sum) is dragging you down, cut your losses and start over from zero.

1. The Strategy: Don't Carry Dead Weight
The goal is to find the contiguous subarray with the largest sum.

Accumulate: Keep adding elements to your current sum.

Record: Every time you add an element, check if the current sum is the best you've ever seen (ans).

The Reset: If your sum ever drops below zero, it means adding this entire "block" to any future elements will only make them smaller. So, you reset sum to 0 and start a new potential subarray from the next element.

2. Key Code Components
ans = max(ans, sum)

This is your Global Maximum.

It "remembers" the highest peak your sum reached, even if the sum later drops.

Initializing ans = INT_MIN ensures it works even if the array contains only negative numbers.

if(sum < 0) { sum = 0; }

This is the Local Reset.

A negative sum is a "burden." By resetting to zero, you are effectively saying, "I'll start my next subarray from the next number instead of carrying this negative total forward."

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(n)	You iterate through the nums vector exactly once.
Space Complexity	O(1)	You only store two integers (sum and ans), no matter how large the input.
4. Revision Comparison
Merge/Quick Sort: O(nlogn) – Sorting.

Boyer-Moore: O(n) – Finding the majority "Survivor."

Kadane's: O(n) – Finding the best "Streak."

💡 Quick Logic Check
If the array is [-2, 1, -3, 4, -1, 2, 1, -5, 4]:

You hit -2, sum becomes < 0, so you reset to 0.

You hit 4, then -1 (sum=3), then 2 (sum=5), then 1 (sum=6).

ans records that 6.

Even when you hit -5 later, ans stays 6.
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0,ans = INT_MIN;
        for(auto i:nums)
        {
            sum+=i;
            ans = max(ans,sum);
            if(sum<0)
            {
                sum = 0;
            }
        }
        return ans;
    }
};