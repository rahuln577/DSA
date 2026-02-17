/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Example 3:

Input: nums = [1,0,1,2]
Output: 3
*/

/*
To remember Longest Consecutive Sequence, think of it as "Finding the Leader of the Pack." You only start counting a sequence if you are standing at its absolute beginning.

1. The Strategy: The Starting Point Rule
If you have a set of numbers like {100, 4, 200, 1, 3, 2}, you don't want to start counting at 2, then 3, then 4, because you'll repeat work. You only want to start counting when you hit 1.

Set Up: Toss everything into an unordered_set. This gives you O(1) lookups and removes duplicates.

Identify the "Start": For every number i, check if i-1 exists in the set.

If i-1 exists, ignore i. It’s part of a sequence, but not the start.

If i-1 does NOT exist, you’ve found the "Leader." Start counting from here!

Count the Streak: From the leader, keep checking for val+1, val+2, etc., and update your maximum length.

2. Key Code Components
st.find(i-1) == st.end()

This is the most important line.

It ensures you only enter the while loop for the very first element of any sequence. This is what keeps the algorithm efficient.

while(st.find(val+1) != st.end())

Once you find a start, you "climb the ladder" as far as it goes. Because of the "Start" check above, each number in the entire array is visited at most twice.

*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        int count = 1;
        if(nums.size() == 0)return 0;
        for(auto i:nums)
        {
            st.insert(i);
        }
        for(auto i:st)
        {
            if(st.find(i-1) == st.end())
            {
                int temp = 1;
                int val = i;
                while(st.find(val+1)!=st.end())
                {
                    temp++;
                    val = val+1;
                }
                count = max(count,temp);
            }
        }
        return count;
    }
};