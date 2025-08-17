/*
LeetCode 40. 组合总和 II (Medium)
https://leetcode.cn/problems/combination-sum-ii/

题目描述：
给定一个候选人编号的集合 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。

示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

示例 2:
输入: candidates = [2,5,2,1,2], target = 5
输出:
[
[1,2,2],
[5]
]

约束条件：
- 1 <= candidates.length <= 100
- 1 <= candidates[i] <= 50
- 1 <= target <= 30

算法分析：
时间复杂度：O(2^n) - 最坏情况需要枚举所有子集
空间复杂度：O(target) - 递归栈深度
核心难点：在39题基础上加入重复元素去重，融合90题去重策略

关键洞察：
1. 与39题区别：39题可重复使用，40题每个元素只能用一次
2. 与90题联系：都需要处理重复元素，但40题有target约束
3. 双重挑战：既要避免重复组合，又要满足target约束
4. 递归参数：使用i+1而不是i，因为每个元素只能用一次

算法融合对比：
39题技巧：
- 可重复使用：backtrack(..., i, ...)
- 目标递减：target - candidates[i]
- 排序剪枝：target < candidates[i] break

90题技巧：
- 排序预处理：sort(candidates)
- 同层去重：if(i > start && candidates[i] == candidates[i-1]) continue
- 确保顺序：只在同一层跳过重复元素

40题融合：
- 排序+去重+目标递减+每个元素仅用一次

与其他回溯题目对比：
- 78题子集：无重复元素，无target约束
- 90题子集II：有重复元素，无target约束  
- 39题组合总和：无重复元素，有target约束，可重复使用
- 40题组合总和II：有重复元素，有target约束，仅用一次

易错点预测：
1. 去重条件：if(i > start && candidates[i] == candidates[i-1]) continue
2. 递归参数：i+1而不是i，因为每个位置元素只能用一次
3. 排序必要性：既为去重也为剪枝优化
4. 理解"同层去重"vs"跨层允许"的精确含义
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> path;
        
        // 关键步骤：排序，既为去重也为剪枝
        sort(candidates.begin(), candidates.end());
        
        backtrack(candidates, target, 0, path, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int target, int start, vector<int>& path, vector<vector<int>>& result) {
        // TODO: 实现组合总和II的回溯算法
        // 1. 递归终止条件：target == 0时收集结果，target < 0时剪枝
        // 2. 遍历候选数字：从start开始，避免重复组合
        // 3. 去重处理：if(i > start && candidates[i] == candidates[i-1]) continue
        // 4. 每个元素仅用一次：递归时使用i+1，不是i
        // 5. 剪枝优化：利用排序性质，target < candidates[i]时直接break
        
        // 递归出口
        if (target == 0) {
            result.push_back(path);
            return;
        }
        if (target < 0) return;
        
        // 遍历选择
        for (int i = start; i < candidates.size(); i++) {
            // 同层去重：跳过重复元素的后续选择
            if (i > start && candidates[i] == candidates[i-1]) {
                continue;
            }
            
            // 剪枝优化：排序后可提前终止
            if (target < candidates[i]) break;
            
            path.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i + 1, path, result);  // 关键：i+1，每个元素只用一次
            path.pop_back();
        }
    }
};

void printCombinations(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1: candidates = [10,1,2,7,6,1,5], target = 8
    cout << "=== 测试用例1: candidates = [10,1,2,7,6,1,5], target = 8 ===" << endl;
    cout << "期望输出: [[1,1,6],[1,2,5],[1,7],[2,6]]" << endl;
    vector<int> candidates1 = {10, 1, 2, 7, 6, 1, 5};
    vector<vector<int>> result1 = solution.combinationSum2(candidates1, 8);
    cout << "实际输出: ";
    printCombinations(result1);
    cout << "组合总数: " << result1.size() << " (期望: 4)" << endl;
    cout << endl;
    
    // 测试用例2: candidates = [2,5,2,1,2], target = 5
    cout << "=== 测试用例2: candidates = [2,5,2,1,2], target = 5 ===" << endl;
    cout << "期望输出: [[1,2,2],[5]]" << endl;
    vector<int> candidates2 = {2, 5, 2, 1, 2};
    vector<vector<int>> result2 = solution.combinationSum2(candidates2, 5);
    cout << "实际输出: ";
    printCombinations(result2);
    cout << "组合总数: " << result2.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例3: candidates = [1], target = 1
    cout << "=== 测试用例3: candidates = [1], target = 1 ===" << endl;
    cout << "期望输出: [[1]]" << endl;
    vector<int> candidates3 = {1};
    vector<vector<int>> result3 = solution.combinationSum2(candidates3, 1);
    cout << "实际输出: ";
    printCombinations(result3);
    cout << "组合总数: " << result3.size() << " (期望: 1)" << endl;
    cout << endl;
    
    // 测试用例4: candidates = [1,1,1,1,1,1,1], target = 3 (测试去重效果)
    cout << "=== 测试用例4: candidates = [1,1,1,1,1,1,1], target = 3 (测试去重) ===" << endl;
    cout << "期望输出: [[1,1,1]]" << endl;
    vector<int> candidates4 = {1, 1, 1, 1, 1, 1, 1};
    vector<vector<int>> result4 = solution.combinationSum2(candidates4, 3);
    cout << "实际输出: ";
    printCombinations(result4);
    cout << "组合总数: " << result4.size() << " (期望: 1, 验证去重效果)" << endl;
    cout << endl;
    
    // 测试用例5: candidates = [3,1,3,5,1,1], target = 8 (复杂去重)
    cout << "=== 测试用例5: candidates = [3,1,3,5,1,1], target = 8 (复杂去重) ===" << endl;
    cout << "期望输出: [[1,1,1,5],[1,1,3,3],[1,3,4],[3,5]]" << endl;
    vector<int> candidates5 = {3, 1, 3, 5, 1, 1};
    vector<vector<int>> result5 = solution.combinationSum2(candidates5, 8);
    cout << "实际输出: ";
    printCombinations(result5);
    cout << "组合总数: " << result5.size() << " (验证复杂去重)" << endl;
    cout << endl;
    
    cout << "=== 40题与39题核心对比分析 ===" << endl;
    cout << " 相同点:" << endl;
    cout << "  - 目标导向：target递减控制递归深度" << endl;
    cout << "  - 剪枝优化：排序后target<candidates[i]可break" << endl;
    cout << "  - 组合性质：通过start参数避免重复组合" << endl;
    cout << " 核心区别:" << endl;
    cout << "  - 元素使用：39题可重复使用(i)，40题仅用一次(i+1)" << endl;
    cout << "  - 重复处理：39题无重复元素，40题需要去重策略" << endl;
    cout << "  - 算法融合：40题 = 39题target控制 + 90题去重技巧" << endl;
    cout << endl;
    
    cout << "=== 回溯算法去重策略总结 ===" << endl;
    cout << " 去重核心条件: if(i > start && candidates[i] == candidates[i-1]) continue" << endl;
    cout << " 条件分解:" << endl;
    cout << "  - i > start: 确保不是当前层第一个选择" << endl;
    cout << "  - candidates[i] == candidates[i-1]: 当前元素与前一个相同" << endl;
    cout << "  - 组合效果: 同层跳过重复，跨层允许使用" << endl;
    cout << " 排序作用: 使相同元素相邻，便于比较去重" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_40 problem_40_template.cpp && ./problem_40

学习要点：
1. 理解39题技巧与90题技巧的融合应用
2. 掌握有重复元素情况下的target约束回溯
3. 深入理解"同层去重"vs"跨层允许"的机制
4. 观察排序在去重和剪枝中的双重作用

核心突破：
- 算法融合：将不同题目的核心技巧组合应用
- 去重升级：从90题简单去重到40题约束去重
- 参数理解：i+1(仅用一次) vs i(可重复) 的精确区别
- 双重优化：去重+剪枝的协同效果

预期收获：
- 完全掌握回溯算法的去重策略应用
- 理解不同约束条件下的回溯设计差异  
- 建立算法技巧融合的设计思维
- 为后续高级回溯问题打下扎实基础

技术意义：
40题标志着回溯算法核心技能的集大成应用，展现了从基础回溯(78题)到约束回溯(77题)到去重回溯(90题)到重复使用(39题)最终到综合应用(40题)的完整技能进化路径。
*/