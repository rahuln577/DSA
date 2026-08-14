/*
Given two strings pat and txt which may be of different sizes, You have to return true if the wildcard pattern i.e. pat, matches with txt else return false.

The wildcard pattern pat can include the characters '?' and '*'.

'?' – matches any single character.
'*' – matches any sequence of characters (including the empty sequence).
Note: The matching should cover the entire txt (not partial txt).

Examples:

Input: txt = "abcde", pat = "a?c*"
Output: true
Explanation: '?' matches with 'b' and '*' matches with "de".
*/

/*
This is **Wildcard Matching**. To remember this, think of it as **"The Flexible Sponge"**: `?` matches a single character, while `*` acts like an elastic sponge that can absorb **zero or more** characters.

--- 

## 1. The Strategy: Handling the `*`

Your top-down memoization logic is completely correct.

1. **Character or `?` Match:** Move both pointers backward $\rightarrow$ `check(i1 - 1, i2 - 1)`.
2. **Wildcard `*` Branch:**
* **Absorb 1 character (`i1 - 1, i2`):** `*` matches `txt[i1]` and stays active for previous characters.
* **Absorb 0 characters (`i1, i2 - 1`):** `*` matches empty sequence and disappears.


3. **Base Cases:**
* Both strings empty (`i1 < 0, i2 < 0`): Match valid $\rightarrow$ `1`.
* Pattern empty but text remains (`i1 >= 0, i2 < 0`): Match invalid $\rightarrow$ `0`.
* Text empty but pattern remains (`i1 < 0, i2 >= 0`): Valid **only if** all remaining pattern characters are `*`.



---

## 2. Key Code Components

```cpp
if (pat[i2] == '*') {
    return dp[i1][i2] = (check(txt, pat, i1 - 1, i2, dp) || 
                         check(txt, pat, i1, i2 - 1, dp));
}

```

* **Difference from Regular Expression Matching (`.*`):** Here, `*` operates standalone. It doesn't depend on the character before it.

---

## 3. Complexity & DP Optimization

### Complexity Cheat Sheet

| Approach | Time Complexity | Space Complexity |
| --- | --- | --- |
| **Top-Down (Your Code)** | $O(N \cdot M)$ | $O(N \cdot M) + O(N + M)$ stack |
| **2D Iterative DP** | $O(N \cdot M)$ | $O(N \cdot M)$ |
| **1D Space-Optimized** | $O(N \cdot M)$ | **$O(M)$** |

*(where $N = \text{txt.size()}$ and $M = \text{pat.size()}$)*

### 1D Space-Optimized Implementation

```cpp
class Solution {
public:
    bool wildCard(string &txt, string &pat) {
        int n = txt.size(), m = pat.size();
        vector<bool> prev(m + 1, false), curr(m + 1, false);

        // Base case: empty text and empty pattern
        prev[0] = true;

        // Base case: empty text matched with initial '*'s
        for (int j = 1; j <= m; j++) {
            if (pat[j - 1] == '*') prev[j] = prev[j - 1];
        }

        for (int i = 1; i <= n; i++) {
            curr[0] = false; // Non-empty text cannot match empty pattern
            for (int j = 1; j <= m; j++) {
                if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                } else if (pat[j - 1] == '*') {
                    curr[j] = prev[j] || curr[j - 1];
                } else {
                    curr[j] = false;
                }
            }
            prev = curr;
        }
        return prev[m];
    }
};

```

---

## 4. Revision Comparison: String Pattern Matching

| Problem | `?` / `.` Meaning | `*` Meaning |
| --- | --- | --- |
| **Wildcard Matching** | `?` matches **any single character** | `*` matches **any sequence** (0 or more) |
| **Regular Expression** | `.` matches **any single character** | `*` matches **0 or more of PREVIOUS char** |

---

## 💡 Quick Logic Check

Text: `"abcde"`, Pattern: `"a*e"`

1. `a` matches `a`.
2. `*` absorbs `"bcd"`.
3. `e` matches `e`.
4. Output: `true`.
*/
class Solution {
  public:
    int check(string &txt, string &pat,int i1,int i2,vector<vector<int>>& dp)
    {
        if(i2<0 && i1<0)return 1;
        if(i2<0 && i1>=0)return 0;
        if(i1<0 && i2>=0)
        {
            for(int i =0;i<=i2;i++)if(pat[i]!='*')return 0;
            return 1;
        }
        if(dp[i1][i2]!=-1)return dp[i1][i2];
        if((txt[i1] == pat[i2]) || (pat[i2] == '?'))
        {
            return (dp[i1][i2]=check(txt,pat,i1-1,i2-1,dp));
        }
        if(pat[i2] == '*')return (dp[i1][i2]=(check(txt,pat,i1-1,i2,dp)||check(txt,pat,i1,i2-1,dp)));
        return (dp[i1][i2]=0);
    }
    bool wildCard(string &txt, string &pat) {
        // code here
        vector<vector<int>> dp(txt.size(),vector<int>(pat.size(),-1));
        return check(txt,pat,txt.size()-1,pat.size()-1,dp);
    }
};