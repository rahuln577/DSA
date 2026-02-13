/*
Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

 

Example 1:

Input: nums = [3,0,1]

Output: 2

Explanation:

n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
*/

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xor1 = 0,xor2 = 0;
        for(auto i:nums)
        {
            xor1^=i;
        }
        for(int i=0;i<nums.size()+1;i++)
        {
            xor2^=i;
        }
        return xor1^xor2;
    }
};

/*xor of two same numbers is 0*/