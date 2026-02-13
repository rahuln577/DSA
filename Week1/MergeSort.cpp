class Solution {
  public:
    void merge(vector<int>& arr,int l,int mid,int r)
    {
        vector<int> temp;
        int i = l,j = mid+1;
        while(i<=mid && j<=r)
        {
            if(arr[i]<arr[j])
            {
                temp.push_back(arr[i]);
                i++;
            }
            else
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
        while(j<=r)
        {
            temp.push_back(arr[j]);
            j++;
        }
        int k=0;
        for(int i = l;i<=r;i++)
        {
            arr[i] = temp[k++];
        }
    }
    void mergeSort(vector<int>& arr, int l, int r) {
        // code here
        if(l>=r)
        {
            return;
        }
        int mid = (l+r)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
};

/*
To remember Merge Sort at a glance, think of it as a "Divide and Conquer" strategy. It’s like breaking a big project into tiny tasks, solving them, and then stitching them back together in order.

1. The Strategy: Divide & Conquer
Merge Sort works in two distinct phases:

Divide (Recursive): Keep cutting the array in half until every element is its own individual "list" (a list of 1 is already sorted).

Conquer (Iterative Merge): Combine those small lists back together in the correct order.

2. Key Code Components
mergeSort(): The Divider

This function is the brain. It handles the recursion.

Base Case: if(l >= r) return; — Stop when the sub-array has 1 or 0 elements.

Split: Calculate mid and call itself twice (left half and right half).

Action: After the halves are "sorted" by the recursion, call merge().

merge(): The Joiner

This function is the muscle. It does the actual sorting.

Two Pointers: i starts at the beginning of the left half; j starts at the beginning of the right half.

The Comparison: Compare arr[i] and arr[j]. Put the smaller one into a temp vector.

The Leftovers: If one half finishes early, dump the remaining elements of the other half into temp.

The Copy: Copy everything from temp back into the original arr.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(nlogn)	You split the array logn times, and each level requires n work to merge.
Space Complexity	O(n)	You need the temp vector to store elements during the merge.
Stability	Stable	It preserves the relative order of equal elements (thanks to arr[i] < arr[j]).
Pro-Tip for Revision
If you ever forget the logic, just remember the "Two-Deck Card Trick": If you have two stacks of cards that are already sorted, you just look at the top card of each, pick the smaller one, and put it in a new pile. Repeat until both stacks are empty.
*/