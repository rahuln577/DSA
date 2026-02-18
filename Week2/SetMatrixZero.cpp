/*
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

 

Example 1:


Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Example 2:


Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
*/

/*
This problem is called Set Matrix Zeroes. To remember this at a glance, think of it as "Using the First Row and Column as a Notebook." Instead of using extra space, you use the matrix's own edges to store "reminders" of which rows and columns should be wiped out.

1. The Strategy: The In-Place Marker
Normally, you’d need a separate array to remember which indices were zero. To save space, we use the 0th row and 0th column as our marker arrays.

Marking Phase: Iterate through the matrix. If matrix[i][j] == 0, mark the start of that row (matrix[i][0]) and the start of that column (matrix[0][j]) as 0.

The Collision Problem: Both the first row and first column share the same top-left corner (matrix[0][0]). To avoid confusion, we use a separate variable col0 just for the first column.

Filling Phase: Go through the matrix (excluding the first row/column) and if its markers are 0, set the cell to 0.

Edge Case Cleanup: Finally, check if the first row and first column themselves need to be zeroed based on their specific markers.

2. Key Code Components
col0 Variable

matrix[0][0] acts as the marker for the 0th row.

col0 acts as the marker for the 0th column.

This prevents the "row zero" logic from accidentally wiping out the "column zero" logic.

The Double Loop (Marking)

When you find a 0, you "shoot" a signal to the edge: matrix[i][0] = 0 and matrix[0][j] = 0.

The Reverse Cleanup

You must fill the inner matrix first (starting from i=1, j=1).

If you zeroed the first row/column first, you would lose all your markers for the rest of the matrix!

3. Complexity Cheat Sheet
Feature	Efficiency	Why?
Time Complexity	O(N×M)	You traverse the matrix twice (once to mark, once to fill).
Space Complexity	O(1)	You use the input matrix itself for storage + 1 variable.
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int col0 = 1;
        for(int i=0;i<matrix.size();i++)
        {
            for(int j=0;j<matrix[0].size();j++)
            {
                if(matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    if(j==0)
                        col0 = 0;
                    else
                    {
                        matrix[0][j] = 0;
                    }
                }
            }
        }
        for(int i=1;i<matrix.size();i++)
        {
            for(int j=1;j<matrix[0].size();j++)
            {
                if(matrix[0][j] == 0 || matrix[i][0] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        for(int i=0;i<matrix[0].size();i++)
        {
            if(matrix[0][0] == 0)
            {
                matrix[0][i] = 0;
            }
        }
        for(int i=0;i<matrix.size();i++)
        {
            if(col0 == 0)
            {
                matrix[i][0] = 0;
            }
        }
    }
};