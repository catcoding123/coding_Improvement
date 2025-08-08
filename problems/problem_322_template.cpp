#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
using namespace std;

/*
题目: 322. 零钱兑换
难度: Medium
标签: [动态规划, 完全背包]
LeetCode链接: https://leetcode.cn/problems/coin-change/

题目描述:
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的最少硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

示例 1:
输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1

示例 2:
输入：coins = [2], amount = 3
输出：-1

示例 3:
输入：coins = [1], amount = 0
输出：0

约束条件:
- 1 <= coins.length <= 12
- 1 <= coins[i] <= 2^31 - 1
- 0 <= amount <= 10^4

思考要点:
1. 这是什么类型的DP？与之前的题目有什么区别？
2. 状态定义：dp[i] 表示什么含义？
3. 状态转移：如何表达"选择不同硬币"的过程？
4. 边界条件：amount = 0 时如何处理？
5. 无解情况：如何判断和表示？

核心难点:
- 理解完全背包问题：每个硬币可以使用无限次
- 正确处理状态转移：枚举所有可能的硬币选择
- 处理无解情况：用特殊值表示无法组成
- 这是求"最少"的优化问题，不是计数问题
*/

class Solution {
public:
    // 方法1: 递归 - 会超时，但有助理解问题本质
    int coinChangeRecursive(vector<int>& coins, int amount) {
        // TODO: 实现递归解法
        // 思考：对于amount，我们可以选择任意一种硬币
        // coinChange(amount) = min(coinChange(amount-coin) + 1) for all valid coins
        
        return helper(coins, amount);
    }
    
private:
    int helper(vector<int>& coins, int amount) {
        // TODO: 实现递归helper
        // 边界条件：amount = 0 时返回0，amount < 0 时返回-1
        // 递归关系：尝试选择每种硬币，取最小值
        if(amount == 0) return 0;
        if(amount <0) return -1; // 
    
        int minCoins = INT_MAX;

        for(int coin:coins) {
            int helpResult = helper(coins,amount-coin);
            if(helpResult != -1) {
                minCoins = min(minCoins, helpResult+1); // +1
            }
        }
        return minCoins == INT_MAX?-1:minCoins; // 失败的递归会被一步步感染
        /*
        -1就像"毒药"一样会层层向上传播！
        🔍 传播过程示例
        coins=[2], amount=3
        helper(3)
        ├── 选择硬币2: helper(1)
            ├── 选择硬币2: helper(-1)
            │   └── return -1  ❌ 第一层失败
            └── subResult == -1, 跳过+1
            └── return -1  ❌ 传播到第二层
        └── subResult == -1, 跳过+1
        └── return -1  ❌ 传播到顶层
    
        🔄 传播路径
        helper(-1) → -1
            ↓ 传播
        helper(1)  → -1
            ↓ 传播
        helper(3)  → -1
        */
    }
    
public:
    // 方法2: 记忆化搜索 - 递归 + 缓存
    int coinChangeMemo(vector<int>& coins, int amount) {
        // TODO: 实现记忆化搜索
        vector<int> memo(amount + 1, -2);  // -2表示未计算，-1表示无解
        return helperMemo(coins, amount, memo);
    }
    
private:
    int helperMemo(vector<int>& coins, int amount, vector<int>& memo) {
        // TODO: 实现记忆化递归
        // 检查缓存，递归计算，存储结果
        if(amount == 0) return 0;
        if(amount <0) return -1; 

        if(memo[amount]!=-2) return memo[amount];

        int minCoins = INT_MAX;
        for(int coin:coins) {
            int helpResult = helperMemo(coins,amount-coin,memo);
            if(helpResult != -1) {  // 关键：过滤失败路径
                minCoins = min(minCoins, helpResult + 1);
            }
        }
        int tmpResult = minCoins == INT_MAX?-1:minCoins;
        memo[amount] = tmpResult;
        return tmpResult;
    }
    
public:
    // 方法3: 动态规划 - 自底向上 ⭐ 推荐
    int coinChangeDP(vector<int>& coins, int amount) {
        // TODO: 实现动态规划解法
        // 1. 状态定义：dp[i] = 组成金额i所需的最少硬币数
        // 2. 状态转移：dp[i] = min(dp[i-coin] + 1) for all valid coins
        // 3. 边界条件：dp[0] = 0
        // 4. 初始化：dp[i] = amount + 1 (表示无解，因为最多需要amount个1元硬币)
        // 5. 返回结果：dp[amount] > amount ? -1 : dp[amount]
        
        vector<int> dp(amount + 1, amount + 1);  // 初始化为不可能的大值
        dp[0] = 0;  // 边界条件 也是动态规划出口
        
        // TODO: 填充dp数组
        for(int i=1;i<=amount;i++) {
            for(int coin:coins) {
                if(coin <= i) {
                    dp[i] = min(dp[i],dp[i-coin]+1);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
    
    // 方法4: BFS解法 - 层序遍历思想 (进阶)
    int coinChangeBFS(vector<int>& coins, int amount) {
        // TODO: 实现BFS解法 (选做)
        // BFS思想：每一层表示使用相同硬币数能达到的所有金额
        // 第一次到达amount的层数就是最少硬币数
        
        return -1;
    }
    
    // 主函数 - 选择你想实现的方法
    int coinChange(vector<int>& coins, int amount) {
        // 推荐先实现动态规划，理解完全背包的核心思想
        return coinChangeDP(coins, amount);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 322. 零钱兑换" << endl;
    cout << "===================" << endl;
    
    // 测试用例1
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    int result1 = sol.coinChange(coins1, amount1);
    cout << "测试1: coins=[1,2,5], amount=11" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 3" << endl;
    cout << (result1 == 3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> coins2 = {2};
    int amount2 = 3;
    int result2 = sol.coinChange(coins2, amount2);
    cout << "测试2: coins=[2], amount=3" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: -1" << endl;
    cout << (result2 == -1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    vector<int> coins3 = {1};
    int amount3 = 0;
    int result3 = sol.coinChange(coins3, amount3);
    cout << "测试3: coins=[1], amount=0" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 0" << endl;
    cout << (result3 == 0 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 大金额
    vector<int> coins4 = {1, 3, 4};
    int amount4 = 6;
    int result4 = sol.coinChange(coins4, amount4);
    cout << "测试4: coins=[1,3,4], amount=6" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 2" << endl;
    cout << (result4 == 2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 完全无解
    vector<int> coins5 = {3, 5};
    int amount5 = 1;
    int result5 = sol.coinChange(coins5, amount5);
    cout << "测试5: coins=[3,5], amount=1" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: -1" << endl;
    cout << (result5 == -1 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 完全背包DP思路演示
void demonstrateCompleteKnapsackDP() {
    cout << "\n📚 完全背包DP思路演示" << endl;
    cout << "=====================" << endl;
    
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << "硬币面额: [";
    for (int i = 0; i < coins.size(); i++) {
        cout << coins[i];
        if (i < coins.size() - 1) cout << ",";
    }
    cout << "], 目标金额: " << amount << endl;
    cout << "目标: 找到最少硬币数" << endl << endl;
    
    cout << "💡 完全背包DP核心思想：" << endl;
    cout << "与01背包不同，每个硬币可以使用无限次" << endl;
    cout << "对于每个金额i，尝试使用每种硬币，选择最优方案" << endl;
    cout << "dp[i] = min(dp[i-coin] + 1) for all valid coins" << endl << endl;
    
    cout << "🔍 手工计算过程：" << endl;
    
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    
    cout << "初始化: dp[0] = 0, 其他dp[i] = " << amount + 1 << " (表示无解)" << endl;
    
    for (int i = 1; i <= amount; i++) {
        cout << "\n计算 dp[" << i << "]:";
        vector<int> choices;
        
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != amount + 1) {
                int choice = dp[i - coin] + 1;
                choices.push_back(choice);
                cout << "\n  使用硬币" << coin << ": dp[" << i-coin << "] + 1 = " 
                     << dp[i-coin] << " + 1 = " << choice;
            }
        }
        
        if (!choices.empty()) {
            dp[i] = *min_element(choices.begin(), choices.end());
            cout << "\n  选择最小值: dp[" << i << "] = " << dp[i];
        } else {
            cout << "\n  无法组成，dp[" << i << "] = " << dp[i];
        }
        cout << endl;
    }
    
    cout << "\n🎯 最终结果：" << (dp[amount] > amount ? -1 : dp[amount]) << " 个硬币" << endl;
    
    // 追踪具体方案
    if (dp[amount] <= amount) {
        cout << "\n🔍 最优方案追踪：" << endl;
        vector<int> solution;
        int curr = amount;
        
        while (curr > 0) {
            for (int coin : coins) {
                if (curr >= coin && dp[curr - coin] + 1 == dp[curr]) {
                    solution.push_back(coin);
                    curr -= coin;
                    break;
                }
            }
        }
        
        cout << "使用硬币: ";
        for (int coin : solution) {
            cout << coin << " ";
        }
        cout << endl;
    }
}

// 复杂度分析和对比
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 递归解法:" << endl;
    cout << "   时间复杂度: O(S^n) - S是金额，n是硬币种类数" << endl;
    cout << "   空间复杂度: O(S) - 递归栈深度" << endl;
    cout << "   问题: 指数级时间复杂度，大量重复计算" << endl << endl;
    
    cout << "2. 记忆化搜索:" << endl;
    cout << "   时间复杂度: O(S × n) - 每个子问题计算一次" << endl;
    cout << "   空间复杂度: O(S) - 缓存数组 + 递归栈" << endl;
    cout << "   优势: 避免重复计算" << endl << endl;
    
    cout << "3. 动态规划: ⭐ 推荐" << endl;
    cout << "   时间复杂度: O(S × n)" << endl;
    cout << "   空间复杂度: O(S)" << endl;
    cout << "   优势: 自底向上，逻辑清晰，无递归开销" << endl << endl;
    
    cout << "4. BFS解法:" << endl;
    cout << "   时间复杂度: O(S × n)" << endl;
    cout << "   空间复杂度: O(S)" << endl;
    cout << "   特点: 层序遍历，第一次到达即最优" << endl << endl;
    
    cout << "💡 与之前DP题目的区别：" << endl;
    cout << "- 53题最大子数组：连续性约束，每个元素最多使用一次" << endl;
    cout << "- 198题打家劫舍：相邻约束，每个房屋最多偷一次" << endl;
    cout << "- 322题零钱兑换：完全背包，每个硬币可以无限次使用" << endl;
    cout << "- 核心区别：使用次数的约束不同" << endl;
}

// 完全背包概念讲解
void completeKnapsackConcepts() {
    cout << "\n🎓 完全背包DP核心概念" << endl;
    cout << "=====================" << endl;
    
    cout << "📖 什么是完全背包问题？" << endl;
    cout << "有n种物品，每种物品有无限个，每个物品有重量和价值" << endl;
    cout << "背包容量为W，求能装入背包的最大价值" << endl;
    cout << "零钱兑换是完全背包的变种：求最少物品数而非最大价值" << endl << endl;
    
    cout << "🔑 完全背包vs01背包：" << endl;
    cout << "- 01背包：每个物品最多选择一次" << endl;
    cout << "- 完全背包：每个物品可以选择无限次" << endl;
    cout << "- 状态转移的差异：完全背包在内层循环中可以使用已更新的dp值" << endl << endl;
    
    cout << "📋 零钱兑换的完全背包建模：" << endl;
    cout << "- 物品：各种面额的硬币" << endl;
    cout << "- 重量：硬币面额" << endl;
    cout << "- 价值：1（每个硬币贡献1个计数）" << endl;
    cout << "- 背包容量：目标金额" << endl;
    cout << "- 目标：最小化硬币总数" << endl << endl;
    
    cout << "🎯 状态转移方程推导：" << endl;
    cout << "设dp[i] = 组成金额i的最少硬币数" << endl;
    cout << "对于每个金额i，尝试使用每种硬币coin：" << endl;
    cout << "- 如果i >= coin，可以使用该硬币" << endl;
    cout << "- 使用后剩余金额为i-coin，需要dp[i-coin]个硬币" << endl;
    cout << "- 加上当前硬币，总计dp[i-coin]+1个" << endl;
    cout << "- 在所有选择中取最小值：dp[i] = min(dp[i-coin]+1)" << endl << endl;
    
    cout << "🌟 常见的完全背包题目：" << endl;
    cout << "- 322. 零钱兑换 (最少硬币数)" << endl;
    cout << "- 518. 零钱兑换II (组合数)" << endl;
    cout << "- 279. 完全平方数 (最少平方数)" << endl;
    cout << "- 377. 组合总和Ⅳ (排列数)" << endl;
}

int main() {
    cout << "🚀 LeetCode 322. 零钱兑换" << endl;
    cout << "========================" << endl;
    cout << "🔥 这是完全背包动态规划的经典题目！" << endl;
    cout << "💡 重点掌握无限选择的DP思维" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    completeKnapsackConcepts();
    demonstrateCompleteKnapsackDP();
    runTests();
    complexityAnalysis();
    
    return 0;
}