/*
LeetCode 142. 环形链表 II (Linked List Cycle II)
难度: Medium

题目链接: https://leetcode.cn/problems/linked-list-cycle-ii/

题目描述:
给定一个链表的头节点 head，返回链表开始入环的第一个节点。如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改链表。

示例 1:
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。

示例 2:
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。

示例 3:
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。

约束条件:
- 链表中节点的数目范围在范围 [0, 10^4] 内
- -10^5 <= Node.val <= 10^5
- pos 的值为 -1 或者链表中的一个有效索引

进阶：你是否可以使用 O(1) 空间解决此题？

算法分析:
时间复杂度目标: O(n)
空间复杂度目标: O(1)

核心考点:
1. 快慢指针检测环的存在
2. Floyd判圈算法(龟兔赛跑算法)找环入口
3. 数学推导：环入口的位置计算

易错点预测:
1. 边界条件：空链表或单节点无环
2. 数学推导理解：为什么重新开始的指针会在环入口相遇
3. 指针空值检查
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // TODO: 实现Floyd判圈算法找到环的入口节点
        // 思路提示：
        // 1. 使用快慢指针检测是否有环
        // 2. 如果有环，重新设置一个指针从头开始
        // 3. 两个指针以相同速度移动，相遇点就是环入口
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }

        if(!fast || !fast->next) return nullptr; // 没有环

        fast = head;
        while(slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
    
    // 额外方法：使用哈希表的解法（空间复杂度O(n)）
    ListNode *detectCycleWithHashSet(ListNode *head) {
        // TODO: 实现基于哈希表的解法
        // 思路：遍历链表，记录访问过的节点，重复访问的就是环入口
        unordered_set<ListNode*> nodeSet;
        while(head) {
            if(nodeSet.count(head)) {
                return head;
            }
            
            nodeSet.insert(head);
            head = head->next;
        }
        return nullptr; //注意返回nullptr
    }
};

// 辅助函数：创建测试链表
ListNode* createLinkedListWithCycle(vector<int>& vals, int pos) {
    if (vals.empty()) return nullptr;
    
    vector<ListNode*> nodes;
    for (int val : vals) {
        nodes.push_back(new ListNode(val));
    }
    
    // 连接节点
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    
    // 创建环
    if (pos >= 0 && pos < nodes.size()) {
        nodes.back()->next = nodes[pos];
    }
    
    return nodes[0];
}

// 辅助函数：获取节点在原数组中的索引（用于验证结果）
int getNodeIndex(ListNode* head, ListNode* target, int pos) {
    if (!target) return -1;
    
    vector<ListNode*> nodes;
    ListNode* curr = head;
    
    // 收集所有节点（不包括环的重复部分）
    while (curr) {
        nodes.push_back(curr);
        curr = curr->next;
        
        // 如果遇到已访问的节点，说明到了环的开始
        for (int i = 0; i < nodes.size() - 1; i++) {
            if (nodes[i] == curr) {
                goto find_index;
            }
        }
    }
    
    find_index:
    // 查找目标节点的索引
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == target) {
            return i;
        }
    }
    return -1;
}

// 测试函数
void testDetectCycle() {
    Solution solution;
    
    // 测试用例1: [3,2,0,-4], pos = 1
    {
        vector<int> vals = {3, 2, 0, -4};
        ListNode* head = createLinkedListWithCycle(vals, 1);
        ListNode* result1 = solution.detectCycle(head);
        ListNode* result2 = solution.detectCycleWithHashSet(head);
        int index1 = getNodeIndex(head, result1, 1);
        int index2 = getNodeIndex(head, result2, 1);
        cout << "测试1 - 输入: [3,2,0,-4], pos=1" << endl;
        cout << "Floyd算法: " << (index1 == -1 ? "null" : "索引" + to_string(index1)) << endl;
        cout << "哈希表法: " << (index2 == -1 ? "null" : "索引" + to_string(index2)) << endl;
        cout << "结果: " << (index1 == 1 && index2 == 1 ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例2: [1,2], pos = 0  
    {
        vector<int> vals = {1, 2};
        ListNode* head = createLinkedListWithCycle(vals, 0);
        ListNode* result = solution.detectCycle(head);
        int index = getNodeIndex(head, result, 0);
        cout << "测试2 - 输入: [1,2], pos=0" << endl;
        cout << "预期: 索引0, 实际: " << (index == -1 ? "null" : "索引" + to_string(index)) << endl;
        cout << "结果: " << (index == 0 ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例3: [1], pos = -1
    {
        vector<int> vals = {1};
        ListNode* head = createLinkedListWithCycle(vals, -1);
        ListNode* result = solution.detectCycle(head);
        cout << "测试3 - 输入: [1], pos=-1" << endl;
        cout << "预期: null, 实际: " << (result == nullptr ? "null" : "非null") << endl;
        cout << "结果: " << (result == nullptr ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例4: 空链表
    {
        ListNode* head = nullptr;
        ListNode* result = solution.detectCycle(head);
        cout << "测试4 - 输入: [], pos=-1" << endl;
        cout << "预期: null, 实际: " << (result == nullptr ? "null" : "非null") << endl;
        cout << "结果: " << (result == nullptr ? "通过" : "失败") << endl << endl;
    }
    
    // 测试用例5: 单节点自环
    {
        ListNode* head = new ListNode(1);
        head->next = head;  // 自指向形成环
        ListNode* result = solution.detectCycle(head);
        cout << "测试5 - 输入: [1], pos=0 (自环)" << endl;
        cout << "预期: 索引0, 实际: " << (result == head ? "索引0" : "其他") << endl;
        cout << "结果: " << (result == head ? "通过" : "失败") << endl << endl;
    }
}

int main() {
    cout << "=== LeetCode 142. 环形链表 II 测试 ===" << endl << endl;
    testDetectCycle();
    return 0;
}

/*
核心算法思路：

方法1: Floyd判圈算法 (推荐，O(1)空间)
1. 第一阶段：使用快慢指针检测环
   - 慢指针每次走1步，快指针每次走2步
   - 如果有环，快慢指针必定相遇

2. 第二阶段：找到环的入口
   - 重新设置一个指针从头开始
   - 原慢指针继续从相遇点开始
   - 两指针都每次走1步，相遇点就是环入口

数学证明：
设链表头到环入口距离为a，环入口到相遇点距离为b，相遇点到环入口距离为c
- 慢指针走过距离：a + b
- 快指针走过距离：a + b + c + b = a + 2b + c
- 因为快指针速度是慢指针2倍：a + 2b + c = 2(a + b)
- 化简得：c = a
- 所以从头和从相遇点同时开始，走a步会在环入口相遇

方法2: 哈希表
1. 遍历链表，将访问过的节点存入哈希表
2. 如果遇到已访问的节点，就是环入口
3. 如果到达null，说明无环

时间复杂度：O(n)
空间复杂度：Floyd算法O(1)，哈希表O(n)
*/