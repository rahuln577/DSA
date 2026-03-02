/*
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Return the kth positive integer that is missing from this array.

 

Example 1:

Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
Example 2:

Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.
*/
/*
This is Kth Missing Positive Number. To remember this at a glance, think of it as "Measuring the Gap." In a perfect world with no missing numbers, arr[i] would be equal to i + 1. The difference between what the number should be and what it actually is tells you exactly how many numbers are missing up to that point.

1. The Strategy: Counting the Holes
Instead of searching for the number itself, we use Binary Search to find the index where the k 
th
  missing number would reside.

Missing Count Formula: At any index mid, the number of missing integers is:

missing=arr[mid]−(mid+1)
The Search:

If missing < k: We haven't skipped enough numbers yet. Move right (st = mid + 1).

If missing >= k: We are at or past the point where the k 
th
  number is missing. Store this index and move left (end = mid - 1).

The Final Calculation: Once we find the window where the k 
th
  number is missing, the answer is:

Result=low+k

(Wait, why low+k? Read the Pro-Tip below!)

2. Key Code Components
arr[mid] - (mid + 1)

This is the "Gap Detector." If arr = [2, 3, 4, 7, 11] and we look at index 3 (value 7):

7 - (3 + 1) = 3.

This tells us that by the time we reached the number 7, exactly 3 numbers have been skipped (1,5,6).

The Boundary Edge Case

C++
if((arr[arr.size()-1] - arr.size()) < k) 
    return arr[arr.size()-1] + (k - (arr[arr.size()-1] - arr.size()));
If even the last element in the array doesn't account for k missing numbers, the answer must be beyond the array. You simply take the last element and add the remaining "missing quota."

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(logn)	Standard binary search over the array indices.
Space Complexity	O(1)	No extra space used.
*/

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        if((arr[arr.size()-1] - arr.size())<k)return arr[arr.size()-1]+(k-(arr[arr.size()-1] - arr.size()));
        int st = 0,end = arr.size()-1;
        int tempAns;
        while(st<=end)
        {
            int mid = st + (end - st)/2;
            if((arr[mid] - (mid+1))>=k)
            {
                tempAns = mid;
                end = mid-1;
            }
            else{
                st = mid+1;
            }
        }
        if(tempAns == 0){
            return k;
        }
        int add = k - (arr[tempAns-1]-(tempAns));
        return arr[tempAns-1]+add;
    }
};