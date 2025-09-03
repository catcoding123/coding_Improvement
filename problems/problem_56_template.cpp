/*
56. 合并区间 (Medium)
https://leetcode.cn/problems/merge-intervals/

题目描述：
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

约束条件：
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti <= endi <= 10^4

专题归属：区间问题 - 贪心算法
相关题目：57.插入区间、435.无重叠区间、452.用最少数量的箭引爆气球

算法分析：
思路提示：
1. 方法一：排序 + 贪心合并
   - 先按区间起始点排序
   - 遍历排序后的区间，判断是否与前一个区间重叠
   - 重叠则合并，不重叠则添加新区间

时间复杂度：O(n log n) - 排序的时间复杂度
空间复杂度：O(1) - 不考虑返回数组的空间

易错点：
1. 排序的重要性：必须先排序才能正确合并
2. 重叠判断条件：intervals[i][0] <= merged.back()[1]
3. 边界情况：空数组、单个区间、所有区间重叠
4. 合并逻辑：更新右边界为两个区间右边界的最大值
*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 边界检查：处理空数组情况
        if (intervals.empty()) return {};
        
        // 步骤1: 按起始点排序（关键步骤）
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        
        // 步骤2: 遍历合并重叠区间
        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] <= merged.back()[1]) {
                // 重叠：合并区间，更新右边界
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // 不重叠：直接添加新区间
                merged.push_back(intervals[i]);
            }
        }
        return merged;
    }
    
    // 辅助函数：打印区间数组
    void printIntervals(const vector<vector<int>>& intervals) {
        cout << "[";
        for (int i = 0; i < intervals.size(); i++) {
            cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
            if (i < intervals.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
};

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 标准重叠情况
    vector<vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    cout << "测试1 - 输入: ";
    solution.printIntervals(intervals1);
    vector<vector<int>> result1 = solution.merge(intervals1);
    cout << "输出: ";
    solution.printIntervals(result1);
    cout << "预期: [[1,6],[8,10],[15,18]]" << endl << endl;
    
    // 测试用例2: 边界重叠
    vector<vector<int>> intervals2 = {{1,4},{4,5}};
    cout << "测试2 - 输入: ";
    solution.printIntervals(intervals2);
    vector<vector<int>> result2 = solution.merge(intervals2);
    cout << "输出: ";
    solution.printIntervals(result2);
    cout << "预期: [[1,5]]" << endl << endl;
    
    // 测试用例3: 无重叠
    vector<vector<int>> intervals3 = {{1,2},{3,4},{5,6}};
    cout << "测试3 - 输入: ";
    solution.printIntervals(intervals3);
    vector<vector<int>> result3 = solution.merge(intervals3);
    cout << "输出: ";
    solution.printIntervals(result3);
    cout << "预期: [[1,2],[3,4],[5,6]]" << endl << endl;
    
    // 测试用例4: 完全包含
    vector<vector<int>> intervals4 = {{1,4},{2,3}};
    cout << "测试4 - 输入: ";
    solution.printIntervals(intervals4);
    vector<vector<int>> result4 = solution.merge(intervals4);
    cout << "输出: ";
    solution.printIntervals(result4);
    cout << "预期: [[1,4]]" << endl << endl;
    
    // 测试用例5: 乱序输入
    vector<vector<int>> intervals5 = {{2,6},{1,3},{15,18},{8,10}};
    cout << "测试5 - 输入: ";
    solution.printIntervals(intervals5);
    vector<vector<int>> result5 = solution.merge(intervals5);
    cout << "输出: ";
    solution.printIntervals(result5);
    cout << "预期: [[1,6],[8,10],[15,18]]" << endl;
    
    return 0;
}

/*
学习重点：
1. 理解贪心算法在区间问题中的应用
2. 掌握排序在算法设计中的重要作用
3. 学会分析重叠条件和合并策略
4. 理解区间问题的通用处理思路

算法思路：
1. 排序是关键：确保能够顺序处理区间
2. 贪心策略：每次尽可能合并更多区间
3. 状态维护：结果数组中始终保持非重叠区间

面试要点：
1. 清楚解释为什么需要排序
2. 准确描述重叠判断条件
3. 正确处理各种边界情况
4. 分析算法的时间和空间复杂度

扩展应用：
- 会议室安排问题
- 任务调度问题
- 时间段冲突检测
- 资源分配优化

相关题目技巧：
- 57题：插入新区间的处理
- 435题：移除区间使其不重叠
- 452题：区间重叠的计数问题
*/