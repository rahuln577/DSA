/*
You are given an array with unique elements of stalls[], which denote the positions of stalls. You are also given an integer k which denotes the number of aggressive cows. The task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.

Examples:

Input: stalls[] = [1, 2, 4, 8, 9], k = 3
Output: 3
Explanation: The first cow can be placed at stalls[0], 
the second cow can be placed at stalls[2] and 
the third cow can be placed at stalls[3]. 
The minimum distance between cows in this case is 3, which is the largest among all possible ways.
Input: stalls[] = [10, 1, 2, 7, 5], k = 3
Output: 4
Explanation: The first cow can be placed at stalls[0],
the second cow can be placed at stalls[1] and
the third cow can be placed at stalls[4].
The minimum distance between cows in this case is 4, which is the largest among all possible ways.
Input: stalls[] = [2, 12, 11, 3, 26, 7], k = 5
Output: 1
Explanation: There are 6 stalls and only 5 cows, we try to place the cows such that the minimum distance between any two cows is as large as possible.
The minimum distance between cows in this case is 1, which is the largest among all possible ways.
*/

/*
This is Aggressive Cows. To remember this at a glance, think of it as the "Social Distancing" problem. Unlike the previous problems where we tried to minimize a maximum (like shipping capacity), here we are trying to maximize the minimum distance between cows to keep them from fighting.

1. The Strategy: Can We Keep Them This Far Apart?
You are searching for the largest possible minimum distance X.

Sort the Stalls: This is non-negotiable. To place cows greedily, you must know the stalls in order.

Define the Range:

Minimum (st): 1 (or 0). The smallest possible distance between any two stalls.

Maximum (end): stalls[last] - stalls[0]. The total distance available if you only had 2 cows.

The Predicate (check): If we force a minimum distance of X, can we fit k cows?

Place the first cow in the first stall.

Keep walking until you find a stall that is at least X distance away. Place the next cow there.

Repeat until you run out of stalls or cows.

Binary Search:

If check is True: We successfully placed k cows! This distance works, but maybe we can push them even further apart. Record ans and search right (st = mid + 1).

If check is False: The distance is too large; we couldn't fit all the cows. Search left (end = mid - 1).

2. Key Code Components
sort(stalls.begin(), stalls.end())

Binary search on the distance is O(log(Range)), but the greedy check requires the positions to be in order. Sorting is the first step you should always perform here.

The check Function (Greedy Placement)

C++
int temp = stalls[0]; // Place 1st cow at the first available stall
k--; // One cow down
for(int i=1; i<stalls.size(); i++) {
    if((stalls[i] - temp) >= space) { // Is this stall far enough?
        temp = stalls[i]; // Place cow
        k--;
    }
}
return k <= 0; // Did we place all k cows?
This is Greedy because placing the cow as early as possible (at the first stall that satisfies the distance) always leaves the maximum amount of space for the remaining cows.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(NlogN+Nlog(maxDist))	O(NlogN) to sort, plus binary search steps.
Space Complexity	O(1)	No extra space used beyond the input (if sorted in place).
*/

class Solution {
  public:
    bool check(vector<int> &stalls, int k,int space)
    {
        int temp = stalls[0];
        k--;
        for(int i=1;i<stalls.size();i++)
        {
            if((stalls[i]-temp)>=space)
            {
                temp = stalls[i];
                k--;
            }
            if(k<=0)return true;
        }
        return k<=0;
    }
    int aggressiveCows(vector<int> &stalls, int k) {
        // code here
        sort(stalls.begin(),stalls.end());
        int st = 0, end = stalls[stalls.size()-1] - stalls[0];
        int ans=-1;
        while(st<=end)
        {
            int mid = st+ (end-st)/2;
            if(check(stalls,k,mid))
            {
                ans = mid;
                st = mid+1;
            }
            else
            {
                end = mid-1;
            }
        }
        return ans;
    }
};