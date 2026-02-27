/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours..

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
*/

/*
This is the Koko Eating Bananas problem, which is the "classic" example of Binary Search on Answer. Instead of searching for an element in an array, you are searching for a value k in a range of possible speeds.

1. The Strategy: Is It Possible?
You don't know the exact speed, but you know it must be somewhere between 1 banana per hour and the maximum number of bananas in any single pile.

Define the Range: * low = 1 (slowest possible speed).

high = max(piles) (fastest speed you'd ever need, as you can only eat one pile per hour anyway).

The Predicate Function (calc): For a given speed k, how many hours will it take to finish all piles?

For each pile, hours taken = ⌈piles[i]/k⌉.

Binary Search: * If timeTaken <= h: Koko is eating fast enough. We record this speed as a potential answer but try to find an even slower speed by moving end = mid - 1.

If timeTaken > h: Koko is too slow. We must increase the speed: st = mid + 1.

2. Key Code Components
i/k + (i%k != 0)

This is a clever way to calculate the ceiling of the division. If there’s a remainder, you need one extra hour for that pile.

Pro-tip: You can also write this as (i + k - 1) / k to avoid the if condition.

sort(piles.begin(), piles.end())

Performance Note: In this specific problem, sorting isn't actually required! You only need the maximum element to set your end pointer. Sorting adds O(NlogN), whereas finding the max is O(N).

long long for Time

Always use long long for timeTaken and mid. If the piles are large and the speed k is small, the number of hours can easily exceed the range of a standard 32-bit int.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(N⋅log(maxPile))	You do a Binary Search over the range of speeds (1 to 10 
9
 ), and for each step, you iterate through the N piles.
Space Complexity	O(1)	No extra data structures used beyond variables.
*/

class Solution {
public:
    long long calc(vector<int>& piles, int k)
    {
        long long ans = 0;
        for(auto i:piles)
        {
            ans+=i/k;
            if(i%k)ans+=1;
        }
        return ans;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        sort(piles.begin(),piles.end());
        long long ans = piles[0];
        long long st = 1,end = piles[piles.size()-1];
        while(st<=end)
        {
            long long mid = st + (end-st)/2;       
            long long timeTaken = calc(piles,mid);
            if(timeTaken<=h){
                ans = mid;
                end = mid-1;
            }
            else st = mid+1;
        }
        return ans;
    }
};