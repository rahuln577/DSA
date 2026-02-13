/*
169. Majority Element
Solved
Easy

Topics
premium lock icon
Companies
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
*/

/*
This code implements the Boyer-Moore Voting Algorithm. To remember this at a glance, think of it as a "Battle Royale" where the majority element is the strongest survivor.

1. The Strategy: The Survival of the Fittest
The algorithm assumes a majority element (one that appears more than n/2 times) exists. It works by "pairing off" different elements. Since the majority element appears more than half the time, it will always have "survivors" left after all other elements have neutralized each other.

Candidate Selection: You pick a candidate (ans).

The Vote: * If you see the same element again, the candidate gets a +1 vote (strength increases).

If you see a different element, it fights the candidate, and both are removed (-1 vote).

Reset: If the count hits zero, the current candidate is "defeated," and the very next element becomes the new candidate.

2. Key Code Components
The count == 0 Check

This is the "New King" logic.

Whenever your current candidate's support is completely wiped out, you pick the current element as the new potential winner and reset count to 1.

The count > 0 Logic

Same Element: nums[i] == ans. You found a supporter! Increase the count.

Different Element: nums[i] != ans. An enemy! They cancel each other out, so decrease the count.

3. Why it Works (The Math)
Because the majority element appears more than 50% of the time, even if every other element in the array teamed up to "vote down" the majority element, they wouldn't have enough numbers to keep its count at zero by the end of the array.

4. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(n)	You only pass through the array exactly once.
Space Complexity	O(1)	You only use two variables (ans and count), regardless of array size.
Constraint	Requires Majority	Only guaranteed to work if an element strictly exceeds n/2 occurrences.
💡 Revision Mental Map
Merge Sort: Divide & Conquer (O(nlogn)).

Quick Sort: Pivot & Partition (O(nlogn)).

Majority Element: Fight & Neutralize (O(n)).

A small tip: In some problems, they don't guarantee a majority exists. In that case, you'd need a second loop to count the occurrences of ans to verify it actually appears more than n/2 times.
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans,count=0;
        for(int i=0;i<nums.size();i++)
        {
            if(count == 0)
            {
                ans = nums[i];
                count++;
            }
            else if(count>0)
            {
                if(nums[i] == ans)count++;
                else count--;
            }
        }
        return ans;
    }
};