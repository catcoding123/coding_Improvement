/*
283. 移动零 (Easy)
https://leetcode.cn/problems/move-zeroes/

题目描述：
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:
输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]

示例 2:
输入: nums = [0]
输出: [0]

约束条件：
- 1 <= nums.length <= 10^4
- -2^31 <= nums[i] <= 2^31 - 1

专题归属：数组 - 双指针
相关题目：27.移除元素、26.删除排序数组中的重复项

算法分析：
思路提示：
1. 方法一：双指针技术 - 快慢指针分离非零元素和零元素
2. 方法二：暴力移动 - 遇到0就删除并在末尾添加（效率较低）

时间复杂度：O(n) - 双指针法
空间复杂度：O(1) - 原地操作

易错点：
1. 必须保持非零元素的相对顺序
2. 必须原地操作，不能使用额外数组
3. 处理全零或无零的边界情况
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // 方法一：双指针法（推荐）
    void moveZeroes(vector<int>& nums) {
        // TODO: 实现双指针解法
        // 提示：使用快慢指针
        // - slow指针：指向下一个非零元素应该放置的位置
        // - fast指针：遍历整个数组寻找非零元素
        // 步骤：1.移动非零元素到前面 2.后面位置补零
        int slow =0;
        for(int fast =0; fast <nums.size(); fast++) {
            if(nums[fast] !=0) {
                nums[slow] = nums[fast];
                slow++;
            }
        }

        // 第二次遍历，将slow后面的都置为0
        for(;slow<nums.size();slow++) {
            nums[slow] =0;
        }
        
    }
    
    // 方法二：一次遍历优化版
    void moveZeroesOptimized(vector<int>& nums) {
        // TODO: 实现一次遍历解法
        // 提示：遍历过程中直接交换，减少写操作次数
        
    }
    
    // 辅助函数：打印数组
    void printArray(const vector<int>& nums) {
        cout << "[";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 标准情况
    vector<int> nums1 = {0, 1, 0, 3, 12};
    cout << "测试1 - 原数组: ";
    solution.printArray(nums1);
    solution.moveZeroes(nums1);
    cout << "移动后: ";
    solution.printArray(nums1);
    cout << "预期结果: [1,3,12,0,0]" << endl << endl;
    
    // 测试用例2: 只有一个零
    vector<int> nums2 = {0};
    cout << "测试2 - 原数组: ";
    solution.printArray(nums2);
    solution.moveZeroes(nums2);
    cout << "移动后: ";
    solution.printArray(nums2);
    cout << "预期结果: [0]" << endl << endl;
    
    // 测试用例3: 没有零
    vector<int> nums3 = {1, 2, 3, 4, 5};
    cout << "测试3 - 原数组: ";
    solution.printArray(nums3);
    solution.moveZeroes(nums3);
    cout << "移动后: ";
    solution.printArray(nums3);
    cout << "预期结果: [1,2,3,4,5]" << endl << endl;
    
    // 测试用例4: 全是零
    vector<int> nums4 = {0, 0, 0, 0};
    cout << "测试4 - 原数组: ";
    solution.printArray(nums4);
    solution.moveZeroes(nums4);
    cout << "移动后: ";
    solution.printArray(nums4);
    cout << "预期结果: [0,0,0,0]" << endl << endl;
    
    // 测试用例5: 零在开头
    vector<int> nums5 = {0, 0, 1, 2, 3};
    cout << "测试5 - 原数组: ";
    solution.printArray(nums5);
    solution.moveZeroes(nums5);
    cout << "移动后: ";
    solution.printArray(nums5);
    cout << "预期结果: [1,2,3,0,0]" << endl;
    
    return 0;
}

/*
学习重点：
1. 掌握双指针技术的经典应用
2. 理解快慢指针的协作机制
3. 体会原地操作的算法设计
4. 注意相对顺序保持的重要性

算法扩展：
- 双指针在数组问题中的广泛应用
- 如何在保持相对顺序的前提下重排数组
- 原地算法vs额外空间算法的权衡

面试要点：
1. 时间复杂度和空间复杂度的分析
2. 边界情况的处理
3. 代码的简洁性和可读性
4. 是否可以进一步优化
*/