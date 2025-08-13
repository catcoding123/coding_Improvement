/**
 * 206. 反转链表 (Easy)
 * 
 * LeetCode链接: https://leetcode.cn/problems/reverse-linked-list/
 * 
 * 题目描述:
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 * 
 * 示例 1:
 * 输入: head = [1,2,3,4,5]
 * 输出: [5,4,3,2,1]
 * 
 * 示例 2:
 * 输入: head = [1,2]
 * 输出: [2,1]
 * 
 * 示例 3:
 * 输入: head = []
 * 输出: []
 * 
 * 约束条件:
 * - 链表中节点的数目范围是 [0, 5000]
 * - -5000 <= Node.val <= 5000
 * 
 * 进阶要求:
 * - 链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
 * 
 * 算法分析:
 * 这道题是链表算法的经典入门题，完美承接你的二叉树指针操作经验：
 * 1. 指针操作：从二叉树的left/right指针 → 链表的next指针
 * 2. 结构变换：类似二叉树翻转，但是线性结构更简单
 * 3. 递归思维：可以运用你已掌握的递归模式
 * 4. 迭代技巧：三指针滑动窗口的经典应用
 * 
 * 核心洞察:
 * - 链表反转 = 改变每个节点的next指针方向
 * - 原链表: 1→2→3→4→5→null
 * - 反转后: null←1←2←3←4←5 (等价于 5→4→3→2→1→null)
 * - 关键：在修改指针前保存下一个节点，避免链表断裂
 * 
 * 时间复杂度: O(n) - 遍历一次链表
 * 空间复杂度: O(1) 迭代版本 / O(n) 递归版本
 * 
 * 知识衔接:
 * - 二叉树指针操作经验 → 链表指针操作
 * - 递归思维模式 → 链表递归处理
 * - 边界条件处理 → 空链表、单节点等特殊情况
 * 
 * 易错点预测:
 * 1. 指针断裂：修改next前忘记保存后续节点
 * 2. 边界处理：空链表、单节点的特殊情况
 * 3. 返回值：应该返回新的头节点（原尾节点）
 * 4. 递归终止：递归版本的边界条件设置
 */

#include <iostream>
#include <vector>
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
    /**
     * 方法1: 迭代三指针法 (推荐实现)
     * 
     * 核心思路:
     * 1. 使用三个指针：prev(前驱)、curr(当前)、next(后继)
     * 2. 逐个改变每个节点的next指向
     * 3. 三指针同步向前移动
     * 
     * 指针变化过程:
     * 初始: prev=null, curr=head, next=curr->next
     * 第1步: null ← 1    2→3→4→5
     * 第2步: null ← 1 ← 2    3→4→5
     * 第3步: null ← 1 ← 2 ← 3    4→5
     * ...
     * 
     * TODO: 实现迭代反转算法
     */
    ListNode* reverseList(ListNode* head) {
        // TODO: 实现你的解法
        
        // 提示：三指针模式
        // ListNode* prev = nullptr;
        // ListNode* curr = head;
        // ListNode* next = nullptr;
        
        // 思考要点：
        // 1. 循环条件是什么？
        // 2. 如何保存下一个节点避免断裂？
        // 3. 如何改变当前节点的指向？
        // 4. 如何更新三个指针？
        // 5. 最终返回什么？
        
        ListNode* pre = nullptr;
        ListNode* curr = head;
        while(curr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre; // 替换为你的实现
    }
    
    /**
     * 方法2: 递归实现 (挑战版本)
     * 
     * 递归思路:
     * 1. 递归反转从head->next开始的子链表
     * 2. 将head节点连接到反转后的链表尾部
     * 3. 返回新的头节点
     * 
     * 递归关系:
     * reverseList([1,2,3,4,5]) = 将1连到reverseList([2,3,4,5])的尾部
     * 
     * TODO: 如果熟练掌握迭代版本后，可以尝试递归实现
     */
    ListNode* reverseListRecursive(ListNode* head) {
        // TODO: 实现递归版本 (可选挑战)
        
        // 提示：递归框架
        // 1. 边界条件：head为空或只有一个节点
        // 2. 递归调用：反转子链表
        // 3. 连接操作：将当前节点连到反转链表尾部
        // 4. 返回新头节点
        
        if(!head || !head->next) return head;
        ListNode* newHead = reverseListRecursive(head->next);
        head->next->next = head; // head的下一个节点指向自己
        head->next = nullptr; // 如果不设置为null，则head会指向head->next，成环了

        return newHead; // 替换为你的实现
        /*
        helper(5) 返回 5
        helper(4) 执行: 5->next = 4, 4->next = nullptr, 返回 5
        helper(3) 执行: 4->next = 3, 3->next = nullptr, 返回 5
        helper(2) 执行: 3->next = 2, 2->next = nullptr, 返回 5
        helper(1) 执行: 2->next = 1, 1->next = nullptr, 返回 5
        */
        /*
        如果不进行node->next = nullptr;
        helper(5) 返回 5
        helper(4) 执行: 5->next = 4, 返回 5  // 4->next 仍然是 5！
        helper(3) 执行: 4->next = 3, 返回 5  // 3->next 仍然是 4！
        helper(2) 执行: 3->next = 2, 返回 5  // 2->next 仍然是 3！
        helper(1) 执行: 2->next = 1, 返回 5  // 1->next 仍然是 2！
        */
    }
};

/**
 * 扩展思考: 相关链表操作
 * 
 * 掌握206题后可以尝试的相关题目：
 * 1. 92. 反转链表II (反转指定区间)
 * 2. 24. 两两交换链表中的节点
 * 3. 25. K个一组翻转链表
 * 4. 234. 回文链表 (结合反转判断回文)
 */

// 测试用例和工具函数
class TestRunner {
public:
    // 根据数组创建链表
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
    
    // 打印链表
    void printLinkedList(ListNode* head, const string& prefix = "") {
        cout << prefix;
        ListNode* curr = head;
        
        if (!curr) {
            cout << "空链表" << endl;
            return;
        }
        
        while (curr) {
            cout << curr->val;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> null" << endl;
    }
    
    // 将链表转换为数组用于验证
    vector<int> linkedListToVector(ListNode* head) {
        vector<int> result;
        ListNode* curr = head;
        
        while (curr) {
            result.push_back(curr->val);
            curr = curr->next;
        }
        
        return result;
    }
    
    // 验证反转是否正确
    bool verifyReverse(vector<int>& original, ListNode* reversed) {
        vector<int> reversedVec = linkedListToVector(reversed);
        
        if (original.size() != reversedVec.size()) return false;
        
        for (int i = 0; i < original.size(); i++) {
            if (original[i] != reversedVec[original.size() - 1 - i]) {
                return false;
            }
        }
        
        return true;
    }
    
    // 创建测试用例1: [1,2,3,4,5]
    vector<int> createTestCase1() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例2: [1,2]
    vector<int> createTestCase2() {
        return {1, 2};
    }
    
    // 创建测试用例3: []
    vector<int> createTestCase3() {
        return {};
    }
    
    // 创建测试用例4: [1]
    vector<int> createTestCase4() {
        return {1};
    }
    
    // 创建测试用例5: [1,2,3,4,5,6,7,8,9,10]
    vector<int> createTestCase5() {
        return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 206. 反转链表测试 ===" << endl;
        
        // 测试用例1: 标准情况
        cout << "\n测试用例1: 标准5节点链表 [1,2,3,4,5]" << endl;
        vector<int> test1 = createTestCase1();
        ListNode* list1 = createLinkedList(test1);
        printLinkedList(list1, "原链表: ");
        
        ListNode* result1 = solution.reverseList(list1);
        printLinkedList(result1, "反转后: ");
        cout << "验证结果: " << (verifyReverse(test1, result1) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例2: 简单情况
        cout << "\n测试用例2: 简单2节点链表 [1,2]" << endl;
        vector<int> test2 = createTestCase2();
        ListNode* list2 = createLinkedList(test2);
        printLinkedList(list2, "原链表: ");
        
        ListNode* result2 = solution.reverseList(list2);
        printLinkedList(result2, "反转后: ");
        cout << "验证结果: " << (verifyReverse(test2, result2) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例3: 边界情况 - 空链表
        cout << "\n测试用例3: 空链表 []" << endl;
        vector<int> test3 = createTestCase3();
        ListNode* list3 = createLinkedList(test3);
        printLinkedList(list3, "原链表: ");
        
        ListNode* result3 = solution.reverseList(list3);
        printLinkedList(result3, "反转后: ");
        cout << "验证结果: " << (verifyReverse(test3, result3) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例4: 边界情况 - 单节点
        cout << "\n测试用例4: 单节点链表 [1]" << endl;
        vector<int> test4 = createTestCase4();
        ListNode* list4 = createLinkedList(test4);
        printLinkedList(list4, "原链表: ");
        
        ListNode* result4 = solution.reverseList(list4);
        printLinkedList(result4, "反转后: ");
        cout << "验证结果: " << (verifyReverse(test4, result4) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例5: 较长链表
        cout << "\n测试用例5: 长链表 [1,2,3,4,5,6,7,8,9,10]" << endl;
        vector<int> test5 = createTestCase5();
        ListNode* list5 = createLinkedList(test5);
        printLinkedList(list5, "原链表: ");
        
        ListNode* result5 = solution.reverseList(list5);
        printLinkedList(result5, "反转后: ");
        cout << "验证结果: " << (verifyReverse(test5, result5) ? "✓ 正确" : "✗ 错误") << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：反转后的链表是否与原链表完全相反" << endl;
    }
};

int main() {
    TestRunner runner;
    runner.runAllTests();
    return 0;
}

/**
 * 学习重点:
 * 
 * 1. **指针操作的核心技巧**:
 *    - 三指针协调：prev、curr、next的同步移动
 *    - 防止断裂：修改指针前先保存后续节点
 *    - 方向改变：curr->next = prev 实现反向连接
 * 
 * 2. **从二叉树到链表的知识迁移**:
 *    - 指针操作：tree->left/right → list->next
 *    - 结构变换：二叉树翻转 → 链表反转
 *    - 递归思维：树形递归 → 线性递归
 * 
 * 3. **算法模式对比**:
 *    - 迭代法：空间O(1)，逻辑清晰，工程中常用
 *    - 递归法：空间O(n)，代码简洁，理论性强
 * 
 * 4. **边界条件的重要性**:
 *    - 空链表：head == nullptr
 *    - 单节点：head->next == nullptr
 *    - 正常情况：多节点链表的处理
 * 
 * 5. **链表算法的通用技巧**:
 *    - 多指针技术：快慢指针、前后指针
 *    - 虚拟头节点：简化边界处理
 *    - 原地修改：节省空间复杂度
 * 
 * 延伸学习:
 * - 92. 反转链表II（部分反转）
 * - 24. 两两交换链表节点（局部反转）
 * - 25. K个一组翻转链表（分组反转）
 * - 234. 回文链表（反转应用）
 * - 143. 重排链表（反转+合并）
 */