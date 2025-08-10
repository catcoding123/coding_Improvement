/*
 * 98. 验证二叉搜索树 (Validate Binary Search Tree)
 * 
 * 链接: https://leetcode.cn/problems/validate-binary-search-tree/
 * 难度: Medium
 * 
 * 题目描述：
 * 给你一个二叉树的根节点 root，判断其是否是一个有效的二叉搜索树。
 * 
 * 有效 二叉搜索树定义如下：
 * - 节点的左子树只包含小于当前节点的数。
 * - 节点的右子树只包含大于当前节点的数。
 * - 所有左子树和右子树自身必须也是二叉搜索树。
 * 
 * 示例 1:
 * 输入：root = [2,1,3]
 * 输出：true
 * 
 * 示例 2:
 * 输入：root = [5,1,4,null,null,3,6]
 * 输出：false
 * 解释：根节点的值是 5 ，但是右子树中节点的值是 4 。
 * 
 * 约束条件：
 * - 树中节点数目范围在[1, 10^4] 内
 * - -2^31 <= Node.val <= 2^31 - 1
 * 
 * 算法分析：
 * 这道题有多种解法，核心是理解BST的定义：
 * 
 * 方法1: 中序遍历 + 有序性检查 (利用94题的成果!)
 * - 思路: BST的中序遍历结果必须严格递增
 * - 时间复杂度: O(n)，空间复杂度: O(h) 
 * - 优势: 简单直观，代码量少
 * 
 * 方法2: 递归 + 范围验证
 * - 思路: 每个节点都有一个有效范围[min, max]
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 * - 优势: 直接验证BST定义，更通用
 * 
 * 方法3: 迭代 + 栈模拟中序遍历
 * - 思路: 手动模拟中序遍历过程，检查有序性
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 * - 优势: 避免递归栈溢出，与94题模式一致
 * 
 * 易错点预测：
 * 1. 边界值处理：INT_MIN/INT_MAX边界情况
 * 2. 相等值判断：BST要求严格大于/小于，不能相等
 * 3. 范围传递：递归时min/max的正确传递
 * 4. 中序遍历：与94题对比，检查实现正确性
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
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
    // 方法1: 中序遍历 + 有序性检查 (推荐实现)
    // 利用94题的中序遍历成果，BST的中序遍历必须严格递增
    bool isValidBST(TreeNode* root) {
        // TODO: 实现中序遍历版本
        // 提示: 可以用递归或迭代(栈)两种方式
        // 关键: 检查相邻元素是否严格递增
        TreeNode* pre = nullptr;
        return helper(root, pre);
    }

    bool helper(TreeNode* node, TreeNode*& pre) {
        if(!node) return true; // 为什么为true
        if(!helper(node->left, pre)) return false;
        
        //关键操作
        if(pre && pre->val >= node->val ) return false;
        pre = node;

        return helper(node->right, pre);

    }
    
    // 方法2: 递归 + 范围验证 (经典解法)
    // 每个节点都有一个有效范围[minVal, maxVal]
    bool isValidBSTRange(TreeNode* root) {
        // TODO: 实现范围递归版本
        // 提示: helper函数 validate(node, minVal, maxVal)
        // 注意: 使用long long避免边界问题
        return validateRange(root, LLONG_MIN, LLONG_MAX);
    }
    
private:
    // 辅助函数：范围验证
    bool validateRange(TreeNode* node, long long minVal, long long maxVal) {
        // TODO: 实现递归范围验证
        // 递归终止条件: node == nullptr
        // 递归逻辑: 检查当前值是否在范围内，并递归左右子树
        return true;
    }
    
    // 方法3: 迭代版中序遍历 (与94题对比学习)
    bool isValidBSTIterative(TreeNode* root) {
        // TODO: 实现迭代版本
        // 提示: 复用94题的栈模拟中序遍历模式
        // 在遍历过程中检查有序性
        return false;
    }
};

// 辅助函数：构建测试用的二叉树
TreeNode* buildTree1() {
    // 构建示例1: [2,1,3] - 有效BST
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* buildTree2() {
    // 构建示例2: [5,1,4,null,null,3,6] - 无效BST
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(6);
    return root;
}

TreeNode* buildTree3() {
    // 构建边界测试: [INT_MIN, null, INT_MAX] - 有效BST
    TreeNode* root = new TreeNode(INT_MIN);
    root->right = new TreeNode(INT_MAX);
    return root;
}

TreeNode* buildTree4() {
    // 构建陷阱案例: [10,5,15,null,null,6,20] - 无效BST
    // 陷阱: 6 < 15，但6 < 10，违反BST定义
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);  // 关键错误点
    root->right->right = new TreeNode(20);
    return root;
}

TreeNode* buildTree5() {
    // 构建重复值测试: [1,1] - 无效BST (不允许相等)
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    return root;
}

// 清理内存的辅助函数
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 可视化辅助：中序遍历打印(用于调试)
void inorderPrint(TreeNode* root) {
    if (!root) return;
    inorderPrint(root->left);
    cout << root->val << " ";
    inorderPrint(root->right);
}

int main() {
    Solution solution;
    
    cout << "=== 98. 验证二叉搜索树 测试 ===" << endl;
    
    // 测试用例1: 有效BST [2,1,3]
    cout << "\n测试1 - 有效BST [2,1,3]:" << endl;
    TreeNode* tree1 = buildTree1();
    cout << "中序遍历: "; inorderPrint(tree1); cout << endl;
    cout << "是否有效BST: " << (solution.isValidBST(tree1) ? "true" : "false") << endl;
    cout << "预期结果: true" << endl;
    
    // 测试用例2: 无效BST [5,1,4,null,null,3,6]
    cout << "\n测试2 - 无效BST [5,1,4,null,null,3,6]:" << endl;
    TreeNode* tree2 = buildTree2();
    cout << "中序遍历: "; inorderPrint(tree2); cout << endl;
    cout << "是否有效BST: " << (solution.isValidBST(tree2) ? "true" : "false") << endl;
    cout << "预期结果: false (4 > 3，违反BST性质)" << endl;
    
    // 测试用例3: 边界值测试
    cout << "\n测试3 - 边界值 [INT_MIN, null, INT_MAX]:" << endl;
    TreeNode* tree3 = buildTree3();
    cout << "是否有效BST: " << (solution.isValidBST(tree3) ? "true" : "false") << endl;
    cout << "预期结果: true" << endl;
    
    // 测试用例4: 经典陷阱 [10,5,15,null,null,6,20]
    cout << "\n测试4 - 经典陷阱 [10,5,15,null,null,6,20]:" << endl;
    TreeNode* tree4 = buildTree4();
    cout << "中序遍历: "; inorderPrint(tree4); cout << endl;
    cout << "是否有效BST: " << (solution.isValidBST(tree4) ? "true" : "false") << endl;
    cout << "预期结果: false (6 < 10，但6在右子树)" << endl;
    
    // 测试用例5: 重复值测试 [1,1]
    cout << "\n测试5 - 重复值测试 [1,1]:" << endl;
    TreeNode* tree5 = buildTree5();
    cout << "中序遍历: "; inorderPrint(tree5); cout << endl;
    cout << "是否有效BST: " << (solution.isValidBST(tree5) ? "true" : "false") << endl;
    cout << "预期结果: false (BST不允许相等值)" << endl;
    
    // 清理内存
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(tree3);
    deleteTree(tree4);
    deleteTree(tree5);
    
    cout << "\n=== 学习重点 ===" << endl;
    cout << "1. 对比三种解法的优劣: 中序遍历、范围递归、迭代栈" << endl;
    cout << "2. 深度理解BST性质: 中序遍历严格递增" << endl;
    cout << "3. 掌握范围递归思维: 传递有效范围进行验证" << endl;
    cout << "4. 复习94题栈模拟: 在迭代版本中应用" << endl;
    cout << "5. 边界和陷阱处理: INT_MIN/MAX、相等值、祖先约束" << endl;
    
    return 0;
}