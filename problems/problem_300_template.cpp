#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 300. 最长递增子序列
难度: Medium
标签: [动态规划, 二分查找, 序列DP]
LeetCode链接: https://leetcode.cn/problems/longest-increasing-subsequence/

题目描述:
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

示例 1:
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,18]，因此长度为 4 。

示例 2:
输入：nums = [0,1,0,3,2,3]
输出：4

示例 3:
输入：nums = [7,7,7,7,7,7,7]
输出：1

约束条件:
- 1 <= nums.length <= 2500
- -10^4 <= nums[i] <= 10^4

进阶:
你能将算法的时间复杂度降低到 O(n log n) 吗?

思考要点:
1. 这是什么类型的DP？与之前学过的题目有什么区别？
2. 状态定义：dp[i] 表示什么含义？
3. 状态转移：如何表达"前面更小的数"的选择过程？
4. 为什么需要二重循环？如何优化到O(n log n)？
5. 序列DP的特点是什么？

核心难点:
- 理解子序列的概念：不要求连续，但要保持相对顺序
- 正确处理状态转移：需要检查前面所有较小的元素
- 掌握序列DP的思维：以第i个元素结尾的最优解
- 理解贪心+二分的优化思路
*/

class Solution {
public:
    // 方法1: 动态规划 - O(n²) 经典解法 ⭐
    int lengthOfLISDP(vector<int>& nums) {
        // TODO: 实现动态规划解法
        // 1. 状态定义：dp[i] = 以nums[i]结尾的最长递增子序列长度
        // 2. 状态转移：dp[i] = max(dp[j] + 1) for all j < i and nums[j] < nums[i]
        // 3. 边界条件：dp[i] = 1 (每个元素自己构成长度为1的序列)
        // 4. 返回结果：max(dp[i]) for all i
        
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n, 1);  // 初始化为1
        
        // TODO: 填充dp数组
        for(int i=1; i<n; i++) {
            for(int j=0;j<i;j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
        }

        // TODO: 返回最大值
        return *max_element(dp.begin(), dp.end()); // 这里不一定是dp[n-1]，在复习的时候出错了
    }
    
    // 方法2: 贪心 + 二分查找 - O(n log n) 最优解法 ⭐⭐
    int lengthOfLISBinary(vector<int>& nums) {
        // TODO: 实现贪心+二分解法
        // 核心思想：维护一个递增数组tails，tails[i]表示长度为i+1的递增子序列的最小尾元素
        // 对于每个新元素：
        //   - 如果比tails中所有元素都大，直接添加到末尾
        //   - 否则，用二分查找找到第一个>=它的位置，进行替换
        
        vector<int> tails;
        for (int num : nums) {
            // TODO: 实现二分查找逻辑
            int pos = tails.size();
            int left = 0, right = tails.size() -1;
            // 找到第一个大于等于num的元素
            while(left <=right) {
                int mid = (left + right) / 2;
                if(tails[mid] >= num) {
                    pos = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1; 
                }
            }
            if(pos == tails.size()) {
                tails.push_back(num);
            } else {
                tails[pos] = num;
            }
        }
        
        return tails.size();
    }
    
    // 方法3: 记忆化搜索 (选做)
    int lengthOfLISMemo(vector<int>& nums) {
        // TODO: 实现记忆化搜索 (选做)
        // 思路：递归计算以每个位置开始的最长递增子序列
        int n = nums.size();
        vector<int> memo(n,-1);
        int maxResult = 1;
        for(int i=0;i<n;i++) {
            maxResult = max(maxResult, helper(nums,i,memo));
        }
        return maxResult;
    }

    int helper(vector<int>&nums, int i, vector<int>& memo) {
        if (memo[i] != -1) return memo[i];
        memo[i] = 1;
        for(int j=0;j<i;j++) {
            if (nums[j] < nums[i]) {
                memo[i] = max(memo[i], helper(nums,j,memo) + 1);
            }
        }
        return memo[i];
    }
    
    // 主函数 - 选择你想实现的方法
    int lengthOfLIS(vector<int>& nums) {
        // 推荐先实现DP解法，理解序列DP的思维
        return lengthOfLISMemo(nums);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 300. 最长递增子序列" << endl;
    cout << "=========================" << endl;
    
    // 测试用例1
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    int result1 = sol.lengthOfLIS(nums1);
    cout << "测试1: nums=[10,9,2,5,3,7,101,18]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 4" << endl;
    cout << "说明: [2,3,7,18] 或 [2,3,7,101]" << endl;
    cout << (result1 == 4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    int result2 = sol.lengthOfLIS(nums2);
    cout << "测试2: nums=[0,1,0,3,2,3]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 4" << endl;
    cout << "说明: [0,1,2,3]" << endl;
    cout << (result2 == 4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    int result3 = sol.lengthOfLIS(nums3);
    cout << "测试3: nums=[7,7,7,7,7,7,7]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 1" << endl;
    cout << "说明: 所有元素相同" << endl;
    cout << (result3 == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 单调递增
    vector<int> nums4 = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    int result4 = sol.lengthOfLIS(nums4);
    cout << "测试4: nums=[1,3,6,7,9,4,10,5,6]" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 6" << endl;
    cout << "说明: [1,3,4,5,6,10] 或其他" << endl;
    cout << (result4 == 6 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 单个元素
    vector<int> nums5 = {10};
    int result5 = sol.lengthOfLIS(nums5);
    cout << "测试5: nums=[10]" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 1" << endl;
    cout << (result5 == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 序列DP思路演示
void demonstrateSequenceDP() {
    cout << "\n📚 序列DP思路演示" << endl;
    cout << "==================" << endl;
    
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "数组: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "目标: 找最长严格递增子序列的长度" << endl << endl;
    
    cout << "💡 序列DP核心思想：" << endl;
    cout << "以每个位置结尾，计算该位置的最优解" << endl;
    cout << "dp[i] = 以nums[i]结尾的最长递增子序列长度" << endl;
    cout << "dp[i] = max(dp[j] + 1) for all j < i and nums[j] < nums[i]" << endl << endl;
    
    cout << "🔍 手工计算过程：" << endl;
    
    int n = nums.size();
    vector<int> dp(n, 1);
    
    cout << "初始化: 每个元素自己构成长度1的序列" << endl;
    cout << "dp = [1,1,1,1,1,1,1,1]" << endl << endl;
    
    for (int i = 1; i < n; i++) {
        cout << "计算 dp[" << i << "] (nums[" << i << "]=" << nums[i] << "):";
        
        bool found = false;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
                cout << "\n  nums[" << j << "]=" << nums[j] << " < " << nums[i] 
                     << ", dp[" << i << "] = max(" << dp[i] << ", " << dp[j] << "+1) = " << max(dp[i], dp[j] + 1);
                found = true;
            }
        }
        
        if (!found) {
            cout << "\n  没有找到更小的前驱元素，dp[" << i << "] = 1";
        }
        
        cout << "\n  最终: dp[" << i << "] = " << dp[i] << endl << endl;
    }
    
    int result = *max_element(dp.begin(), dp.end());
    cout << "🎯 最终结果：" << result << endl;
    
    // 构造具体的序列
    cout << "\n🔍 构造最长递增子序列：" << endl;
    cout << "最终dp数组: [";
    for (int i = 0; i < n; i++) {
        cout << dp[i];
        if (i < n - 1) cout << ",";
    }
    cout << "]" << endl;
    
    // 找到最长长度的位置
    int maxLen = result;
    vector<int> lis;
    
    // 从后往前构造（简单版本）
    for (int i = n - 1; i >= 0; i--) {
        if (dp[i] == maxLen) {
            lis.push_back(nums[i]);
            maxLen--;
        }
    }
    
    reverse(lis.begin(), lis.end());
    cout << "一个可能的最长递增子序列: [";
    for (int i = 0; i < lis.size(); i++) {
        cout << lis[i];
        if (i < lis.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

// 贪心+二分查找思路讲解
void demonstrateBinarySearchOptimization() {
    cout << "\n🚀 贪心+二分查找优化思路" << endl;
    cout << "=========================" << endl;
    
    cout << "💡 核心思想：" << endl;
    cout << "维护一个数组tails，tails[i]表示长度为i+1的递增子序列的最小尾元素" << endl;
    cout << "为什么要维护最小尾元素？因为尾元素越小，后续添加新元素的机会越大！" << endl << endl;
    
    cout << "🔧 算法步骤：" << endl;
    cout << "1. 对于每个新元素num：" << endl;
    cout << "   - 如果num > tails中所有元素，添加到末尾" << endl;
    cout << "   - 否则，二分查找第一个>=num的位置，替换它" << endl;
    cout << "2. tails的长度就是最长递增子序列的长度" << endl << endl;
    
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "🔍 演示过程 (nums=[10,9,2,5,3,7,101,18])：" << endl;
    
    vector<int> tails;
    
    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        cout << "\n处理 nums[" << i << "]=" << num << ":" << endl;
        
        auto it = lower_bound(tails.begin(), tails.end(), num);
        
        if (it == tails.end()) {
            tails.push_back(num);
            cout << "  " << num << " > 所有元素，添加到末尾" << endl;
        } else {
            int pos = it - tails.begin();
            cout << "  二分查找：替换tails[" << pos << "]=" << *it << " 为 " << num << endl;
            *it = num;
        }
        
        cout << "  当前tails: [";
        for (int j = 0; j < tails.size(); j++) {
            cout << tails[j];
            if (j < tails.size() - 1) cout << ",";
        }
        cout << "], 长度=" << tails.size() << endl;
    }
    
    cout << "\n🎯 最终长度：" << tails.size() << endl;
    cout << "\n⚠️  注意：tails数组不一定是实际的最长递增子序列！" << endl;
    cout << "它只保证长度正确，元素可能不是真实序列的组成部分。" << endl;
}

// 复杂度分析和对比
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 动态规划解法:" << endl;
    cout << "   时间复杂度: O(n²) - 双重循环" << endl;
    cout << "   空间复杂度: O(n) - dp数组" << endl;
    cout << "   优势: 思路直观，容易理解和实现" << endl;
    cout << "   劣势: 时间复杂度较高" << endl << endl;
    
    cout << "2. 贪心+二分查找: ⭐ 最优解" << endl;
    cout << "   时间复杂度: O(n log n) - n次二分查找" << endl;
    cout << "   空间复杂度: O(n) - tails数组" << endl;
    cout << "   优势: 时间复杂度最优" << endl;
    cout << "   劣势: 理解难度较高，无法直接构造序列" << endl << endl;
    
    cout << "💡 序列DP的特点：" << endl;
    cout << "- 状态定义通常包含'以第i个元素结尾'" << endl;
    cout << "- 需要考虑前面所有可能的转移" << endl;
    cout << "- 最终答案可能需要遍历所有状态取最优值" << endl << endl;
    
    cout << "🔄 与之前DP题目的对比：" << endl;
    cout << "- 70题爬楼梯：递推关系，f(n) = f(n-1) + f(n-2)" << endl;
    cout << "- 198题打家劫舍：决策关系，选择 vs 不选择" << endl;
    cout << "- 53题最大子数组：连续约束，继续 vs 重新开始" << endl;
    cout << "- 322题零钱兑换：完全背包，无限使用" << endl;
    cout << "- 300题最长递增子序列：序列关系，需要检查所有前驱" << endl;
}

// 扩展应用和变种题目
void extensionProblems() {
    cout << "\n🌟 扩展应用" << endl;
    cout << "==========" << endl;
    
    cout << "相关题目:" << endl;
    cout << "- 354. 俄罗斯套娃信封问题 (二维LIS)" << endl;
    cout << "- 673. 最长递增子序列的个数 (计数问题)" << endl;
    cout << "- 1143. 最长公共子序列 (两个序列的LCS)" << endl;
    cout << "- 1035. 不相交的线 (LCS变种)" << endl;
    cout << "- 368. 最大整除子集 (整除关系的LIS)" << endl << endl;
    
    cout << "序列DP模式总结:" << endl;
    cout << "1. 单序列DP: 300题这种，考虑前面所有元素" << endl;
    cout << "2. 双序列DP: LCS问题，考虑两个序列的匹配" << endl;
    cout << "3. 特殊约束: 整除、包含等特殊关系" << endl;
}

int main() {
    cout << "🚀 LeetCode 300. 最长递增子序列" << endl;
    cout << "==============================" << endl;
    cout << "🔥 这是序列DP的经典题目！" << endl;
    cout << "💡 重点掌握序列DP思维和贪心优化" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    demonstrateSequenceDP();
    demonstrateBinarySearchOptimization();
    runTests();
    complexityAnalysis();
    extensionProblems();
    
    return 0;
}