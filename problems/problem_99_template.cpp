/**
 * 99. 恢复二叉搜索树 (Hard)
 * 
 * LeetCode链接: https://leetcode.cn/problems/recover-binary-search-tree/
 * 
 * 题目描述:
 * 给你二叉搜索树的根节点 root，该树中的恰好两个节点的值被错误地交换。
 * 请在不改变其结构的情况下，恢复这棵树。
 * 
 * 示例 1:
 * 输入: root = [1,3,null,null,2]
 *       1
 *      /
 *     3
 *      \
 *       2
 * 输出: [3,1,null,null,2]
 *       3
 *      /
 *     1
 *      \
 *       2
 * 
 * 示例 2:
 * 输入: root = [3,1,4,null,null,2]
 *       3
 *      / \
 *     1   4
 *        /
 *       2
 * 输出: [2,1,4,null,null,3]
 *       2
 *      / \
 *     1   4
 *        /
 *       3
 * 
 * 约束条件:
 * - 树上节点的数目在范围 [2, 1000] 内
 * - -2^31 <= Node.val <= 2^31 - 1
 * - 恰好有两个节点的值被交换了
 * 
 * 进阶要求:
 * - 使用 O(1) 空间复杂度的解法
 * 
 * 算法分析:
 * 这是BST系列的经典难题，结合了多个重要概念：
 * 1. BST中序遍历的有序性质
 * 2. 错误节点的识别模式
 * 3. 指针交换的实现技巧
 * 4. Morris遍历的O(1)空间优化
 * 
 * 核心思路:
 * - 标准解法: 中序遍历 + 识别逆序对 + 交换节点值 (O(h)空间)
 * - 进阶解法: Morris中序遍历 (O(1)空间)
 * 
 * 时间复杂度: O(n) - 遍历整棵树
 * 空间复杂度: O(h) 递归版本 / O(1) Morris版本
 * 
 * 关键洞察:
 * - 中序遍历中，错误的两个节点会形成逆序对
 * - 情况1: 两个错误节点相邻 -> 一个逆序对
 * - 情况2: 两个错误节点不相邻 -> 两个逆序对
 * 
 * 易错点预测:
 * 1. 逆序对识别逻辑: 相邻vs不相邻的不同处理
 * 2. 指针维护: prev指针的更新时机
 * 3. 边界处理: 只有一个逆序对的情况
 * 4. Morris遍历: 线索的建立和删除
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /**
     * 方法1: 中序遍历 + 识别逆序对 (推荐实现)
     * 
     * 思路:
     * 1. 中序遍历BST，正常情况下应该是严格递增序列
     * 2. 有两个节点被交换，会打破递增性，形成逆序对
     * 3. 识别逆序对模式，找到需要交换的两个节点
     * 4. 交换节点的值，恢复BST性质
     * 
     * 逆序对分析:
     * - 情况1: 相邻节点交换 [1,3,2,4] -> 一个逆序对 (3,2)
     * - 情况2: 不相邻节点交换 [1,4,3,2,5] -> 两个逆序对 (4,3) 和 (3,2)
     * 
     * TODO: 实现中序遍历，识别逆序对，记录需要交换的节点
     */
    void recoverTree(TreeNode* root) {
        // TODO: 实现你的解法
        
        // 提示: 需要维护的变量
        // TreeNode* firstError = nullptr;   // 第一个错误节点
        // TreeNode* secondError = nullptr;  // 第二个错误节点  
        // TreeNode* prev = nullptr;         // 中序遍历的前一个节点
        
        // 步骤1: 中序遍历，识别逆序对
        // 步骤2: 根据逆序对模式确定错误节点
        // 步骤3: 交换两个错误节点的值
        TreeNode* firstError = nullptr;
        TreeNode* secondError = nullptr;
        TreeNode* prev = new TreeNode(INT_MIN);

        inorderTraversal(root, prev, firstError, secondError);

        swap(firstError->val, secondError->val);
    }
    
private:
    /**
     * 辅助函数: 中序遍历
     * TODO: 实现中序遍历，在遍历过程中识别逆序对
     */
    void inorderTraversal(TreeNode* node, TreeNode*& prev, TreeNode*& firstError, TreeNode*& secondError) {
        // TODO: 实现递归中序遍历
        // 在访问当前节点时，检查 prev->val > node->val 的逆序情况
        if(!node) return;

        inorderTraversal(node->left, prev, firstError, secondError);
        
        if(!firstError && prev->val > node->val) {
            firstError = prev;
            secondError = node; 
        }
        if(firstError && prev->val > node->val) {
            secondError = node;
        }
        prev = node;

        inorderTraversal(node->right, prev, firstError, secondError);

    }
    /*
    易错点：
    1）审题，易错点可能相邻，也可能不相邻，所以secondError在firstError空或者不为空都需要赋值
    2）注意力不集中，基本变量写错了,需要好的检查习惯
    3) node 为nullptr 直接return
    */
};

/**
 * 进阶解法: Morris中序遍历 (O(1)空间)
 * 
 * 这是一个更高难度的实现，使用线索二叉树的思想：
 * 1. 利用叶子节点的空右指针建立临时链接
 * 2. 实现O(1)空间的中序遍历
 * 3. 在遍历过程中识别并修复错误节点
 * 
 * Morris遍历原理:
 * - 对于每个节点，找到其中序前驱
 * - 建立临时线索指向当前节点
 * - 遍历完成后删除临时线索
 */
class SolutionMorris {
public:
    void recoverTree(TreeNode* root) {
        // TODO: 实现Morris中序遍历版本 (挑战任务)
        // 这个版本较复杂，可以先完成标准版本后再尝试
    }
};

// 测试用例
class TestRunner {
public:
    // 创建测试用例1: [1,3,null,null,2] -> [3,1,null,null,2]
    TreeNode* createTestCase1() {
        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(3);
        root->left->right = new TreeNode(2);
        return root;
    }
    
    // 创建测试用例2: [3,1,4,null,null,2] -> [2,1,4,null,null,3]
    TreeNode* createTestCase2() {
        TreeNode* root = new TreeNode(3);
        root->left = new TreeNode(1);
        root->right = new TreeNode(4);
        root->right->left = new TreeNode(2);
        return root;
    }
    
    // 创建测试用例3: 相邻节点交换 [2,1,3]
    TreeNode* createTestCase3() {
        TreeNode* root = new TreeNode(2);
        root->left = new TreeNode(1);
        root->right = new TreeNode(3);
        // 模拟交换: 应该是[1,2,3]，现在1和2被交换了
        return root;
    }
    
    // 创建测试用例4: 不相邻节点交换 [3,1,4,null,null,2]
    TreeNode* createTestCase4() {
        TreeNode* root = new TreeNode(3);
        root->left = new TreeNode(1);
        root->right = new TreeNode(4);
        root->right->left = new TreeNode(2);
        return root;
    }
    
    // 验证BST性质
    bool isValidBST(TreeNode* root) {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        for (int i = 1; i < inorder.size(); i++) {
            if (inorder[i] <= inorder[i-1]) return false;
        }
        return true;
    }
    
    // 中序遍历收集节点值
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
    
    // 打印中序遍历结果
    void printInorder(TreeNode* root, const string& prefix = "") {
        vector<int> result;
        inorderTraversal(root, result);
        cout << prefix << "中序遍历: ";
        for (int val : result) {
            cout << val << " ";
        }
        cout << (isValidBST(root) ? "(有效BST)" : "(无效BST)") << endl;
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 99. 恢复二叉搜索树测试 ===" << endl;
        
        // 测试用例1
        cout << "\n测试用例1: 相邻错误节点" << endl;
        TreeNode* test1 = createTestCase1();
        printInorder(test1, "修复前: ");
        solution.recoverTree(test1);
        printInorder(test1, "修复后: ");
        
        // 测试用例2  
        cout << "\n测试用例2: 不相邻错误节点" << endl;
        TreeNode* test2 = createTestCase2();
        printInorder(test2, "修复前: ");
        solution.recoverTree(test2);
        printInorder(test2, "修复后: ");
        
        // 测试用例3
        cout << "\n测试用例3: 根节点参与交换" << endl;
        TreeNode* test3 = createTestCase3();
        printInorder(test3, "修复前: ");
        solution.recoverTree(test3);
        printInorder(test3, "修复后: ");
        
        // 测试用例4
        cout << "\n测试用例4: 叶子节点交换" << endl;
        TreeNode* test4 = createTestCase4();
        printInorder(test4, "修复前: ");
        solution.recoverTree(test4);
        printInorder(test4, "修复后: ");
        
        cout << "\n所有测试完成！" << endl;
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
 * 1. **BST性质的应用**:
 *    - 中序遍历产生有序序列
 *    - 违反有序性的模式分析
 * 
 * 2. **逆序对识别技巧**:
 *    - 第一个逆序对: firstError = prev, secondError = current
 *    - 第二个逆序对: 只更新 secondError = current
 * 
 * 3. **指针状态管理**:
 *    - prev指针的维护和更新
 *    - 错误节点指针的记录策略
 * 
 * 4. **边界情况处理**:
 *    - 只有一个逆序对（相邻交换）
 *    - 两个逆序对（不相邻交换）
 * 
 * 5. **算法扩展**:
 *    - 从递归到Morris遍历的空间优化
 *    - 线索二叉树的理解和应用
 * 
 * 延伸题目:
 * - 98. 验证二叉搜索树（基础）
 * - 230. BST第K小元素（应用）
 * - 108. 有序数组转BST（构造）
 * - 173. BST迭代器（遍历）
 */