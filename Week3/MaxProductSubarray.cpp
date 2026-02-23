/*
This is the Maximum Product Subarray problem. Think of it as "Kadane’s Algorithm for Products." However, because two negative numbers can multiply to create a huge positive number, we have to look at the array from both ends simultaneously.

1. The Strategy: Two-Way Streaks
The maximum product subarray will always start from one of the ends unless there is a zero in the way.

The Zero Problem: A zero "kills" any product streak. If you hit a zero, you must treat the next element as a fresh start (reset prefix/suffix to 1).

The Negative Problem: * If there is an even number of negative numbers, the whole array product is positive.

If there is an odd number of negative numbers, you have to "exclude" one negative number. This split effectively leaves the best product either starting from the left or starting from the right.

The Solution: By calculating a Prefix Product (left to right) and a Suffix Product (right to left) at the same time, you are guaranteed to capture the best possible segment.

2. Key Code Components
if(prefix == 0) prefix = 1;

This is the Reset Button.

If the product becomes 0, it means you've hit a 0 in the array. You reset to 1 so the next element can start a new potential maximum product subarray.

suffix *= nums[nums.size() - i - 1];

This calculates the product starting from the end of the array moving backwards.

It ensures that if the best subarray is tucked away at the very end (e.g., [-1, -2, 40]), the suffix will catch it.

ans = max(ans, max(suffix, prefix))

At every step, you compare the best thing you've seen so far with the current running products from both directions.
*/

/*
Given an integer array nums, find a subarray that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

Note that the product of an array with a single element is the value of that element.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN;
        int prefix = 1,suffix = 1;
        for(int i=0;i<nums.size();i++)
        {
            if(prefix == 0)prefix = 1;
            if(suffix == 0)suffix = 1;
            prefix*=nums[i];
            suffix*=nums[nums.size()-i-1];
            ans = max(ans,max(suffix,prefix));
        }
        return ans;
    }
};