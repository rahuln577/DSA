/*
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
*/

/*
Think of Next Permutation as finding the "next largest number" using the same digits. To remember this at a glance, visualize the array as a mountain range.

1. The Strategy: The Peak and the Pivot
To find the next lexicographical permutation, you look for the first place where the numbers stop increasing (from right to left).

Find the Breakpoint (bp): Scan from right to left to find the first "dip" (where nums[i] < nums[i+1]). This is the point that needs to change to make the number larger.

Find the Smallest "Larger" Number: To make the change as small as possible, look to the right of the breakpoint for the smallest number that is still larger than nums[bp].

Swap & Minimize: Swap those two numbers. Now, to ensure it's the immediate next permutation, sort everything to the right of the breakpoint in ascending order (making it as small as possible).

2. Key Code Components
The First Loop (Finding the Dip)

if(nums[i] < nums[i+1]): This identifies the Breakpoint. If you can't find one (flag == false), it means the array is in descending order (the largest possible permutation).

The Second Loop (Finding the Replacement)

You look for the "next best thing" to put at the breakpoint. You need a value that is > nums[bp] but as small as possible (< val) among the available options to the right.

The Final Touch

If flag is true: You swap and then sort (or reverse, since the right side is guaranteed to be descending) the remaining elements to get the smallest tail.

If flag is false: The number is at its absolute maximum (e.g., 3, 2, 1). The next permutation "wraps around" to the smallest possible version, so you just reverse the whole thing.
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int bp = nums.size()-1;
        bool flag = false;
        int val=INT_MAX,pos=-1;
        for(int i = nums.size()-2;i>=0;i--)
        {
            if(nums[i]<nums[i+1])
            {
                bp = i;
                flag = true;
                break;
            }
        }
        for(int i = bp;i<nums.size();i++)
        {
            if(nums[i]>nums[bp] && nums[i]<val)
            {
                val = nums[i];
                pos = i;
            }
        }
        if(flag)
        {
            swap(nums[pos],nums[bp]);
            sort(nums.begin()+bp+1,nums.end());
            return;
        }
        reverse(nums.begin(),nums.end());
    }
};