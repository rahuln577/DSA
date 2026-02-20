/*
Count Subarrays with given XOR
Difficulty: MediumAccuracy: 58.86%Submissions: 74K+Points: 4
Given an array of integers arr[] and a number k, count the number of subarrays having XOR of their elements as k.

Examples: 

Input: arr[] = [4, 2, 2, 6, 4], k = 6
Output: 4
Explanation: The subarrays having XOR of their elements as 6 are [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], and [6]. Hence, the answer is 4.
Input: arr[] = [5, 6, 7, 8, 9], k = 5
Output: 2
Explanation: The subarrays having XOR of their elements as 5 are [5] and [5, 6, 7, 8, 9]. Hence, the answer is 2.
Input: arr[] = [1, 1, 1, 1], k = 0
Output: 4
Explanation: The subarrays are [1, 1], [1, 1], [1, 1] and [1, 1, 1, 1].
*/

/*
o remember Count Subarrays with XOR k, think of it as the "Mirror Image" of the Subarray Sum Equals k problem. It uses the exact same logic, but swaps Addition/Subtraction for the XOR operator.

1. The Strategy: The XOR Property
The algorithm relies on a unique property of XOR: if A⊕B=C, then A⊕C=B.

Prefix XOR: As you traverse the array, keep a running XOR total (Finalxor).

The Target: You want a subarray that XORs to k. If your current prefix XOR is Finalxor, you are looking for a previous prefix XOR (req) such that:
req ^ k = Finalxor  → which means req = k ^ Finalxor.

The Map: Store the frequency of every prefix XOR you've seen so far in an unordered_map.
*/
class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        // code here
        unordered_map<int,int> m;
        m[0] = 1;
        long ans = 0;
        int Finalxor = 0;
        for(auto i:arr)
        {
            Finalxor^=i;
            int req = k^Finalxor;
            if(m.find(req) != m.end())
            {
                ans+=m[req];
            }
            m[Finalxor]++;
        }
        return ans;
    }
};