/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Example 2:


Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
*/

/*
To remember Rotate Image (90 degrees clockwise), think of the phrase: "Transpose then Flip." It is the most elegant way to rotate a square matrix without using any extra space.

1. The Strategy: The Two-Step Dance
Rotating a matrix directly is geometrically confusing. Breaking it into two simple matrix operations makes it trivial:

Transpose: Swap the rows with the columns. Imagine a diagonal line from the top-left to the bottom-right; you are simply reflecting every element across that line.

Reverse Rows: Flip each row horizontally. This moves the elements from the "left" side to the "right" side, completing the 90-degree turn.

2. Key Code Components
Step 1: Transpose

The Loop: for(int j = i; j < n; j++) (or j >= i as in your code).

The Logic: You only iterate over the upper triangle of the matrix. If you iterated over the whole thing, you would swap elements twice (e.g., swapping (1,2) with (2,1) and then later swapping (2,1) back with (1,2)), ending up right where you started!

The Swap: swap(matrix[i][j], matrix[j][i]).

Step 2: Reverse

The Logic: Once transposed, the matrix looks like a 90-degree rotation that was also mirrored. Reversing each row fixes the mirroring.

The Action: reverse(matrix[i].begin(), matrix[i].end()).
*/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i=0;i<matrix.size();i++)
        {
            for(int j=matrix.size()-1;j>=i;j--)
            {
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(int i=0;i<matrix.size();i++)
        {
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};