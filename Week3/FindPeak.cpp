/*
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

*/

/*
To remember Find Peak Element, think of it as "Walking Uphill." Since the problem guarantees that nums[−1] and nums[n] are −∞, you are essentially on a mountain range. If you are currently walking upward, there must be a peak somewhere ahead of you.

1. The Strategy: Following the Slope
A peak is any element that is strictly greater than its neighbors. You don't need to find the highest peak, just any peak.

Check the Slope: Compare nums[mid] with its neighbors.

The Upward Slope: If nums[mid] < nums[mid+1], you are currently on an incline going right. Since the range eventually drops to −∞ at the end, a peak is guaranteed to exist in that direction. Move right (st = mid + 1).

The Downward Slope: If nums[mid] > nums[mid+1], you are either at a peak or the range is currently dropping. However, since the range started at −∞, there must have been a peak to your left. Move left (end = mid - 1).

2. Key Code Components
Boundary Protection

Manual checks: Your code explicitly handles size == 1 and size == 2.

Index Safety: The if(mid == 0) and else if(mid == nums.size()-1) blocks prevent the code from checking mid-1 or mid+1 when the middle lands on the very first or last element.

Slope Logic

C++
if(nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) return mid; // Peak!
if(nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1]) st = mid+1; // Go Upright
else end = mid-1; // Go Upleft
If you are in a "valley" (nums[mid] is smaller than both neighbors), your code defaults to end = mid - 1. Both directions would actually lead to a peak, so choosing one is sufficient.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(logn)	You reduce the search space by half by following the direction of the slope.
Space Complexity	O(1)	No extra storage is used.
4. Revision Quick-Map
Problem	Key Observation
Find Minimum	Look for the "Cliff" (drop in value).
Single Element	Look for the "Glitch" in Even-Odd pairs.
Find Peak	Follow the Slope (always go uphill).
💡 Quick Logic Check
Array: [1, 2, 1, 3, 5, 6, 4]

mid = index 3 (value 3).

3 > 1 (left) but 3 < 5 (right). You are on an upward slope to the right.

Move st to index 4.

Eventually, you find 6 (index 5), which is greater than 5 and 4. Return 5.
*/

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int st = 0,end = nums.size()-1;
        if(nums.size() == 1)return 0;
        if(nums.size() == 2){
            if(nums[0]<nums[1])return 1;
            return 0;
        }
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(mid == 0)
            {
                if(nums[0]<nums[1]){
                    return 1;
                }
                else return 0;
            }
            else if(mid == nums.size()-1){
                if(nums[mid]<nums[mid-1]){
                    return mid-1;
                }
                else return mid;
            }
            if(nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1])return mid;
            if(nums[mid]>nums[mid-1] && nums[mid]<nums[mid+1])st = mid+1;
            else end = mid-1;
        }
        return nums[nums.size()-1];
    }
};