/*
We have a horizontal number line. On that number line, we have gas stations at positions stations[0], stations[1], ..., stations[n-1]. Now, we add k more gas stations so that d, the maximum distance between adjacent gas stations, is minimized. We have to find the smallest possible value of d. Find the answer exactly to 6 decimal places.
Note: stations is in a strictly increasing order.

Examples:

Input: stations[] = [1, 2, 3, 4, 5], k = 2
Output: 1.00
Explanation: Since all gaps are already equal (1 unit each), adding extra stations in between does not reduce the maximum distance.
Input: stations[] = [3, 6, 12, 19, 33], k = 3
Output: 6.00 
Explanation: The largest gap is 14 (between 19 and 33). Adding 2 stations there splits it into approx 4.67. The next largest gap is 7 (between 12 and 19). Adding 1 station splits it into 3.5. Now the maximum gap left is 6.
Constraint:
1 ≤ stations.size() ≤ 105
0 ≤ stations[i] ≤ 106
0 ≤ k ≤ 105
*/

/*
This is the Minimize Max Distance to Gas Stations problem. Your current approach uses a Priority Queue (Max-Heap), which is great for understanding the greedy logic but can be too slow for large constraints.

To remember this problem, think of it as "The Rubber Band": you have fixed points (stations) and you want to insert new points to "stretch" the gaps as evenly as possible so the largest gap is as small as it can be.

1. The Strategy: Two Ways to Play
A. The Greedy (Priority Queue) Approach — Current

Calculate the initial distances between all adjacent stations.

In each step, pick the largest current distance and place a station there.

If you place 1 station in a gap, the distance becomes D/2. If you place 2, it becomes D/3, and so on.

Issue: If K is 10 
6
 , this loop runs a million times. O(KlogN) is too slow.

B. The Binary Search on Answer — Optimization

Instead of placing stations one by one, we guess a "Max Distance" X and see if K stations are enough to make all gaps ≤X.

Range: st = 0, end = stations[last] - stations[0].

Predicate (check): For a gap D, you need ⌊D/X⌋ stations to ensure no sub-gap exceeds X.

Binary Search: This runs in O(Nlog(Precision)), which is much faster when K is huge.

2. Key Code Components (Greedy Version)
(double)(dist) / (hasPoints[i] + 1)

This is the "Division Logic." If you have a gap of 10 and you add 1 station, you have 2 sections of 5. If you add 2 stations, you have 3 sections of 3.33. You always divide the original distance by the number of sections (stations_added + 1).

pq.push({new_dist, index})

After updating a gap, you put it back into the heap. The heap ensures that for the next of your K stations, you are always attacking the "weakest link" (the largest current gap).

3. Complexity Cheat Sheet
Approach	Time Complexity	Best For...
Priority Queue	O(KlogN)	Small K, Easy to visualize.
Binary Search	O(Nlog( 
precision
max_dist
​	
 ))	Large K (e.g., K=10 
6
 ).
4. The Binary Search Version (For your Revision)
If the interviewer says "K is very large," you switch to this logic:

C++
bool check(double dist, vector<int> &stations, int K) {
    int count = 0;
    for (int i = 0; i < stations.size() - 1; i++) {
        count += floor((stations[i+1] - stations[i]) / dist);
    }
    return count <= K;
}
💡 Quick Logic Check
Stations: [0, 10], K=1

PQ: Max gap is 10. Add 1 station. New gap = 10/(1+1)=5.

Result: 5.

Stations: [0, 10], K=2

PQ: Max gap is 10. Add 1 station. Gap becomes 5.

PQ: Max gap is now 5 (from the two sections). Add another station to one of those.

Actually, the PQ logic would see the original gap of 10 and realize adding 2 stations makes it 10/3=3.33.
*/

class Solution {
  public:
    double minMaxDist(vector<int> &stations, int K) {
        // Code here
        priority_queue<pair<double,int>> pq;
        vector<int> hasPoints;
        if(stations.size()<=1)return 0;
        for(int i=0;i<stations.size()-1;i++)
        {
            hasPoints.push_back(0);
            pq.push({stations[i+1]-stations[i],i});
        }
        while(K>0)
        {
            auto maxi = pq.top() ;
            hasPoints[maxi.second]++;
            K--;
            pq.pop();
            pq.push({(double)(stations[maxi.second+1]-stations[maxi.second])/(double)(hasPoints[maxi.second]+1),maxi.second});
        }
        return pq.top().first;
    }
} ;