/*
560. 和为 K 的子数组 (Medium)
https://leetcode.cn/problems/subarray-sum-equals-k/

题目描述：
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数 。

示例 1：
输入：nums = [1,1,1], k = 2
输出：2

示例 2：
输入：nums = [1,2,3], k = 3
输出：2

约束条件：
- 1 <= nums.length <= 2 * 10^4
- -1000 <= nums[i] <= 1000
- -10^7 <= k <= 10^7

专题归属：数组 - 前缀和 + 哈希表
相关题目：1.两数之和、523.连续的子数组和、974.和可被K整除的子数组

算法分析：
思路提示：
1. 方法一：暴力法 - 枚举所有子数组
   - 双重循环，计算每个子数组的和
   - 时间复杂度O(n²)，空间复杂度O(1)

2. 方法二：前缀和 + 哈希表（推荐）
   - 核心思想：prefix_sum[j] - prefix_sum[i] = k
   - 即：prefix_sum[i] = prefix_sum[j] - k
   - 边计算前缀和，边查找哈希表中是否存在目标值

时间复杂度：O(n) - 前缀和 + 哈希表法
空间复杂度：O(n) - 哈希表存储前缀和

易错点：
1. 前缀和的初始化：map[0] = 1（处理从头开始的子数组）
2. 先查找再更新：避免当前位置的前缀和影响查找结果
3. 理解连续子数组的含义：必须是相邻的元素
4. 负数的处理：前缀和可能减少，哈希表是必需的
*/

#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：暴力法
    int subarraySum_bruteforce(vector<int>& nums, int k) {
        // TODO: 实现暴力解法
        // 提示：
        // 1. 外层循环：枚举起始位置i
        // 2. 内层循环：枚举结束位置j
        // 3. 计算从i到j的子数组和，等于k则计数+1
        
        return 0;
    }
    
    // 方法二：前缀和 + 哈希表（推荐）
    int subarraySum(vector<int>& nums, int k) {
        // 本来直接用一个数组来计算前缀和的，但题目中可能会存在多个组合，所以用一个map
        // 思考为什么不能用双指针？
        unordered_map<int, int> prekey_map;
        prekey_map[0] =1; // 没有的话就会找不到
        int curr_sum = 0;
        int count =0;
        for(int i=0; i<nums.size(); i++) {
            curr_sum += nums[i];
            if(prekey_map.find(curr_sum -k) != prekey_map.end()) {
                 count += prekey_map[curr_sum-k];
            }
            prekey_map[curr_sum]++;
        }
        return count;
    }
    
    // 方法三：前缀和数组 + 哈希表
    int subarraySum_prefixArray(vector<int>& nums, int k) {
        // TODO: 实现前缀和数组版本
        // 提示：先计算前缀和数组，再用哈希表统计
        
        return 0;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 基本情况
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "测试1 - nums=[1,1,1], k=2" << endl;
    cout << "预期结果: 2, 实际结果: " << solution.subarraySum(nums1, k1) << endl << endl;
    
    // 测试用例2: 不同子数组
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "测试2 - nums=[1,2,3], k=3" << endl;
    cout << "预期结果: 2, 实际结果: " << solution.subarraySum(nums2, k2) << endl << endl;
    
    // 测试用例3: 包含负数
    vector<int> nums3 = {1, -1, 0};
    int k3 = 0;
    cout << "测试3 - nums=[1,-1,0], k=0" << endl;
    cout << "预期结果: 3, 实际结果: " << solution.subarraySum(nums3, k3) << endl << endl;
    
    // 测试用例4: 单个元素
    vector<int> nums4 = {1};
    int k4 = 1;
    cout << "测试4 - nums=[1], k=1" << endl;
    cout << "预期结果: 1, 实际结果: " << solution.subarraySum(nums4, k4) << endl << endl;
    
    // 测试用例5: 没有符合条件的子数组
    vector<int> nums5 = {1, 2, 3};
    int k5 = 7;
    cout << "测试5 - nums=[1,2,3], k=7" << endl;
    cout << "预期结果: 0, 实际结果: " << solution.subarraySum(nums5, k5) << endl << endl;
    
    // 测试用例6: 复杂情况
    vector<int> nums6 = {3, 4, 7, 2, -3, 1, 4, 2};
    int k6 = 7;
    cout << "测试6 - nums=[3,4,7,2,-3,1,4,2], k=7" << endl;
    cout << "实际结果: " << solution.subarraySum(nums6, k6) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解前缀和的概念和计算方法
2. 掌握前缀和 + 哈希表的经典组合
3. 学会处理连续子数组和的问题模式
4. 理解"差值查找"的数学思想

算法精髓：
1. 前缀和转化：将子数组和问题转化为两个前缀和的差值
2. 哈希表优化：O(1)时间查找目标前缀和
3. 边算边查：避免额外的空间和时间开销
4. 初始状态：map[0]=1处理从头开始的情况

数学原理：
- 子数组sum[i,j] = prefix[j] - prefix[i-1] = k
- 即：prefix[i-1] = prefix[j] - k
- 遍历到j时，查找前面是否存在值为prefix[j]-k的前缀和

面试要点：
1. 解释前缀和的概念和优势
2. 分析为什么需要哈希表
3. 正确处理初始状态map[0]=1
4. 扩展到其他前缀和问题

相关题目模式：
- 两数之和：target = a + b
- 和为K的子数组：k = prefix[j] - prefix[i]
- 和可被K整除：(prefix[j] - prefix[i]) % k == 0
- 连续子数组和：长度至少为2且和为K的倍数

扩展思考：
- 如何求和为K的最长子数组？
- 如何求和为K的子数组的所有起止位置？
- 如何处理二维数组的子矩阵和问题？
*/