/*
72. 编辑距离 (Hard)
https://leetcode.cn/problems/edit-distance/

题目描述：
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数。

你可以对一个单词进行如下三种操作：
- 插入一个字符
- 删除一个字符
- 替换一个字符

示例 1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

约束条件：
- 0 <= word1.length, word2.length <= 500
- word1 和 word2 由小写英文字母组成

专题归属：动态规划 - 双序列DP
相关题目：1143.最长公共子序列、583.两个字符串的删除操作、712.两个字符串的最小ASCII删除和

算法分析：
思路提示：
1. 状态定义：dp[i][j] 表示将word1的前i个字符转换为word2的前j个字符的最少操作数
2. 状态转移：
   - 如果word1[i-1] == word2[j-1]：dp[i][j] = dp[i-1][j-1]
   - 否则：dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
     - dp[i-1][j] + 1：删除word1[i-1]
     - dp[i][j-1] + 1：插入word2[j-1]到word1
     - dp[i-1][j-1] + 1：替换word1[i-1]为word2[j-1]
3. 初始化：dp[i][0] = i, dp[0][j] = j

时间复杂度：O(m*n) - m和n分别是两个字符串的长度
空间复杂度：O(m*n) - DP数组，可优化到O(min(m,n))

易错点：
1. 字符串索引：dp[i][j]对应word1[i-1]和word2[j-1]
2. 初始化边界：空字符串到非空字符串的转换次数
3. 操作理解：插入、删除、替换的具体含义
4. 状态转移方程：三种操作对应的前状态选择
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：二维DP（经典解法）
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for(int i=0; i<m+1; i++) {
            dp[i][0] = i;
        }
        for(int j=0; j<n+1; j++) {
            dp[0][j] = j;
        }
        
        for(int i=1; i<m+1; i++) {
            for(int j=1; j<n+1; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }else {
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }
            }
        }
        return dp[m][n];
    }
    
    // 方法二：递归 + 记忆化搜索
    int minDistanceMemo(string word1, string word2) {
        // TODO: 实现记忆化搜索解法
        // 提示：
        // 1. 定义递归函数helper(i, j)：从位置i,j开始的最小编辑距离
        // 2. 使用memo数组缓存计算结果
        // 3. 递归终止条件：其中一个字符串到达末尾
        
        return 0;
    }
    
    // 方法三：空间优化的DP
    int minDistanceOptimized(string word1, string word2) {
        // TODO: 实现空间优化版本
        // 提示：观察状态转移只依赖于前一行，可以用滚动数组优化
        
        return 0;
    }

private:
    // 辅助函数：记忆化搜索的递归函数
    int helper(string& word1, string& word2, int i, int j, vector<vector<int>>& memo) {
        // TODO: 实现递归逻辑
        
        return 0;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 基本情况
    string word1_1 = "horse", word2_1 = "ros";
    cout << "测试1 - word1=\"horse\", word2=\"ros\"" << endl;
    cout << "预期结果: 3, 实际结果: " << solution.minDistance(word1_1, word2_1) << endl << endl;
    
    // 测试用例2: 复杂情况
    string word1_2 = "intention", word2_2 = "execution";
    cout << "测试2 - word1=\"intention\", word2=\"execution\"" << endl;
    cout << "预期结果: 5, 实际结果: " << solution.minDistance(word1_2, word2_2) << endl << endl;
    
    // 测试用例3: 空字符串
    string word1_3 = "", word2_3 = "abc";
    cout << "测试3 - word1=\"\", word2=\"abc\"" << endl;
    cout << "预期结果: 3, 实际结果: " << solution.minDistance(word1_3, word2_3) << endl << endl;
    
    // 测试用例4: 相同字符串
    string word1_4 = "abc", word2_4 = "abc";
    cout << "测试4 - word1=\"abc\", word2=\"abc\"" << endl;
    cout << "预期结果: 0, 实际结果: " << solution.minDistance(word1_4, word2_4) << endl << endl;
    
    // 测试用例5: 完全不同
    string word1_5 = "abc", word2_5 = "def";
    cout << "测试5 - word1=\"abc\", word2=\"def\"" << endl;
    cout << "预期结果: 3, 实际结果: " << solution.minDistance(word1_5, word2_5) << endl << endl;
    
    // 测试用例6: 单字符
    string word1_6 = "a", word2_6 = "b";
    cout << "测试6 - word1=\"a\", word2=\"b\"" << endl;
    cout << "预期结果: 1, 实际结果: " << solution.minDistance(word1_6, word2_6) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解编辑距离问题的本质和应用
2. 掌握双序列DP的状态设计和转移
3. 学会分析字符串的三种基本操作
4. 理解记忆化搜索与DP的关系

算法精髓：
1. 状态设计：用二维数组表示两个字符串的转换关系
2. 操作分析：插入、删除、替换的数学抽象
3. 最优子结构：大问题的最优解包含子问题的最优解
4. 边界处理：空字符串的特殊情况

数学原理：
- 字符相同时：无需操作，继承之前的结果
- 字符不同时：三种操作取最小值
  - 删除：dp[i-1][j] + 1
  - 插入：dp[i][j-1] + 1  
  - 替换：dp[i-1][j-1] + 1

面试要点：
1. 清楚解释三种操作的含义
2. 正确画出DP状态转移图
3. 分析时间和空间复杂度
4. 讨论空间优化的可能性

实际应用：
- 拼写检查和纠错
- DNA序列比对
- 版本控制中的差异比较
- 自然语言处理中的相似度计算

扩展思考：
- 如何记录具体的编辑操作序列？
- 如何处理不同操作有不同代价的情况？
- 如何扩展到多个字符串的编辑距离？
- 如何优化大字符串的计算效率？

相关题目：
- 583题：只允许删除操作
- 712题：考虑字符的ASCII值
- 1143题：最长公共子序列（相关但不同的问题）
*/