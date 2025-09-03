/*
128. 最长连续序列 (Medium)
https://leetcode.cn/problems/longest-consecutive-sequence/

题目描述：
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

示例 2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

约束条件：
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9

专题归属：数组 - 哈希表
相关题目：300.最长递增子序列、674.最长连续递增序列

算法分析：
思路提示：
1. 方法一：排序法
   - 先排序，再遍历计算连续序列长度
   - 时间复杂度O(n log n)，不满足题目要求

2. 方法二：哈希表法（推荐）
   - 用HashSet存储所有数字，实现O(1)查找
   - 对每个数字，检查是否是连续序列的起点
   - 从起点开始向右扩展，计算连续序列长度
   - 关键优化：只从序列起点开始搜索

时间复杂度：O(n) - 每个数字最多被访问2次
空间复杂度：O(n) - 哈希表存储

易错点：
1. 起点判断：只有当num-1不存在时，num才是起点
2. 重复元素：需要去重或正确处理重复值
3. 边界情况：空数组、单元素数组
4. 优化理解：为什么时间复杂度是O(n)而不是O(n²)
*/

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：哈希表法（推荐）
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        unordered_set<int> m_set(nums.begin(), nums.end());
        int max_len = 1;
        int curr_len = 0;
        for(auto& num: m_set) {
            if(m_set.find(num-1) == m_set.end()) { // 核心点：必须要保证是起点,长度才有意义
                int curr_num = num;
                curr_len = 1;
                while(m_set.find(curr_num+1) != m_set.end()) {
                    curr_num++;
                    curr_len++;
                }
                max_len = max(max_len, curr_len);
            }
        }
        return max_len;
    }
    
    // 方法二：排序法
    int longestConsecutiveSorted(vector<int>& nums) {
        // TODO: 实现排序解法
        // 提示：
        // 1. 先对数组排序
        // 2. 遍历排序后的数组，计算连续序列长度
        // 3. 注意处理重复元素
        
        return 0;
    }
    
    // 方法三：Union-Find（并查集）
    int longestConsecutiveUnionFind(vector<int>& nums) {
        // TODO: 实现并查集解法（进阶）
        // 提示：将相邻的数字合并到同一个集合中
        
        return 0;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 基本情况
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "测试1 - nums=[100,4,200,1,3,2]" << endl;
    cout << "预期结果: 4, 实际结果: " << solution.longestConsecutive(nums1) << endl << endl;
    
    // 测试用例2: 连续序列较长
    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "测试2 - nums=[0,3,7,2,5,8,4,6,0,1]" << endl;
    cout << "预期结果: 9, 实际结果: " << solution.longestConsecutive(nums2) << endl << endl;
    
    // 测试用例3: 空数组
    vector<int> nums3 = {};
    cout << "测试3 - nums=[]" << endl;
    cout << "预期结果: 0, 实际结果: " << solution.longestConsecutive(nums3) << endl << endl;
    
    // 测试用例4: 单个元素
    vector<int> nums4 = {1};
    cout << "测试4 - nums=[1]" << endl;
    cout << "预期结果: 1, 实际结果: " << solution.longestConsecutive(nums4) << endl << endl;
    
    // 测试用例5: 无连续序列
    vector<int> nums5 = {1, 3, 5, 7, 9};
    cout << "测试5 - nums=[1,3,5,7,9]" << endl;
    cout << "预期结果: 1, 实际结果: " << solution.longestConsecutive(nums5) << endl << endl;
    
    // 测试用例6: 包含重复元素
    vector<int> nums6 = {1, 2, 0, 1};
    cout << "测试6 - nums=[1,2,0,1]" << endl;
    cout << "预期结果: 3, 实际结果: " << solution.longestConsecutive(nums6) << endl << endl;
    
    // 测试用例7: 负数
    vector<int> nums7 = {-1, -2, -3, 0, 1};
    cout << "测试7 - nums=[-1,-2,-3,0,1]" << endl;
    cout << "预期结果: 5, 实际结果: " << solution.longestConsecutive(nums7) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解哈希表在算法优化中的关键作用
2. 掌握"起点优化"的思想：避免重复计算
3. 学会分析算法的时间复杂度：为什么是O(n)
4. 理解去重在算法中的重要性

算法精髓：
1. 数据结构选择：HashSet提供O(1)的查找效率
2. 优化策略：只从连续序列的起点开始搜索
3. 搜索方向：从起点向右单向扩展
4. 去重处理：HashSet天然去重，简化逻辑

时间复杂度分析：
- 虽然有嵌套循环，但每个数字最多被访问2次：
  1. 外层循环访问1次
  2. 内层while循环中作为起点时访问1次
- 因此总时间复杂度是O(n)

面试要点：
1. 解释为什么需要O(n)时间复杂度
2. 分析起点优化的原理和必要性
3. 正确处理边界情况和重复元素
4. 对比不同方法的优缺点

算法优化：
1. 起点判断：num-1不存在时才开始搜索
2. 单向搜索：只向右扩展，避免重复
3. 早期终止：可以在找到更长序列时提前结束

实际应用：
- 数据库中连续ID的查找
- 时间序列中连续时间段的识别
- 游戏中连击计数的计算
- 基因序列中连续片段的分析

扩展思考：
- 如何找到所有最长连续序列？
- 如何处理连续序列有gaps的情况？
- 如何扩展到二维数组中的连续区域？
- 如何在数据流中维护最长连续序列？

相关题目对比：
- 300题：最长递增子序列（不要求连续）
- 674题：最长连续递增子序列（要求原数组连续）
- 128题：最长连续序列（数值连续但位置可不连续）
*/