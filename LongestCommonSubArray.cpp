/*
Given two strings s1 and s2, determine the length of the longest substring that appears in both strings.

Examples:

Input: s1 = "ABCDGH", s2 = "ACDGHR"
Output: 4
Explanation: The longest common substring is "CDGH" with a length of 4.
Input: s1 = "abc", s2 = "acb"
Output: 1
Explanation: The longest common substrings are "a", "b", "c" all having length 1.
*/

/*
This is the **Longest Common Substring** problem. To remember this, think of it as **"The Continuous Chain"**: unlike Longest Common *Subsequence* where characters can be scattered, a *substring* requires characters to match consecutively. If a pair fails to match, the contiguous chain immediately breaks and resets to `0`.

---

## 1. The Strategy: Extend or Break

Your 2D dynamic programming solution is optimal in structure:

1. **State Definition:** `dp[i][j]` represents the length of the longest common suffix ending at index `s1[i-1]` and `s2[j-1]`.
2. **Matching Pair (`s1[i-1] == s2[j-1]`):** Extend the contiguous chain found at the previous diagonal element $\rightarrow$ `dp[i][j] = 1 + dp[i-1][j-1]`.
3. **Mismatched Pair (`s1[i-1] != s2[j-1]`):** The chain breaks. Since `dp` table is initialized to `0`, `dp[i][j]` remains `0`.
4. **Track Maximum:** Since the longest common substring can end at *any* pair of characters, keep a global tracker `ans` for the maximum value seen in the grid.

---

## 2. Key Code Components

```cpp
if (s1[i-1] == s2[j-1]) {
    dp[i][j] = 1 + dp[i-1][j-1];
    ans = max(ans, dp[i][j]);
}
// Else branch implicitly sets dp[i][j] = 0

```

* **Difference from Subsequence (LCS):** In LCS, on a mismatch, you take `max(dp[i-1][j], dp[i][j-1])`. In Substring, mismatch instantly resets the length to `0`.

---

## 3. Complexity & Space Optimization

### Complexity Cheat Sheet

| Feature | 2D Approach (Your Code) | 1D Space-Optimized Approach |
| --- | --- | --- |
| **Time Complexity** | $O(N \cdot M)$ | $O(N \cdot M)$ |
| **Space Complexity** | $O(N \cdot M)$ | **$O(M)$** |

*(where $N = \text{s1.size()}$ and $M = \text{s2.size()}$)*

### 1D Space Optimization Code

Since row `i` only depends on the previous row `i-1` and strictly on the left-diagonal cell `j-1`, we can traverse backwards through columns using a single row array:

```cpp
class Solution {
  public:
    int longCommSubstr(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<int> dp(m + 1, 0);
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = 1 + dp[j - 1];
                    ans = max(ans, dp[j]);
                } else {
                    dp[j]  = 0; // Crucial reset on mismatch
                }
            }
        }
        return ans; 
    }
};

```

---

## 4. Revision Quick-Map: Substring vs. Subsequence

| Problem | Mismatch Condition | Answer Location |
| --- | --- | --- |
| **Longest Common Subsequence** | `dp[i][j] = max(dp[i-1][j], dp[i][j-1])` | Always at bottom-right cell `dp[N][M]` |
| **Longest Common Substring** | `dp[i][j] = 0` | Maximum value anywhere in the DP matrix |

---

## 💡 Quick Logic Check

Strings: `s1 = "ABCDGH"`, `s2 = "ACDGHR"`

1. `s1[1..3]` ("CDG") matches `s2[1..3]` ("CDG").
2. Matching continues through `s1[4]` ("H") and `s2[4]` ("H") $\rightarrow$ chain grows up to length `4`.
3. Output: `4` ("CDGH").
*/
class Solution {
  public:
    int longCommSubstr(string& s1, string& s2) {
        // code here
        int ans = 0;
        vector<vector<int>> dp(s1.size()+1,vector<int>(s2.size()+1,0));
        for(int i=1;i<=s1.size();i++)
        {
            for(int j=1;j<=s2.size();j++)
            {
                if(s1[i-1] == s2[j-1])
                {
                    dp[i][j]=1+dp[i-1][j-1];
                    ans = max(ans,dp[i][j]);
                }
            }
        }
        return ans;
    }
};