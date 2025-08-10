/*
 * 230. 二叉搜索树中第K小的元素 (Kth Smallest Element in a BST)
 * 
 * 链接: https://leetcode.cn/problems/kth-smallest-element-in-a-bst/
 * 难度: Medium
 * 
 * 题目描述：
 * 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小的元素（从 1 开始计数）。
 * 
 * 示例 1:
 * 输入：root = [3,1,4,null,2], k = 1
 * 输出：1
 * 
 * 示例 2:
 * 输入：root = [5,3,6,2,4,null,null,1], k = 3
 * 输出：3
 * 
 * 约束条件：
 * - 树中的节点数为 n。
 * - 1 <= k <= n <= 10^4
 * - 0 <= Node.val <= 10^4
 * 
 * 进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？
 * 
 * 算法分析：
 * 这道题完美应用了前面学过的98题BST性质和94题中序遍历！
 * 
 * 核心洞察：BST的中序遍历结果是有序的！
 * - BST中序遍历：左 → 根 → 右 = 递增序列
 * - 第K小元素就是中序遍历的第K个节点
 * 
 * 方法1: 递归中序遍历 + 计数器 (推荐)
 * - 思路: 中序遍历过程中用计数器k，找到第k个节点
 * - 时间复杂度: O(H + k) 最优，H是树高
 * - 空间复杂度: O(H) 递归栈
 * - 优势: 提前终止，不需要遍历整棵树
 * 
 * 方法2: 迭代中序遍历 + 栈模拟 (与94题对比)
 * - 思路: 用栈手动模拟中序遍历，计数到第k个
 * - 时间复杂度: O(H + k)
 * - 空间复杂度: O(H) 栈空间
 * - 优势: 避免递归栈溢出，控制更精确
 * 
 * 方法3: 中序遍历收集所有值 (暴力但直观)
 * - 思路: 先中序遍历收集所有值，再返回第k个
 * - 时间复杂度: O(n)
 * - 空间复杂度: O(n)
 * - 缺点: 无法提前终止，效率较低
 * 
 * 进阶优化：树节点增强 (面试加分点)
 * - 为每个节点添加子树大小信息
 * - 查找时间复杂度降到 O(H)
 * - 支持高频查询场景
 * 
 * 易错点预测：
 * 1. 计数器管理：k从1开始还是从0开始
 * 2. 提前终止：如何正确判断找到第k个节点
 * 3. 引用传递：计数器需要跨递归调用更新
 * 4. 栈模拟：与94题中序遍历模式的对比应用
 */

#include <iostream>
#include <vector>
#include <stack>
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
    // 方法1: 递归中序遍历 + 计数器 (推荐实现)
    // 利用BST中序遍历有序的性质，找第k个节点
    int kthSmallest(TreeNode* root, int k) {
        // TODO: 实现递归版本
        // 提示: 需要helper函数，用引用传递维护计数器和结果
        // 关键: 中序遍历过程中递减k，当k==0时找到答案
        int result = 0;
        inorderTraversal(root, k, result);
        return result;
    }
    
private:
    // 辅助函数：递归中序遍历
    void inorderTraversal(TreeNode* node, int& k, int& result) {
        // TODO: 实现递归中序遍历
        // 递归终止条件: node == nullptr 或 k == 0 (已找到)
        // 中序遍历: 左 → 根(处理k计数) → 右
        // 关键: 当k递减到0时，当前节点就是第k小的元素
        if(node == nullptr) return;

        inorderTraversal(node->left, k, result);
        k--;
        if(k == 0) {
            result = node->val;
            return;
        }
        inorderTraversal(node->right, k, result);

    }
    
public:
    // 方法2: 迭代中序遍历 + 栈模拟 (与94题对比学习)
    // 复用94题的栈模拟中序遍历模式
    int kthSmallestIterative(TreeNode* root, int k) {
        // TODO: 实现迭代版本
        // 提示: 复用94题的while(!st.empty() || curr != nullptr)模式
        // 在每次访问节点时递减k，当k==0时返回结果
        stack<TreeNode*> st;
        TreeNode* curr = root;
        
        while (!st.empty() || curr != nullptr) {
            // TODO: 完成栈模拟中序遍历逻辑
            // 1. 向左深入
            // 2. 弹栈访问节点，处理k计数
            // 3. 向右转移
            while(curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            TreeNode* node = st.top();
            st.pop();
            k--;
            if(k == 0) {
                return node->val;
            }

            curr = node->right; // 这个经常写错

        }
        
        return -1; // 不应该到达这里
    }
    
    // 方法3: 收集所有值再返回第k个 (暴力但直观)
    int kthSmallestBruteForce(TreeNode* root, int k) {
        // TODO: 实现暴力版本
        // 1. 中序遍历收集所有值到vector
        // 2. 返回vector[k-1]
        vector<int> values;
        collectInorder(root, values);
        return values[k-1];
    }
    
    void collectInorder(TreeNode* node, vector<int>& values) {
        // TODO: 标准中序遍历收集所有值
        if (!node) return;
        collectInorder(node->left, values);
        values.push_back(node->val);
        collectInorder(node->right, values);
    }
};

// 进阶：增强节点结构 (面试加分点)
struct EnhancedTreeNode {
    int val;
    int count;  // 以此节点为根的子树中的节点数
    EnhancedTreeNode *left;
    EnhancedTreeNode *right;
    
    EnhancedTreeNode(int x) : val(x), count(1), left(nullptr), right(nullptr) {}
};

class EnhancedSolution {
public:
    // 进阶方法：基于子树大小的O(H)查找
    int kthSmallestOptimal(EnhancedTreeNode* root, int k) {
        // TODO: 实现进阶版本 (可选挑战)
        // 思路: 利用子树大小快速定位
        // 1. 如果左子树大小 >= k，在左子树中找第k小
        // 2. 如果左子树大小 == k-1，当前节点就是答案
        // 3. 否则在右子树中找第(k-左子树大小-1)小
        return 0;
    }
    
private:
    int getCount(EnhancedTreeNode* node) {
        return node ? node->count : 0;
    }
};

// 辅助函数：构建测试用的二叉搜索树
TreeNode* buildBST1() {
    // 构建示例1: [3,1,4,null,2] - 中序遍历: 1,2,3,4
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);
    return root;
}

TreeNode* buildBST2() {
    // 构建示例2: [5,3,6,2,4,null,null,1] - 中序遍历: 1,2,3,4,5,6
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->left->left->left = new TreeNode(1);
    return root;
}

TreeNode* buildBST3() {
    // 构建单节点测试: [1]
    return new TreeNode(1);
}

TreeNode* buildBST4() {
    // 构建大树测试: [10,5,15,3,7,12,20,1,4,6,8] 
    // 中序遍历: 1,3,4,5,6,7,8,10,12,15,20
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(20);
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(8);
    return root;
}

// 清理内存的辅助函数
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 可视化辅助：中序遍历打印(验证BST性质)
void inorderPrint(TreeNode* root) {
    if (!root) return;
    inorderPrint(root->left);
    cout << root->val << " ";
    inorderPrint(root->right);
}

int main() {
    Solution solution;
    
    cout << "=== 230. 二叉搜索树中第K小的元素 测试 ===" << endl;
    
    // 测试用例1: [3,1,4,null,2], k=1
    cout << "\n测试1 - BST [3,1,4,null,2], k=1:" << endl;
    TreeNode* tree1 = buildBST1();
    cout << "中序遍历: "; inorderPrint(tree1); cout << endl;
    cout << "第1小元素: " << solution.kthSmallest(tree1, 1) << endl;
    cout << "预期结果: 1" << endl;
    
    // 测试用例2: [5,3,6,2,4,null,null,1], k=3
    cout << "\n测试2 - BST [5,3,6,2,4,null,null,1], k=3:" << endl;
    TreeNode* tree2 = buildBST2();
    cout << "中序遍历: "; inorderPrint(tree2); cout << endl;
    cout << "第3小元素: " << solution.kthSmallest(tree2, 3) << endl;
    cout << "预期结果: 3" << endl;
    
    // 测试用例3: 单节点 [1], k=1
    cout << "\n测试3 - 单节点 [1], k=1:" << endl;
    TreeNode* tree3 = buildBST3();
    cout << "中序遍历: "; inorderPrint(tree3); cout << endl;
    cout << "第1小元素: " << solution.kthSmallest(tree3, 1) << endl;
    cout << "预期结果: 1" << endl;
    
    // 测试用例4: 大树测试 - 验证提前终止优化
    cout << "\n测试4 - 大树测试, k=5:" << endl;
    TreeNode* tree4 = buildBST4();
    cout << "中序遍历: "; inorderPrint(tree4); cout << endl;
    cout << "第5小元素: " << solution.kthSmallest(tree4, 5) << endl;
    cout << "预期结果: 6" << endl;
    
    // 边界测试: k = 最大值
    cout << "\n测试5 - 边界测试, k=最大值:" << endl;
    cout << "第11小元素(最大): " << solution.kthSmallest(tree4, 11) << endl;
    cout << "预期结果: 20" << endl;
    
    // 清理内存
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(tree3);
    deleteTree(tree4);
    
    cout << "\n=== 学习重点 ===" << endl;
    cout << "1. 深度应用98题BST性质: 中序遍历有序" << endl;
    cout << "2. 巧妙融合94题中序遍历: 递归和迭代两种实现" << endl;
    cout << "3. 掌握提前终止优化: O(H+k) vs O(n)的效率差异" << endl;
    cout << "4. 理解引用传递应用: 跨递归调用的计数器管理" << endl;
    cout << "5. 对比三种解法优劣: 递归、迭代、暴力收集" << endl;
    cout << "6. 面试进阶思考: 高频查询场景的树结构优化" << endl;
    
    cout << "\n=== 知识链接回顾 ===" << endl;
    cout << "• 与94题连接: 栈模拟中序遍历的复用和优化" << endl;
    cout << "• 与98题连接: BST中序遍历有序性质的深度应用" << endl;
    cout << "• 与104题连接: 树高度在时间复杂度分析中的作用" << endl;
    cout << "• 算法思维升级: 从遍历到查找的递进应用" << endl;
    
    return 0;
}