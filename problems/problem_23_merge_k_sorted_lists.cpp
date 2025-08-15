/*
LeetCode 23. 合并 K 个升序链表 (Merge k Sorted Lists)
难度: Hard

题目链接: https://leetcode.cn/problems/merge-k-sorted-lists/

题目描述:
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1:
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到：
1->1->2->3->4->4->5->6

示例 2:
输入：lists = []
输出：[]

示例 3:
输入：lists = [[]]
输出：[]

约束条件:
- k == lists.length
- 0 <= k <= 10^4
- 0 <= lists[i].length <= 500
- -10^4 <= lists[i][j] <= 10^4
- lists[i] 按升序排列
- lists.length 的总和不超过 10^4

算法分析:
时间复杂度目标: O(n log k) - n为所有节点总数，k为链表个数
空间复杂度目标: O(log k) - 分治递归栈深度

核心考点:
1. 分治算法 - 两两合并的递归分解
2. 优先队列(最小堆) - K路归并排序
3. 逐一合并优化 - 复杂度分析能力
4. 链表操作熟练度 - 指针处理技巧

易错点预测:
1. 边界条件：空数组、单链表、空链表混合
2. 分治合并的区间划分：mid计算和递归边界
3. 优先队列比较函数：最小堆的构造方式
4. 链表合并细节：虚拟头节点的使用
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 方法1: 分治算法 (推荐，最优解)
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // TODO: 实现分治算法合并K个有序链表
        // 思路提示：
        // 1. 递归分解：将K个链表分成两半
        // 2. 递归合并：分别合并左半部分和右半部分
        // 3. 合并结果：将两个有序链表合并成一个
        if(lists.empty()) return nullptr;
        return mergeHelper(lists,0,lists.size()-1);
    }
    
    // 方法2: 优先队列(最小堆)
    ListNode* mergeKListsWithPriorityQueue(vector<ListNode*>& lists) {
        // TODO: 实现基于优先队列的K路归并
        // 思路提示：
        // 1. 将所有链表的头节点放入最小堆
        // 2. 每次取出最小节点，将其后继节点放入堆
        // 3. 重复直到堆为空
        auto cmp = [](ListNode* a, ListNode* b) {return a->val > b->val;}; //后面还要加；吗？
        struct Cmp {
            bool operator()(ListNode* a, ListNode* b) { 
                return a->val > b->val; //return a->val > b->val 表示"如果a的值更大，则a优先级更低"
            }
        };
        priority_queue<ListNode*, vector<ListNode*>, Cmp> pq; //priority_queue别拼错了
        for(auto list:lists) {
            if(list) {
                pq.push(list);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        while(!pq.empty()) {
            ListNode* top = pq.top();
            pq.pop();
            curr->next = top;
            curr = curr->next;
            if(top->next) {
                pq.push(top->next);
            }
        }
        return dummy->next;
    }
    
    // 方法3: 逐一合并 (朴素解法，用于对比)
    ListNode* mergeKListsOneByOne(vector<ListNode*>& lists) {
        // TODO: 逐一合并链表，复杂度较高但思路简单
        // 思路：依次将每个链表与结果链表合并
        // ListNode* dummy = new ListNode(0);
        ListNode* curr = nullptr;
        for(auto list: lists) {
            curr = mergeTwoLists(curr,list);
        }
        return curr;
    }

private:
    // 辅助函数：合并两个有序链表 (复用21题解法)
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // TODO: 实现两个有序链表的合并
        // 经典双指针技巧
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        while(list1 && list2) {
            if (list1->val <= list2->val) {
                curr->next = list1;
                list1 = list1->next;
            } else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }
        if(list1) {
            curr->next = list1;
        }else{
            curr->next = list2;
        }

        return dummy->next;
    }
    
    // 辅助函数：分治合并的递归实现
    ListNode* mergeHelper(vector<ListNode*>& lists, int start, int end) {
        // TODO: 递归合并lists[start...end]范围内的链表
        // 分治思想的核心实现
        if(start == end) return lists[start];
        if(start > end) return nullptr;
        int mid = (start + end) / 2;
        ListNode* left = mergeHelper(lists, start, mid);
        ListNode* right = mergeHelper(lists, mid+1, end);

        return mergeTwoLists(left, right);
    }
};

// 辅助函数：从数组创建链表
ListNode* createLinkedList(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    
    ListNode* head = new ListNode(nums[0]);
    ListNode* curr = head;
    
    for (int i = 1; i < nums.size(); i++) {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
    }
    
    return head;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << "->";
        head = head->next;
    }
    cout << endl;
}

// 辅助函数：链表转数组(用于验证结果)
vector<int> listToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// 测试函数
void testMergeKLists() {
    Solution solution;
    
    // 测试用例1: [[1,4,5],[1,3,4],[2,6]]
    {
        vector<vector<int>> input = {{1,4,5}, {1,3,4}, {2,6}};
        vector<ListNode*> lists;
        
        for (auto& nums : input) {
            lists.push_back(createLinkedList(nums));
        }
        
        ListNode* result = solution.mergeKLists(lists);
        vector<int> output = listToVector(result);
        vector<int> expected = {1,1,2,3,4,4,5,6};
        
        cout << "测试1 - 输入: [[1,4,5],[1,3,4],[2,6]]" << endl;
        cout << "预期: [1,1,2,3,4,4,5,6]" << endl;
        cout << "实际: [";
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
            if (i < output.size() - 1) cout << ",";
        }
        cout << "]" << endl;
        cout << "结果: " << (output == expected ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例2: [] (空数组)
    {
        vector<ListNode*> lists;
        ListNode* result = solution.mergeKLists(lists);
        
        cout << "测试2 - 输入: []" << endl;
        cout << "预期: []" << endl;
        cout << "实际: " << (result == nullptr ? "[]" : "非空") << endl;
        cout << "结果: " << (result == nullptr ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例3: [[]] (包含空链表)
    {
        vector<ListNode*> lists = {nullptr};
        ListNode* result = solution.mergeKLists(lists);
        
        cout << "测试3 - 输入: [[]]" << endl;
        cout << "预期: []" << endl;
        cout << "实际: " << (result == nullptr ? "[]" : "非空") << endl;
        cout << "结果: " << (result == nullptr ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例4: 单个链表
    {
        vector<int> nums = {1,2,3};
        vector<ListNode*> lists = {createLinkedList(nums)};
        
        ListNode* result = solution.mergeKLists(lists);
        vector<int> output = listToVector(result);
        vector<int> expected = {1,2,3};
        
        cout << "测试4 - 输入: [[1,2,3]]" << endl;
        cout << "预期: [1,2,3]" << endl;
        cout << "实际: [";
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
            if (i < output.size() - 1) cout << ",";
        }
        cout << "]" << endl;
        cout << "结果: " << (output == expected ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例5: 大小不一的链表
    {
        vector<vector<int>> input = {{1,4,5}, {1,3,4}, {2,6}, {0}, {7,8,9,10}};
        vector<ListNode*> lists;
        
        for (auto& nums : input) {
            lists.push_back(createLinkedList(nums));
        }
        
        ListNode* result = solution.mergeKLists(lists);
        vector<int> output = listToVector(result);
        vector<int> expected = {0,1,1,2,3,4,4,5,6,7,8,9,10};
        
        cout << "测试5 - 输入: [[1,4,5],[1,3,4],[2,6],[0],[7,8,9,10]]" << endl;
        cout << "预期: [0,1,1,2,3,4,4,5,6,7,8,9,10]" << endl;
        cout << "实际: [";
        for (int i = 0; i < output.size(); i++) {
            cout << output[i];
            if (i < output.size() - 1) cout << ",";
        }
        cout << "]" << endl;
        cout << "结果: " << (output == expected ? "通过" : "失败") << endl << endl;
    }
}

// 性能测试函数
void performanceTest() {
    Solution solution;
    
    // 生成大规模测试数据
    vector<ListNode*> lists;
    const int k = 1000;  // 1000个链表
    const int listSize = 10;  // 每个链表10个节点
    
    for (int i = 0; i < k; i++) {
        vector<int> nums;
        for (int j = 0; j < listSize; j++) {
            nums.push_back(i * listSize + j);  // 生成有序数据
        }
        lists.push_back(createLinkedList(nums));
    }
    
    cout << "性能测试 - " << k << "个链表，每个" << listSize << "个节点" << endl;
    
    // 这里可以添加计时代码测试不同算法的性能
    auto start = chrono::high_resolution_clock::now();
    ListNode* result = solution.mergeKLists(lists);
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "执行时间: " << duration.count() << "ms" << endl;
    
    // 验证结果正确性(检查是否有序)
    bool isValid = true;
    ListNode* curr = result;
    int count = 0;
    while (curr && curr->next) {
        if (curr->val > curr->next->val) {
            isValid = false;
            break;
        }
        curr = curr->next;
        count++;
    }
    if (curr) count++;  // 计算最后一个节点
    
    cout << "结果验证: " << (isValid ? "有序✓" : "无序✗") << endl;
    cout << "节点总数: " << count << " (预期: " << k * listSize << ")" << endl;
}

int main() {
    cout << "=== LeetCode 23. 合并K个升序链表 测试 ===" << endl << endl;
    
    testMergeKLists();
    
    cout << "=== 性能测试 ===" << endl;
    // performanceTest();  // 实现完成后取消注释
    
    return 0;
}

/*
核心算法思路：

方法1: 分治算法 (最优解，推荐)
1. 递归分解：将K个链表分成两半 [0, mid] 和 [mid+1, end]
2. 递归合并：分别合并左半部分和右半部分
3. 合并结果：调用mergeTwoLists合并两个有序链表
时间复杂度：O(n log k) - 每层合并O(n)，共log k层
空间复杂度：O(log k) - 递归栈深度

方法2: 优先队列(最小堆)
1. 初始化：将所有非空链表的头节点放入最小堆
2. 循环处理：取出堆顶最小节点，添加到结果链表
3. 堆维护：将取出节点的next指针(如果非空)放入堆
4. 重复直到堆为空
时间复杂度：O(n log k) - n个节点，每次堆操作O(log k)  
空间复杂度：O(k) - 堆中最多k个节点

方法3: 逐一合并 (朴素解法)
1. 初始化result为空链表
2. 依次将每个链表与result合并
3. 使用mergeTwoLists完成两链表合并
时间复杂度：O(kn) - 第i次合并需要O(i*平均长度)，总和为O(kn)
空间复杂度：O(1) - 只使用常数额外空间

关键技巧：
1. 分治思想：K路问题分解为2路问题的递归
2. 堆优化：利用优先队列维护K个候选节点  
3. 虚拟头节点：简化链表构建的边界处理
4. 复杂度分析：理解不同算法的时间空间权衡

实现要点：
- 边界条件：空数组、空链表的特殊处理
- 递归边界：单个或两个链表的终止条件  
- 堆构造：最小堆的比较函数定义
- 指针维护：确保链表连接的正确性

扩展应用：
- 外部排序中的多路归并
- 数据库中的多表排序合并
- 分布式系统中的结果聚合
*/