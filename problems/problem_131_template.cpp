/*
LeetCode 131. 分割回文串 (Medium)
https://leetcode.cn/problems/palindrome-partitioning/

题目描述：
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
返回 s 所有可能的分割方案。

回文串是正着读和反着读都一样的字符串。

示例 1：
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

示例 2：
输入：s = "raceacar"
输出：[["r","a","c","e","a","c","a","r"],["r","a","ce","ca","r"],["r","ace","ca","r"],["raceacar"]]

示例 3：
输入：s = "a"
输出：[["a"]]

约束条件：
- 1 <= s.length <= 16
- s 仅由小写英文字母组成

算法分析：
时间复杂度：O(N * 2^N) - N是字符串长度，2^N种分割方案，每种方案需要O(N)时间验证
空间复杂度：O(N) - 递归栈深度最大为N
核心难点：回溯算法 + 字符串分割 + 回文判断的三重结合

关键洞察：
1. 回溯决策：每个位置选择"在此处分割"或"继续延伸"
2. 约束条件：分割出的每个子串必须是回文串
3. 优化策略：预处理回文判断 或 中心扩展法实时判断
4. 分割边界：start参数控制分割起始位置

算法模式对比：
- 39/40题：数字组合，target递减控制
- 46/47题：元素排列，used数组状态管理  
- 78/90题：元素子集，选择/不选择决策
- 131题：字符串分割，位置分割 + 回文约束

与其他分割问题对比：
- 131题：分割回文串，每段必须是回文
- 132题：分割回文串II，求最少分割次数（DP问题）
- 93题：复原IP地址，数字分割 + 有效性验证

回溯 + 字符串处理核心技巧：
1. 分割位置枚举：for(int i = start; i < s.length(); i++)
2. 子串提取：s.substr(start, i - start + 1)
3. 回文判断：isPalindrome(s, start, i)
4. 路径构建：path存储当前分割方案

易错点预测：
1. 子串边界：substr(start, len) 的len参数是长度，不是结束位置
2. 回文判断：注意字符串边界，避免越界访问
3. 递归参数：下一层递归start应该是i+1，表示从下一个字符开始
4. 路径恢复：字符串path.pop_back()的正确时机
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> path;
        
        backtrack(s, 0, path, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, vector<string>& path, vector<vector<string>>& result) {
        // TODO: 实现分割回文串的回溯算法
        // 1. 递归终止条件：start == s.length() 时，已完成所有字符的分割
        // 2. 枚举分割位置：从start开始，尝试每个可能的结束位置
        // 3. 回文验证：只有当前子串是回文时，才进行递归
        // 4. 路径管理：将回文子串加入path，递归后移除
        if(start == s.length()) {
            result.push_back(path);
            return;
        }
        
        for(int i=start; i<s.length(); i++) {
            auto substr = s.substr(start,i-start+1);
            if(isPalindrome(substr)) {
                path.push_back(substr);
                backtrack(s,i+1, path,result);
                path.pop_back();
            }
        }
        
    }
    
    // 方法1：简单回文判断
    bool isPalindrome(const string& s) {
        // TODO: 实现回文判断
        // 双指针法：从两端向中间移动比较
        int left = 0, right = s.length() -1;
        while(left < right) {      // 这里如果🟰会如何？
            if(s[left] != s[right]) {
                return false;
            }else {
                left++;
                right--;
            }
        }
        return true;
    }
    
    // 方法2：优化版回文判断（直接在原字符串上判断，避免substr开销）
    bool isPalindromeOptimized(const string& s, int start, int end) {
        // TODO: 优化版回文判断
        // 直接在原字符串上判断，避免substr的额外开销
        while(start < end) {
            if(s[start] != s[end]) {
                return false;
            }else {
                start++;
                end--;
            }
        }
        return true;
    }
};

// 优化版Solution：预处理回文信息，避免重复计算
class SolutionOptimized {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<string>> result;
        vector<string> path;
        
        // TODO: 预处理回文信息
        // 使用动态规划预计算所有子串的回文信息
        // isPalin[i][j] 表示 s[i..j] 是否为回文
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        for(int i=0; i<n; i++) {
            isPalin[i][i] = true;
        }
        
        for(int len=2; len<=n; len++) {
            for(int i=0; i<= n-len; i++) {
                int j = i+len -1;
                /*if(s[i] == s[j]) { // 比如len=2, i=0, j=1时： 查询isPalin[1][0]，但这个位置还没有被初始化！
                    isPalin[i][j] = isPalin[i+1][j-1];
                }else {
                    isPalin[i][j] = false;
                }
                */
                if(len==2) {
                    isPalin[i][j] = (s[i] ==s[j]);
                } else {
                    isPalin[i][j] = (s[i] ==s[j]) && isPalin[i+1][j-1];
                }
            }
        }

        backtrackOptimized(s, 0, path, result, isPalin);
        return result;
    }
    
private:
    void backtrackOptimized(string& s, int start, vector<string>& path, 
                           vector<vector<string>>& result, vector<vector<bool>>& isPalin) {
        // TODO: 优化版回溯实现
        // 直接查表判断回文，O(1) 时间复杂度

        if(start == s.length()) {
            result.push_back(path);
            return;
        }

        for(int i=start; i<s.length(); i++) {  //理解下为什么是 [start, s.length()),start不等于0的时候基本就是在递归子问题了
            if(isPalin[start][i]) {
                path.push_back(s.substr(start, i-start+1));
                backtrackOptimized(s, i+1,path, result, isPalin);
                path.pop_back();
            }
        }

    }
};

void printPartitions(const vector<vector<string>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    SolutionOptimized solutionOpt;
    
    // 测试用例1: s = "aab"
    cout << "=== 测试用例1: s = \"aab\" ===" << endl;
    cout << "期望输出: [[\"a\",\"a\",\"b\"],[\"aa\",\"b\"]]" << endl;
    string s1 = "aab";
    vector<vector<string>> result1 = solution.partition(s1);
    cout << "基础版实际输出: ";
    printPartitions(result1);
    
    vector<vector<string>> result1_opt = solutionOpt.partition(s1);
    cout << "优化版实际输出: ";
    printPartitions(result1_opt);
    cout << "分割方案数: " << result1.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例2: s = "raceacar"
    cout << "=== 测试用例2: s = \"raceacar\" ===" << endl;
    cout << "期望输出: [[\"r\",\"a\",\"c\",\"e\",\"a\",\"c\",\"a\",\"r\"],[\"r\",\"a\",\"ce\",\"ca\",\"r\"],[\"r\",\"ace\",\"ca\",\"r\"],[\"raceacar\"]]" << endl;
    string s2 = "raceacar";
    vector<vector<string>> result2 = solution.partition(s2);
    cout << "实际输出: ";
    printPartitions(result2);
    cout << "分割方案数: " << result2.size() << " (期望: 4)" << endl;
    cout << endl;
    
    // 测试用例3: s = "a"
    cout << "=== 测试用例3: s = \"a\" ===" << endl;
    cout << "期望输出: [[\"a\"]]" << endl;
    string s3 = "a";
    vector<vector<string>> result3 = solution.partition(s3);
    cout << "实际输出: ";
    printPartitions(result3);
    cout << "分割方案数: " << result3.size() << " (期望: 1)" << endl;
    cout << endl;
    
    // 测试用例4: s = "aba" (回文串)
    cout << "=== 测试用例4: s = \"aba\" (测试回文) ===" << endl;
    cout << "期望输出: [[\"a\",\"b\",\"a\"],[\"aba\"]]" << endl;
    string s4 = "aba";
    vector<vector<string>> result4 = solution.partition(s4);
    cout << "实际输出: ";
    printPartitions(result4);
    cout << "分割方案数: " << result4.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例5: s = "abcba" (更复杂的回文)
    cout << "=== 测试用例5: s = \"abcba\" (复杂回文测试) ===" << endl;
    string s5 = "abcba";
    vector<vector<string>> result5 = solution.partition(s5);
    cout << "实际输出: ";
    printPartitions(result5);
    cout << "分割方案数: " << result5.size() << " (验证回文识别能力)" << endl;
    cout << endl;
    
    cout << "=== 131题与回溯算法体系对比总结 ===" << endl;
    cout << " 核心差异:" << endl;
    cout << "  - 决策对象: 39/40题选择数字，131题选择分割位置" << endl;
    cout << "  - 约束条件: 39/40题target约束，131题回文约束" << endl;  
    cout << "  - 路径构建: 39/40题数字路径，131题字符串路径" << endl;
    cout << "  - 优化策略: 39/40题排序剪枝，131题DP预处理" << endl;
    cout << " 共同思维:" << endl;
    cout << "  - 回溯框架: 选择→递归→撤销的标准模式" << endl;
    cout << "  - 边界处理: 递归出口的精确设计" << endl;
    cout << "  - 状态管理: path路径的动态维护" << endl;
    cout << "  - 剪枝思想: 约束条件的智能应用" << endl;
    cout << endl;
    
    cout << "=== 回溯算法专题完美收官总结 ===" << endl;
    cout << " 技能进化路径 (8/8题完成):" << endl;
    cout << "  78→77→90→46→47→39→40→131" << endl;
    cout << "  子集→组合→去重→排列→高级去重→组合总和→技巧融合→分割问题" << endl;
    cout << " 核心思维建立:" << endl;
    cout << "  - 决策树思维: 将问题建模为选择序列" << endl;
    cout << "  - 约束建模: 将限制条件转化为算法设计" << endl;
    cout << "  - 状态管理: 路径构建与撤销的系统方法" << endl;
    cout << "  - 优化意识: 剪枝、预处理等效率提升技巧" << endl;
    cout << "  - 融合创新: 基于已有技术的组合设计能力" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_131 problem_131_template.cpp && ./problem_131

学习要点：
1. 理解回溯算法在字符串分割问题中的应用
2. 掌握回文判断的多种实现方式和优化策略
3. 理解分割位置枚举与路径构建的关系
4. 观察DP预处理在回溯算法中的优化作用

核心突破：
- 分割思维：从元素选择到位置分割的思维转变
- 约束复合：回溯逻辑 + 字符串处理 + 回文判断的三重结合
- 优化升级：从暴力判断到DP预处理的效率提升
- 专题圆满：回溯算法8题全部完成，知识体系大圆满

预期收获：
- 完全掌握回溯算法的所有核心模式
- 理解字符串分割问题的标准解法
- 建立回溯+字符串处理的复合应用能力
- 实现回溯算法专题的完美收官

技术意义：
131题作为回溯算法专题的压轴题目，展现了回溯思维从简单数字选择到复杂字符串处理的适应性，
标志着回溯算法学习的完整闭环，为后续高级算法问题奠定了坚实的思维基础。
*/