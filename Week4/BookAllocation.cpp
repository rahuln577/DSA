/*
Given an array arr[] of integers, where each element arr[i] represents the number of pages in the i-th book. You also have an integer k representing the number of students. The task is to allocate books to each student such that:

Each student receives atleast one book.
Each student is assigned a contiguous sequence of books.
No book is assigned to more than one student.
The objective is to minimize the maximum number of pages assigned to any student. In other words, out of all possible allocations, find the arrangement where the student who receives the most pages still has the smallest possible maximum.

Note: If it is not possible to allocate books to all students, return -1.

Examples:

Input: arr[] = [12, 34, 67, 90], k = 2
Output: 113
Explanation: Allocation can be done in following ways:
=> [12] and [34, 67, 90] Maximum Pages = 191
=> [12, 34] and [67, 90] Maximum Pages = 157
=> [12, 34, 67] and [90] Maximum Pages = 113.
The third combination has the minimum pages assigned to a student which is 113.
Input: arr[] = [15, 17, 20], k = 5
Output: -1
Explanation: Since there are more students than total books, it's impossible to allocate a book to each student.
*/

/*
This is the Book Allocation Problem. It is the absolute twin of the "Ship Packages" problem. To remember this, think of it as "Fair Distribution": you want to give books to k students such that the student who has to read the most pages reads as little as possible.

1. The Strategy: Minimize the Maximum
You are searching for the minimum "Max Pages" any single student has to read.

Define the Range:

Low (st): The book with the most pages (max_element). A student must be able to at least read the largest single book.

High (end): The sum of all pages. This is the case where there is only 1 student who reads everything.

The Predicate (check): If we set a limit of X pages per student, how many students do we need?

Assign books greedily. If adding the next book exceeds X, give it to a new student.

Binary Search:

If studentsNeeded <= k: This limit is possible! But we want to see if we can be even "fairer" and lower the limit. Search left (end = mid - 1).

If studentsNeeded > k: The limit is too tight; we need more students than we have. Increase the limit. Search right (st = mid + 1).

2. Key Code Components
if(k > arr.size()) return -1

The Constraint: Each student must get at least one book. If there are more students than books, it's impossible to satisfy the condition.

The check Logic

C++
if(arr[i] + temp <= maxPages) {
    temp += arr[i]; // Same student keeps reading
} else {
    temp = arr[i]; // New student starts here
    count++;
}
This ensures books are allocated contiguously. You cannot skip a book or reorder them. This is why the problem is perfect for Binary Search rather than a complex DP (unless the order didn't matter).

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(N⋅log(sum−max))	Linear scan for each binary search step.
Space Complexity	O(1)	Constant extra space.
*/

class Solution {
  public:
    bool check(vector<int> &arr, int k,int maxPages)
    {
        int count = 1;
        int temp = arr[0];
        for(int i = 1;i<arr.size();i++)
        {
            if(arr[i]+temp <= maxPages)
            {
                temp += arr[i];
            }
            else if(arr[i]<=maxPages)
            {
                temp = arr[i];
                count++;
            }
            else{
                return false;
            }
        }
        //cout<<maxPages<<" "<<count<<endl;
        return k>=count;
    }
    int findPages(vector<int> &arr, int k) {
        // code here
        if(k>arr.size())return -1;
        int st = *max_element(arr.begin(),arr.end()), end = 0;
        for(auto i:arr)end+=i;
        int ans = -1;
        while(st<=end)
        {
            int mid = st + (end-st)/2;
            if(check(arr,k,mid))
            {
                ans = mid;
                end = mid-1;
            }
            else
            {
                
                st = mid+1;
            }
        }
        return ans;
    }
};