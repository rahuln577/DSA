/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
*/

/*
This is the Search in Rotated Sorted Array algorithm using the Pivot Method. Think of it as "The Bridge Method": find where the sorted array "breaks" (the pivot), then perform Binary Search on whichever side of the bridge the target belongs.

1. The Strategy: Find the Break, then Search
A rotated sorted array (like [4,5,6,1,2,3]) consists of two sorted sub-segments.

Find the Pivot: The findMid function looks for the point where the rotation happened. This is usually the smallest element in the array (the "dip").

Identify the Sub-segment: * The first segment is from index 0 to pivot - 1.

The second segment is from pivot to end.

Binary Search: Since both segments are individually sorted, you just run a standard Binary Search on both (or check the range first to see which one to search).

2. Key Code Components
findMid (The Pivot Hunter)

The Logic: In a rotated array, all elements to the left of the pivot are ≥ the first element (nums[0]), and all elements to the right are < nums[0].

The Check: if(nums[mid] >= nums[0]): You are still on the "upper" sorted part. Move right (st = mid + 1).

The Check: else: You are on the "lower" sorted part. Move left (end = mid - 1) to find the exact start of that dip.

Two Binary Searches

After finding middle, your code splits the array into two search zones.

Zone 1: 0 to middle-1 (the "high" numbers).

Zone 2: middle to size-1 (the "low" numbers).
*/

class Solution {
public:
    int findMid(vector<int>& nums)
    {
        if(nums[0]<=nums[nums.size()-1])return nums.size()-1;
        if(nums.size() >=2 && nums[nums.size()-1]<nums[nums.size()-2])return nums.size()-1;
        int st = 0,end = nums.size()-1;
        while(st<=end)
        {
            int mid = st +(end-st)/2;
            if((mid-1>=0) && (mid+1 < nums.size()) && nums[mid]<nums[mid-1] && nums[mid]<nums[mid+1])return mid;
            if(nums[mid] >= nums[0])
            {
                st = mid+1;
            }
            else if(nums[mid] < nums[0])
            {
                end = mid-1;
            }
        }
        return end;
    }
    int search(vector<int>& nums, int target) {
        int middle = findMid(nums);

        int st = 0,end = middle-1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(nums[mid] == target)return mid;
            else if(nums[mid]<target)st =mid+1;
            else end = mid-1;
        }
        st = middle,end = nums.size()-1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(nums[mid] == target)return mid;
            else if(nums[mid]<target)st =mid+1;
            else end = mid-1;
        }
        return -1;
    }
};