/*
33. 搜索旋转排序数组 (Medium)
https://leetcode.cn/problems/search-in-rotated-sorted-array/

题目描述：
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标从 0 开始计数）。
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

示例 1：
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4

示例 2：
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1

示例 3：
输入：nums = [1], target = 0
输出：-1

约束条件：
- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- nums 中的每个值都 独一无二
- 题目数据保证 nums 在预先未知的某个下标上进行了旋转
- -10^4 <= target <= 10^4

专题归属：数组 - 二分查找
相关题目：81.搜索旋转排序数组II、153.寻找旋转排序数组中的最小值、162.寻找峰值

算法分析：
思路提示：
1. 方法一：二分查找（推荐）
   - 核心思想：旋转数组分为两个有序部分
   - 判断mid在哪个有序部分，然后判断target在哪个范围
   - 根据判断结果调整left或right指针

2. 方法二：先找旋转点，再二分查找
   - 先用二分查找找到最小值的位置（旋转点）
   - 确定target在哪个有序部分
   - 在对应部分进行标准二分查找

时间复杂度：O(log n) - 二分查找
空间复杂度：O(1) - 只用常量额外空间

易错点：
1. 边界条件：判断nums[mid]与nums[left]、nums[right]的关系
2. 范围判断：target是否在当前有序的半边
3. 重复元素：题目保证无重复，简化了判断逻辑
4. 旋转理解：理解旋转数组的性质和分段特点
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：一次二分查找（推荐）
    int search(vector<int>& nums, int target) {
        // TODO: 实现一次二分查找解法
        int n = nums.size();
        int left = 0;
        int right = n-1;
        while(left <= right) { // ✅ 修复：必须包含等号
            int mid = left + (right - left) / 2; // ✅ 防止溢出
            if(nums[mid] == target) {
                return mid;
            }
            if(nums[left] <= nums[mid]) { // 左半部分有序
                if(target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // 右半部分有序
                if(target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
    
    // 方法二：先找旋转点，再二分查找
    int searchTwoStep(vector<int>& nums, int target) {
        // TODO: 实现两步法解法
        // 提示：
        // 1. 先找到最小值的索引（旋转点）
        // 2. 确定target应该在哪个有序部分
        // 3. 在对应部分进行标准二分查找
        
        return -1;
    }

private:
    // 辅助函数：找到最小值的索引
    int findMinIndex(vector<int>& nums) {
        // TODO: 实现寻找最小值索引的逻辑
        
        return 0;
    }
    
    // 辅助函数：在指定范围内进行二分查找
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        // TODO: 实现标准二分查找
        
        return -1;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 基本情况
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    cout << "测试1 - nums=[4,5,6,7,0,1,2], target=0" << endl;
    cout << "预期结果: 4, 实际结果: " << solution.search(nums1, target1) << endl << endl;
    
    // 测试用例2: 目标不存在
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    cout << "测试2 - nums=[4,5,6,7,0,1,2], target=3" << endl;
    cout << "预期结果: -1, 实际结果: " << solution.search(nums2, target2) << endl << endl;
    
    // 测试用例3: 单个元素
    vector<int> nums3 = {1};
    int target3 = 0;
    cout << "测试3 - nums=[1], target=0" << endl;
    cout << "预期结果: -1, 实际结果: " << solution.search(nums3, target3) << endl << endl;
    
    // 测试用例4: 目标在左半部分
    vector<int> nums4 = {4, 5, 6, 7, 0, 1, 2};
    int target4 = 6;
    cout << "测试4 - nums=[4,5,6,7,0,1,2], target=6" << endl;
    cout << "预期结果: 2, 实际结果: " << solution.search(nums4, target4) << endl << endl;
    
    // 测试用例5: 目标在右半部分
    vector<int> nums5 = {4, 5, 6, 7, 0, 1, 2};
    int target5 = 1;
    cout << "测试5 - nums=[4,5,6,7,0,1,2], target=1" << endl;
    cout << "预期结果: 5, 实际结果: " << solution.search(nums5, target5) << endl << endl;
    
    // 测试用例6: 无旋转（特殊情况）
    vector<int> nums6 = {1, 2, 3, 4, 5};
    int target6 = 3;
    cout << "测试6 - nums=[1,2,3,4,5], target=3" << endl;
    cout << "预期结果: 2, 实际结果: " << solution.search(nums6, target6) << endl << endl;
    
    // 测试用例7: 旋转点在开头
    vector<int> nums7 = {3, 1, 2};
    int target7 = 1;
    cout << "测试7 - nums=[3,1,2], target=1" << endl;
    cout << "预期结果: 1, 实际结果: " << solution.search(nums7, target7) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解旋转数组的性质：分为两个有序部分
2. 掌握在部分有序数组中的二分查找技巧
3. 学会分析和判断mid点在哪个有序部分
4. 理解范围判断的逻辑：target是否在当前有序范围内

算法精髓：
1. 旋转数组性质：至少有一半是严格有序的
2. 分情况讨论：判断哪一半有序，target在哪个范围
3. 二分查找思想：每次排除一半的搜索空间
4. 边界处理：正确处理等号和边界条件

关键判断逻辑：
1. 判断哪半边有序：
   - nums[left] <= nums[mid]：左半边有序
   - 否则：右半边有序

2. 判断target在哪个范围：
   - 左半边有序且target在[nums[left], nums[mid]]：搜索左半边
   - 右半边有序且target在[nums[mid], nums[right]]：搜索右半边
   - 否则搜索另一半

面试要点：
1. 清楚解释旋转数组的性质
2. 正确分析判断逻辑的各种情况
3. 准确处理边界条件和等号判断
4. 分析时间复杂度为O(log n)的原因

常见陷阱：
1. 边界判断错误：<=与<的区别
2. 范围判断错误：target在哪个区间的判断
3. 特殊情况遗漏：无旋转、单元素等
4. 指针更新错误：mid+1还是mid的选择

扩展思考：
- 如何处理包含重复元素的旋转数组？
- 如何找到旋转数组中的最小值？
- 如何判断一个数组是否为旋转数组？
- 如何在旋转数组中找到峰值？

相关题目：
- 81题：搜索旋转排序数组II（包含重复元素）
- 153题：寻找旋转排序数组中的最小值
- 154题：寻找旋转排序数组中的最小值II（包含重复元素）
*/