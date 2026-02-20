/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/

/*
Think of 3Sum as a "Fixed Point + Two Pointers" strategy. To remember this at a glance, visualize fixing one number and then playing a game of "tug-of-war" with the other two to reach a sum of zero.

1. The Strategy: Sort & Squeeze
The goal is to find all unique triplets that sum to zero.

Sort: First, sort the array. This allows us to use two pointers and easily skip duplicates.

Fix i: Iterate through the array, treating nums[i] as the first element of your triplet.

Two Pointers: For the remaining part of the array, set a st (start) pointer at i+1 and an end pointer at the very end.

If the sum is too big (>0): Move end left to decrease the sum.

If the sum is too small (<0): Move st right to increase the sum.

If the sum is zero: You found a triplet!

Skip Duplicates: This is the "secret sauce." To avoid duplicate triplets, whenever you move i, st, or end, skip over any identical numbers.

2. Key Code Components
sort(nums.begin(), nums.end())

Crucial Step: Without sorting, the two-pointer logic won't work because you wouldn't know which direction to move to change the sum.

The val == 0 Logic

When you find a match, you don't just move one step. The while loops (nums[st] == first and nums[end] == sec) push the pointers past all identical values to ensure the next triplet you find is unique.

The Outer while Loop

Similar to the inner pointers, the outer loop moves i past any duplicate values. If nums[i] was -2 and you already found all triplets starting with -2, you don't want to process -2 again.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(n 
2
 )	Sorting takes O(nlogn), but the nested loops (an O(n) pointer search inside an O(n) loop) dominate.
Space Complexity	O(1) or O(n)	O(1) if you don't count the output list; O(n) for some sorting implementations.
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        int i=0;
        while(i<nums.size()-2)
        {
            int st=i+1,end=nums.size()-1;
            while(st<end)
            {
                int val = nums[i]+nums[st]+nums[end];
                if(val>0)
                {
                    end--;
                }
                else if(val<0)
                {
                    st++;
                }
                else if(val==0)
                {
                    ans.push_back({nums[i],nums[st],nums[end]});
                    int first = nums[st],sec = nums[end];
                    while(st<end&&nums[st] == first)st++;
                    while(end>st && nums[end] == sec)end--;
                }
            }
            
            bool flag = false;
            int val = nums[i];
            while(i<nums.size() && val == nums[i])
            {
                flag = true;
                i++;
            }
            if(!flag)i++;
        }
        return ans;
    }
};