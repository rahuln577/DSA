/*
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
*/

/*
To remember Single Element in a Sorted Array, think of it as "The Even-Odd Index Rule." In a perfectly paired sorted array, the first occurrence of a pair is always at an even index, and the second is at an odd index. The single element is the "glitch" that flips this pattern.

1. The Strategy: Spotting the Pattern Break
Before the single element, pairs follow the (Even, Odd) pattern. After the single element, pairs shift to an (Odd, Even) pattern.

Mid-Check: If nums[mid] is not equal to its neighbors, you've found the single element.

The Pair Logic:

If nums[mid] == nums[mid-1]: You are at the second element of a pair.

If mid is Odd, everything is normal so far. The single element is to the right.

If mid is Even, the pattern has already broken. The single element is to the left.

If nums[mid] == nums[mid+1]: You are at the first element of a pair.

If mid is Even, everything is normal. Search right.

If mid is Odd, the pattern is broken. Search left.

2. Key Code Components
Boundary Checks

if(mid == 0 ...) and if(mid == nums.size()-1 ...): These handle the cases where the single element is at the very beginning or the very end of the array, preventing out-of-bounds errors when checking neighbors.

The Index Pattern

Your code uses mid % 2 == 0 and (nums.size() - mid - 1) % 2 == 0 to decide which half is "corrupted."

Revision Shortcut: If the "first" occurrence of a pair is at an Odd index, you are past the single element. If it's at an Even index, you are before it.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(logn)	Classic binary search; the search space is halved based on index parity.
Space Complexity	O(1)	No extra memory used.
4. Revision Quick-Map
Sorted Array Problem	Search Logic
Lower Bound	arr[mid] >= target → search left.
Find Minimum	arr[mid] < arr[0] → search left.
Single Element	Check if mid and its pair match the (Even, Odd) rule.
💡 Quick Logic Check
Array: [1, 1, 2, 3, 3, 4, 4] (Single element is 2 at index 2)

mid = index 3 (value 3).

nums[3] == nums[4] (Value 3).

mid (3) is Odd. In a normal (Even, Odd) pair, the first 3 should be at an Even index.

Since it's at an Odd index, the "glitch" happened earlier. Move left.
*/

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int st = 0,end = nums.size()-1;
        if(nums.size() == 1)return nums[0];
        while(st<=end)
        {
            int mid = st+(end-st)/2;
            if(mid == 0 && nums[mid]!=nums[1])return nums[mid];
            if(mid == nums.size()-1 && nums[mid]!=nums[mid-1])return nums[mid];
            if(nums[mid] == nums[mid-1])
            {
                if(mid%2 == 0)end = mid-1;
                else st = mid+1;
            }
            else if(nums[mid] == nums[mid+1])
            {
                if((nums.size()-mid-1)%2 == 0)st = mid+1;
                else end = mid-1;
            }
            else return nums[mid];
        }
        return -1;
    }
};