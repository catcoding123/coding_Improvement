/**
 * 92. 反转链表 II (Medium)
 * 
 * LeetCode链接: https://leetcode.cn/problems/reverse-linked-list-ii/
 * 
 * 题目描述:
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right。
 * 请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 * 
 * 示例 1:
 * 输入: head = [1,2,3,4,5], left = 2, right = 4
 * 输出: [1,4,3,2,5]
 * 解释: 位置2到4的节点[2,3,4]被反转为[4,3,2]
 * 
 * 示例 2:
 * 输入: head = [5], left = 1, right = 1
 * 输出: [5]
 * 解释: 只有一个节点，反转自己
 * 
 * 示例 3:
 * 输入: head = [3,5], left = 1, right = 2
 * 输出: [5,3]
 * 解释: 反转整个链表
 * 
 * 约束条件:
 * - 链表中节点数目为 n
 * - 1 <= n <= 500
 * - -500 <= Node.val <= 500
 * - 1 <= left <= right <= n
 * 
 * 进阶要求:
 * 你可以使用一趟扫描完成反转吗？
 * 
 * 算法分析:
 * 这道题是你已掌握技巧的完美融合，体现了算法技能的复合应用：
 * 1. 206题基础：反转整个链表的核心三指针技巧
 * 2. 25题进阶：模块化设计思想，局部处理+连接管理
 * 3. 92题升华：精确区间控制，定位+反转+连接的复合操作
 * 4. 边界掌握：1-based索引的准确处理，虚拟头节点的巧妙运用
 * 
 * 核心洞察:
 * - 区间反转 = 精确定位 + 局部反转 + 前后连接
 * - 关键难点：区间边界的准确识别，连接的完整性保证
 * - 技巧融合：既要有206的反转技巧，又要有25的连接管理
 * 
 * 算法思路对比:
 * 方法1: 定位区间 + 原地反转 + 重新连接 (一趟扫描)
 * 方法2: 递归分治 + 区间处理 + 结果合并
 * 
 * 时间复杂度: O(n) - 一趟扫描完成
 * 空间复杂度: O(1) 迭代版本 / O(n) 递归版本
 * 
 * 知识链接:
 * - 206题反转链表 → 掌握三指针反转的基本操作
 * - 25题K组翻转 → 掌握模块化设计和连接管理
 * - 92题区间反转 → 精确定位+局部反转的复合技巧
 * 
 * 易错点预测:
 * 1. 索引计算：1-based vs 0-based的转换处理
 * 2. 边界定位：准确找到反转区间的前驱和后继
 * 3. 连接顺序：反转后的重新连接顺序
 * 4. 特殊情况：left=1时的头节点处理
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
     * 方法1: 三段式连接法 (推荐实现)
     * 
     * 核心思路:
     * 1. 使用虚拟头节点简化边界处理
     * 2. 定位并保存关键边界节点（前驱和后继）
     * 3. 断开连接，对指定区间执行反转（复用206题技巧）
     * 4. 重新连接三段：前段 + 反转段 + 后段
     * 
     * 算法步骤:
     * - 边界定位：找到left前驱和right后继节点
     * - 安全断开：断开反转段与后续的连接
     * - 局部反转：使用206题技巧反转[left,right]区间
     * - 三段重连：前段→反转段头，反转段尾→后段
     * 
     * TODO: 实现三段式区间反转算法
     */
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // TODO: 实现你的解法
        
        // 提示：主要步骤
        
        
        // 思考要点：
        // 1. 如何准确定位left前驱和right后继？
        // 2. 为什么要先断开连接再反转？
        // 3. 如何复用206题的反转技巧？
        // 4. 三段重连的顺序有什么要求？
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* startPre = findPrevNode(dummy, left);
        ListNode* startNode = startPre->next;
        ListNode* endNode = findTargetNode(dummy,right);
        ListNode* nextNode = endNode->next;

        
        endNode->next = nullptr; // 一定要断开

        auto [newHead, newTail] = reverseSegment(startNode);

        startPre->next = newHead;
        newTail->next = nextNode;
        return dummy->next; // 返回可能变化的头节点
    }
    
private:
    /**
     * 辅助函数1: 定位前驱节点
     * 
     * 找到第pos个节点的前驱节点（1-based）
     * 例如：findPrevNode(dummy, 3) 返回第2个节点
     * 
     * TODO: 实现定位前驱节点的功能
     */
    ListNode* findPrevNode(ListNode* dummy, int pos) {
        // TODO: 实现定位逻辑
        ListNode * node = dummy;
        for(int i=0; i<pos-1;i++) {
            node = node->next;
        }
        return node; // 替换为你的实现
    }
    
    /**
     * 辅助函数2: 定位目标节点
     * 
     * 找到第pos个节点（1-based）
     * 例如：findTargetNode(dummy, 3) 返回第3个节点
     * 
     * TODO: 实现定位目标节点的功能
     */
    ListNode* findTargetNode(ListNode* dummy, int pos) {
        // TODO: 实现定位逻辑
        
        // 提示：从dummy开始，移动pos步
        // ListNode* node = dummy;
        // for (int i = 0; i < pos; i++) {
        //     node = node->next;
        // }
        // return node;
        ListNode* node = dummy;
        for(int i=0; i< pos; i++) {
            node = node->next;
        }
        return node; // 替换为你的实现
    }
    
    /**
     * 辅助函数3: 反转链表段
     * 
     * 反转从start开始的链表段，返回新的头和尾
     * 复用206题的经典三指针反转技巧
     * 
     * TODO: 实现链表段反转功能
     */
    pair<ListNode*, ListNode*> reverseSegment(ListNode* start) {
        // TODO: 实现反转逻辑
        
        // 提示：使用206题的三指针反转技巧
        // ListNode* prev = nullptr;
        // ListNode* curr = start;
        // ListNode* originalStart = start;  // 保存原始头，将成为新的尾
        
        // while (curr) {
        //     ListNode* next = curr->next;
        //     curr->next = prev;
        //     prev = curr;
        //     curr = next;
        // }
        
        // return {prev, originalStart}; // {新头, 新尾}
        ListNode* pre = nullptr;
        ListNode* curr = start;
        while(curr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        
        return {pre, start}; // {新头, 新尾}
    }

public:
    /**
     * 方法2: 头插法实现 (可选挑战)
     * 
     * 核心思想:
     * 将区间内的节点逐个"头插"到前驱节点后面
     * 避免了三段式的断开和重连，在一趟扫描中完成
     * 
     * 算法步骤:
     * 1. 定位到left-1位置的前驱节点prev
     * 2. 将left+1到right的节点逐个插入到prev后面
     * 3. 头插的性质自然形成反转效果
     * 
     * TODO: 如果熟练掌握三段式后，可以尝试头插法实现
     */
    ListNode* reverseBetweenHeadInsert(ListNode* head, int left, int right) {
        // TODO: 实现头插法版本 (可选挑战)
        
        // 提示：头插法核心操作
        // 1. 定位前驱：找到left-1位置的节点prev
        // 2. 头插循环：将left+1到right的节点逐个头插
        //    - curr->next = next->next;      // 跳过即将移动的节点
        //    - next->next = prev->next;      // 新节点指向当前头部
        //    - prev->next = next;            // 更新头部为新节点
        // 3. 自然反转：头插性质形成反转效果
        
        return nullptr; // 替换为你的实现
    }
};

/**
 * 扩展思考: 区间反转的变种问题
 * 
 * 掌握92题后可以尝试的相关变种：
 * 1. 多个区间反转 (给定多个[left,right]区间)
 * 2. 条件反转 (满足特定条件才反转)
 * 3. 循环反转 (在环形链表中的区间反转)
 * 4. 交替反转 (奇数区间正序，偶数区间反转)
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
    
    // 验证区间反转是否正确
    bool verifyReverseRange(vector<int>& original, ListNode* reversed, int left, int right) {
        vector<int> reversedVec = linkedListToVector(reversed);
        vector<int> expected = original;
        
        // 在expected中反转[left-1, right-1]区间 (转换为0-based)
        if (left <= right && left >= 1 && right <= expected.size()) {
            reverse(expected.begin() + left - 1, expected.begin() + right);
        }
        
        return reversedVec == expected;
    }
    
    // 创建测试用例1: [1,2,3,4,5], left=2, right=4
    vector<int> createTestCase1() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例2: [5], left=1, right=1
    vector<int> createTestCase2() {
        return {5};
    }
    
    // 创建测试用例3: [3,5], left=1, right=2
    vector<int> createTestCase3() {
        return {3, 5};
    }
    
    // 创建测试用例4: [1,2,3,4,5], left=1, right=5
    vector<int> createTestCase4() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例5: [1,2,3], left=1, right=2
    vector<int> createTestCase5() {
        return {1, 2, 3};
    }
    
    // 创建测试用例6: [1,2,3], left=2, right=3
    vector<int> createTestCase6() {
        return {1, 2, 3};
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 92. 反转链表II测试 ===" << endl;
        
        // 测试用例1: 标准区间反转
        cout << "\n测试用例1: [1,2,3,4,5], left=2, right=4" << endl;
        vector<int> test1 = createTestCase1();
        ListNode* list1 = createLinkedList(test1);
        printLinkedList(list1, "原链表: ");
        
        ListNode* result1 = solution.reverseBetween(list1, 2, 4);
        printLinkedList(result1, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test1, result1, 2, 4) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [1,4,3,2,5]" << endl;
        
        // 测试用例2: 单节点反转
        cout << "\n测试用例2: [5], left=1, right=1" << endl;
        vector<int> test2 = createTestCase2();
        ListNode* list2 = createLinkedList(test2);
        printLinkedList(list2, "原链表: ");
        
        ListNode* result2 = solution.reverseBetween(list2, 1, 1);
        printLinkedList(result2, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test2, result2, 1, 1) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [5]" << endl;
        
        // 测试用例3: 整个链表反转
        cout << "\n测试用例3: [3,5], left=1, right=2" << endl;
        vector<int> test3 = createTestCase3();
        ListNode* list3 = createLinkedList(test3);
        printLinkedList(list3, "原链表: ");
        
        ListNode* result3 = solution.reverseBetween(list3, 1, 2);
        printLinkedList(result3, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test3, result3, 1, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [5,3]" << endl;
        
        // 测试用例4: 反转整个链表
        cout << "\n测试用例4: [1,2,3,4,5], left=1, right=5" << endl;
        vector<int> test4 = createTestCase4();
        ListNode* list4 = createLinkedList(test4);
        printLinkedList(list4, "原链表: ");
        
        ListNode* result4 = solution.reverseBetween(list4, 1, 5);
        printLinkedList(result4, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test4, result4, 1, 5) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [5,4,3,2,1]" << endl;
        
        // 测试用例5: 从头开始的部分反转
        cout << "\n测试用例5: [1,2,3], left=1, right=2" << endl;
        vector<int> test5 = createTestCase5();
        ListNode* list5 = createLinkedList(test5);
        printLinkedList(list5, "原链表: ");
        
        ListNode* result5 = solution.reverseBetween(list5, 1, 2);
        printLinkedList(result5, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test5, result5, 1, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,3]" << endl;
        
        // 测试用例6: 到尾部的部分反转
        cout << "\n测试用例6: [1,2,3], left=2, right=3" << endl;
        vector<int> test6 = createTestCase6();
        ListNode* list6 = createLinkedList(test6);
        printLinkedList(list6, "原链表: ");
        
        ListNode* result6 = solution.reverseBetween(list6, 2, 3);
        printLinkedList(result6, "反转后: ");
        cout << "验证结果: " << (verifyReverseRange(test6, result6, 2, 3) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [1,3,2]" << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：区间反转是否正确处理了边界和连接" << endl;
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
 * 1. **三段式连接法的核心理念**:
 *    - 边界定位：精确找到前驱和后继节点
 *    - 安全断开：避免反转时影响后续节点
 *    - 局部反转：复用206题的成熟技巧
 *    - 三段重连：前段→反转段→后段的完整连接
 * 
 * 2. **从206到25到92的技术融合**:
 *    - 206题：整体反转的三指针技巧
 *    - 25题：模块化设计和连接管理思想
 *    - 92题：精确区间控制+复用已有技巧
 *    - 技能复用：将分散的技巧有机整合
 * 
 * 3. **模块化设计的优势**:
 *    - findPrevNode(): 专注于前驱定位
 *    - findTargetNode(): 专注于目标定位  
 *    - reverseSegment(): 专注于局部反转
 *    - 主函数: 专注于整体流程协调
 * 
 * 4. **虚拟头节点的边界简化**:
 *    - 统一处理left=1的特殊情况
 *    - 避免头节点变化的复杂逻辑
 *    - 让算法逻辑更加通用和清晰
 * 
 * 5. **连接完整性的系统保证**:
 *    - 反转前：保存所有关键边界节点
 *    - 反转中：在隔离环境中安全操作
 *    - 反转后：按正确顺序重建连接关系
 * 
 * 6. **算法复用能力的体现**:
 *    - 206题技巧：直接用于reverseSegment()
 *    - 25题思想：模块化设计和连接管理
 *    - 边界处理：1-based索引的精确控制
 * 
 * 7. **两种实现方式的对比**:
 *    - 三段式：清晰模块化，易于理解和扩展
 *    - 头插法：紧凑高效，一趟扫描完成
 *    - 选择标准：根据场景需求选择合适方案
 * 
 * 延伸学习:
 * - 25. K个一组翻转链表（分组反转的通用版本）
 * - 206. 反转链表（基础反转技巧）
 * - 61. 旋转链表（整体移动操作）
 * - 143. 重排链表（复杂重组模式）
 * 
 * 关键理解:
 * 92题是区间操作的经典题目，成功掌握后你将具备：
 * - 精确区间定位的能力
 * - 局部反转的复合应用技巧
 * - 复杂连接关系的管理能力
 * - 一趟扫描解决复杂问题的效率意识
 */