/*
A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.

 

Example 1:

Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
Example 2:

Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4
Example 3:

Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day:  1
2nd day: 2
3rd day: 3
4th day: 1, 1

*/
/*
This is Capacity to Ship Packages Within D Days. It is functionally identical to the Split Array Largest Sum and Book Allocation problems. Think of it as "Packing Suitcases": you have a fixed number of suitcases (days), and you want to find the smallest possible suitcase size (capacity) that fits all your clothes (weights) in the order they appear.

1. The Strategy: Can This Suitcase Fit Everything?
Since you must ship weights in the order given, this is a Binary Search on Answer problem.

Define the Range:

Minimum (st): The heaviest single package (max(weights)). You can't have a capacity smaller than your biggest item.

Maximum (end): The sum of all weights. This is the capacity if you shipped everything in exactly 1 day.

The Predicate (check): If the boat has capacity X, how many days does it take?

Walk through the weights, adding them to the "current day's load."

If adding the next weight exceeds capacity X, start a "new day" and reset the load.

Binary Search:

If curDays <= days: This capacity works! Record it as ans and try an even smaller capacity (end = mid - 1).

If curDays > days: The boat is too small; we need more capacity (st = mid + 1).

2. Key Code Components
if(weights[i] > capacity) return false;

Your code handles this by setting the lower bound st = max(weights). This ensures you never even test a capacity that is smaller than the largest package.

The check Logic

C++
if(curWeight + weights[i] > capacity) {
    curWeight = weights[i]; // Start fresh for the next day
    curDays++;
} else {
    curWeight += weights[i]; // Keep adding to the same day
}
This is the standard Greedy approach. You fill the boat as much as possible for the current day before moving to the next.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(N⋅log(Σweights−maxWeight))	Binary search over the total weight range with a linear scan at each step.
Space Complexity	O(1)	Only using integer variables.
*/

class Solution {
public:
    bool check(vector<int>& weights, int days,int capacity)
    {
        int curWeight = 0;
        int curDays = 1;
        for(int i=0;i<weights.size();i++)
        {
            if(weights[i]>capacity)return false;
            if(curWeight+weights[i]>capacity)
            {
                curWeight = weights[i];
                curDays++;
            }
            else{
                curWeight+=weights[i];
            }
        }

        return curDays<=days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        check(weights,days,41);
        int st = 0,end = 0;
        for(auto i:weights){
            end += i;
            st = max(st,i);
            }
        int ans = -1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(check(weights,days,mid))
            {
                ans = mid;
                end = mid-1;
                
            }
            else
            {
                st = mid+1;
            }
        }
        return ans;
    }
};