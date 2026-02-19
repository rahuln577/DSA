/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
*/
/*
This is the Extended Boyer-Moore Voting Algorithm (finding elements that appear more than n/3 times). Think of it as "The Two-Survivor Battle."

1. The Strategy: Two Seats, Three Tiers
Mathematically, in any array, there can be at most two elements that appear more than n/3 times. This algorithm maintains two potential candidates simultaneously.

The Pair-Off: If you encounter a number that isn't ans1 or ans2, it "fights" both of them. One neutralizer removes one vote from both candidates.

The Priority: * If you see an existing candidate, increment their specific count.

If a seat is empty (count == 0), the current number takes that seat.

If both seats are full and the number is different, decrement both counts.

The Confirmation: Unlike the n/2 version, the survivors here aren't guaranteed to be the majority. You must do a second pass to count their actual occurrences and verify they exceed n/3.

2. Key Code Components
i != ans2 and i != ans1 Checks

These are crucial! When count1 is 0, you must ensure the new candidate you are picking isn't already occupying the ans2 seat. This prevents both candidates from being the same number.

count1-- and count2--

This is the "Triple Match" logic. If a number doesn't match either candidate, it effectively cancels out one instance of ans1 AND one instance of ans2.

The Verification Loop

The first loop only finds the most frequent elements. The second loop checks if they are frequent enough (i.e., >n/3).
*/
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int ans1=INT_MIN,ans2=INT_MIN;
        int count1=0,count2=0;
        for(auto i:nums)
        {
            if(count1 == 0 && i!=ans2)
            {
                count1=1;
                ans1 = i;
            }
            else if(count2 == 0 && i!=ans1)
            {
                count2=1;
                ans2 = i;
            }
            else if(i == ans1)
            {
                count1++;
            }
            else if(i == ans2)
            {
                count2++;
            }
            else
            {
                count1--;
                count2--;
            }
        }
        vector<int> ans;
        vector<int> temp(2,0);
        for(auto i:nums)
        {
            if(i == ans1)temp[0]++;
            if(i == ans2)temp[1]++;
        }
        if(temp[0]>nums.size()/3)ans.push_back(ans1);
        if(temp[1]>nums.size()/3)ans.push_back(ans2);
        return ans;
    }
};