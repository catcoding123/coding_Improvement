/**
 * 19. 删除链表的倒数第 N 个结点 (Medium)
 * 
 * LeetCode链接: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 * 
 * 题目描述:
 * 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 * 
 * 示例 1:
 * 输入: head = [1,2,3,4,5], n = 2
 * 输出: [1,2,3,5]
 * 解释: 删除倒数第2个节点4，结果为[1,2,3,5]
 * 
 * 示例 2:
 * 输入: head = [1], n = 1
 * 输出: []
 * 解释: 删除唯一节点，结果为空链表
 * 
 * 示例 3:
 * 输入: head = [1,2], n = 1
 * 输出: [1]
 * 解释: 删除倒数第1个节点2，结果为[1]
 * 
 * 示例 4:
 * 输入: head = [1,2], n = 2
 * 输出: [2]
 * 解释: 删除倒数第2个节点1(头节点)，结果为[2]
 * 
 * 约束条件:
 * - 链表中结点的数目为 sz
 * - 1 <= sz <= 30
 * - 0 <= Node.val <= 100
 * - 1 <= n <= sz
 * 
 * 进阶要求: 你能尝试使用一趟扫描实现吗？
 * 
 * 算法分析:
 * 这是一道经典的双指针技巧题，完美承接链表基础操作：
 * 1. 核心难点：如何在一次遍历中定位倒数第N个节点
 * 2. 关键洞察：使用快慢指针维持固定间距
 * 3. 边界处理：删除头节点的特殊情况需要虚拟头节点
 * 4. 技巧升华：从正数索引到倒数索引的思维转换
 * 
 * 核心思路:
 * - 双指针间距控制：快指针领先慢指针N+1步
 * - 一次遍历删除：当快指针到达末尾时，慢指针指向待删除节点的前驱
 * - 虚拟头节点：统一处理删除头节点和非头节点的情况
 * 
 * 算法思路对比:
 * 方法1: 双指针一次遍历 (推荐) - O(L)时间，O(1)空间，优雅高效
 * 方法2: 两次遍历 - O(L)时间，O(1)空间，思路直观但效率略低
 * 方法3: 递归回溯 - O(L)时间，O(L)空间，递归思维练习
 * 
 * 时间复杂度: O(L) - L为链表长度，最多遍历一次
 * 空间复杂度: O(1) - 仅使用常数额外空间
 * 
 * 与其他链表题目的联系:
 * - 206题反转链表 → 掌握基础指针操作
 * - 142题环形链表 → 理解快慢指针技巧
 * - 19题删除节点 → 双指针+间距控制的综合应用
 * 
 * 易错点预测:
 * 1. 间距计算：快指针应该领先N+1步还是N步？
 * 2. 边界处理：删除头节点时的特殊逻辑
 * 3. 指针更新：删除操作的正确步骤
 * 4. 内存管理：删除节点后的内存释放
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
     * 方法1: 双指针一次遍历法 (推荐实现)
     * 
     * 核心思路:
     * 1. 使用虚拟头节点简化边界处理
     * 2. 快指针先走N+1步，建立与慢指针的间距
     * 3. 快慢指针同步移动，直到快指针到达末尾
     * 4. 此时慢指针指向待删除节点的前驱
     * 5. 执行删除操作并处理内存
     * 
     * 关键洞察:
     * - 间距设计：N+1的间距确保慢指针指向前驱节点
     * - 前驱重要性：删除操作需要修改前驱节点的next指针
     * - 虚拟头节点：统一处理删除头节点的特殊情况
     * 
     * TODO: 实现双指针一次遍历算法
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // TODO: 实现你的解法
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = dummy;
        ListNode* slow = dummy;

        for(int i=0; i<=n; i++) {
            fast = fast->next;
        }

        while(fast) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* toDelete = slow->next;
        slow->next = toDelete->next;
        delete toDelete;

        ListNode* result = dummy->next; // 可能会有的错误：不能直接返回head，因为head有可能被删除了
        delete dummy;
        return result;

        

        // 思考要点：
        // 1. 为什么快指针要先走N+1步而不是N步？
        // 2. 如何理解"倒数第N个"的索引关系？
        // 3. 虚拟头节点如何简化删除头节点的处理？
        // 4. 删除操作的完整步骤是什么？
        
    }
    
    /**
     * 方法2: 两次遍历法 (对比实现)
     * 
     * 思路更加直观:
     * 1. 第一次遍历计算链表总长度L
     * 2. 第二次遍历找到第(L-N)个节点(倒数第N个的前驱)
     * 3. 执行删除操作
     * 
     * 优点：思路直观，容易理解
     * 缺点：需要两次遍历，效率略低
     * 
     * TODO: 如果想练习不同思路，可以实现这个版本
     */
    ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
        // TODO: 实现两次遍历版本 (可选)
        
        // 提示：算法步骤
        // 1. 计算链表长度
        // 2. 找到第(length-n)个节点
        // 3. 执行删除操作
        
        return nullptr; // 替换为你的实现
    }
    
    /**
     * 方法3: 递归回溯法 (挑战实现)
     * 
     * 递归思路:
     * 1. 递归到链表末尾，然后回溯计数
     * 2. 在回溯过程中记录当前是倒数第几个节点
     * 3. 当计数等于N时，删除当前节点
     * 
     * 特点：递归思维，但空间复杂度O(L)
     * 
     * TODO: 如果熟练掌握递归，可以尝试这个挑战版本
     */
    ListNode* removeNthFromEndRecursive(ListNode* head, int n) {
        // TODO: 实现递归版本 (可选挑战)
        
        // 提示：递归框架
        // 1. 设计辅助函数返回倒数位置
        // 2. 在回溯过程中处理删除逻辑
        // 3. 注意递归边界和删除时机
        
        return nullptr; // 替换为你的实现
    }
};

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
    
    // 验证删除结果是否正确
    bool verifyDeletion(vector<int>& original, ListNode* result, int n) {
        // 计算期望结果
        vector<int> expected;
        int deleteIndex = original.size() - n;  // 倒数第n个的正数索引
        
        for (int i = 0; i < original.size(); i++) {
            if (i != deleteIndex) {
                expected.push_back(original[i]);
            }
        }
        
        // 比较实际结果
        vector<int> actual = linkedListToVector(result);
        return actual == expected;
    }
    
    // 创建测试用例1: [1,2,3,4,5], n=2
    vector<int> createTestCase1() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例2: [1], n=1
    vector<int> createTestCase2() {
        return {1};
    }
    
    // 创建测试用例3: [1,2], n=1
    vector<int> createTestCase3() {
        return {1, 2};
    }
    
    // 创建测试用例4: [1,2], n=2
    vector<int> createTestCase4() {
        return {1, 2};
    }
    
    // 创建测试用例5: [1,2,3], n=3
    vector<int> createTestCase5() {
        return {1, 2, 3};
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 19. 删除链表的倒数第N个结点测试 ===" << endl;
        
        // 测试用例1: 删除中间节点
        cout << "\n测试用例1: [1,2,3,4,5], n=2 (删除倒数第2个)" << endl;
        vector<int> test1 = createTestCase1();
        ListNode* list1 = createLinkedList(test1);
        printLinkedList(list1, "原链表: ");
        
        ListNode* result1 = solution.removeNthFromEnd(list1, 2);
        printLinkedList(result1, "删除后: ");
        cout << "验证结果: " << (verifyDeletion(test1, result1, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [1,2,3,5]" << endl;
        
        // 测试用例2: 删除唯一节点
        cout << "\n测试用例2: [1], n=1 (删除唯一节点)" << endl;
        vector<int> test2 = createTestCase2();
        ListNode* list2 = createLinkedList(test2);
        printLinkedList(list2, "原链表: ");
        
        ListNode* result2 = solution.removeNthFromEnd(list2, 1);
        printLinkedList(result2, "删除后: ");
        cout << "验证结果: " << (verifyDeletion(test2, result2, 1) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [] (空链表)" << endl;
        
        // 测试用例3: 删除尾节点
        cout << "\n测试用例3: [1,2], n=1 (删除尾节点)" << endl;
        vector<int> test3 = createTestCase3();
        ListNode* list3 = createLinkedList(test3);
        printLinkedList(list3, "原链表: ");
        
        ListNode* result3 = solution.removeNthFromEnd(list3, 1);
        printLinkedList(result3, "删除后: ");
        cout << "验证结果: " << (verifyDeletion(test3, result3, 1) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [1]" << endl;
        
        // 测试用例4: 删除头节点
        cout << "\n测试用例4: [1,2], n=2 (删除头节点)" << endl;
        vector<int> test4 = createTestCase4();
        ListNode* list4 = createLinkedList(test4);
        printLinkedList(list4, "原链表: ");
        
        ListNode* result4 = solution.removeNthFromEnd(list4, 2);
        printLinkedList(result4, "删除后: ");
        cout << "验证结果: " << (verifyDeletion(test4, result4, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2]" << endl;
        
        // 测试用例5: 删除头节点(多节点)
        cout << "\n测试用例5: [1,2,3], n=3 (删除头节点)" << endl;
        vector<int> test5 = createTestCase5();
        ListNode* list5 = createLinkedList(test5);
        printLinkedList(list5, "原链表: ");
        
        ListNode* result5 = solution.removeNthFromEnd(list5, 3);
        printLinkedList(result5, "删除后: ");
        cout << "验证结果: " << (verifyDeletion(test5, result5, 3) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,3]" << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：双指针间距控制和虚拟头节点的作用" << endl;
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
 * 1. **双指针技巧的核心理解**:
 *    - 间距控制：N+1的间距设计保证慢指针指向前驱
 *    - 同步移动：快慢指针的协调移动机制
 *    - 时机把握：快指针到达末尾的判断条件
 *    - 空间效率：O(1)空间复杂度的优雅实现
 * 
 * 2. **删除操作的系统性理解**:
 *    - 前驱定位：删除需要找到待删除节点的前驱
 *    - 指针修改：前驱节点next指针的正确更新
 *    - 内存管理：删除节点后的内存释放
 *    - 边界处理：删除头节点的特殊情况统一化
 * 
 * 3. **虚拟头节点的设计价值**:
 *    - 边界统一：头节点和非头节点的删除逻辑一致化
 *    - 代码简化：避免删除头节点的特殊判断
 *    - 指针安全：确保慢指针总能找到有效的前驱
 *    - 返回处理：通过dummy->next返回新的头节点
 * 
 * 4. **倒数索引的数学理解**:
 *    - 索引转换：倒数第N个 = 正数第(L-N+1)个
 *    - 间距设计：快指针领先N+1步的数学原理
 *    - 边界分析：N的有效范围和边界情况处理
 *    - 一次遍历：如何在单次扫描中完成定位
 * 
 * 5. **算法设计思维的提升**:
 *    - 问题转化：从"倒数定位"到"间距控制"的思维转换
 *    - 空间优化：从两次遍历到一次遍历的效率提升
 *    - 通用模式：双指针+间距控制的算法模式
 *    - 扩展应用：这种技巧在其他链表问题中的应用
 * 
 * 延伸学习:
 * - 61. 旋转链表 (双指针+环形思维)
 * - 143. 重排链表 (综合运用找中点、反转、合并)
 * - 160. 相交链表 (双指针消除长度差)
 * - 234. 回文链表 (双指针+反转的巧妙结合)
 * 
 * 关键理解:
 * 这道题是双指针技巧的经典应用，成功掌握后你将具备：
 * - 间距控制的精确计算能力
 * - 一次遍历解决定位问题的思维
 * - 虚拟头节点简化边界的设计技巧
 * - 双指针算法模式的深度理解
 */