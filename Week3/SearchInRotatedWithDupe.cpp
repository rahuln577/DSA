/*

*/
/*
This is Search in Rotated Sorted Array II (the version with duplicates). Think of this as the "One-Pass Search" with an added "Duplicate Shrink" step.

1. The Strategy: Isolate the Sorted Half
In a rotated array, at least one half (left or right) is always sorted.

Find the Sorted Side: Compare nums[st] and nums[mid].

If nums[st] <= nums[mid], the left side is sorted.

Otherwise, the right side is sorted.

Range Check: Check if the target lies within the sorted half’s range.

If it does, narrow your search to that half.

If it doesn't, the target must be in the other (unsorted) half.

The Duplicate Trap: If nums[st] == nums[mid] == nums[end], you can't tell which side is sorted (e.g., [1, 0, 1, 1, 1]). In this case, simply shrink both ends (st++, end--) and try again.

2. Key Code Components
The "Duplicate Shrink"

C++
if((nums[mid] == nums[st]) && (nums[mid] == nums[end])) {
    st++; end--;
    continue;
}
This is the only difference between this problem and the one without duplicates.

When all three points are equal, Binary Search logic fails because we don't know which direction is "sorted." We manually move the pointers one step inward to break the stalemate.

The Range Check Logic

Left Half Sorted: If nums[st] <= target < nums[mid], search left.

Right Half Sorted: If nums[mid] < target <= nums[end], search right.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Best/Avg Time	O(logn)	Standard binary search behavior.
Worst Time	O(n)	Happens when almost all elements are duplicates (e.g., [1, 1, 1, 0, 1]), forcing the O(n) shrink.
Space Complexity	O(1)	Purely iterative with pointers.
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int st = 0,end = nums.size()-1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(nums[mid] == target)
            {
                return true;
            }
            if((nums[mid] == nums[st]) && (nums[mid] == nums[end]))
            {
                st++;end--;
                continue;
            }
                if(nums[st]<=nums[mid])
                {
                    if(nums[st]<=target && target < nums[mid])
                    {
                        end = mid-1;
                    }
                    else{
                        st = mid+1;
                    }
                }
                else{
                    if(nums[mid]<target && target<=nums[end])
                    {
                        st = mid+1;
                    }
                    else {
                        end = mid-1;
                    }
                }

        }
        return false;
    }
};