/*
Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:

0 <= i < j < nums.length and
nums[i] > 2 * nums[j].
 

Example 1:

Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
Example 2:

Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1

*/

/*
This is Reverse Pairs. Think of it as "Inversion Count’s Strict Older Brother." Instead of just looking for arr[i]>arr[j], it looks for pairs where arr[i]>2×arr[j].

1. The Strategy: The Two-Pass Merge
Unlike standard Inversion Count, you cannot count reverse pairs during the merge step easily because the 2× condition breaks the simple (mid−i+1) math. Instead, we perform two passes inside the merge function:

The Counting Pass: Before merging the two sorted halves, use two pointers to find all pairs that satisfy arr[i]>2×arr[j].

The Sorting Pass: Perform the standard Merge Sort "combine" step to keep the array sorted for the next level of recursion.

2. Key Code Components
The Pre-Merge Counting Loop

C++
while(i <= mid) {
    while(j <= second && ((long long)arr[i] > 2LL * arr[j])) {
        j++;
    }
    count += (j - (mid + 1));
    i++;
}
Why this works: Both halves are sorted. If arr[i] is greater than 2×arr[j], then arr[i+1] (which is even larger) will definitely be greater than 2×arr[j].

The Pointer j doesn't reset: Notice j only moves forward. This makes the counting pass O(N) rather than O(N 
2
 ).

2LL: Essential to prevent integer overflow when doubling large numbers.

The Standard Merge

After counting, the code proceeds to sort the elements into temp. This is strictly to maintain the "sorted" property required for the counting pass in the next recursive level.
*/

class Solution {
public:
void merge(vector<int>& arr,int first,int mid,int second,int& count)
    {
        int i = first,j = mid+1;
        vector<int> temp;
        while(i<=mid)
        {
            while(j<=second && ((long long)arr[i] > 2LL * arr[j]))
            {
                j++;
            }
            count+=(j-(mid+1));
            i++;
        }
        i = first,j = mid+1;
        while(i<=mid && j<=second)
        {
            if(arr[i] < arr[j])
            {
                temp.push_back(arr[i]);
                i++;
            }
            else if(arr[i]>=arr[j])
            {
                temp.push_back(arr[j]);
                j++;
            }
        }
        while(i<=mid)
        {
            temp.push_back(arr[i]);
           i++;
        }
        while(j<=second){
            temp.push_back(arr[j]);
            j++;
        }
        i = first;
        for(auto j:temp)
        {
            arr[i++]=j;
        }
    }
    void mergeSort(vector<int>& arr, int first,int second,int& count)
    {
        if(first >= second)return;
        int mid = (first+second)/2;
        mergeSort(arr,first,mid,count);
        mergeSort(arr,mid+1,second,count);
        merge(arr,first,mid,second,count);
    }
    int reversePairs(vector<int>& nums) {
        int count = 0;
        mergeSort(nums,0,nums.size()-1,count);
        return count;
    }
};