/*
LeetCode 5. 最长回文子串
Difficulty: Medium
Link: https://leetcode.cn/problems/longest-palindromic-substring/

题目描述：
给你一个字符串 s，找到 s 中最长的回文子串。

示例 1：
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。

示例 2：
输入：s = "cbbd"
输出："bb"

约束条件：
- 1 <= s.length <= 1000
- s 仅由数字和英文字母组成

算法分析：
时间复杂度：O(n²) - 中心扩展法 / O(n²) - 动态规划
空间复杂度：O(1) - 中心扩展法 / O(n²) - 动态规划

核心思想：
1. 方法1：中心扩展法 - 以每个字符为中心向两边扩展
2. 方法2：动态规划 - dp[i][j]表示s[i..j]是否为回文
3. 注意处理奇偶长度回文串的不同中心位置

思考要点：
1. 回文串的特点是什么？
2. 如何处理奇数长度和偶数长度的回文串？
3. 中心扩展时的边界条件是什么？
4. 基于你516题(最长回文子序列)的经验，这题有什么区别？

易错点：
1. 忘记处理偶数长度回文串的情况 (需要处理两种中心：单点和双点)
2. 边界检查：确保不越界 (left >= 0 && right < s.length())
3. 最长回文串的起始位置和长度记录 (更新maxLen时同步更新start)
4. 子串vs子序列的区别理解 (子串必须连续，子序列可以不连续)
5. expandAroundCenter函数的返回值理解 (返回长度，不是结束位置)
6. 中心扩展时的停止条件 (s[left] != s[right] 或 越界时停止)

相关题目：
- 516. 最长回文子序列 (你已掌握)
- 647. 回文子串
- 125. 验证回文串
- 234. 回文链表
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // 方法1：中心扩展法 (推荐实现)
    string longestPalindromeExpand(string s) {
        // TODO: 实现中心扩展算法
        // 提示1: 对每个可能的中心进行扩展
        // 提示2: 奇数长度中心是单个字符，偶数长度中心是两个字符之间
        // 提示3: 实现辅助函数expandAroundCenter(s, left, right)
        
        // 实现框架:
        // if (s.empty()) return "";
        // int start = 0, maxLen = 1;
        // for (int i = 0; i < s.length(); i++) {
        //     // 奇数长度回文: 以i为中心
        //     int len1 = expandAroundCenter(s, i, i);
        //     // 偶数长度回文: 以i和i+1之间为中心  
        //     int len2 = expandAroundCenter(s, i, i + 1);
        //     int len = max(len1, len2);
        //     if (len > maxLen) {
        //         maxLen = len;
        //         start = i - (len - 1) / 2;  // 计算起始位置
        //     }
        // }
        // return s.substr(start, maxLen);
        
        return "";
    }
    
    // 方法2：动态规划法 (基于你516题的DP经验)
    string longestPalindromeDP(string s) {
        // TODO: 实现动态规划算法
        // 提示1: dp[i][j] = s[i..j]是否为回文串
        // 提示2: 状态转移：dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]
        // 提示3: 参考你516题的区间DP思路，但这题要求连续子串
        
        return "";
    }
    
    // 辅助函数：中心扩展
    int expandAroundCenter(string s, int left, int right) {
        // TODO: 实现中心扩展辅助函数
        // 返回以(left,right)为中心的最长回文串长度
        
        // 实现提示:
        // while (left >= 0 && right < s.length() && s[left] == s[right]) {
        //     left--;
        //     right++;
        // }
        // return right - left - 1;  // 注意：退出循环时已经不满足条件
        
        return 0;
    }
    
    // 主函数
    string longestPalindrome(string s) {
        // 推荐先实现中心扩展法，再挑战DP法
        return longestPalindromeExpand(s);
    }
};

// 辅助函数：验证是否为回文
bool isPalindrome(const string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// 测试用例
void testSolution() {
    Solution sol;
    
    cout << "🧪 测试 5. 最长回文子串" << endl;
    cout << "=====================" << endl;
    
    // 测试用例1: 奇数长度回文
    string s1 = "babad";
    string result1 = sol.longestPalindrome(s1);
    cout << "Test 1: \"" << s1 << "\" -> \"" << result1 << "\"";
    cout << " ✓验证: " << (isPalindrome(result1) ? "是回文" : "❌不是回文") << endl;
    
    // 测试用例2: 偶数长度回文
    string s2 = "cbbd";
    string result2 = sol.longestPalindrome(s2);
    cout << "Test 2: \"" << s2 << "\" -> \"" << result2 << "\"";
    cout << " ✓验证: " << (isPalindrome(result2) ? "是回文" : "❌不是回文") << endl;
    
    // 测试用例3: 单字符
    string s3 = "a";
    string result3 = sol.longestPalindrome(s3);
    cout << "Test 3: \"" << s3 << "\" -> \"" << result3 << "\"";
    cout << " ✓验证: " << (isPalindrome(result3) ? "是回文" : "❌不是回文") << endl;
    
    // 测试用例4: 全相同字符
    string s4 = "aaaa";
    string result4 = sol.longestPalindrome(s4);
    cout << "Test 4: \"" << s4 << "\" -> \"" << result4 << "\"";
    cout << " ✓验证: " << (isPalindrome(result4) ? "是回文" : "❌不是回文") << endl;
    
    // 测试用例5: 无回文(除单字符)
    string s5 = "abcdef";
    string result5 = sol.longestPalindrome(s5);
    cout << "Test 5: \"" << s5 << "\" -> \"" << result5 << "\"";
    cout << " ✓验证: " << (isPalindrome(result5) ? "是回文" : "❌不是回文") << endl;
    
    // 测试用例6: 复杂回文 (新增)
    string s6 = "raceacar";
    string result6 = sol.longestPalindrome(s6);
    cout << "Test 6: \"" << s6 << "\" -> \"" << result6 << "\"";
    cout << " ✓验证: " << (isPalindrome(result6) ? "是回文" : "❌不是回文") << endl;
}

// 算法思路提示
void showHints() {
    cout << "\n💡 算法思路提示" << endl;
    cout << "===============" << endl;
    cout << R"(
方法1：中心扩展法
1. 遍历每个可能的回文中心
2. 对于奇数长度：中心是单个字符 (i, i)
3. 对于偶数长度：中心是两个字符之间 (i, i+1)
4. 从中心向两边扩展，直到不是回文为止
5. 记录最长的回文串

方法2：动态规划法
1. dp[i][j] 表示 s[i..j] 是否为回文串
2. 状态转移：
   - 如果 s[i] == s[j] 且 dp[i+1][j-1] 为true，则dp[i][j] = true
   - 特殊情况：j - i <= 2 时，只需检查 s[i] == s[j]
3. 填表顺序：按字符串长度从短到长

与516题的区别：
- 516题：最长回文子序列（可以删除字符）
- 5题：最长回文子串（必须连续）

实现建议：
- 先实现 expandAroundCenter 辅助函数
- 注意边界检查，避免数组越界
- 记录最长回文的起始位置和长度
)" << endl;
}

int main() {
    cout << "🚀 LeetCode 5. 最长回文子串" << endl;
    cout << "===========================" << endl;
    cout << "🎯 基于你516题的DP经验，这题可以用中心扩展法更优雅解决！" << endl;
    cout << "💡 重点理解奇偶长度回文串的中心扩展策略" << endl << endl;
    
    testSolution();
    showHints();
    
    return 0;
}

/*
专题归属：字符串 + 动态规划/中心扩展
难度评估：⭐⭐⭐ (Medium难度，回文问题经典题)
技能基础：基于你516题的区间DP经验，这题可以用更简洁的中心扩展法
*/