
/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
*/

/*
This is **Edit Distance (Levenshtein Distance)**. To remember this, think of it as **"The Alignment Grid"**: at each character pair, you decide whether to **Delete**, **Replace**, or **Insert** to morph `word1` into `word2`.

---

## 1. The Strategy: Choice Tree

Your recursive formulation captures the core logic perfectly, but contains **one critical bug** in the base cases.

1. **Character Match (`word1[i] == word2[j]`):** No operation cost added. Move both indices backward $\rightarrow$ `calc(i-1, j-1)`.
2. **Character Mismatch:** Try all 3 operations and take the minimum ($1 + \text{min}$):
* **Delete:** Remove character from `word1` $\rightarrow$ `calc(i-1, j)`
* **Replace:** Swap character in `word1` to match `word2` $\rightarrow$ `calc(i-1, j-1)`
* **Insert:** Insert character into `word1` to match `word2` $\rightarrow$ `calc(i, j-1)`



---

## 2. Bug Fix in Your Base Cases

```cpp
// ❌ INCORRECT IN YOUR CODE
if(index1 < 0) return index2 + 1;
if(index2 < 0) return index2 + 1; // Bug! Returning index2+1 when index2 < 0 gives 0!

// ✅ FIXED BASE CASES
if(index1 < 0) return index2 + 1; // Need (index2 + 1) insertions
if(index2 < 0) return index1 + 1; // Need (index1 + 1) deletions

```

* If `word2` runs out (`index2 < 0`), you must delete all remaining characters of `word1`, which takes `index1 + 1` operations.

---

## 3. Complexity & DP Optimization

Without memoization, pure recursion takes exponential time $O(3^{N+M})$ causing TLE.

### Complexity Cheat Sheet

| Approach | Time Complexity | Space Complexity |
| --- | --- | --- |
| **Recursive** | $O(3^{N+M})$ | $O(N + M)$ recursion stack |
| **2D DP Bottom-Up** | $O(N \cdot M)$ | $O(N \cdot M)$ |
| **1D Space-Optimized** | $O(N \cdot M)$ | **$O(M)$** |

*(where $N = \text{word1.size()}$ and $M = \text{word2.size()}$)*

### Iterative 2D DP Implementation

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Base cases
        for (int i = 0; i <= n; i++) dp[i][0] = i; // Deletions
        for (int j = 0; j <= m; j++) dp[0][j] = j; // Insertions

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],    // Delete
                        dp[i - 1][j - 1],// Replace
                        dp[i][j - 1]     // Insert
                    });
                }
            }
        }
        return dp[n][m];
    }
};

```

---

## 4. Revision Quick-Map: 3-Choice DP Problems

| Problem | Recurrence Mismatch |
| --- | --- |
| **Edit Distance** | $1 + \min(\text{Delete}, \text{Replace}, \text{Insert})$ |
| **Distinct Subsequences** | Match: $\text{take} + \text{skip}$, Mismatch: $\text{skip}$ |
| **Wildcard Matching** | Match (`?`): `dp[i-1][j-1]`, Star (`*`): `dp[i-1][j] | dp[i][j-1]` |

---

## 💡 Quick Logic Check

`word1 = "horse"`, `word2 = "ros"`

1. `horse` $\rightarrow$ `rorse` (Replace 'h' with 'r')
2. `rorse` $\rightarrow$ `rose` (Delete 'r')
3. `rose` $\rightarrow$ `ros` (Delete 'e')
4. **Total Operations:** `3`
*/
class Solution {
public:
    int calc(int index1,int index2,string word1, string word2)
    {
        if(index1<0)return index2+1;
        if(index2<0)return index2+1;
        if(word1[index1] == word2[index2])
        {
            return calc(index1-1,index2-1,word1,word2);
        }
        int first = 1+calc(index1-1,index2,word1,word2);
        int second = 1+calc(index1-1,index2-1,word1,word2);
        int third = 1+calc(index1,index2-1,word1,word2);
        return min(first,min(second,third));
    }
    int minDistance(string word1, string word2) {
        return calc(word1.size()-1,word2.size()-1,word1,word2);
    }
};