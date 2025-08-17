#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
LeetCode 77. 组合 (Medium)
链接: https://leetcode.cn/problems/combinations/

题目描述:
给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
你可以按 任何顺序 返回答案。

示例 1：
输入：n = 4, k = 2
输出：[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
解释：共有 4!/(2!*(4-2)!) = 6 种组合

示例 2：
输入：n = 1, k = 1
输出：[[1]]

示例 3：
输入：n = 4, k = 1
输出：[[1],[2],[3],[4]]

约束条件:
- 1 <= n <= 20
- 1 <= k <= n

算法分析:
- 这是回溯算法的经典应用，相比78题子集，这里有固定长度约束
- 核心思想：从[1,n]中选择k个数字，组合不考虑顺序
- 时间复杂度：O(C(n,k)) - 组合数，最坏情况O(2^n)
- 空间复杂度：O(k) - 递归栈深度为k

与78题子集的区别:
1. 子集：选择任意数量的元素，长度不固定
2. 组合：选择固定数量k的元素，有明确终止条件

回溯算法优化策略:
1. 剪枝优化：当剩余数字不足以构成k个元素时提前终止
2. 起始位置控制：避免重复组合，如[1,2]和[2,1]
3. 长度检查：当当前组合长度达到k时收集结果

易错点预测:
1. 剪枝条件的数学推导
2. 递归终止条件的正确设置
3. 起始位置的正确传递
4. 组合vs排列的概念区分
*/

class Solution {
public:
    // 方法1: 标准回溯 (推荐) ⭐
    vector<vector<int>> combineBacktrack(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        
        // TODO: 实现标准回溯算法
        backtrack(n, k, 1, current, result);
        
        return result;
    }
    
    // 方法2: 优化剪枝回溯 ⭐⭐
    vector<vector<int>> combineOptimized(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        
        // TODO: 实现带剪枝优化的回溯算法
        backtrackOptimized(n, k, 1, current, result);
        
        return result;
    }
    
    // 方法3: 迭代生成法 (数学方法)
    vector<vector<int>> combineIterative(int n, int k) {
        vector<vector<int>> result;
        
        // TODO: 实现基于位操作或数学的迭代生成法
        // 提示: 可以使用next_permutation或位操作
        
        return result;
    }

private:
    // 实现标准回溯辅助函数
    void backtrack(int n, int k, int start, vector<int>& current, vector<vector<int>>& result) {
        // 递归终止条件：达到所需长度
        if (current.size() == k) {
            result.push_back(current);
            return;
        }
        
        // 从start开始尝试所有可能的数字
        for (int i = start; i <= n; i++) {
            current.push_back(i);          // 选择
            backtrack(n, k, i + 1, current, result);  // 递归
            current.pop_back();            // 撤销
        }
    }
    
    // 实现优化剪枝辅助函数
    void backtrackOptimized(int n, int k, int start, vector<int>& current, vector<vector<int>>& result) {
        // 递归终止条件：达到所需长度
        if (current.size() == k) {
            result.push_back(current);
            return;
        }
        
        // 剪枝优化：计算还需要多少个数字
        int need = k - current.size();
        
        // 剪枝条件：剩余数字不足以填满
        for (int i = start; i <= n - need + 1; i++) {
            current.push_back(i);
            backtrackOptimized(n, k, i + 1, current, result);
            current.pop_back();
        }
    }
};

// 测试函数
void printCombinations(const vector<vector<int>>& combinations) {
    cout << "[";
    for (int i = 0; i < combinations.size(); i++) {
        cout << "[";
        for (int j = 0; j < combinations[i].size(); j++) {
            cout << combinations[i][j];
            if (j < combinations[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < combinations.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1: 标准情况
    int n1 = 4, k1 = 2;
    cout << "测试用例1: n = " << n1 << ", k = " << k1 << endl;
    cout << "期望输出: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]" << endl;
    
    auto result1 = solution.combineBacktrack(n1, k1);
    cout << "标准回溯结果: ";
    printCombinations(result1);
    
    // 测试用例2: 边界情况 k=1
    int n2 = 4, k2 = 1;
    cout << "\n测试用例2: n = " << n2 << ", k = " << k2 << endl;
    cout << "期望输出: [[1],[2],[3],[4]]" << endl;
    
    auto result2 = solution.combineBacktrack(n2, k2);
    cout << "标准回溯结果: ";
    printCombinations(result2);
    
    // 测试用例3: 边界情况 k=n
    int n3 = 3, k3 = 3;
    cout << "\n测试用例3: n = " << n3 << ", k = " << k3 << endl;
    cout << "期望输出: [[1,2,3]]" << endl;
    
    auto result3 = solution.combineBacktrack(n3, k3);
    cout << "标准回溯结果: ";
    printCombinations(result3);
    
    // 测试用例4: 最小情况
    int n4 = 1, k4 = 1;
    cout << "\n测试用例4: n = " << n4 << ", k = " << k4 << endl;
    cout << "期望输出: [[1]]" << endl;
    
    auto result4 = solution.combineBacktrack(n4, k4);
    cout << "标准回溯结果: ";
    printCombinations(result4);
    
    cout << "\n=== 77题与78题对比学习 ===" << endl;
    cout << "78题子集: 选择任意数量元素，2^n种可能" << endl;
    cout << "77题组合: 选择固定k个元素，C(n,k)种可能" << endl;
    cout << "共同点: 都使用回溯算法，都要避免重复" << endl;
    cout << "区别: 组合有长度约束，子集长度任意" << endl;
    
    cout << "\n=== 剪枝优化学习要点 ===" << endl;
    cout << "1. 剪枝条件: 剩余数字 < 还需数字 时提前终止" << endl;
    cout << "2. 数学推导: i <= n - need + 1 的边界计算" << endl;
    cout << "3. 时间优化: 减少无效的递归分支" << endl;
    cout << "4. 空间不变: 递归深度仍为k" << endl;
    
    return 0;
}

/*
编译运行指令:
g++ -std=c++11 -o problem_77 problem_77_template.cpp && ./problem_77

组合问题学习要点:
1. 理解组合与子集的区别：固定长度vs任意长度
2. 掌握剪枝优化：数学推导减少无效分支
3. 正确设置起始位置：避免重复组合
4. 终止条件明确：长度达到k时收集结果

剪枝优化数学推导:
- 当前已选: current.size()
- 还需选择: need = k - current.size()  
- 剩余数字: n - i + 1
- 剪枝条件: 剩余数字 >= 还需数字
- 即: n - i + 1 >= need
- 化简: i <= n - need + 1

这是回溯算法的重要进阶：从无约束到有约束，从全量搜索到优化剪枝。
*/