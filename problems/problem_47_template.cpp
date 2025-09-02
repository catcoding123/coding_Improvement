/*
LeetCode 47. 全排列 II (Medium)
https://leetcode.cn/problems/permutat
ions-ii/

题目描述：
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

示例 1：
输入：nums = [1,1,2]
输出：[[1,1,2],[1,2,1],[2,1,1]]

示例 2：
输入：nums = [1,2,1,3]
输出：[[1,1,2,3],[1,1,3,2],[1,2,1,3],[1,2,3,1],[1,3,1,2],[1,3,2,1],[2,1,1,3],[2,1,3,1],[2,3,1,1],[3,1,1,2],[3,1,2,1],[3,2,1,1]]

示例 3：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

约束条件：
- 1 <= nums.length <= 8
- -10 <= nums[i] <= 10

算法分析：
时间复杂度：O(n! * n) - 在最坏情况下生成n!个排列，每个排列长度为n
空间复杂度：O(n) - 递归栈深度 + used数组空间
核心难点：重复元素的去重策略 - 如何避免生成重复的排列

关键洞察：
1. 46题 + 去重：在46题基础上增加去重策略
2. 排序预处理：将相同元素聚集在一起，便于去重判断
3. 同层去重：在同一递归层中，相同元素只能按顺序使用
4. 不同层可重复：不同递归层可以使用相同值的元素

去重策略核心：
- 排序：sort(nums.begin(), nums.end())
- 同层剪枝：if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

剪枝条件详解：
- i > 0：确保不是第一个元素（避免越界）
- nums[i] == nums[i-1]：当前元素与前一个元素值相同
- !used[i-1]：前一个相同元素在当前递归层还未被使用

为什么这样能去重？
以 [1,1,2] 为例：
- 第一层选择：只能选择第一个1（nums[0]），不能选择第二个1（nums[1]）
- 确保相同元素在同一层的使用顺序：必须先用nums[0]的1，再用nums[1]的1
- 避免 [第二个1,第一个1,2] 和 [第一个1,第二个1,2] 这种重复排列

回溯算法模式对比：
- 46题全排列：无重复元素，只需used数组标记使用状态
- 47题全排列II：有重复元素，需要排序 + 同层去重策略
- 90题子集II：子集去重，使用相似的同层去重策略

易错点预测：
1. 忘记排序：没有排序就无法正确去重
2. 剪枝条件错误：!used[i-1] vs used[i-1] 的理解
3. 边界检查遗漏：i > 0 条件容易忘记
4. 去重逻辑理解：不理解为什么这样能去重
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);  // 错误：这个容易漏掉
        
        // 关键步骤：排序，使相同元素相邻
        sort(nums.begin(), nums.end()); // 错误：去重的任务一定要先排序
        
        backtrack(nums, path, used, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& result) {
        // TODO: 实现带去重的回溯算法
        // 1. 终止条件：与46题相同
        // 2. 选择列表：所有未使用的元素
        // 3. 去重策略：同层去重剪枝
        // 4. 回溯操作：撤销选择和状态
        
        if(path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for(int i=0; i< nums.size(); i++) {
            if(used[i]) continue; // 如果这个位置被选择了，就不用选择这个位置元素

            if(i>0 && nums[i] == nums[i-1] && !used[i-1]) { //错误：这里是!used[i-1]不是!used[i]
                continue;
            } //used 用来判断是否同层，如果同层则剪枝

            path.push_back(nums[i]);
            used[i] = true;

            backtrack(nums, path, used, result);

            path.pop_back();
            used[i] = false;

        }
    }
};

// 辅助函数：验证结果是否去重
bool hasDuplicates(const vector<vector<int>>& result) {
    for (int i = 0; i < result.size(); i++) {
        for (int j = i + 1; j < result.size(); j++) {
            if (result[i] == result[j]) {
                return true;
            }
        }
    }
    return false;
}

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
    
    // 测试用例1: nums = [1,1,2]
    cout << "=== 测试用例1: nums = [1,1,2] ===" << endl;
    cout << "期望输出: [[1,1,2],[1,2,1],[2,1,1]]" << endl;
    vector<int> nums1 = {1, 1, 2};
    vector<vector<int>> result1 = solution.permuteUnique(nums1);
    cout << "实际输出: ";
    printPermutations(result1);
    cout << "排列总数: " << result1.size() << " (期望: 3)" << endl;
    cout << "去重检查: " << (hasDuplicates(result1) ? "❌ 有重复" : "✅ 无重复") << endl;
    cout << endl;
    
    // 测试用例2: nums = [1,2,1,3]
    cout << "=== 测试用例2: nums = [1,2,1,3] ===" << endl;
    cout << "期望输出: 12个不重复排列" << endl;
    vector<int> nums2 = {1, 2, 1, 3};
    vector<vector<int>> result2 = solution.permuteUnique(nums2);
    cout << "排列总数: " << result2.size() << " (期望: 12)" << endl;
    cout << "去重检查: " << (hasDuplicates(result2) ? "❌ 有重复" : "✅ 无重复") << endl;
    cout << "前6个排列: ";
    if (result2.size() >= 6) {
        vector<vector<int>> first6(result2.begin(), result2.begin() + 6);
        printPermutations(first6);
    }
    cout << endl;
    
    // 测试用例3: nums = [1,2,3] (无重复元素)
    cout << "=== 测试用例3: nums = [1,2,3] (无重复元素) ===" << endl;
    cout << "期望输出: 6个排列，与46题结果相同" << endl;
    vector<int> nums3 = {1, 2, 3};
    vector<vector<int>> result3 = solution.permuteUnique(nums3);
    cout << "实际输出: ";
    printPermutations(result3);
    cout << "排列总数: " << result3.size() << " (期望: 6)" << endl;
    cout << "去重检查: " << (hasDuplicates(result3) ? "❌ 有重复" : "✅ 无重复") << endl;
    cout << endl;
    
    // 测试用例4: nums = [2,2,1,1] (多重复元素)
    cout << "=== 测试用例4: nums = [2,2,1,1] (多重复元素) ===" << endl;
    cout << "期望输出: 6个不重复排列" << endl;
    vector<int> nums4 = {2, 2, 1, 1};
    vector<vector<int>> result4 = solution.permuteUnique(nums4);
    cout << "实际输出: ";
    printPermutations(result4);
    cout << "排列总数: " << result4.size() << " (期望: 6)" << endl;
    cout << "去重检查: " << (hasDuplicates(result4) ? "❌ 有重复" : "✅ 无重复") << endl;
    cout << endl;
    
    cout << "=== 47题与46题对比学习 ===" << endl;
    cout << " 46题全排列: 无重复元素 → 只需used数组" << endl;
    cout << " 47题全排列II: 有重复元素 → 排序 + 同层去重" << endl;
    cout << " 核心增加: 排序预处理 + 剪枝条件" << endl;
    cout << " 去重策略: if (i > 0 && nums[i] == nums[i-1] && !used[i-1])" << endl;
    cout << endl;
    
    cout << "=== 回溯去重策略总结 ===" << endl;
    cout << " 90题子集II: 子集去重，start参数 + 同层剪枝" << endl;
    cout << " 47题全排列II: 排列去重，used数组 + 同层剪枝" << endl;
    cout << " 共同点: 排序 + 同层去重的核心思想" << endl;
    cout << " 区别: 子集用start控制，排列用used控制" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_47 problem_47_template.cpp && ./problem_47

学习要点：
1. 理解排序在去重中的关键作用
2. 掌握同层去重的剪枝条件
3. 理解 !used[i-1] 与 used[i-1] 的区别
4. 观察去重前后的结果差异

核心突破：
- 去重策略：从无重复到有重复的算法进化
- 剪枝优化：在46题基础上增加去重剪枝
- 状态管理：排序 + used数组的组合应用
- 算法融合：结合90题的去重思想

预期收获：
- 完全掌握排列问题的去重技巧
- 理解回溯算法中去重的通用策略
- 建立处理重复元素的思维框架
- 为更复杂的回溯问题打下基础

易错分析：
1. 排序遗漏：没有排序导致去重失败
2. 剪枝条件：!used[i-1] 写成 used[i-1]
3. 边界检查：忘记 i > 0 导致越界
4. 逻辑理解：不理解为什么这样能去重
*/