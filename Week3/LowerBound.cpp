/*
Given a sorted array arr[] and a number target, the task is to find the lower bound of the target in this given array. The lower bound of a number is defined as the smallest index in the sorted array where the element is greater than or equal to the given number.

Note: If all the elements in the given array are smaller than the target, the lower bound will be the length of the array. 

Examples :

Input:  arr[] = [2, 3, 7, 10, 11, 11, 25], target = 9
Output: 3
Explanation: 3 is the smallest index in arr[] where element (arr[3] = 10) is greater than or equal to 9.
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 11
Output: 4
Explanation: 4 is the smallest index in arr[] where element (arr[4] = 11) is greater than or equal to 11.
Input: arr[] = [2, 3, 7, 10, 11, 11, 25], target = 100
Output: 7
Explanation: As no element in arr[] is greater than 100, return the length of array.
*/

/*
To remember Lower Bound, think of it as "The First Possible Spot." It is a Binary Search variation that doesn't just look for an element, but finds the smallest index where the value is at least the target.

1. The Strategy: Keep Pushing Left
Standard Binary Search stops when it finds the target. Lower Bound says, "I found it, but can I find a smaller index that also works?"

Search Condition: If arr[mid] >= target, this index is a potential candidate.

The Store & Shrink: Record the current index (ans = mid) and then shrink the search space to the left (end = mid - 1) to see if the target (or something greater) appears even earlier.

The Else: If arr[mid] < target, you are too far left; move right (st = mid + 1).

2. Key Code Components
int mid = st + (end - st) / 2

This is the standard way to prevent integer overflow (instead of (st + end) / 2).

if(arr[mid] >= target)

This handles two scenarios:

The element is exactly the target.

The element is the next best thing (first element larger than target).

By setting end = mid - 1, you effectively "ignore" everything to the right because you already have a candidate at mid and you want the lowest index.

if(ans == -1) return arr.size()

If the loop finishes and ans is still -1, it means every single number in the array is smaller than the target. The "first spot" would theoretically be the index just past the end of the array.
*/

class Solution {
  public:
    int lowerBound(vector<int>& arr, int target) {
        // code here
        int ans = -1;
        int st = 0,end = arr.size()-1;
        while(st<=end)
        {
            int mid = st+(end-st)/2;
            if(arr[mid] >= target)
            {
                ans = mid;
                end = mid-1;
            }
            else if(arr[mid]<target)
            {
                st = mid+1;
            }
        }
        if(ans == -1)return arr.size();
        return ans;
    }
};
