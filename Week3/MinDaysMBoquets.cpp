/*
You are given an integer array bloomDay, an integer m and an integer k.

You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.

Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.

 

Example 1:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let us see what happened in the first three days. x means flower bloomed and _ means flower did not bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
Example 2:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.
Example 3:

Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here is the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
*/

/*
This is Minimum Number of Days to Make m Bouquets. Just like the Koko Eating Bananas problem, this is a Binary Search on Answer challenge. To remember it, think: "Is X days enough time to pick m groups of k adjacent flowers?"

1. The Strategy: Can We Pick Them?
You are looking for the minimum day X. The search range is between the earliest a flower blooms (min(bloomDay)) and the latest any flower blooms (max(bloomDay)).

The Constraint: You need m bouquets, and each bouquet needs k adjacent flowers.

The Predicate (possible): If we wait X days, which flowers have bloomed?

Traverse the array. If bloomDay[i] <= X, that flower is ready.

Count consecutive ready flowers. Once you hit k, you've made one bouquet! Reset your counter and look for the next set.

The Decision: * If you can make ≥m bouquets, X days is a valid answer. Try a smaller number of days (end = mid - 1).

If not, you need to wait longer (st = mid + 1).

2. Key Code Components
if(bloomDay.size() / m < k)

This is your Sanity Check. If the total number of flowers available is less than the total flowers needed (m×k), it's mathematically impossible. Return −1 immediately.

Note: Use (long long)m * k to avoid overflow if m and k are large.

The possible Loop

C++
if(i <= days) temp++;
else temp = 0; // The adjacency is broken!

if(temp == k) {
    m--; 
    temp = 0; // Bouquet complete, reset counter
}
The else temp = 0 is the most important part. It enforces the adjacency rule. If a flower in the middle hasn't bloomed yet, you can't use the flowers to its left and right for the same bouquet.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(N⋅log(maxDay−minDay))	Binary search over the range of days, with a linear scan (O(N)) at each step.
Space Complexity	O(1)	No extra space used except for variables.
4. Revision Quick-Map
Problem	Adjacency Needed?	Counting Logic
Koko Bananas	No	Sum of ceil(piles[i]/k).
Bouquets	Yes	Reset counter if flower not bloomed.
Split Array Max Sum	Yes	Reset sum if it exceeds mid.
*/

class Solution {
public:
    bool possible(vector<int>& bloomDay,int days,int m, int k)
    {
        int temp = 0;
        for(auto i:bloomDay)
        {
            if(i<=days)
            {
                temp++;
            }
            else
            {
                temp = 0;
            }
            if(temp == k)
            {
                m--;
                temp = 0;
            }
        }
        return (m<=0);
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        if(bloomDay.size()/m < k)return -1;
        long long end = INT_MIN,st = INT_MAX;
        long long ans;
        for(long long i:bloomDay){
            end = max(end,i);
            st = min(st,i);
        }
        ans = st;
        while(st<=end)
        {
            long long mid = st + (end-st)/2;
            if(possible(bloomDay,mid,m,k)){
                ans = mid;
                end = mid-1;
            }
            else st = mid+1;
        }
        return ans;
    }
};