#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
using namespace std;

/*
题目: 53. 最大子数组和
难度: Medium
标签: [动态规划, 数组, 分治]
LeetCode链接: https://leetcode.cn/problems/maximum-subarray/

题目描述:
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），
返回其最大和。

子数组是数组中的一个连续部分。

示例 1:
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2:
输入：nums = [1]
输出：1
解释：连续子数组 [1] 的和最大，为 1 。

示例 3:
输入：nums = [5,4,-1,7,8]
输出：23
解释：连续子数组 [5,4,-1,7,8] 的和最大，为 23 。

约束条件:
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4

思考要点:
1. 什么是连续子数组？与子序列有什么区别？
2. 如何定义状态？dp[i] 表示什么含义？
3. 状态转移：对于当前元素，我们有什么选择？
4. 全局最优 vs 局部最优：最终答案如何获得？
5. 能否用O(1)空间解决？

核心难点:
- 理解连续子数组的约束条件
- 正确定义DP状态的含义
- 区分局部最优解和全局最优解
- 这是Kadane算法的经典应用！
*/

class Solution {
public:
    // 方法1: 暴力解法 - O(n²) 时间复杂度
    int maxSubArrayBruteForce(vector<int>& nums) {
        // TODO: 实现暴力解法
        // 枚举所有可能的连续子数组，计算和的最大值
        int n = nums.size();
        int maxSum = INT_MIN;
        
        // 你的代码实现
        
        return maxSum;
    }
    
    // 方法2: 动态规划 - O(n) 时间复杂度 ⭐ 推荐
    int maxSubArrayDP(vector<int>& nums) {
        // TODO: 实现动态规划解法 (Kadane算法)
        // 1. 状态定义：dp[i] = 以nums[i]结尾的最大子数组和
        // 2. 状态转移：dp[i] = max(nums[i], dp[i-1] + nums[i])
        // 3. 边界条件：dp[0] = nums[0]
        // 4. 返回结果：max(dp[0], dp[1], ..., dp[n-1])
        
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n);
        // TODO: 初始化和填充dp数组
        dp[0] = nums[0];
        int max_result = dp[0];
        for(int i=1;i<nums.size();i++) {
            dp[i]= max(nums[i], nums[i]+dp[i-1]);
            max_result = max(max_result, dp[i]);
        }  
        return max_result;
    }
    
    // 方法3: 动态规划空间优化 - O(1) 空间
    int maxSubArrayDPOptimized(vector<int>& nums) {
        // TODO: 实现空间优化版本
        // 观察：dp[i] 只依赖于 dp[i-1]，所以只需要一个变量
        
        int n = nums.size();
        if (n == 0) return 0;
        
        int currentSum = nums[0];   // 当前以nums[i]结尾的最大和
        int maxSum = nums[0];       // 全局最大和
        
        // TODO: 遍历数组，更新currentSum和maxSum
        for(int i=1;i<nums.size();i++) {
            currentSum = max(nums[i], currentSum+nums[i]);
            maxSum = max(currentSum,maxSum);
        }
        return maxSum;
    }
    
    // 方法4: 分治法 - O(n log n) 时间复杂度 (进阶)
    int maxSubArrayDivideConquer(vector<int>& nums) {
        // TODO: 实现分治解法 (选做)
        // 分治思想：最大子数组要么在左半部分，要么在右半部分，要么跨越中间
        
        return divideConquer(nums, 0, nums.size() - 1);
    }
    
private:
    int divideConquer(vector<int>& nums, int left, int right) {
        // TODO: 实现分治递归
        // 1. 递归终止条件
        // 2. 计算左半部分最大子数组和
        // 3. 计算右半部分最大子数组和  
        // 4. 计算跨越中间的最大子数组和
        // 5. 返回三者最大值
        if(left == right) return nums[left];
        int mid = (left + right) / 2;
        int leftMax = divideConquer(nums, left, mid);
        int rightMax = divideConquer(nums, mid+1, right);
        
        // left 从mid开始
        int sumLeft = nums[mid];
        int maxSumLeft = sumLeft;
        for(int i=mid-1;i>=left;i--) {
            sumLeft += nums[i];
            maxSumLeft = max(maxSumLeft, sumLeft);
        }

        // right从mid+1开始
        int sumRight = nums[mid+1];
        int maxSumRight = sumRight;
        for(int i=mid+2;i<=right;i++) {
            sumRight += nums[i];
            maxSumRight = max(maxSumRight, sumRight);
        }

        int crossSum = maxSumLeft + maxSumRight;
        return max({leftMax,rightMax,crossSum});

        //做个笔记：实际crossSum包含了mid->right的情况，if num[mid] < 0 不包含正常，if num[mid] >0 则会包含在maxSumLeft中通过crossSum加进来。
    }
    
public:
    // 主函数 - 选择你想实现的方法
    int maxSubArray(vector<int>& nums) {
        // 推荐先实现动态规划，理解Kadane算法的精髓
        return maxSubArrayDP(nums);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 53. 最大子数组和" << endl;
    cout << "======================" << endl;
    
    // 测试用例1
    vector<int> nums1 = {-2,1,-3,4,-1,2,1,-5,4};
    int result1 = sol.maxSubArray(nums1);
    cout << "测试1: [-2,1,-3,4,-1,2,1,-5,4]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 6" << endl;
    cout << (result1 == 6 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> nums2 = {1};
    int result2 = sol.maxSubArray(nums2);
    cout << "测试2: [1]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 1" << endl;
    cout << (result2 == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    vector<int> nums3 = {5,4,-1,7,8};
    int result3 = sol.maxSubArray(nums3);
    cout << "测试3: [5,4,-1,7,8]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 23" << endl;
    cout << (result3 == 23 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 全负数
    vector<int> nums4 = {-3,-2,-1,-4};
    int result4 = sol.maxSubArray(nums4);
    cout << "测试4: [-3,-2,-1,-4]" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: -1" << endl;
    cout << (result4 == -1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 混合正负数
    vector<int> nums5 = {-1,2,3,-4,5};
    int result5 = sol.maxSubArray(nums5);
    cout << "测试5: [-1,2,3,-4,5]" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 6" << endl;
    cout << (result5 == 6 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// Kadane算法演示
void demonstrateKadaneAlgorithm() {
    cout << "\n📚 Kadane算法演示" << endl;
    cout << "=================" << endl;
    
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "数组: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "目标: 找到最大连续子数组和" << endl << endl;
    
    cout << "💡 Kadane算法核心思想：" << endl;
    cout << "对于每个位置i，决定是否要\"带着\"之前的子数组" << endl;
    cout << "- 如果之前的和为正，就带着（有利）" << endl;
    cout << "- 如果之前的和为负，就抛弃（有害），从当前位置重新开始" << endl << endl;
    
    cout << "🔍 手工计算过程：" << endl;
    int n = nums.size();
    vector<int> dp(n);
    int maxSum = nums[0];
    dp[0] = nums[0];
    
    cout << "dp[0] = " << dp[0] << ", maxSum = " << maxSum << endl;
    
    for (int i = 1; i < n; i++) {
        // 关键决策：要不要带着前面的子数组
        int keepPrevious = dp[i-1] + nums[i];
        int startNew = nums[i];
        dp[i] = max(keepPrevious, startNew);
        maxSum = max(maxSum, dp[i]);
        
        cout << "i=" << i << ": nums[" << i << "]=" << nums[i] << endl;
        cout << "  选择1: 带着前面 = " << dp[i-1] << " + " << nums[i] << " = " << keepPrevious << endl;
        cout << "  选择2: 重新开始 = " << startNew << endl;
        cout << "  决策: dp[" << i << "] = " << dp[i];
        
        if (dp[i] == keepPrevious) {
            cout << " (选择带着前面)" << endl;
        } else {
            cout << " (选择重新开始)" << endl;
        }
        
        cout << "  当前全局最大值: " << maxSum << endl << endl;
    }
    
    cout << "🎯 最终结果：最大子数组和 = " << maxSum << endl;
    
    // 追踪最优子数组
    cout << "\n🔍 最优子数组追踪：" << endl;
    int currentSum = 0;
    int start = 0, end = 0, tempStart = 0;
    maxSum = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        currentSum += nums[i];
        
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
        
        if (currentSum < 0) {
            currentSum = 0;
            tempStart = i + 1;
        }
    }
    
    cout << "最优子数组: [";
    for (int i = start; i <= end; i++) {
        cout << nums[i];
        if (i < end) cout << ",";
    }
    cout << "] = " << maxSum << endl;
}

// 复杂度分析和对比
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 暴力解法:" << endl;
    cout << "   时间复杂度: O(n²) - 枚举所有子数组" << endl;
    cout << "   空间复杂度: O(1)" << endl;
    cout << "   适用场景: 小规模数据" << endl << endl;
    
    cout << "2. 动态规划 (Kadane算法): ⭐ 最优解法" << endl;
    cout << "   时间复杂度: O(n) - 单次遍历" << endl;
    cout << "   空间复杂度: O(n) / O(1) - 可优化" << endl;
    cout << "   优势: 时间最优，思路清晰" << endl << endl;
    
    cout << "3. 分治法:" << endl;
    cout << "   时间复杂度: O(n log n)" << endl;
    cout << "   空间复杂度: O(log n) - 递归栈" << endl;
    cout << "   特点: 思路巧妙，但不是最优解" << endl << endl;
    
    cout << "💡 与其他DP题目的区别：" << endl;
    cout << "- 70题爬楼梯：纯递推，f(n) = f(n-1) + f(n-2)" << endl;
    cout << "- 198题打家劫舍：决策选择，f(n) = max(选择A, 选择B)" << endl;
    cout << "- 53题最大子数组：连续约束，f(n) = max(继续, 重新开始)" << endl;
    cout << "- 核心区别：连续性约束带来的状态转移特点" << endl;
}

// 连续子数组DP概念讲解
void continuousSubarrayDPConcepts() {
    cout << "\n🎓 连续子数组DP核心概念" << endl;
    cout << "=======================" << endl;
    
    cout << "📖 什么是连续子数组DP？" << endl;
    cout << "处理连续子数组问题的动态规划方法，核心是维护\"连续性\"约束" << endl;
    cout << "关键：状态必须包含\"以当前元素结尾\"的语义" << endl << endl;
    
    cout << "🔑 连续子数组DP的特征：" << endl;
    cout << "1. 状态定义必须包含\"以i结尾\"的约束" << endl;
    cout << "2. 状态转移体现\"继续 vs 重新开始\"的决策" << endl;
    cout << "3. 全局最优需要在所有局部最优中选择" << endl << endl;
    
    cout << "📋 解题步骤：" << endl;
    cout << "1. 定义状态：dp[i] = 以nums[i]结尾的最优解" << endl;
    cout << "2. 分析选择：继续之前的序列 vs 重新开始" << endl;
    cout << "3. 写出转移：dp[i] = opt(nums[i], dp[i-1] op nums[i])" << endl;
    cout << "4. 全局最优：max(dp[0], dp[1], ..., dp[n-1])" << endl << endl;
    
    cout << "🎯 最大子数组和的DP分析：" << endl;
    cout << "- 状态：dp[i] = 以nums[i]结尾的最大子数组和" << endl;
    cout << "- 选择：带着前面 vs 重新开始" << endl;
    cout << "- 转移：dp[i] = max(nums[i], dp[i-1] + nums[i])" << endl;
    cout << "- 答案：max(dp[0], dp[1], ..., dp[n-1])" << endl << endl;
    
    cout << "🌟 常见的连续子数组DP题目：" << endl;
    cout << "- 53. 最大子数组和 (和的最大值)" << endl;
    cout << "- 152. 乘积最大子数组 (乘积的最大值)" << endl;
    cout << "- 718. 最长重复子数组 (长度的最大值)" << endl;
    cout << "- 209. 长度最小的子数组 (滑动窗口变种)" << endl;
}

int main() {
    cout << "🚀 LeetCode 53. 最大子数组和" << endl;
    cout << "=============================" << endl;
    cout << "🔥 这是连续子数组DP的经典题目！" << endl;
    cout << "💡 重点掌握Kadane算法的核心思想" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    continuousSubarrayDPConcepts();
    demonstrateKadaneAlgorithm();
    runTests();
    complexityAnalysis();
    
    return 0;
}