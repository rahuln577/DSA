/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

[4,5,6,7,0,1,2] if it was rotated 4 times.
[0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
Example 2:

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
Example 3:

Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
*/

/*
To remember Find Minimum in Rotated Sorted Array, think of it as "Hunting for the Cliff." You are looking for the exact point where the values stop being "high" (part of the first segment) and drop to their "lowest" (the start of the second segment).

1. The Strategy: The Two-Curve Logic
A rotated sorted array (e.g., [4, 5, 6, 1, 2, 3]) has two increasing curves. The minimum element is the first element of the second curve.

The Benchmark: Compare nums[mid] against nums[0].

On the High Curve: If nums[mid] >= nums[0], you are still on the "high" part of the rotation. The minimum must be further to the right.

On the Low Curve: If nums[mid] < nums[0], you have fallen off the "cliff." You are now in the section containing the minimum. This mid could be the answer, so you store it and keep looking left to see if the "cliff" started even earlier.

2. Key Code Components
if(nums[mid] >= nums[0])

This tells you that the segment from 0 to mid is perfectly sorted and hasn't dropped yet.

To find the minimum, you must jump across the rotation point by setting st = mid + 1.

middle = nums[mid] (The Candidate)

Whenever you find a value smaller than nums[0], it becomes your best candidate for the minimum.

By setting end = mid - 1, you are effectively searching for an even earlier point where the values "dropped."

if(middle == -1) return nums[0]

This is a crucial edge case. If the loop never finds an element smaller than nums[0], the array was never rotated (or rotated N times). In that case, the first element is the smallest.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(logn)	Standard binary search; the search space is halved every iteration.
Space Complexity	O(1)	No extra data structures are used.
4. Revision Quick-Map
Problem	Goal	Comparison Point
Search Rotated	Find target	Compare mid with st or end to find the sorted half.
Find Min Rotated	Find the "Dip"	Compare mid with nums[0] to see which curve you're on.
💡 Quick Logic Check
Array: [4, 5, 6, 7, 1, 2]

mid is 6. 6 >= 4, so st moves to 7.

mid is 7. 7 >= 4, so st moves to 1.

mid is 1. 1 < 4. middle = 1, end moves to 7.

Loop ends. Return 1.
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int st = 0,end = nums.size()-1;
        int middle = -1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(nums[mid]>=nums[0])
            {
                st = mid+1;
            }
            else
            {
                middle = nums[mid];
                end = mid-1;
            }
        }
        if(middle == -1){
            return nums[0];
        }
        return middle;
    }
};