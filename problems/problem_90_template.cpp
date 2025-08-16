#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
LeetCode 90. 子集 II (Medium)
链接: https://leetcode.cn/problems/subsets-ii/

题目描述:
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

示例 1：
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

示例 2：
输入：nums = [0]
输出：[[],[0]]

约束条件:
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10

算法分析:
- 这是78题子集的进阶版本，核心挑战是处理重复元素
- 关键技巧：排序 + 跳过重复元素，避免生成重复子集
- 时间复杂度：O(2^n) - 最多2^n个子集
- 空间复杂度：O(n) - 递归栈深度

与78题子集的核心区别:
1. 输入数组可能包含重复元素
2. 需要去重策略，避免生成重复子集
3. 排序是去重的前提条件

去重策略核心:
1. 先对数组排序，使相同元素相邻
2. 在同一层递归中，跳过重复元素
3. 关键判断：if (i > start && nums[i] == nums[i-1]) continue;

易错点预测:
1. 忘记排序数组
2. 去重条件的边界判断
3. 理解"同层去重"vs"不同层可重复"
4. 递归调用中start参数的正确传递
*/

class Solution {
public:
    // 方法1: 排序+去重回溯 (推荐) ⭐
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        
        // 排序
        sort(nums.begin(), nums.end());

        // 回溯
        backtrack(nums, 0, current, result);
        
        return result;
    }
    
    // 方法2: 基于索引的去重回溯 (进阶)
    vector<vector<int>> subsetsWithDupIndex(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        
        // TODO: 排序 + 基于索引的去重策略
        // sort(nums.begin(), nums.end());
        // backtrackIndex(nums, 0, current, result);
        
        return result;
    }
    
    // 方法3: 使用set去重 (不推荐，效率低)
    vector<vector<int>> subsetsWithDupSet(vector<int>& nums) {
        // TODO: 生成所有子集，用set自动去重
        // 注意：这种方法简单但效率较低
        
        return {};
    }

private:
    // TODO: 实现基于路径的去重回溯
     void backtrack(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        result.push_back(current);

        // 选择
        for(int i = start; i<nums.size(); i++) {
            // 去重
            if(i >start && nums[i] == nums[i-1]) continue;
            
            current.push_back(nums[i]);
            backtrack(nums,i+1,current,result);
            current.pop_back();
        }
     }
    
    // TODO: 实现基于索引的去重回溯
    // void backtrackIndex(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
    //     if (index == nums.size()) {
    //         result.push_back(current);
    //         return;
    //     }
    //     
    //     // 选择1: 不选择当前元素
    //     backtrackIndex(nums, index + 1, current, result);
    //     
    //     // 选择2: 选择当前元素
    //     current.push_back(nums[index]);
    //     backtrackIndex(nums, index + 1, current, result);
    //     current.pop_back();
    //     
    //     // TODO: 跳过所有相同的元素，避免重复
    //     // while (index + 1 < nums.size() && nums[index + 1] == nums[index]) {
    //     //     index++;
    //     // }
    // }
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
    
    // 测试用例1: 标准情况 - 包含重复元素
    vector<int> nums1 = {1, 2, 2};
    cout << "测试用例1: nums = [1,2,2]" << endl;
    cout << "期望输出: [[],[1],[1,2],[1,2,2],[2],[2,2]]" << endl;
    
    auto result1 = solution.subsetsWithDup(nums1);
    cout << "去重回溯结果: ";
    printSubsets(result1);
    
    // 测试用例2: 单元素
    vector<int> nums2 = {0};
    cout << "\n测试用例2: nums = [0]" << endl;
    cout << "期望输出: [[],[0]]" << endl;
    
    auto result2 = solution.subsetsWithDup(nums2);
    cout << "去重回溯结果: ";
    printSubsets(result2);
    
    // 测试用例3: 多个重复元素
    vector<int> nums3 = {4, 4, 4, 1, 4};
    cout << "\n测试用例3: nums = [4,4,4,1,4]" << endl;
    cout << "期望输出: 去重后的所有子集" << endl;
    
    auto result3 = solution.subsetsWithDup(nums3);
    cout << "去重回溯结果: ";
    printSubsets(result3);
    
    // 测试用例4: 全部相同元素
    vector<int> nums4 = {1, 1, 1};
    cout << "\n测试用例4: nums = [1,1,1]" << endl;
    cout << "期望输出: [[],[1],[1,1],[1,1,1]]" << endl;
    
    auto result4 = solution.subsetsWithDup(nums4);
    cout << "去重回溯结果: ";
    printSubsets(result4);
    
    cout << "\n=== 90题与78题对比学习 ===\n";
    cout << "78题子集: 元素互不相同，无需去重\n";
    cout << "90题子集II: 可能包含重复元素，需要去重策略\n";
    cout << "核心区别: 排序+同层去重的处理技巧\n";
    cout << "去重关键: if (i > start && nums[i] == nums[i-1]) continue;\n";
    
    cout << "\n=== 去重策略深度理解 ===\n";
    cout << "1. 排序作用: 使相同元素相邻，便于去重判断\n";
    cout << "2. 同层去重: 避免在同一层递归中选择重复元素\n";
    cout << "3. 不同层可重复: 不同递归层可以选择相同元素值\n";
    cout << "4. i > start: 确保在当前递归层的非第一个位置才去重\n";
    
    return 0;
}

/*
编译运行指令:
g++ -std=c++11 -o problem_90 problem_90_template.cpp && ./problem_90

90题子集II学习要点:
1. 理解去重的本质：避免生成相同的子集
2. 掌握排序+跳过重复元素的经典技巧
3. 区分"同层去重"和"跨层可重复"的概念
4. 理解 i > start 条件的深层含义

与之前题目的联系:
- 78题: 回溯算法基础，无重复元素
- 77题: 带约束的回溯，剪枝优化
- 90题: 去重技巧，处理重复元素的核心策略

去重算法在其他题目中的应用:
- 40. 组合总和II (去重组合)
- 47. 全排列II (去重排列)
- 491. 递增子序列 (不排序的去重策略)
*/