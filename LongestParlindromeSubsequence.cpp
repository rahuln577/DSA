/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".
*/

/*
This is the **Longest Palindromic Subsequence (LPS)** problem. Your solution cleverly leverages a classic algorithm equivalence: **LPS of string $S$ is equal to the Longest Common Subsequence (LCS) between $S$ and its reverse $S^R$**.

---

## 1. The Strategy: Palindrome via Reversal

A palindrome reads the same forwards and backwards. Finding the longest sequence of characters that appears in the same order both forwards and backwards is identical to finding the **Longest Common Subsequence** of `s` and `reverse(s)`.

1. **Reversal:** Generate string `s2` as `reverse(s)`.
2. **LCS Matching:**
* **Matching Characters (`s[i-1] == s2[j-1]`):** Extend the common sequence $\rightarrow$ `dp[i][j] = 1 + dp[i-1][j-1]`.
* **Mismatch (`s[i-1] != s2[j-1]`):** Take the maximum by either ignoring character from `s` or from `s2` $\rightarrow$ `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.


3. **Result:** The bottom-right cell `dp[n][n]` holds the answer.

---

## 2. Key Code Components

```cpp
string s2{s};
reverse(s2.begin(), s2.end());

```

* **The Bridge:** Transforming the problem into LCS eliminates the need for 2-pointer interval DP (`i` to `j` on a single string) and lets you reuse standard 2D grid LCS logic directly.

---

## 3. Complexity Cheat Sheet

| Feature | 2D Approach (Your Code) | 1D Space-Optimized Approach |
| --- | --- | --- |
| **Time Complexity** | $O(N^2)$ | $O(N^2)$ |
| **Space Complexity** | $O(N^2)$ | **$O(N)$** |

*(where $N = \text{s.size()}$)*

### 1D Space-Optimized Implementation

Since row `i` only depends on the current and previous rows, space can be reduced to two 1D vectors or a single vector using a temporary diagonal tracking variable:

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        string s2 = s;
        reverse(s2.begin(), s2.end());
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        return prev[n];
    }
};

```

---

## 4. Revision Comparison: Palindrome Problems

| Problem | Core DP Strategy | Recurrence on Mismatch |
| --- | --- | --- |
| **Longest Common Subsequence** | Compare 2 strings | `max(dp[i-1][j], dp[i][j-1])` |
| **Longest Palindromic Subsequence** | LCS of `s` and `reverse(s)` | `max(dp[i-1][j], dp[i][j-1])` |
| **Longest Palindromic Substring** | Contiguous substring match | Resets to `0` / invalid |
| **Minimum Deletions to Make Palindrome** | Total length - LPS | $N - \text{LPS}(s)$ |

---

## 💡 Quick Logic Check

String: `s = "bbbab"` $\rightarrow$ Reversed: `s2 = "babbb"`

1. **LCS Alignment:** The longest common sequence between `"bbbab"` and `"babbb"` is `"bbbb"` of length 4.
2. **Output:** `4`.
*/

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string s2{s};
        reverse(s2.begin(),s2.end());
        vector<vector<int>> dp(s.size()+1,vector<int>(s.size()+1,0));
        for(int i=1;i<=s.size();i++)
        {
            for(int j=1;j<=s2.size();j++)
            {
                if(s[i-1] == s2[j-1])
                {
                    dp[i][j] = 1+dp[i-1][j-1];
                    continue;
                }
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[s.size()][s.size()];
    }
};