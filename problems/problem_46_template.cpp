/*
LeetCode 46. 全排列 (Medium)
https://leetcode.cn/problems/permutations/

题目描述：
给定一个不含重复数字的数组 nums ，返回其 所有可能的排列 。你可以 按任意顺序 返回答案。

示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例 3：
输入：nums = [1]
输出：[[1]]

约束条件：
- 1 <= nums.length <= 6
- -10 <= nums[i] <= 10
- nums 中的所有整数 互不相同

算法分析：
时间复杂度：O(n! * n) - 生成n!个排列，每个排列长度为n
空间复杂度：O(n) - 递归栈深度 + used数组空间
核心难点：状态管理 - 如何标记已使用元素，如何回溯状态

关键洞察：
1. 排列 vs 组合：排列关心顺序，组合不关心顺序
2. 状态空间：每层递归从所有未使用元素中选择
3. 状态管理：used数组标记使用状态，回溯时需要重置
4. 终止条件：当前排列长度等于原数组长度

回溯算法模式对比：
- 78题子集：选择/不选择 (二叉决策树)
- 77题组合：从候选中选择k个 (固定长度)
- 90题子集II：子集 + 去重策略
- 46题全排列：全选 + 顺序管理 (used数组)

易错点预测：
1. used数组的更新时机：选择时设置true，回溯时重置false
2. 循环起始位置：排列从0开始，组合从start开始
3. 终止条件：path.size() == nums.size()
4. 状态收集：在叶子节点收集，不是每层都收集
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        
        backtrack(nums, path, used, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& result) {
        // TODO: 实现回溯算法
        // 1. 终止条件：当前排列长度等于原数组长度
        // 2. 选择列表：所有未使用的元素
        // 3. 状态管理：used数组标记使用状态
        // 4. 回溯操作：撤销选择和状态
        
        // 提示：
        // - 终止条件: if (path.size() == nums.size())
        // - 循环遍历: for (int i = 0; i < nums.size(); i++)
        // - 剪枝条件: if (used[i]) continue;
        // - 做选择: path.push_back(nums[i]); used[i] = true;
        // - 递归调用: backtrack(nums, path, used, result);
        // - 撤销选择: path.pop_back(); used[i] = false;

        // 回溯退出
        if(path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        // 做选择
        for (int i=0; i< nums.size(); i++) {
            if(used[i]) continue;

            path.push_back(nums[i]);
            used[i] = true;
            backtrack(nums, path, used, result);

            path.pop_back();
            used[i] = false; // 别忘记了
        }
    }

    //我还实现一种交换的方式
public:
    void backtrack2(vector<int>& nums, int index, vector<vector<int>>& result) {
        if(index == nums.size()-1) {
            result.push_back(nums);
            return;
        }

        for(int i = index; i<nums.size(); i++) {
            swap(nums[i], nums[index]); // 最开始自己也会交换，比如a和a
            backtrack2(nums, index+1, result);
            swap(nums[i], nums[index]);
        }
    }
};

void printPermutations(const vector<vector<int>>& result) {
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
    
    // 测试用例1: nums = [1,2,3]
    cout << "=== 测试用例1: nums = [1,2,3] ===" << endl;
    cout << "期望输出: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]" << endl;
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> result1 = solution.permute(nums1);
    cout << "实际输出: ";
    printPermutations(result1);
    cout << "排列总数: " << result1.size() << " (期望: 6)" << endl;
    cout << endl;
    
    // 测试用例2: nums = [0,1]
    cout << "=== 测试用例2: nums = [0,1] ===" << endl;
    cout << "期望输出: [[0,1],[1,0]]" << endl;
    vector<int> nums2 = {0, 1};
    vector<vector<int>> result2 = solution.permute(nums2);
    cout << "实际输出: ";
    printPermutations(result2);
    cout << "排列总数: " << result2.size() << " (期望: 2)" << endl;
    cout << endl;
    
    // 测试用例3: nums = [1]
    cout << "=== 测试用例3: nums = [1] ===" << endl;
    cout << "期望输出: [[1]]" << endl;
    vector<int> nums3 = {1};
    vector<vector<int>> result3 = solution.permute(nums3);
    cout << "实际输出: ";
    printPermutations(result3);
    cout << "排列总数: " << result3.size() << " (期望: 1)" << endl;
    cout << endl;
    
    // 测试用例4: nums = [1,2,3,4] (挑战)
    cout << "=== 测试用例4: nums = [1,2,3,4] (挑战) ===" << endl;
    cout << "期望输出: 全排列共24个" << endl;
    vector<int> nums4 = {1, 2, 3, 4};
    vector<vector<int>> result4 = solution.permute(nums4);
    cout << "排列总数: " << result4.size() << " (期望: 24)" << endl;
    // 只显示前几个排列
    cout << "前6个排列: ";
    vector<vector<int>> first6(result4.begin(), result4.begin() + min(6, (int)result4.size()));
    printPermutations(first6);
    cout << endl;
    
    // 测试交换算法
    cout << "=== 测试交换算法: nums = [1,2,3] ===" << endl;
    vector<int> nums_swap = {1, 2, 3};
    vector<vector<int>> result_swap;
    solution.backtrack2(nums_swap, 0, result_swap);
    cout << "交换算法输出: ";
    printPermutations(result_swap);
    cout << "排列总数: " << result_swap.size() << " (期望: 6)" << endl;
    cout << endl;
    
    cout << "=== 46题与78题对比学习 ===" << endl;
    cout << " 78题子集: 选择/不选择 → 2^n种结果" << endl;
    cout << " 46题全排列: 全选+顺序 → n!种结果" << endl;
    cout << " 核心区别: 子集关心元素，排列关心顺序" << endl;
    cout << " 状态管理: 子集用索引，排列用used数组" << endl;
    cout << endl;
    
    cout << "=== 回溯算法思维进化 ===" << endl;
    cout << " 1. 选择空间: 子集(选/不选) → 排列(从剩余中选)" << endl;
    cout << " 2. 循环方式: 子集(二叉) → 排列(n叉)" << endl;
    cout << " 3. 状态管理: 子集(index) → 排列(used[])" << endl;
    cout << " 4. 剪枝策略: 子集(索引边界) → 排列(使用状态)" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_46 problem_46_template.cpp && ./problem_46

学习要点：
1. 理解排列与组合的本质区别
2. 掌握used数组的状态管理技巧
3. 理解回溯算法的"做选择→递归→撤销选择"三步法
4. 观察排列生成的递归树结构

预期收获：
- 掌握全排列算法的标准实现
- 理解状态空间搜索的经典模式
- 建立排列问题的思维框架
- 为47题(含重复数字的全排列)打基础
*/