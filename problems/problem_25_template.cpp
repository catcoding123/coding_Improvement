/**
 * 25. K 个一组翻转链表 (Hard)
 * 
 * LeetCode链接: https://leetcode.cn/problems/reverse-nodes-in-k-group/
 * 
 * 题目描述:
 * 给你链表的头节点 head 和一个整数 k ，请你设计一个算法将链表中每 k 个节点一组进行翻转，并返回修改后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 * 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 * 
 * 示例 1:
 * 输入: head = [1,2,3,4,5], k = 2
 * 输出: [2,1,4,3,5]
 * 解释: 第一组[1,2]翻转为[2,1]，第二组[3,4]翻转为[4,3]，剩余[5]保持不变
 * 
 * 示例 2:
 * 输入: head = [1,2,3,4,5], k = 3
 * 输出: [3,2,1,4,5]
 * 解释: 第一组[1,2,3]翻转为[3,2,1]，剩余[4,5]不足k个，保持不变
 * 
 * 示例 3:
 * 输入: head = [1,2,3,4,5,6,7,8], k = 3
 * 输出: [3,2,1,6,5,4,7,8]
 * 
 * 约束条件:
 * - 链表中的节点数目为 n
 * - 1 <= k <= n <= 5000
 * - 0 <= Node.val <= 1000
 * 
 * 算法分析:
 * 这道题完美承接你的206+24题基础，是链表算法的集大成之作：
 * 1. 206题基础：反转整个链表的核心技巧
 * 2. 24题进阶：分组处理的虚拟头节点技巧（k=2的特例）
 * 3. 25题升华：任意k值的通用算法，复合操作的完美融合
 * 4. 算法复合：计数+分组+反转+连接的多技巧协调
 * 
 * 核心洞察:
 * - K组翻转 = 分组识别 + 局部反转 + 连接操作
 * - 关键难点：不足k个节点的处理，连接的正确性
 * - 复合操作：既要会反转，又要会分组，还要会连接
 * 
 * 算法思路对比:
 * 方法1: 计数分组 + 206题反转子链表 + 重新连接
 * 方法2: 递归分治 + 局部处理 + 结果合并
 * 
 * 时间复杂度: O(n) - 每个节点最多被处理常数次
 * 空间复杂度: O(1) 迭代版本 / O(n/k) 递归版本
 * 
 * 知识链接:
 * - 206题反转链表 → 掌握反转的基本操作
 * - 24题两两交换 → 掌握分组处理和虚拟头节点
 * - 25题K组翻转 → 复合技巧的综合应用
 * 
 * 易错点预测:
 * 1. 长度检查：如何准确判断是否有k个节点
 * 2. 边界连接：翻转后的子链表与原链表的正确连接
 * 3. 剩余处理：不足k个的节点保持原序
 * 4. 指针管理：多个辅助指针的协调使用
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
     * 方法1: 迭代分组反转法 (推荐实现)
     * 
     * 核心思路:
     * 1. 使用虚拟头节点简化边界处理
     * 2. 先检查是否有k个节点，不足则停止
     * 3. 反转k个节点的子链表
     * 4. 将反转后的子链表连接到原链表
     * 5. 更新指针，继续下一组
     * 
     * 算法步骤:
     * - 计数检查：确保有k个节点可反转
     * - 局部反转：反转当前k个节点
     * - 连接操作：将反转段与前后部分正确连接
     * 
     * TODO: 实现迭代分组反转算法
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        // TODO: 实现你的解法
        
        // 提示：主要步骤
        // 1. 创建虚拟头节点
        // ListNode* dummy = new ListNode(0);
        // dummy->next = head;
        // ListNode* prevGroupEnd = dummy;
        
        // 2. 主循环：处理每一组
        // while (true) {
        //     检查是否有k个节点
        //    反转这k个节点
        //    连接到原链表
        //    更新指针
        // }
        
        // 思考要点：
        // 1. 如何检查是否有k个节点？
        // 2. 如何反转k个节点的子链表？
        // 3. 反转后如何正确连接前后部分？
        // 4. 如何更新指针继续下一组？
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prevGroupEnd = dummy;

        while(hasKNodes(prevGroupEnd->next,k)) {
            pair<ListNode*, ListNode*> result = reverseKNodes(prevGroupEnd->next, k);
            ListNode* newhead = result.first;
            ListNode* newtail = result.second;
            
            prevGroupEnd->next = newhead;
            prevGroupEnd = newtail;
        }

        return dummy->next; // 替换为你的实现
    }
    
private:
    /**
     * 辅助函数1: 检查从start开始是否有k个节点
     * TODO: 实现节点计数检查
     */
    bool hasKNodes(ListNode* start, int k) {
        // TODO: 实现计数逻辑
        ListNode* curr = start;
        while(curr && k > 0) {
            k--;
            curr = curr->next;
        }
        return k == 0; 
    }
    
    /**
     * 辅助函数2: 反转从start开始的k个节点，返回新的头和尾
     * TODO: 实现k个节点的反转操作
     */
    pair<ListNode*, ListNode*> reverseKNodes(ListNode* start, int k) {
        // TODO: 实现k个节点反转
        // 类似206题的反转操作，但要控制反转k个节点

        if(!start || (k==0)) {
            return {nullptr, nullptr};
        }

        ListNode* pre = nullptr;
        ListNode* startNode = start;
        ListNode* curr = start;
        while(curr && k>0) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
            k--;
        }
        startNode->next = curr;  // 新尾连接到剩余链表

        return {pre, startNode}; // {newHead, newTail}
    }

public:
    /**
     * 方法2: 递归实现 (挑战版本)
     * 
     * 递归思路:
     * 1. 检查当前是否有k个节点
     * 2. 反转当前k个节点
     * 3. 递归处理剩余链表
     * 4. 连接当前翻转段与递归结果
     * 
     * 递归关系:
     * reverseKGroup([1,2,3,4,5], 3) = reverse([1,2,3]) + reverseKGroup([4,5], 3)
     * 
     * TODO: 如果熟练掌握迭代版本后，可以尝试递归实现
     */
    ListNode* reverseKGroupRecursive(ListNode* head, int k) {
        // TODO: 实现递归版本 (可选挑战)
        
        // 提示：递归框架
        // 1. 边界条件：不足k个节点
        // 2. 反转操作：反转当前k个节点
        // 3. 递归调用：处理剩余链表
        // 4. 连接操作：当前段与递归结果连接
        
        return nullptr; // 替换为你的实现
    }
};

/**
 * 扩展思考: K组翻转的变种问题
 * 
 * 掌握25题后可以尝试的相关变种：
 * 1. 每K个节点反转，剩余也反转 (移除"保持原序"限制)
 * 2. 从右往左K个一组反转 (不同的分组方式)
 * 3. 奇数组正序，偶数组反转 (条件反转)
 * 4. 螺旋式K组反转 (复杂模式)
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
    
    // 验证K组翻转是否正确
    bool verifyKGroupReverse(vector<int>& original, ListNode* reversed, int k) {
        vector<int> reversedVec = linkedListToVector(reversed);
        vector<int> expected;
        
        // 构建期望结果：K个一组翻转
        for (int i = 0; i < original.size(); i += k) {
            if (i + k <= original.size()) {
                // 有完整的k个，反转这一组
                for (int j = i + k - 1; j >= i; j--) {
                    expected.push_back(original[j]);
                }
            } else {
                // 不足k个，保持原序
                for (int j = i; j < original.size(); j++) {
                    expected.push_back(original[j]);
                }
            }
        }
        
        return reversedVec == expected;
    }
    
    // 创建测试用例1: [1,2,3,4,5], k=2
    vector<int> createTestCase1() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例2: [1,2,3,4,5], k=3
    vector<int> createTestCase2() {
        return {1, 2, 3, 4, 5};
    }
    
    // 创建测试用例3: [1,2,3,4,5,6,7,8], k=3
    vector<int> createTestCase3() {
        return {1, 2, 3, 4, 5, 6, 7, 8};
    }
    
    // 创建测试用例4: [1], k=1
    vector<int> createTestCase4() {
        return {1};
    }
    
    // 创建测试用例5: [1,2], k=2
    vector<int> createTestCase5() {
        return {1, 2};
    }
    
    // 创建测试用例6: [1,2,3,4,5,6], k=2
    vector<int> createTestCase6() {
        return {1, 2, 3, 4, 5, 6};
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 25. K个一组翻转链表测试 ===" << endl;
        
        // 测试用例1: k=2的情况 (对应24题)
        cout << "\n测试用例1: [1,2,3,4,5], k=2" << endl;
        vector<int> test1 = createTestCase1();
        ListNode* list1 = createLinkedList(test1);
        printLinkedList(list1, "原链表: ");
        
        ListNode* result1 = solution.reverseKGroup(list1, 2);
        printLinkedList(result1, "k=2翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test1, result1, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,4,3,5]" << endl;
        
        // 测试用例2: k=3的情况
        cout << "\n测试用例2: [1,2,3,4,5], k=3" << endl;
        vector<int> test2 = createTestCase2();
        ListNode* list2 = createLinkedList(test2);
        printLinkedList(list2, "原链表: ");
        
        ListNode* result2 = solution.reverseKGroup(list2, 3);
        printLinkedList(result2, "k=3翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test2, result2, 3) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [3,2,1,4,5]" << endl;
        
        // 测试用例3: 较长链表 k=3
        cout << "\n测试用例3: [1,2,3,4,5,6,7,8], k=3" << endl;
        vector<int> test3 = createTestCase3();
        ListNode* list3 = createLinkedList(test3);
        printLinkedList(list3, "原链表: ");
        
        ListNode* result3 = solution.reverseKGroup(list3, 3);
        printLinkedList(result3, "k=3翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test3, result3, 3) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [3,2,1,6,5,4,7,8]" << endl;
        
        // 测试用例4: 边界情况 k=1
        cout << "\n测试用例4: [1], k=1" << endl;
        vector<int> test4 = createTestCase4();
        ListNode* list4 = createLinkedList(test4);
        printLinkedList(list4, "原链表: ");
        
        ListNode* result4 = solution.reverseKGroup(list4, 1);
        printLinkedList(result4, "k=1翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test4, result4, 1) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [1] (k=1不改变)" << endl;
        
        // 测试用例5: 完整分组 k=2
        cout << "\n测试用例5: [1,2], k=2" << endl;
        vector<int> test5 = createTestCase5();
        ListNode* list5 = createLinkedList(test5);
        printLinkedList(list5, "原链表: ");
        
        ListNode* result5 = solution.reverseKGroup(list5, 2);
        printLinkedList(result5, "k=2翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test5, result5, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1]" << endl;
        
        // 测试用例6: 完整分组 k=2
        cout << "\n测试用例6: [1,2,3,4,5,6], k=2" << endl;
        vector<int> test6 = createTestCase6();
        ListNode* list6 = createLinkedList(test6);
        printLinkedList(list6, "原链表: ");
        
        ListNode* result6 = solution.reverseKGroup(list6, 2);
        printLinkedList(result6, "k=2翻转: ");
        cout << "验证结果: " << (verifyKGroupReverse(test6, result6, 2) ? "✓ 正确" : "✗ 错误") << endl;
        cout << "期望: [2,1,4,3,6,5]" << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：K组翻转是否正确处理了完整分组和剩余节点" << endl;
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
 * 1. **复合算法设计**:
 *    - 分组识别：准确判断是否有k个节点
 *    - 局部反转：复用206题的反转技巧
 *    - 连接操作：保证反转段与原链表的正确连接
 *    - 指针管理：多个辅助指针的协调使用
 * 
 * 2. **从24题到25题的技术升华**:
 *    - 24题：固定k=2的特例，四指针协调
 *    - 25题：任意k值的通用算法，复合操作
 *    - 思维进阶：从特例到通用的算法抽象能力
 * 
 * 3. **边界条件的系统处理**:
 *    - 不足k个节点：保持原序，不进行翻转
 *    - k=1的情况：链表保持不变
 *    - 完整分组：所有节点都能被k整除
 *    - 混合情况：部分完整分组+部分剩余节点
 * 
 * 4. **算法复杂度分析**:
 *    - 时间复杂度：O(n) - 每个节点最多被处理常数次
 *    - 空间复杂度：O(1) 迭代版本，O(n/k) 递归版本
 *    - 与206、24题的复杂度对比分析
 * 
 * 5. **链表算法模式的完整建立**:
 *    - 单一操作：206题整体反转
 *    - 固定分组：24题两两交换  
 *    - 通用分组：25题K组翻转
 *    - 模式认知：从特殊到一般的算法设计思维
 * 
 * 6. **辅助函数的设计思想**:
 *    - hasKNodes(): 计数检查，分离关注点
 *    - reverseKNodes(): 局部反转，模块化设计
 *    - 函数分解：复杂问题的模块化解决方案
 * 
 * 延伸学习:
 * - 92. 反转链表II（指定区间反转）
 * - 61. 旋转链表（整体移动操作）
 * - 328. 奇偶链表（按规则分组）
 * - 143. 重排链表（复杂重组模式）
 * 
 * 关键理解:
 * 这道题是链表算法的集大成之作，成功掌握后你将具备：
 * - 复合算法的设计能力
 * - 复杂边界条件的处理能力  
 * - 模块化编程的思维方式
 * - 从特例到通用的抽象能力
 */