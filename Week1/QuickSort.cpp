class Solution {
  public:
    void quickSort(vector<int>& arr, int low, int high) {
        if(low>=high)return;
        int pivot = partition(arr,low,high);
        quickSort(arr,low,pivot-1);
        quickSort(arr,pivot+1,high);
    }

  public:
    int partition(vector<int>& arr, int low, int high) {
        
        int maxCount = 0;
        int pivotElement = arr[low];
        int i = low,j=high;
        while(i<j)
        {
            while(arr[i]<=pivotElement && i<=high)i++;
            while(arr[j]>pivotElement && j>=low)j--;
            if(i<j)swap(arr[i],arr[j]);
            
        }
        swap(arr[low],arr[j]);
        return j;
    }
};

/*
To master QuickSort, think of it as the "Pick a Leader" algorithm. Unlike Merge Sort, which splits things blindly in the middle, QuickSort picks an element (the pivot) and organizes the entire array around it.

1. The Strategy: Partitioning
QuickSort is all about finding the correct spot for one element at a time.

Pick a Pivot: In your code, the first element (arr[low]) is chosen as the pivot.

Partition: Rearrange the array so that everything smaller than the pivot is on its left, and everything larger is on its right.

Recursion: Now that the pivot is in its final sorted position, repeat the process for the left and right sub-arrays.

2. Key Code Components
partition(): The Organizer

This is where the heavy lifting happens. It places the pivot in its "final home."

The Goal: Move i (looking for elements larger than pivot) and j (looking for elements smaller than pivot).

The Swap: When i and j stop, swap them to fix their "out of place" elements.

The Final Step: Once i and j cross, swap the pivot (at low) with arr[j]. Now, j is the index where the pivot officially belongs.

quickSort(): The Manager

This function handles the recursive calls.

Base Case: if(low >= high) — Stop if the segment has 1 or 0 elements.

The Split: It gets the pivot index from the partitioner and then tells the left side (low to pivot-1) and the right side (pivot+1 to high) to go sort themselves.

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Best/Avg Time	O(nlogn)	When the pivot splits the array roughly in half each time.
Worst Time	O(n 
2
 )	Happens if the array is already sorted and you pick the first/last element as pivot.
Space	O(logn)	It’s "in-place" (no temp vector), but uses stack space for recursion.
Stability	Unstable	Swapping elements across the pivot can change the relative order of equals.
💡 Quick Revision Mental Map
Merge Sort: Divide first, then sort while merging. (Needs extra space).

Quick Sort: Sort (partition) first, then divide. (Saves space).

Note on your code: In partition, the while(i<=high) check is great for safety, but usually, i < high is sufficient. Also, the maxCount variable in your code isn't being used—you can safely delete it to keep things clean!
*/