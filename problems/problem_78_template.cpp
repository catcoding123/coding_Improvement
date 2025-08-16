#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
LeetCode 78. 子集 (Medium)
链接: https://leetcode.cn/problems/subsets/

题目描述:
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

示例 2：
输入：nums = [1]
输出：[[],[1]]

约束条件:
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10
- nums 中的所有元素 互不相同

算法分析:
- 这是回溯算法的经典入门题目，体现"选择/不选择"的决策树思维
- 对于每个元素，都有两种选择：选择该元素或不选择该元素
- 时间复杂度：O(2^n) - 每个元素有两种选择，共2^n种组合
- 空间复杂度：O(n) - 递归栈深度为n

回溯算法核心模式:
1. 选择 (make choice)
2. 递归 (recurse)
3. 撤销选择 (undo choice)

三种经典实现方式:
1. 基于索引的回溯 - 每个位置选择是否包含该元素
2. 基于路径的回溯 - 逐步构建当前子集
3. 迭代生成法 - 基于位操作的数学方法

易错点预测:
1. 递归终止条件的设置
2. 回溯时的状态恢复
3. 结果收集的时机
4. 数组越界检查
*/

class Solution {
public:
    // 方法1: 基于索引的回溯 (推荐) ⭐
    vector<vector<int>> subsetsBacktrack(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        
        // TODO: 实现基于索引的回溯算法
        backtract(nums,0,current,result);
        return result;
    }
    
    // 方法2: 基于路径的回溯
    vector<vector<int>> subsetsPath(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        
        // TODO: 实现基于路径的回溯算法
        generateSubsets(nums, 0, path, result);
        return result;
    }
    
    // 方法3: 迭代生成法 (位操作)
    vector<vector<int>> subsetsIterative(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // TODO: 实现基于位操作的迭代生成法
        // 提示: 2^n种组合，每种组合对应一个二进制数
        
        return result;
    }

private:
    void backtract(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
        // 终止条件
        if(index == nums.size()) { // 这里如果 index == nums.size() -1 // 收集的是"上一个状态"的结果
            result.push_back(current);
            return;
        }
        
        // 不选择
        backtract(nums, index+1, current, result);

        // 选择
        current.push_back(nums[index]);
        backtract(nums, index+1, current, result);
        current.pop_back();
    }
    
    void generateSubsets(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        // 写入
        result.push_back(current);

        // 选择
        for(int i =start; i< nums.size(); i++) {
            current.push_back(nums[i]);
            generateSubsets(nums, i+1, current, result); // i+1 而不是start+1
            current.pop_back();
        }
    }
};

// 测试函数
void printSubsets(const vector<vector<int>>& subsets) {
    cout << "[";
    for (int i = 0; i < subsets.size(); i++) {
        cout << "[";
        for (int j = 0; j < subsets[i].size(); j++) {
            cout << subsets[i][j];
            if (j < subsets[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < subsets.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1: 标准情况
    vector<int> nums1 = {1, 2, 3};
    cout << "测试用例1: nums = [1,2,3]" << endl;
    cout << "期望输出: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]" << endl;
    
    auto result1 = solution.subsetsBacktrack(nums1);
    cout << "索引回溯结果: ";
    printSubsets(result1);
    
    auto result1_path = solution.subsetsPath(nums1);
    cout << "路径回溯结果: ";
    printSubsets(result1_path);
    
    // 测试用例2: 单元素
    vector<int> nums2 = {1};
    cout << "\n测试用例2: nums = [1]" << endl;
    cout << "期望输出: [[],[1]]" << endl;
    
    auto result2 = solution.subsetsBacktrack(nums2);
    cout << "回溯法结果: ";
    printSubsets(result2);
    
    // 测试用例3: 空数组边界情况
    vector<int> nums3 = {};
    cout << "\n测试用例3: nums = []" << endl;
    cout << "期望输出: [[]]" << endl;
    
    auto result3 = solution.subsetsBacktrack(nums3);
    cout << "回溯法结果: ";
    printSubsets(result3);
    
    // 测试用例4: 负数情况
    vector<int> nums4 = {-1, 0, 1};
    cout << "\n测试用例4: nums = [-1,0,1]" << endl;
    cout << "期望输出: 包含所有8种组合" << endl;
    
    auto result4 = solution.subsetsBacktrack(nums4);
    cout << "回溯法结果: ";
    printSubsets(result4);
    
    cout << "\n=== 回溯算法核心理念 ===" << endl;
    cout << "1. 决策树思维: 每个元素都有选择/不选择两种分支" << endl;
    cout << "2. 递归结构: 大问题分解为子问题" << endl;
    cout << "3. 状态管理: 回溯时要正确恢复状态" << endl;
    cout << "4. 结果收集: 在正确的时机收集有效解" << endl;
    
    return 0;
}

/*
编译运行指令:
g++ -std=c++11 -o problem_78 problem_78_template.cpp && ./problem_78

回溯算法学习要点:
1. 理解决策树的概念：每层递归对应一个决策点
2. 掌握"选择→递归→撤销"的三步模式
3. 正确设置递归终止条件
4. 理解状态的传递和恢复机制

与之前学过的算法对比:
- DP: 最优子结构，重叠子问题，通过记忆化避免重复计算
- 回溯: 穷举所有可能，通过剪枝避免无效搜索，不避免重复计算
- 递归: 两者都使用递归，但目标不同（最优解 vs 所有解）
*/