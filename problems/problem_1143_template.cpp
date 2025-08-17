#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 1143. 最长公共子序列
难度: Medium
标签: [动态规划, 双序列DP, 字符串]
LeetCode链接: https://leetcode.cn/problems/longest-common-subsequence/

题目描述:
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
如果不存在公共子序列，返回 0。

一个字符串的子序列是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的公共子序列是这两个字符串所共同拥有的子序列。

示例 1:
输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace" ，它的长度为 3 。

示例 2:
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。

示例 3:
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。

约束条件:
- 1 <= text1.length, text2.length <= 1000
- text1 和 text2 仅由小写英文字符组成

思考要点:
1. 这是什么类型的DP？与之前学过的单序列DP有什么区别？
2. 状态定义：dp[i][j] 表示什么含义？
3. 状态转移：当 text1[i] == text2[j] 时怎么处理？不等时怎么处理？
4. 边界条件：空字符串的LCS长度是多少？
5. 双序列DP的特点是什么？

核心难点:
- 理解双序列DP的二维状态定义
- 正确处理字符匹配和不匹配的状态转移
- 理解LCS问题的本质：在两个序列中找最长的共同模式
- 掌握二维DP的边界条件处理
*/

class Solution {
public:
    // 方法1: 二维动态规划 - 经典解法 ⭐
    int longestCommonSubsequenceDP(string text1, string text2) {
        // TODO: 实现二维DP解法
        // 1. 状态定义：dp[i][j] = text1前i个字符和text2前j个字符的LCS长度
        // 2. 状态转移：
        //    if (text1[i-1] == text2[j-1]): dp[i][j] = dp[i-1][j-1] + 1
        //    else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        // 3. 边界条件：dp[0][j] = 0, dp[i][0] = 0 (空字符串的LCS为0)
        // 4. 返回结果：dp[m][n]
        
        int m = text1.length(), n = text2.length();
        
        // 创建(m+1)x(n+1)的DP表，多出来的一行一列用于边界 -- 有点类似哨兵，记录在dynamic_programming.md中
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));      
        // TODO: 填充DP表
        for(int i=0; i< m; i++) {
            for(int j=0; j<n; j++) {
                if(text1[i] == text2[j]) {
                    dp[i+1][j+1] = dp[i][j] + 1;
                } else {
                    dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // 方法2: 记忆化搜索 - 自顶向下 ⭐
    int longestCommonSubsequenceMemo(string text1, string text2) {
        // TODO: 实现记忆化搜索
        // 递归思路：
        // lcs(i, j) = 考虑text1[0..i-1]和text2[0..j-1]的LCS
        // if (text1[i-1] == text2[j-1]): lcs(i, j) = lcs(i-1, j-1) + 1
        // else: lcs(i, j) = max(lcs(i-1, j), lcs(i, j-1))
        
        int m = text1.length(), n = text2.length();
        vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
        
        return helper(text1, text2, m, n, memo);
    }
    
private:
    int helper(string& text1, string& text2, int i, int j, vector<vector<int>>& memo) {
        // TODO: 实现递归helper
        // 边界条件：i == 0 或 j == 0 时返回 0
        // 检查缓存
        // 递归计算并缓存结果
        //出口
        if(i==0 || j==0) {
            return 0;
        }
        if(memo[i][j] != -1) return memo[i][j];
        int currCount = 0;
        if(text1[i] == text2[j]) {
            currCount = helper(text1,text2,i-1,j-1,memo) + 1;
        } else {
            currCount = max(helper(text1,text2,i,j-1,memo),helper(text1,text2,i-1,j,memo));
        }
        memo[i][j] = currCount;
        return currCount;
    }
    
public:
    // 方法3: 空间优化 - 一维DP ⭐⭐ 进阶
    int longestCommonSubsequenceOptimized(string text1, string text2) {
        // TODO: 实现空间优化版本
        // 观察：dp[i][j] 只依赖于 dp[i-1][j-1], dp[i-1][j], dp[i][j-1]
        // 可以用滚动数组优化空间复杂度从O(mn)到O(min(m,n))
        int m = text1.size(), n = text2.size();
        if(m==0 || n==0) return 0;

        vector<int> pre(n+1, 0);
        vector<int> curr(n+1, 0);

        for(int i=0; i<m; i++) {
            curr[0] = 0;
            for(int j=0; j<n; j++) {
                if(text1[i] == text2[j]) {
                    curr[j+1] = pre[j] + 1;
                } else {
                    curr[j+1] = max(pre[j+1],curr[j]);
                }
            }
            swap(pre,curr);
        }
        
        return pre[n]; // curr最终的结果会包含在pre中，swap
    }
    
    // 方法4: 构造具体的LCS字符串 (选做)
    string buildLCS(string text1, string text2) {
        // TODO: 构造具体的最长公共子序列字符串
        // 先计算DP表，然后从dp[m][n]回溯构造字符串
        
        return "";
    }
    
    // 主函数 - 选择你想实现的方法
    int longestCommonSubsequence(string text1, string text2) {
        // 推荐先实现二维DP，理解双序列DP的思维
        return longestCommonSubsequenceDP(text1, text2);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 1143. 最长公共子序列" << endl;
    cout << "===========================" << endl;
    
    // 测试用例1
    string text1_1 = "abcde", text2_1 = "ace";
    int result1 = sol.longestCommonSubsequence(text1_1, text2_1);
    cout << "测试1: text1=\"abcde\", text2=\"ace\"" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 3" << endl;
    cout << "说明: LCS是\"ace\"" << endl;
    cout << (result1 == 3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    string text1_2 = "abc", text2_2 = "abc";
    int result2 = sol.longestCommonSubsequence(text1_2, text2_2);
    cout << "测试2: text1=\"abc\", text2=\"abc\"" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 3" << endl;
    cout << "说明: 完全相同的字符串" << endl;
    cout << (result2 == 3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    string text1_3 = "abc", text2_3 = "def";
    int result3 = sol.longestCommonSubsequence(text1_3, text2_3);
    cout << "测试3: text1=\"abc\", text2=\"def\"" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 0" << endl;
    cout << "说明: 没有公共字符" << endl;
    cout << (result3 == 0 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 复杂情况
    string text1_4 = "abcdgh", text2_4 = "aedfhr";
    int result4 = sol.longestCommonSubsequence(text1_4, text2_4);
    cout << "测试4: text1=\"abcdgh\", text2=\"aedfhr\"" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 3" << endl;
    cout << "说明: LCS可能是\"adh\"" << endl;
    cout << (result4 == 3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 单字符
    string text1_5 = "a", text2_5 = "a";
    int result5 = sol.longestCommonSubsequence(text1_5, text2_5);
    cout << "测试5: text1=\"a\", text2=\"a\"" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 1" << endl;
    cout << (result5 == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 双序列DP思路演示
void demonstrateDualSequenceDP() {
    cout << "\n📚 双序列DP思路演示" << endl;
    cout << "===================" << endl;
    
    string text1 = "abcde", text2 = "ace";
    cout << "字符串1: \"" << text1 << "\"" << endl;
    cout << "字符串2: \"" << text2 << "\"" << endl;
    cout << "目标: 找到最长公共子序列的长度" << endl << endl;
    
    cout << "💡 双序列DP核心思想：" << endl;
    cout << "用二维DP表表示两个序列的匹配关系" << endl;
    cout << "dp[i][j] = text1前i个字符和text2前j个字符的LCS长度" << endl << endl;
    
    cout << "🎯 状态转移分析：" << endl;
    cout << "对于每个位置(i,j)，有两种情况：" << endl;
    cout << "1. text1[i-1] == text2[j-1]: 字符匹配" << endl;
    cout << "   dp[i][j] = dp[i-1][j-1] + 1" << endl;
    cout << "2. text1[i-1] != text2[j-1]: 字符不匹配" << endl;
    cout << "   dp[i][j] = max(dp[i-1][j], dp[i][j-1])" << endl << endl;
    
    cout << "🔍 手工计算DP表：" << endl;
    
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    cout << "初始化：第0行和第0列都为0（空字符串的LCS为0）" << endl;
    
    // 打印表头
    cout << "\n     ε  ";
    for (char c : text2) {
        cout << c << "  ";
    }
    cout << endl;
    
    for (int i = 0; i <= m; i++) {
        // 打印行标签
        cout << (i == 0 ? "ε" : string(1, text1[i-1])) << "    ";
        
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                cout << dp[i][j] << "  ";
                continue;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
            cout << dp[i][j] << "  ";
        }
        cout << endl;
        
        // 解释计算过程
        if (i > 0) {
            cout << "     计算第" << i << "行: text1[" << (i-1) << "]='" << text1[i-1] << "'";
            for (int j = 1; j <= n; j++) {
                cout << endl << "       dp[" << i << "][" << j << "]: ";
                if (text1[i-1] == text2[j-1]) {
                    cout << "'" << text1[i-1] << "'=='" << text2[j-1] << "' → dp[" << (i-1) << "][" << (j-1) << "]+1 = " << dp[i][j];
                } else {
                    cout << "'" << text1[i-1] << "'!='" << text2[j-1] << "' → max(dp[" << (i-1) << "][" << j << "], dp[" << i << "][" << (j-1) << "]) = max(" << dp[i-1][j] << "," << dp[i][j-1] << ") = " << dp[i][j];
                }
            }
            cout << endl << endl;
        }
    }
    
    cout << "🎯 最终结果：LCS长度 = " << dp[m][n] << endl;
}

// LCS与LIS对比分析
void compareLCSAndLIS() {
    cout << "\n🔄 LCS vs LIS 对比分析" << endl;
    cout << "=====================" << endl;
    
    cout << "📊 问题对比：" << endl;
    cout << "- LIS (300题): 单序列，找最长递增子序列" << endl;
    cout << "- LCS (1143题): 双序列，找最长公共子序列" << endl << endl;
    
    cout << "🎯 状态定义对比：" << endl;
    cout << "- LIS: dp[i] = 以第i个元素结尾的最长递增子序列长度" << endl;
    cout << "- LCS: dp[i][j] = 两个序列前i和前j个元素的最长公共子序列长度" << endl << endl;
    
    cout << "⚡ 状态转移对比：" << endl;
    cout << "- LIS: dp[i] = max(dp[j] + 1) for all j<i and nums[j]<nums[i]" << endl;
    cout << "- LCS: " << endl;
    cout << "  if (s1[i]==s2[j]): dp[i][j] = dp[i-1][j-1] + 1" << endl;
    cout << "  else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])" << endl << endl;
    
    cout << "🧠 思维模式对比：" << endl;
    cout << "- LIS: 检查前面所有可能的转移，选择最优" << endl;
    cout << "- LCS: 考虑匹配/不匹配两种情况，选择最优" << endl << endl;
    
    cout << "📈 复杂度对比：" << endl;
    cout << "- LIS: 时间O(n²) → O(n log n)(贪心+二分)" << endl;
    cout << "- LCS: 时间O(mn)，空间O(mn) → O(min(m,n))(滚动数组)" << endl;
}

// 双序列DP应用扩展
void dualSequenceDPApplications() {
    cout << "\n🌟 双序列DP应用扩展" << endl;
    cout << "==================" << endl;
    
    cout << "📋 经典双序列DP题目：" << endl;
    cout << "1. 1143. 最长公共子序列 (LCS基础)" << endl;
    cout << "2. 72. 编辑距离 (插入、删除、替换操作)" << endl;
    cout << "3. 97. 交错字符串 (路径匹配)" << endl;
    cout << "4. 115. 不同的子序列 (计数问题)" << endl;
    cout << "5. 516. 最长回文子序列 (LCS变种)" << endl << endl;
    
    cout << "🎨 双序列DP特征：" << endl;
    cout << "- 二维状态空间：dp[i][j]" << endl;
    cout << "- 考虑两个序列的匹配关系" << endl;
    cout << "- 通常有字符匹配/不匹配两种转移" << endl;
    cout << "- 可以通过滚动数组优化空间" << endl << endl;
    
    cout << "💡 解题模式：" << endl;
    cout << "1. 确定状态定义：dp[i][j]的含义" << endl;
    cout << "2. 分析转移条件：匹配时和不匹配时的处理" << endl;
    cout << "3. 确定边界条件：空序列的处理" << endl;
    cout << "4. 考虑空间优化：是否可以用滚动数组" << endl;
}

// 复杂度分析
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 二维动态规划:" << endl;
    cout << "   时间复杂度: O(m × n) - 填充整个DP表" << endl;
    cout << "   空间复杂度: O(m × n) - 二维DP表" << endl;
    cout << "   优势: 思路直观，容易理解和实现" << endl;
    cout << "   劣势: 空间消耗较大" << endl << endl;
    
    cout << "2. 记忆化搜索:" << endl;
    cout << "   时间复杂度: O(m × n) - 每个子问题计算一次" << endl;
    cout << "   空间复杂度: O(m × n) - 缓存 + 递归栈" << endl;
    cout << "   优势: 自顶向下思维自然" << endl;
    cout << "   劣势: 递归开销，栈溢出风险" << endl << endl;
    
    cout << "3. 空间优化: ⭐ 推荐" << endl;
    cout << "   时间复杂度: O(m × n)" << endl;
    cout << "   空间复杂度: O(min(m, n)) - 滚动数组" << endl;
    cout << "   优势: 空间效率高" << endl;
    cout << "   劣势: 实现稍复杂，不能直接构造LCS字符串" << endl << endl;
    
    cout << "💡 双序列DP的特点：" << endl;
    cout << "- 时间复杂度通常是O(mn)，难以进一步优化" << endl;
    cout << "- 空间复杂度可以通过滚动数组优化" << endl;
    cout << "- 状态转移相对简单，主要考虑匹配/不匹配情况" << endl;
}

int main() {
    cout << "🚀 LeetCode 1143. 最长公共子序列" << endl;
    cout << "===============================" << endl;
    cout << "🔥 这是双序列DP的经典题目！" << endl;
    cout << "💡 重点掌握二维DP状态定义和转移" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    demonstrateDualSequenceDP();
    compareLCSAndLIS();
    runTests();
    complexityAnalysis();
    dualSequenceDPApplications();
    
    return 0;
}