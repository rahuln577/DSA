/*
This is the **Unbounded Knapsack Problem** (also known as the Knapsack with Duplicate Items). Think of it as **"The Unlimited Supply Bag"**: unlike the 0/1 Knapsack where each item can be picked at most once, here you can pick an item as many times as you want as long as your total weight doesn't exceed `capacity`.

---

## 1. The Strategy: Pick, Stay, and Repeat

Because item supplies are infinite, whenever you decide to **take** an item, you stay at the *same item index* `i` instead of moving to `i - 1`.

1. **State Definition:** `dp[i][j]` represents the maximum value achievable considering items up to index `i` with weight capacity `j`.
2. **Transition Logic:**
* **Do Not Take:** Skip the current item and inherit the best value using previous items $\rightarrow$ `dp[j][i - 1]`.
* **Take Item:** Include `wt[i]` into the capacity, collect `val[i]`, and remain eligible to choose item `i` again $\rightarrow$ `val[i] + dp[j - wt[i]][i]`.


3. **The 1D Space Optimization:** Because transitions only depend on values from the current column/row at smaller capacities, we can compress the 2D table into a 1D array traversed from left to right.

---

## 2. Key Code Components & Bugs to Fix

Your code logic is fundamentally correct for 2D DP, but it contains **two subtle bugs**:

### Bug 1: Out-of-Bounds Index Return

```cpp
// ❌ WRONG
return dp[capacity][wt.size() - 1]; 

```

* You passed `val.size()` rows/columns, but referenced `wt.size() - 1` in `dp[capacity]`. If `wt` and `val` are guaranteed same size it's fine, but your table indexing layout is `dp[weight][item_index]`. The safe reference is `dp[capacity][val.size() - 1]`.

### Bug 2: Table Dimensions vs Loop Access

* Your table is instantiated as `dp[capacity + 1][val.size()]` where rows are capacities and columns are item indices.
* Accessing `dp[j][i]` works, but standard DP conventions usually place items on rows and capacity on columns `dp[items][capacity]` for better cache locality.

---

## 3. Complexity & Space Optimization

### Complexity Cheat Sheet

| Feature | 2D Approach (Your Code) | 1D Optimized Approach |
| --- | --- | --- |
| **Time Complexity** | $O(N \cdot W)$ | $O(N \cdot W)$ |
| **Space Complexity** | $O(N \cdot W)$ | **$O(W)$** |

*(where $N$ is the number of items and $W$ is `capacity`)*

### 1D Space Optimization Code

```cpp
class Solution {
  public:
    int knapSack(vector<int>& val, vector<int>& wt, int capacity) {
        vector<int> dp(capacity + 1, 0);
        
        for (int i = 0; i < val.size(); i++) {
            for (int j = wt[i]; j <= capacity; j++) {
                dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
            }
        }
        return dp[capacity];
    }
};

```

---

## 4. Revision Comparison: 0/1 vs Unbounded Knapsack

| Feature | 0/1 Knapsack | Unbounded Knapsack |
| --- | --- | --- |
| **Recurrence (Take)** | `val[i] + dp[i-1][j - wt[i]]` | `val[i] + dp[i][j - wt[i]]` |
| **1D Array Loop** | Traverse capacity **Right-to-Left** (`W` down to `wt[i]`) | Traverse capacity **Left-to-Right** (`wt[i]` up to `W`) |

---

## 💡 Quick Logic Check

Items: `val = [1, 4, 5, 6]`, `wt = [1, 2, 3, 4]`, Capacity = `5`

1. **Item 0 (`val=1, wt=1`):** `dp = [0, 1, 2, 3, 4, 5]`
2. **Item 1 (`val=4, wt=2`):** `dp` updates for $j \ge 2$:
* $j=2$: $\max(2, 4 + 0) = 4$
* $j=3$: $\max(3, 4 + 1) = 5$
* $j=4$: $\max(4, 4 + 4) = 8$
* $j=5$: $\max(5, 4 + 5) = 9$


3. **Result for capacity 5:** `9` (Take item 1 twice and item 0 once: $4 + 4 + 1 = 9$).
*/
class Solution {
  public:
    int knapSack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        int value = 0;
        vector<vector<int>> dp(capacity+1,vector<int>(val.size(),0));
        for(int j=0;j<=capacity;j++)
        {
            if(j>=wt[0])
            {
                dp[j][0] = (j/wt[0])*val[0];
                
            }
        }
        for(int i=1;i<val.size();i++)
        {
            for(int j=0;j<=capacity;j++)
            {
                int nottake = dp[j][i-1];
                int take = 0;
                if(j>=wt[i])
                {
                    take = val[i]+dp[j-wt[i]][i];
                }
                dp[j][i]=max(take,nottake);
            }
        }
        return dp[capacity][wt.size()-1];
    }
};