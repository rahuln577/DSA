/*
Given an array of integers arr[]. You have to find the Inversion Count of the array. 
Note : Inversion count is the number of pairs of elements (i, j) such that i < j and arr[i] > arr[j].

Examples:

Input: arr[] = [2, 4, 1, 3, 5]
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
Input: arr[] = [2, 3, 4, 5, 6]
Output: 0
Explanation: As the sequence is already sorted so there is no inversion count.
Input: arr[] = [10, 10, 10]
Output: 0
Explanation: As all the elements of array are same, so there is no inversion count.
*/

/*
This is the Inversion Count problem. To remember this at a glance, think of it as "Enhanced Merge Sort." It uses the sorting process to catch elements that are "out of order."

1. The Strategy: The "Jump" Count
An inversion happens whenever a larger number appears before a smaller number. Since Merge Sort already compares elements from a left (earlier) half and a right (later) half, it’s the perfect place to count these occurrences.

The Divide: Just like standard Merge Sort, split the array until you have single elements.

The Conquer (and Count): When merging two sorted halves:

If arr[i] <= arr[j]: No inversion. Move the left element.

If arr[i] > arr[j]: Inversion detected! Because the left half is already sorted, if arr[i] is bigger than arr[j], then every element from i to the end of the left half is also bigger than arr[j].

The Math: Total inversions for that step =(mid−i+1).

2. Key Code Components
count += (mid - i + 1)

This is the heart of the algorithm.

Instead of incrementing count by 1, we add the entire remaining length of the left subarray.

Why? Because if 5 is greater than 3, and we know 6 and 7 come after 5 (since it's sorted), then 6 and 7 must also be greater than 3. That's 3 inversions found instantly.

Standard Merge Sort Logic

The rest of the code is identical to Merge Sort. By the time the recursion finishes, the array is sorted, and the count variable has accumulated every "jump" a smaller element made to the left.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(nlogn)	It’s just Merge Sort with one extra addition operation.
Space Complexity	O(n)	Required for the temp vector during the merge step.
*/
class Solution {
  public:
    void merge(vector<int>& arr,int first,int mid,int second,int& count)
    {
        int i = first,j = mid+1;
        vector<int> temp;
        while(i<=mid && j<=second)
        {
            if(arr[i] <= arr[j])
            {
                temp.push_back(arr[i]);
                i++;
            }
            else if(arr[i]>arr[j])
            {
                count+=(mid-i+1);
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
    int inversionCount(vector<int> &arr) {
        // Code Here
        int count = 0;
        mergeSort(arr,0,arr.size()-1,count);
        return count;
    }
};