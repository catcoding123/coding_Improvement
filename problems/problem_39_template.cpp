/*
LeetCode 39. 组合总和 (Medium)
https://leetcode.cn/problems/combination-sum/

题目描述：
给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
找出 candidates 中可以使数字和为目标数 target 的所有不同组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两个组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。

示例 1：
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。

示例 2：
输入：candidates = [2,3,5], target = 8
输出：[[2,2,2,2],[2,3,3],[3,5]]

示例 3：
输入：candidates = [2], target = 1
输出：[]

约束条件：
- 1 <= candidates.length <= 30
- 2 <= candidates[i] <= 40
- candidates 中的所有元素 互不相同
- 1 <= target <= 40

算法分析：
时间复杂度：O(N^(T/M)) - N是数组长度，T是target，M是数组最小值
空间复杂度：O(T/M) - 递归栈深度最大为target除以最小候选数
核心难点：理解"可重复使用"的回溯实现，掌握目标值递减的剪枝策略

关键洞察：
1. 与47题区别：47题是排列去重，39题是组合重复使用
2. 无限使用策略：递归时起始位置不变，允许重复选择当前元素
3. 剪枝优化：排序后target<candidates[i]可直接break
4. 组合去重：通过起始位置start确保按顺序选择，避免重复组合

回溯算法模式对比：
- 46/47题全排列：used数组 + 全元素遍历 (顺序重要)
- 78/90题子集：start参数 + 选择/不选择 (避免重复)
- 39题组合总和：start参数 + 可重复使用 (无限选择)

与其他题目对比：
- 39题：无重复元素，可重复使用
- 40题：有重复元素，每个元素只能使用一次
- 377题：考虑顺序的组合总和(排列)

易错点预测：
1. 递归调用起始位置：应该是i而不是i+1
2. 剪枝时机：target<0时return，target==0时收集结果
3. 排序的作用：便于剪枝优化，不是为了去重
4. 理解"组合"含义：[2,3]和[3,2]是同一个组合
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> path;
        
        // 关键步骤：排序，便于剪枝优化
        sort(candidates.begin(), candidates.end());
        
        backtrack(candidates, target, 0, path, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int target, int start, vector<int>& path, vector<vector<int>>& result) {
        // TODO: 实现组合总和的回溯算法
        // 1. 递归终止条件：target == 0时收集结果，target < 0时剪枝
        // 2. 遍历候选数字：从start开始，避免重复组合
        // 3. 可重复使用：递归时起始位置仍为i，不是i+1
        // 4. 剪枝优化：利用排序性质，target < candidates[i]时直接break
        

        // 出口
        if(target == 0) {
            result.push_back(path);
            return;
        }
        if(target <0) return;


        // 选择
        for (int i=start; i< candidates.size(); i++) {
            if(target < candidates[i]) break;

            path.push_back(candidates[i]);
            backtrack(candidates, target-candidates[i], i, path, result);  // 关键：i而非i+1，允许重复使用
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
    
    // 测试用例1: candidates = [2,3,6,7], target = 7
    cout << "=== 测试用例1: candidates = [2,3,6,7], target = 7 ===" << endl;
    cout << "期望输出: [[2,2,3],[7]]" << endl;
    vector<int> candidates1 = {2, 3, 6, 7};
    vector<vector<int>> result1 = solution.combinationSum(candidates1, 7);
    cout << "实际输出: ";
    printCombinations(result1);
    cout << "组合总数: " << result1.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例2: candidates = [2,3,5], target = 8
    cout << "=== 测试用例2: candidates = [2,3,5], target = 8 ===" << endl;
    cout << "期望输出: [[2,2,2,2],[2,3,3],[3,5]]" << endl;
    vector<int> candidates2 = {2, 3, 5};
    vector<vector<int>> result2 = solution.combinationSum(candidates2, 8);
    cout << "实际输出: ";
    printCombinations(result2);
    cout << "组合总数: " << result2.size() << " (期望: 3)" << endl;
    cout << endl;
    
    // 测试用例3: candidates = [2], target = 1
    cout << "=== 测试用例3: candidates = [2], target = 1 ===" << endl;
    cout << "期望输出: []" << endl;
    vector<int> candidates3 = {2};
    vector<vector<int>> result3 = solution.combinationSum(candidates3, 1);
    cout << "实际输出: ";
    printCombinations(result3);
    cout << "组合总数: " << result3.size() << " (期望: 0)" << endl;
    cout << endl;
    
    // 测试用例4: candidates = [3,5,8], target = 11
    cout << "=== 测试用例4: candidates = [3,5,8], target = 11 ===" << endl;
    cout << "期望输出: [[3,3,5],[3,8]]" << endl;
    vector<int> candidates4 = {3, 5, 8};
    vector<vector<int>> result4 = solution.combinationSum(candidates4, 11);
    cout << "实际输出: ";
    printCombinations(result4);
    cout << "组合总数: " << result4.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例5: candidates = [7,3,2], target = 18 (测试排序效果)
    cout << "=== 测试用例5: candidates = [7,3,2], target = 18 (测试排序) ===" << endl;
    cout << "期望输出: [[2,2,2,2,2,2,2,2,2],[2,2,2,2,2,2,3,3],[2,2,2,3,3,3,3],[2,2,7,7],[2,3,3,3,7],[3,3,3,3,3,3]]" << endl;
    vector<int> candidates5 = {7, 3, 2};
    vector<vector<int>> result5 = solution.combinationSum(candidates5, 18);
    cout << "实际输出: ";
    printCombinations(result5);
    cout << "组合总数: " << result5.size() << " (验证剪枝效果)" << endl;
    cout << endl;
    
    cout << "=== 39题与其他回溯题目对比学习 ===" << endl;
    cout << " 78题子集: 选择/不选择，收集所有子集" << endl;
    cout << " 77题组合: 固定长度k，一次选择后不可重复" << endl;
    cout << " 90题子集II: 排序+去重，处理重复元素" << endl;
    cout << " 46题全排列: used数组，全选但关心顺序" << endl;
    cout << " 47题全排列II: used数组双重作用，高级去重" << endl;
    cout << " 39题组合总和: 可重复使用，目标值递减剪枝" << endl;
    cout << endl;
    
    cout << "=== 回溯算法核心模式总结 ===" << endl;
    cout << " 选择策略: 39题允许同一元素重复选择" << endl;
    cout << " 起始位置: 递归时start=i(可重复)，不是i+1" << endl;
    cout << " 剪枝优化: 排序+target<candidates[i]时break" << endl;
    cout << " 状态管理: target递减，path动态构建" << endl;
    cout << " 避免重复: start参数确保按顺序选择" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_39 problem_39_template.cpp && ./problem_39

学习要点：
1. 理解"可重复使用"的回溯实现机制
2. 掌握目标值递减的剪枝策略
3. 理解组合与排列的本质区别
4. 观察排序在剪枝优化中的关键作用

核心突破：
- 无限使用策略：从"一次性选择"到"可重复使用"的思维转变
- 剪枝优化：排序预处理在回溯算法中的妙用
- 状态传递：target递减比路径构建的优雅设计
- 模式总结：建立组合总和问题的通用解题模板

预期收获：
- 完全掌握可重复使用的回溯策略
- 理解目标导向的剪枝优化技巧
- 建立组合总和问题的思维框架
- 为40题组合总和II（去重版本）打下基础

技术进阶：
从47题的used数组双重作用到39题的可重复使用策略，展现了回溯算法在不同约束条件下的灵活应用，体现算法设计的适应性和扩展性。
*/