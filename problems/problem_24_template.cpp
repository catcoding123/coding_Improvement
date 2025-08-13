/**
 * 24. 两两交换链表中的节点 (Medium)
 * 
 * LeetCode链接: https://leetcode.cn/problems/swap-nodes-in-pairs/
 * 
 * 题目描述:
 * 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
 * 你必须在不修改链表节点值的情况下完成本题（即，只能进行节点交换）。
 * 
 * 示例 1:
 * 输入: head = [1,2,3,4]
 * 输出: [2,1,4,3]
 * 解释: 1↔2交换，3↔4交换
 * 
 * 示例 2:
 * 输入: head = []
 * 输出: []
 * 
 * 示例 3:
 * 输入: head = [1]
 * 输出: [1]
 * 
 * 示例 4:
 * 输入: head = [1,2,3,4,5]
 * 输出: [2,1,4,3,5]
 * 
 * 约束条件:
 * - 链表中节点的数目在范围 [0, 100] 内
 * - 0 <= Node.val <= 100
 * 
 * 算法分析:
 * 这道题完美承接你的链表学习，结合206题的指针操作经验：
 * 1. 指针技巧：从206题的三指针 → 24题的四指针协调
 * 2. 局部操作：每次处理两个相邻节点的交换
 * 3. 递归vs迭代：两种经典实现方式的对比
 * 4. 虚拟头节点：简化边界处理的重要技巧
 * 
 * 核心洞察:
 * - 两两交换 = 局部反转 + 连接操作
 * - 原链表: 1→2→3→4 交换后: 2→1→4→3
 * - 关键：保持交换对与剩余链表的正确连接
 * 
 * 时间复杂度: O(n) - 遍历一次链表
 * 空间复杂度: O(1) 迭代版本 / O(n) 递归版本
 * 
 * 知识衔接:
 * - 206题反转链表 → 掌握指针操作基础
 * - 24题两两交换 → 局部反转的应用
 * - 递归思维 → 大问题分解为子问题
 * 
 * 易错点预测:
 * 1. 指针连接：交换后与前后节点的正确连接
 * 2. 边界处理：空链表、单节点、奇数个节点
 * 3. 递归终止：正确的边界条件设置
 * 4. 虚拟头节点：统一处理头节点交换的情况
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
     * 方法1: 迭代四指针法 (推荐实现)
     * 
     * 核心思路:
     * 1. 使用虚拟头节点简化边界处理
     * 2. 维护四个指针：prev(前驱)、first(第一个)、second(第二个)、next(后继)
     * 3. 每次交换一对节点，更新指针位置
     * 
     * 指针交换过程:
     * 原始: prev → first → second → next → ...
     * 交换: prev → second → first → next → ...
     * 
     * TODO: 实现迭代交换算法
     */
    ListNode* swapPairs(ListNode* head) {
        // TODO: 实现你的解法
        
        // 提示：四指针模式
        // ListNode* dummy = new ListNode(0);
        // dummy->next = head;
        // ListNode* prev = dummy;
        
        // 思考要点：
        // 1. 循环条件是什么？
        // 2. 如何识别需要交换的两个节点？
        // 3. 交换的具体步骤是什么？
        // 4. 如何更新prev指针继续下一对交换？
        // 5. 如何处理奇数个节点的情况？
        
        // pre -> first -> second ->next =>
        // pre -> second -> first -> next
        // 其实只需要维护pre就行，因为first 和second可以由其推导
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        while(pre->next && pre->next->next) {
            ListNode* first = pre->next;
            ListNode* second = pre->next->next;

            ListNode* next = second->next;
            second->next = first;
            first->next = next;
            pre->next = second;

            pre = first; // 因为first已经交换到末尾了
        }
        ListNode* newHead = dummy->next;
        delete dummy;

        return newHead;
    }
    
    /**
     * 方法2: 递归实现 (挑战版本)
     * 
     * 递归思路:
     * 1. 递归交换从第3个节点开始的子链表
     * 2. 交换当前的前两个节点
     * 3. 连接交换后的节点对与递归结果
     * 
     * 递归关系:
     * swapPairs([1,2,3,4]) = [2,1] + swapPairs([3,4])
     * 
     * TODO: 如果熟练掌握迭代版本后，可以尝试递归实现
     */
    ListNode* swapPairsRecursive(ListNode* head) {
        // TODO: 实现递归版本 (可选挑战)
        
        // 提示：递归框架
        // 1. 边界条件：空节点或单节点
        // 2. 递归调用：交换后续节点对
        // 3. 局部交换：交换当前两个节点
        // 4. 返回新头节

        if(!head || !head->next) return head;

        ListNode* next = head->next;
        ListNode* nextNode = swapPairsRecursive(head->next->next);
        next->next = head;
        head->next = nextNode;
        return next;
    }
};

/**
 * 扩展思考: 相关链表操作
 * 
 * 掌握24题后可以尝试的相关题目：
 * 1. 25. K个一组翻转链表 (24题的推广)
 * 2. 92. 反转链表II (部分反转)
 * 3. 143. 重排链表 (复杂链表重组)
 * 4. 61. 旋转链表 (整体移动)
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
    
    // 验证交换是否正确
    bool verifySwap(vector<int>& original, ListNode* swapped) {
        vector<int> swappedVec = linkedListToVector(swapped);
        vector<int> expected;
        
        // 构建期望结果：两两交换
        for (int i = 0; i < original.size(); i += 2) {
            if (i + 1 < original.size()) {
                // 有配对，交换
                expected.push_back(original[i + 1]);
                expected.push_back(original[i]);
            } else {
                // 无配对，保持原样
                expected.push_back(original[i]);
            }
        }
        
        return swappedVec == expected;
    }
    
    // 创建测试用例1: [1,2,3,4]
    vector<int> createTestCase1() {
        return {1, 2, 3, 4};
    }
    
    // 创建测试用例2: []
    vector<int> createTestCase2() {
        return {};
    }
    
    // 创建测试用例3: [1]
    vector<int> createTestCase3() {
        return {1};
    }
    
    // 创建测试用例4: [1,2,3,4,5]
    vector<int> createTestCase4() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例5: [1,2]
    vector<int> createTestCase5() {
        return {1, 2};
    }
    
    // 创建测试用例6: [1,2,3,4,5,6]
    vector<int> createTestCase6() {
        return {1, 2, 3, 4, 5, 6};
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 24. 两两交换链表中的节点测试 ===" << endl;
        
        // 测试用例1: 标准偶数节点
        cout << "\n测试用例1: 标准4节点链表 [1,2,3,4]" << endl;
        vector<int> test1 = createTestCase1();
        ListNode* list1 = createLinkedList(test1);
        printLinkedList(list1, "原链表: ");
        
        ListNode* result1 = solution.swapPairs(list1);
        printLinkedList(result1, "交换后: ");
        cout << "验证结果: " << (verifySwap(test1, result1) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,4,3]" << endl;
        
        // 测试用例2: 边界情况 - 空链表
        cout << "\n测试用例2: 空链表 []" << endl;
        vector<int> test2 = createTestCase2();
        ListNode* list2 = createLinkedList(test2);
        printLinkedList(list2, "原链表: ");
        
        ListNode* result2 = solution.swapPairs(list2);
        printLinkedList(result2, "交换后: ");
        cout << "验证结果: " << (verifySwap(test2, result2) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例3: 边界情况 - 单节点
        cout << "\n测试用例3: 单节点链表 [1]" << endl;
        vector<int> test3 = createTestCase3();
        ListNode* list3 = createLinkedList(test3);
        printLinkedList(list3, "原链表: ");
        
        ListNode* result3 = solution.swapPairs(list3);
        printLinkedList(result3, "交换后: ");
        cout << "验证结果: " << (verifySwap(test3, result3) ? "✓ 正确" : "✗ 错误") << endl;
        
        // 测试用例4: 奇数节点
        cout << "\n测试用例4: 奇数5节点链表 [1,2,3,4,5]" << endl;
        vector<int> test4 = createTestCase4();
        ListNode* list4 = createLinkedList(test4);
        printLinkedList(list4, "原链表: ");
        
        ListNode* result4 = solution.swapPairs(list4);
        printLinkedList(result4, "交换后: ");
        cout << "验证结果: " << (verifySwap(test4, result4) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,4,3,5]" << endl;
        
        // 测试用例5: 简单两节点
        cout << "\n测试用例5: 简单2节点链表 [1,2]" << endl;
        vector<int> test5 = createTestCase5();
        ListNode* list5 = createLinkedList(test5);
        printLinkedList(list5, "原链表: ");
        
        ListNode* result5 = solution.swapPairs(list5);
        printLinkedList(result5, "交换后: ");
        cout << "验证结果: " << (verifySwap(test5, result5) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1]" << endl;
        
        // 测试用例6: 偶数长链表
        cout << "\n测试用例6: 偶数6节点链表 [1,2,3,4,5,6]" << endl;
        vector<int> test6 = createTestCase6();
        ListNode* list6 = createLinkedList(test6);
        printLinkedList(list6, "原链表: ");
        
        ListNode* result6 = solution.swapPairs(list6);
        printLinkedList(result6, "交换后: ");
        cout << "验证结果: " << (verifySwap(test6, result6) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,4,3,6,5]" << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：交换后的链表是否正确保持了两两配对交换的模式" << endl;
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
 * 1. **四指针协调技巧**:
 *    - prev：前驱节点，连接交换后的节点对
 *    - first：第一个要交换的节点
 *    - second：第二个要交换的节点  
 *    - next：保存后续链表，防止丢失
 * 
 * 2. **虚拟头节点的威力**:
 *    - 统一处理：头节点交换不再是特殊情况
 *    - 简化逻辑：避免复杂的边界判断
 *    - 通用模式：很多链表题的标准技巧
 * 
 * 3. **从206题到24题的知识升华**:
 *    - 206题：整体反转 → 三指针滑动
 *    - 24题：局部反转 → 四指针协调 + 虚拟头节点
 *    - 思维进阶：从线性操作到分组操作
 * 
 * 4. **递归vs迭代的设计思考**:
 *    - 迭代法：空间O(1)，逻辑清晰，工程实用
 *    - 递归法：空间O(n)，代码简洁，思维自然
 *    - 选择策略：根据空间要求和代码可读性权衡
 * 
 * 5. **边界条件的系统处理**:
 *    - 空链表：直接返回
 *    - 单节点：无法配对，保持原样
 *    - 奇数节点：最后一个节点不参与交换
 *    - 偶数节点：所有节点都能完美配对
 * 
 * 6. **算法模式的推广应用**:
 *    - 两两交换 → K个一组交换 (25题)
 *    - 局部反转 → 区间反转 (92题)
 *    - 分组处理 → 链表重组 (143题)
 * 
 * 延伸学习:
 * - 25. K个一组翻转链表（推广到K个节点）
 * - 92. 反转链表II（指定区间反转）
 * - 143. 重排链表（复杂的节点重组）
 * - 328. 奇偶链表（按奇偶位置分组）
 */