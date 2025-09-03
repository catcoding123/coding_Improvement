/*
121. 买卖股票的最佳时机 (Easy)
https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/

题目描述：
给定一个数组 prices，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。
设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0。

示例 1：
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

示例 2：
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。

约束条件：
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^4

专题归属：动态规划 - 状态机DP
相关题目：122.买卖股票II、123.买卖股票III、188.买卖股票IV

算法分析：
思路提示：
1. 方法一：一次遍历 - 记录最低价格，计算每天卖出的最大利润
2. 方法二：动态规划 - 状态机模型，考虑每天持有/不持有股票的状态

时间复杂度：O(n)
空间复杂度：O(1) - 一次遍历法，O(n) - DP数组法

易错点：
1. 必须先买后卖，注意买卖顺序
2. 同一天不能买卖
3. 没有利润时返回0
*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：单调栈
    int maxProfit(vector<int>& prices) {
        // TODO: 实现一次遍历解法
        // 提示：维护到目前为止的最低价格，计算每天卖出的最大利润
        if(prices.size() <=1) return 0;
        stack<int> st;
        int max_val = 0;
        for(int i=0;i<prices.size(); i++) {
            while(!st.empty() && prices[i] < st.top()) {
                st.pop();
            }
            if(st.empty()) {
                st.push(prices[i]); // st底部保留一定是最小的
            } else {
                max_val = max(max_val, prices[i] - st.top());
            }
        }
        return max_val;
    }
    
    // 方法二：动态规划法 
    int maxProfitDP(vector<int>& prices) {
        // TODO: 实现DP解法
        // 提示：定义状态 dp[i][0/1] 表示第i天不持有/持有股票的最大利润
        // 状态转移：
        // dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  // 今天不持有
        // dp[i][1] = max(dp[i-1][1], -prices[i])             // 今天持有
        
        return 0;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 标准情况
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "测试1 - 预期结果: 5, 实际结果: " << solution.maxProfit(prices1) << endl;
    
    // 测试用例2: 递减序列
    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "测试2 - 预期结果: 0, 实际结果: " << solution.maxProfit(prices2) << endl;
    
    // 测试用例3: 递增序列
    vector<int> prices3 = {1, 2, 3, 4, 5};
    cout << "测试3 - 预期结果: 4, 实际结果: " << solution.maxProfit(prices3) << endl;
    
    // 测试用例4: 单个元素
    vector<int> prices4 = {1};
    cout << "测试4 - 预期结果: 0, 实际结果: " << solution.maxProfit(prices4) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解状态机DP的基本概念
2. 掌握空间优化技巧：二维DP到一维DP到O(1)空间
3. 体会贪心思想在DP中的应用
4. 为后续多次交易的股票问题打基础

相关扩展：
- 122题：可以多次买卖，贪心策略
- 123题：最多完成两笔交易，状态机DP进阶
- 309题：含冷冻期的买卖股票，状态更复杂
*/