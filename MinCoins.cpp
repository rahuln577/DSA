/*
322. Coin Change

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

*/

class Solution {
public:
    int calc(vector<int>& coins, int amount,int index,map<pair<int,int>,int>& dp)
    {
        if(index==(coins.size()-1)){
            if(amount == 0)return 0;
            if((amount%coins[index]) == 0)return (amount/coins[index]);
            return 1e9;
        }
        if(dp.find({index,amount})!=dp.end())return dp[{index,amount}];
        int nottake = calc(coins,amount,index+1,dp);
        int take = INT_MAX;
        if(coins[index]<=amount){
            take = 1+calc(coins,amount-coins[index],index,dp);
        }
        return (dp[{index,amount}]=min(take,nottake));
}
    int coinChange(vector<int>& coins, int amount) {
        map<pair<int,int>,int> dp;
        int ans = calc(coins,amount,0,dp);
        if(ans>=1e9)return -1;
        return ans;
    }
};