/*
236. 二叉树的最近公共祖先 (Medium)
https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/

题目描述：
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为："对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。"

示例 1：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。

示例 2：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。

示例 3：
输入：root = [1,2], p = 1, q = 2
输出：1

约束条件：
- 树中节点数目在范围 [2, 10^5] 内。
- -10^9 <= Node.val <= 10^9
- 所有 Node.val 互不相同 。
- p != q
- p 和 q 均存在于给定的二叉树中。

专题归属：二叉树 - 递归遍历
相关题目：235.二叉搜索树的最近公共祖先、1644.二叉树的最近公共祖先II

算法分析：
思路提示：
1. 方法一：递归后序遍历
   - 对于当前节点，递归查找左右子树
   - 如果当前节点是p或q之一，返回当前节点
   - 如果左右子树都找到了目标节点，当前节点就是LCA
   - 如果只有一边找到，返回找到的那一边

2. 方法二：存储父节点路径
   - 遍历树，记录每个节点的父节点
   - 从p开始向上追溯到根，记录路径
   - 从q开始向上追溯，找到第一个在p路径中出现的节点

时间复杂度：O(n) - 需要遍历树的节点
空间复杂度：O(h) - 递归栈的深度，h为树的高度

易错点：
1. 理解递归的含义：子函数返回值的正确解释
2. 边界条件：当前节点为空或等于目标节点的处理
3. LCA的判断逻辑：左右子树查找结果的组合判断
4. 节点存在性：题目保证p和q都存在，简化了逻辑
*/

#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 方法一：递归后序遍历（推荐）
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // TODO: 实现递归解法
        // 提示：
        // 1. 递归终止条件：root为空 或 root等于p或q
        // 2. 递归查找左右子树
        // 3. 根据左右子树的查找结果判断：
        //    - 如果左右都不为空：当前节点是LCA
        //    - 如果只有一边不为空：返回不为空的那一边
        //    - 如果都为空：返回空
            if(p==root || q==root || root==nullptr) return root;
            TreeNode* leftNode = lowestCommonAncestor(root->left, p, q);
            TreeNode* rightNode = lowestCommonAncestor(root->right, p, q);
            if(leftNode && rightNode) {
                return root;
            }
            return leftNode?leftNode:rightNode;
    }
    
    // 方法二：存储父节点路径
    TreeNode* lowestCommonAncestorWithParent(TreeNode* root, TreeNode* p, TreeNode* q) {
        // TODO: 实现父节点路径法
        // 提示：
        // 1. 遍历树，建立节点到父节点的映射
        // 2. 从p开始向上追溯到根，记录所有祖先节点
        // 3. 从q开始向上追溯，找到第一个在p祖先集合中的节点
        
        return nullptr;
    }

private:
    // 辅助函数：构建父节点映射
    void buildParentMap(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent) {
        // TODO: 实现父节点映射构建
        
    }
};

// 辅助函数：创建测试树
TreeNode* createTestTree() {
    // 创建树: [3,5,1,6,2,0,8,null,null,7,4]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    return root;
}

TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

// 测试用例
int main() {
    Solution solution;
    TreeNode* root = createTestTree();
    
    // 测试用例1: p=5, q=1
    TreeNode* p1 = findNode(root, 5);
    TreeNode* q1 = findNode(root, 1);
    TreeNode* result1 = solution.lowestCommonAncestor(root, p1, q1);
    cout << "测试1 - p=5, q=1" << endl;
    cout << "预期结果: 3, 实际结果: " << (result1 ? result1->val : -1) << endl << endl;
    
    // 测试用例2: p=5, q=4
    TreeNode* p2 = findNode(root, 5);
    TreeNode* q2 = findNode(root, 4);
    TreeNode* result2 = solution.lowestCommonAncestor(root, p2, q2);
    cout << "测试2 - p=5, q=4" << endl;
    cout << "预期结果: 5, 实际结果: " << (result2 ? result2->val : -1) << endl << endl;
    
    // 测试用例3: p=6, q=7
    TreeNode* p3 = findNode(root, 6);
    TreeNode* q3 = findNode(root, 7);
    TreeNode* result3 = solution.lowestCommonAncestor(root, p3, q3);
    cout << "测试3 - p=6, q=7" << endl;
    cout << "预期结果: 5, 实际结果: " << (result3 ? result3->val : -1) << endl << endl;
    
    // 测试用例4: p=0, q=8
    TreeNode* p4 = findNode(root, 0);
    TreeNode* q4 = findNode(root, 8);
    TreeNode* result4 = solution.lowestCommonAncestor(root, p4, q4);
    cout << "测试4 - p=0, q=8" << endl;
    cout << "预期结果: 1, 实际结果: " << (result4 ? result4->val : -1) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解递归在树结构中的应用
2. 掌握后序遍历的思想：先处理子树，再处理当前节点
3. 学会分析递归函数的返回值含义
4. 理解树的路径和祖先关系

算法精髓：
1. 递归的信任机制：相信子函数能正确返回结果
2. 分情况讨论：根据子树查找结果进行逻辑判断
3. 节点关系分析：父子、祖先、兄弟节点的相对位置

面试要点：
1. 清楚解释LCA的定义和性质
2. 准确描述递归思路和终止条件
3. 正确分析各种情况的处理逻辑
4. 能够扩展到BST等特殊情况

扩展思考：
- 如果p或q可能不存在怎么处理？
- 如何找到两个节点的距离？
- 如何处理多个节点的LCA？
- BST中的LCA有什么特殊性质？

相关题目：
- 235题：BST的LCA（可以利用BST性质优化）
- 1644题：节点可能不存在的情况
- 1650题：带有父指针的节点
*/