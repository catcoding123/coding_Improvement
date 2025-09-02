/*
LeetCode 76. 最小覆盖子串
Difficulty: Hard
Link: https://leetcode.cn/problems/minimum-window-substring/

题目描述：
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：
- 对于 t 中重复字符，我们寻找的子串中该字符数量必须不少于 t 中该字符数量。
- 如果 s 中存在这样的子串，我们保证它是唯一的答案。

示例 1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。

示例 2：
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。

示例 3：
输入：s = "a", t = "aa"
输出：""
解释：t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子串，返回空字符串。

约束条件：
- m == s.length
- n == t.length
- 1 <= m, n <= 10^5
- s 和 t 由英文字母组成

算法分析：
时间复杂度：O(m + n) - 滑动窗口
空间复杂度：O(m + n) - 哈希表存储字符频次

核心思想：
1. 滑动窗口的高级应用
2. 维护窗口内字符频次，确保覆盖目标字符串
3. 窗口扩展：right指针移动，收集字符
4. 窗口收缩：left指针移动，寻找最小窗口

基于你的技能基础：
- 基于题目3(无重复字符最长子串)的滑动窗口经验
- 这题是滑动窗口的巅峰应用，复杂约束条件

思考要点：
1. 如何判断当前窗口是否覆盖了目标字符串？
2. 窗口什么时候扩展？什么时候收缩？
3. 如何维护字符频次的匹配状态？
4. 与题目3的滑动窗口有什么区别？

易错点：
1. 字符频次的正确维护（重复字符处理）
2. 窗口收缩的时机判断
3. valid计数器的更新时机
4. 最小窗口的记录和更新

相关题目：
- 3. 无重复字符的最长子串 (你已掌握)
- 438. 找到字符串中所有字母异位词
- 567. 字符串的排列
- 209. 长度最小的子数组
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        // TODO: 实现滑动窗口算法
        // 提示1: 使用两个哈希表 - need存储t的字符频次，window存储窗口字符频次
        // 提示2: 使用valid计数器记录窗口中已满足频次要求的字符种类数
        // 提示3: right扩展窗口收集字符，left收缩窗口寻找最小
        // 提示4: 当valid == need.size()时，当前窗口覆盖了t
        int count = t.size(); // 一个字符可能出现多次
        unordered_map<char, int> char_map;
        for(auto& c:t) {
            char_map[c] += 1;
        }
        int left = 0;
        int right = 0;
        int min_len = INT_MAX;
        int start = 0;
        while(right < s.size()) {
            if(char_map[s[right]] >0) {
                  count--; // 因为一个字符串可能出现多次
            }
            char_map[s[right]]--;
            right++;

            while(count == 0) {
                if((right-left) < min_len) {
                    min_len = right-left;
                    start = left;
                }
                char_map[s[left]]++;
                if(char_map[s[left]] >0) {
                    count++;
                }
                left++;
            }
        }
        return min_len==INT_MAX?"":s.substr(start,min_len);
    }
    

};

// 测试用例
void testSolution() {
    Solution sol;
    
    cout << "🧪 测试 76. 最小覆盖子串" << endl;
    cout << "======================" << endl;
    
    // 测试用例1: 基本情况
    string s1 = "ADOBECODEBANC", t1 = "ABC";
    cout << "Test 1: s=\"" << s1 << "\", t=\"" << t1 << "\"" << endl;
    cout << "Result: \"" << sol.minWindow(s1, t1) << "\" (Expected: \"BANC\")" << endl << endl;
    
    // 测试用例2: 单字符匹配
    string s2 = "a", t2 = "a";
    cout << "Test 2: s=\"" << s2 << "\", t=\"" << t2 << "\"" << endl;
    cout << "Result: \"" << sol.minWindow(s2, t2) << "\" (Expected: \"a\")" << endl << endl;
    
    // 测试用例3: 无法覆盖
    string s3 = "a", t3 = "aa";
    cout << "Test 3: s=\"" << s3 << "\", t=\"" << t3 << "\"" << endl;
    cout << "Result: \"" << sol.minWindow(s3, t3) << "\" (Expected: \"\")" << endl << endl;
    
    // 测试用例4: 复杂情况
    string s4 = "ADOBECODEBANC", t4 = "AABC";
    cout << "Test 4: s=\"" << s4 << "\", t=\"" << t4 << "\"" << endl;
    cout << "Result: \"" << sol.minWindow(s4, t4) << "\" (Expected: 包含2个A,1个B,1个C的最小子串)" << endl << endl;
}

// 算法思路提示
void showHints() {
    cout << "\n💡 算法思路提示" << endl;
    cout << "===============" << endl;
    cout << R"(
滑动窗口核心思路：
1. 扩展阶段：right指针移动，收集字符到窗口
2. 收缩阶段：当窗口满足条件时，left指针移动寻找最小窗口
3. 更新答案：在有效窗口中记录最小长度

关键数据结构：
- need: 存储t中每个字符的需要数量
- window: 存储当前窗口中每个字符的数量  
- valid: 记录窗口中满足频次要求的字符种类数

算法流程：
```
1. 初始化need哈希表，统计t中字符频次
2. 使用left,right双指针维护窗口[left,right)
3. 当valid == need.size()时，当前窗口覆盖了t
4. 在满足条件的窗口中收缩left寻找最小窗口
```

与题目3的区别：
- 题目3: 窗口内无重复字符 (限制条件)
- 题目76: 窗口内覆盖目标字符串 (满足条件)
- 题目3: 求最大窗口
- 题目76: 求最小窗口

实现要点：
1. valid的更新时机：当window[c] == need[c]时valid++
2. 窗口收缩条件：valid == need.size()
3. 最小窗口更新：在满足条件时更新答案
4. 字符频次的正确维护

这是滑动窗口的最高难度应用，掌握后其他滑动窗口题目都不是问题！
)" << endl;
}

// 滑动窗口算法框架展示
void showSlidingWindowFramework() {
    cout << "\n📖 滑动窗口算法框架" << endl;
    cout << "===================" << endl;
    cout << R"(
// 基于你题目3经验的进阶框架：
string slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    
    int left = 0, right = 0;
    int valid = 0;  // 窗口中满足need条件的字符个数
    
    // 记录最小覆盖子串的起始索引及长度
    int start = 0, len = INT_MAX;
    
    while (right < s.size()) {
        char c = s[right];
        right++;
        
        // 进行窗口内数据的一系列更新
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c])
                valid++;
        }
        
        // 判断左侧窗口是否要收缩
        while (valid == need.size()) {
            // 在这里更新最小覆盖子串
            if (right - left < len) {
                start = left;
                len = right - left;
            }
            
            char d = s[left];
            left++;
            
            // 进行窗口内数据的一系列更新
            if (need.count(d)) {
                if (window[d] == need[d])
                    valid--;
                window[d]--;
            }
        }
    }
    
    return len == INT_MAX ? "" : s.substr(start, len);
}
)" << endl;
}

int main() {
    cout << "🚀 LeetCode 76. 最小覆盖子串" << endl;
    cout << "============================" << endl;
    cout << "🎯 基于你题目3的滑动窗口基础，这是滑动窗口的巅峰挑战！" << endl;
    cout << "💡 重点理解复杂约束条件下的窗口控制机制" << endl << endl;
    
    testSolution();
    showHints();
    showSlidingWindowFramework();
    
    return 0;
}

/*
专题归属：字符串 + 滑动窗口
难度评估：⭐⭐⭐⭐⭐ (Hard难度，滑动窗口的最高难度应用)
技能基础：基于你题目3的滑动窗口经验，这是复杂约束条件的高级应用
核心突破：掌握valid计数器技巧，理解窗口收缩的时机控制
*/