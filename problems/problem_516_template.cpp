#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 516. 最长回文子序列
难度: Medium
标签: [动态规划, 区间DP, 字符串]
LeetCode链接: https://leetcode.cn/problems/longest-palindromic-subsequence/

题目描述:
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

示例 1:
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。

示例 2:
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。

约束条件:
- 1 <= s.length <= 1000
- s 只包含小写英文字母

思考要点:
1. 这是什么类型的DP？与之前学过的双序列DP有什么联系？
2. 状态定义：dp[i][j] 表示什么含义？
3. 状态转移：当 s[i] == s[j] 时怎么处理？不等时怎么处理？
4. 边界条件：单个字符的回文长度是多少？
5. 区间DP的特点是什么？如何处理区间长度？

核心难点:
- 理解回文子序列的概念：不要求连续，但要求对称
- 正确处理区间DP的状态转移：从小区间到大区间
- 掌握区间DP的经典思维：子问题的分解方式
- 理解与LCS问题的联系：s与reverse(s)的LCS
*/

class Solution {
public:
    // 方法1: 区间动态规划 - 经典解法 ⭐
    // 核心方法：不同窗口大小的滑动窗口方法，大窗口依赖小窗口
    int longestPalindromeSubseqDP(string s) {  
        // TODO: 实现区间DP解法
        // 1. 状态定义：dp[i][j] = s[i..j]范围内的最长回文子序列长度
        // 2. 状态转移：
        //    if (s[i] == s[j]): dp[i][j] = dp[i+1][j-1] + 2
        //    else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        // 3. 边界条件：dp[i][i] = 1 (单个字符)
        // 4. 遍历顺序：按区间长度从小到大
        
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // TODO: 填充DP表
        for(int i = 0; i<n; i++) {
            dp[i][i] = 1;
        }
        for(int len=2; len<=n; len++) {
            for(int i=0; i<=n-len; i++) {
                int j = i+ len -1;
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2; // 边界可能会有问题
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        return dp[0][n-1]; // 最大的窗口
    }
    
    // 方法2: 转化为LCS问题 - 巧妙思路 ⭐⭐
    int longestPalindromeSubseqLCS(string s) {
        // TODO: 实现LCS转化思路
        // 核心思想：s的最长回文子序列 = s与reverse(s)的最长公共子序列
        // 为什么？回文序列在原串和反转串中都存在！
        
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        
        // 调用LCS算法
        return longestCommonSubsequence(s, rev_s);
    }
    
private:
    // 辅助函数：计算两个字符串的LCS（复用1143题的代码）
    int longestCommonSubsequence(string text1, string text2) {
        // TODO: 实现LCS算法（可以直接复用1143题的实现）
        
        return 0;
    }
    
public:
    // 方法3: 记忆化搜索 - 自顶向下 ⭐
    int longestPalindromeSubseqMemo(string s) {
        // TODO: 实现记忆化搜索
        // 递归思路：
        // lps(i, j) = 考虑s[i..j]范围的最长回文子序列
        // if (s[i] == s[j]): lps(i, j) = lps(i+1, j-1) + 2
        // else: lps(i, j) = max(lps(i+1, j), lps(i, j-1))
        
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        
        return helper(s, 0, n-1, memo);
    }
    
private:
    int helper(string& s, int i, int j, vector<vector<int>>& memo) {
        // TODO: 实现递归helper
        // 边界条件：i > j 时返回 0，i == j 时返回 1
        if(i >j) return 0;
        if(i == j) return 1;

        // 检查缓存
        if(memo[i][j] != -1) return memo[i][j];
        // 递归计算并缓存结果
        if(s[i] == s[j]) {
            memo[i][j] = helper(s, i+1, j-1, memo) + 2;
        } else {
            memo[i][j] = max(helper(s, i+1, j, memo), helper(s, i, j-1, memo));
        }
        return memo[i][j];
    }
    
public:
    // 方法4: 空间优化 - 一维DP (选做，难度较高)
    int longestPalindromeSubseqOptimized(string s) {
        // TODO: 实现空间优化版本
        // 观察：dp[i][j] 只依赖于 dp[i+1][j-1], dp[i+1][j], dp[i][j-1]
        // 可以用滚动数组优化空间复杂度
        
        return 0;
    }
    
    // 主函数 - 选择你想实现的方法
    int longestPalindromeSubseq(string s) {
        // 推荐先实现区间DP，理解区间DP的思维
        return longestPalindromeSubseqDP(s);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 516. 最长回文子序列" << endl;
    cout << "==========================" << endl;
    
    // 测试用例1
    string s1 = "bbbab";
    int result1 = sol.longestPalindromeSubseq(s1);
    cout << "测试1: s=\"bbbab\"" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 4" << endl;
    cout << "说明: \"bbbb\"" << endl;
    cout << (result1 == 4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    string s2 = "cbbd";
    int result2 = sol.longestPalindromeSubseq(s2);
    cout << "测试2: s=\"cbbd\"" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 2" << endl;
    cout << "说明: \"bb\"" << endl;
    cout << (result2 == 2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    string s3 = "a";
    int result3 = sol.longestPalindromeSubseq(s3);
    cout << "测试3: s=\"a\"" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 1" << endl;
    cout << "说明: 单个字符" << endl;
    cout << (result3 == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 完全回文
    string s4 = "abcba";
    int result4 = sol.longestPalindromeSubseq(s4);
    cout << "测试4: s=\"abcba\"" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 5" << endl;
    cout << "说明: 整个字符串就是回文" << endl;
    cout << (result4 == 5 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 复杂情况
    string s5 = "aabaa";
    int result5 = sol.longestPalindromeSubseq(s5);
    cout << "测试5: s=\"aabaa\"" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 5" << endl;
    cout << "说明: \"aabaa\"本身就是回文" << endl;
    cout << (result5 == 5 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 区间DP思路演示
void demonstrateIntervalDP() {
    cout << "\n📚 区间DP思路演示" << endl;
    cout << "=================" << endl;
    
    string s = "bbbab";
    cout << "字符串: \"" << s << "\"" << endl;
    cout << "目标: 找最长回文子序列的长度" << endl << endl;
    
    cout << "💡 区间DP核心思想：" << endl;
    cout << "用区间[i,j]表示子问题，从小区间逐步扩展到大区间" << endl;
    cout << "dp[i][j] = s[i..j]范围内的最长回文子序列长度" << endl << endl;
    
    cout << "🎯 状态转移分析：" << endl;
    cout << "对于区间[i,j]，考虑两端字符s[i]和s[j]：" << endl;
    cout << "1. s[i] == s[j]: 两端匹配，可以组成更长回文" << endl;
    cout << "   dp[i][j] = dp[i+1][j-1] + 2" << endl;
    cout << "2. s[i] != s[j]: 两端不匹配，选择更优的子区间" << endl;
    cout << "   dp[i][j] = max(dp[i+1][j], dp[i][j-1])" << endl << endl;
    
    cout << "🔍 手工计算DP表：" << endl;
    
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    cout << "步骤1: 初始化对角线（单个字符的回文长度为1）" << endl;
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // 打印初始状态
    cout << "初始DP表：" << endl;
    cout << "     ";
    for (int j = 0; j < n; j++) {
        cout << s[j] << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << s[i] << "    ";
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                cout << dp[i][j] << "  ";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "步骤2: 按区间长度填充DP表" << endl;
    
    // 按区间长度从2开始填充
    for (int len = 2; len <= n; len++) {
        cout << "\n处理长度为 " << len << " 的区间：" << endl;
        
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            cout << "  区间[" << i << "," << j << "] (\"" << s.substr(i, len) << "\")：";
            
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
                cout << " s[" << i << "]='\" << s[i] << \"' == s[" << j << "]='\" << s[j] << \"'";
                cout << " → dp[" << (i+1) << "][" << (j-1) << "] + 2 = " << dp[i+1][j-1] << " + 2 = " << dp[i][j] << endl;
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                cout << " s[" << i << "]='\" << s[i] << \"' != s[" << j << "]='\" << s[j] << \"'";
                cout << " → max(dp[" << (i+1) << "][" << j << "], dp[" << i << "][" << (j-1) << "]) = max(" << dp[i+1][j] << "," << dp[i][j-1] << ") = " << dp[i][j] << endl;
            }
        }
    }
    
    cout << "\n最终DP表：" << endl;
    cout << "     ";
    for (int j = 0; j < n; j++) {
        cout << s[j] << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << s[i] << "    ";
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                cout << dp[i][j] << "  ";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
    
    cout << "\n🎯 最终结果：dp[0][" << (n-1) << "] = " << dp[0][n-1] << endl;
}

// LCS转化思路讲解
void demonstrateLCSTransformation() {
    cout << "\n🚀 LCS转化思路讲解" << endl;
    cout << "=================" << endl;
    
    cout << "💡 核心思想：" << endl;
    cout << "最长回文子序列 = 原字符串与其反转串的最长公共子序列！" << endl << endl;
    
    cout << "🔧 为什么这样转化是正确的？" << endl;
    cout << "1. 回文序列的特点：正读反读都相同" << endl;
    cout << "2. 如果一个子序列在原串中存在，且在反转串中也存在" << endl;
    cout << "3. 那么这个子序列必然是回文的！" << endl << endl;
    
    string s = "bbbab";
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    
    cout << "🔍 演示例子 (s=\"bbbab\")：" << endl;
    cout << "原字符串:   \"" << s << "\"" << endl;
    cout << "反转字符串: \"" << rev_s << "\"" << endl << endl;
    
    cout << "寻找它们的最长公共子序列：" << endl;
    cout << "原串:  b b b a b" << endl;
    cout << "反串:  b a b b b" << endl;
    cout << "LCS:   b   b   b  (长度3) 或者 b b b b (长度4)" << endl << endl;
    
    cout << "验证：\"bbbb\"确实是\"bbbab\"的回文子序列！" << endl;
    
    cout << "\n⭐ 这种转化的优势：" << endl;
    cout << "- 可以直接复用LCS的代码" << endl;
    cout << "- 算法复杂度相同：O(n²)" << endl;
    cout << "- 提供了不同的思考角度" << endl;
}

// 区间DP vs 双序列DP对比
void compareIntervalAndSequenceDP() {
    cout << "\n🔄 区间DP vs 双序列DP 对比" << endl;
    cout << "===========================" << endl;
    
    cout << "📊 问题类型对比：" << endl;
    cout << "- 双序列DP (1143题): 考虑两个不同序列的匹配关系" << endl;
    cout << "- 区间DP (516题): 考虑单个序列内部的最优划分" << endl << endl;
    
    cout << "🎯 状态定义对比：" << endl;
    cout << "- 双序列DP: dp[i][j] = 两个序列前i和前j个元素的最优解" << endl;
    cout << "- 区间DP: dp[i][j] = 区间[i,j]内的最优解" << endl << endl;
    
    cout << "⚡ 状态转移对比：" << endl;
    cout << "- 双序列DP: 考虑元素匹配/不匹配" << endl;
    cout << "  if (s1[i]==s2[j]): dp[i][j] = dp[i-1][j-1] + 1" << endl;
    cout << "  else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])" << endl;
    cout << "- 区间DP: 考虑区间端点的处理" << endl;
    cout << "  if (s[i]==s[j]): dp[i][j] = dp[i+1][j-1] + 2" << endl;
    cout << "  else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])" << endl << endl;
    
    cout << "🔄 遍历顺序对比：" << endl;
    cout << "- 双序列DP: 从前往后，i和j都递增" << endl;
    cout << "- 区间DP: 按区间长度递增，先小区间后大区间" << endl << endl;
    
    cout << "🧠 思维模式对比：" << endl;
    cout << "- 双序列DP: 序列对齐思维，考虑位置对应关系" << endl;
    cout << "- 区间DP: 分治思维，将大问题分解为小区间问题" << endl;
}

// 区间DP应用扩展
void intervalDPApplications() {
    cout << "\n🌟 区间DP应用扩展" << endl;
    cout << "================" << endl;
    
    cout << "📋 经典区间DP题目：" << endl;
    cout << "1. 516. 最长回文子序列 (基础入门)" << endl;
    cout << "2. 5. 最长回文子串 (连续性约束)" << endl;
    cout << "3. 312. 戳气球 (乘积最大化)" << endl;
    cout << "4. 1039. 多边形三角剖分的最低得分 (几何DP)" << endl;
    cout << "5. 87. 扰乱字符串 (字符串分割)" << endl << endl;
    
    cout << "🎨 区间DP特征：" << endl;
    cout << "- 状态表示：dp[i][j]表示区间[i,j]的最优解" << endl;
    cout << "- 状态转移：考虑区间端点或分割点" << endl;
    cout << "- 遍历顺序：按区间长度从小到大" << endl;
    cout << "- 边界条件：单点区间或空区间" << endl << endl;
    
    cout << "💡 解题模式：" << endl;
    cout << "1. 确定状态定义：dp[i][j]的含义" << endl;
    cout << "2. 分析转移方式：端点处理 vs 区间分割" << endl;
    cout << "3. 确定遍历顺序：通常按区间长度递增" << endl;
    cout << "4. 处理边界条件：单点和空区间的初始化" << endl;
}

// 复杂度分析
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 区间动态规划:" << endl;
    cout << "   时间复杂度: O(n²) - 双重循环填充DP表" << endl;
    cout << "   空间复杂度: O(n²) - 二维DP表" << endl;
    cout << "   优势: 直观理解区间DP思维" << endl;
    cout << "   劣势: 空间消耗较大" << endl << endl;
    
    cout << "2. LCS转化方法:" << endl;
    cout << "   时间复杂度: O(n²) - LCS算法复杂度" << endl;
    cout << "   空间复杂度: O(n²) - 或O(n)用滚动数组" << endl;
    cout << "   优势: 复用已有代码，思路巧妙" << endl;
    cout << "   劣势: 需要额外空间存储反转串" << endl << endl;
    
    cout << "3. 记忆化搜索:" << endl;
    cout << "   时间复杂度: O(n²) - 每个子问题计算一次" << endl;
    cout << "   空间复杂度: O(n²) - 缓存 + 递归栈" << endl;
    cout << "   优势: 自顶向下思维自然" << endl;
    cout << "   劣势: 递归开销，可能栈溢出" << endl << endl;
    
    cout << "💡 区间DP的特点：" << endl;
    cout << "- 时间复杂度通常是O(n²)或O(n³)" << endl;
    cout << "- 空间复杂度可以优化，但比较复杂" << endl;
    cout << "- 适合处理区间相关的最优化问题" << endl;
}

int main() {
    cout << "🚀 LeetCode 516. 最长回文子序列" << endl;
    cout << "==============================" << endl;
    cout << "🔥 这是区间DP的经典入门题目！" << endl;
    cout << "💡 重点掌握区间DP思维和LCS转化技巧" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    demonstrateIntervalDP();
    demonstrateLCSTransformation();
    runTests();
    compareIntervalAndSequenceDP();
    complexityAnalysis();
    intervalDPApplications();
    
    return 0;
}