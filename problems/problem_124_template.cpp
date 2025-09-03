/*
124. 二叉树中的最大路径和 (Hard)
https://leetcode.cn/problems/binary-tree-maximum-path-sum/

题目描述：
二叉树中的 路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。

示例 1：
输入：root = [1,2,3]
      1
     / \
    2   3
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6

示例 2：
输入：root = [-10,9,20,null,null,15,7]
       -10
       / \
      9  20
        /  \
       15   7
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42

约束条件：
- 树中节点数目范围是 [1, 3 * 10^4]
- -1000 <= Node.val <= 1000

专题归属：二叉树 - 树形DP
相关题目：543.二叉树的直径、687.最长同值路径

算法分析：
思路提示：
1. 核心思想：对于每个节点，考虑以该节点为"拐点"的最大路径和
2. 路径形态：左子树路径 -> 当前节点 -> 右子树路径
3. 递归函数设计：返回以当前节点为起点的最大单边路径和
4. 全局变量：维护所有拐点路径和的最大值

时间复杂度：O(n) - 每个节点访问一次
空间复杂度：O(h) - 递归栈深度，h为树的高度

易错点：
1. 理解"路径"的定义：不一定经过根节点
2. 负值节点的处理：可以选择不包含某条路径
3. 递归返回值vs全局最优值的区别
4. 拐点路径vs单边路径的概念区分
*/

#include <algorithm>
#include <climits>
#include <iostream>
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
    int maxPathSum(TreeNode* root) {
        int max_val = INT_MIN;
        helper(root, max_val);
        return max_val;
    }
    int helper(TreeNode* node, int& max_val) {
    if(node == nullptr) {
        return 0;
    }
    int leftMax = max(helper(node->left, max_val),0);
    int rightMax = max(helper(node->right, max_val),0);
    max_val = max(max_val,node->val + leftMax + rightMax);
    return max(leftMax + node->val, rightMax + node->val);
    }
};

// 辅助函数：创建测试树
TreeNode* createTree1() {
    // 创建示例1的树: [1,2,3]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTree2() {
    // 创建示例2的树: [-10,9,20,null,null,15,7]
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createTree3() {
    // 创建测试树: [-3]
    return new TreeNode(-3);
}

TreeNode* createTree4() {
    // 创建测试树: [5,4,8,11,null,13,4,7,2,null,null,null,1]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(1);
    return root;
}

// 测试用例
int main() {
    Solution solution;
    
    // 测试用例1: 简单正值树
    TreeNode* tree1 = createTree1();
    cout << "测试1 - 树: [1,2,3]" << endl;
    cout << "预期结果: 6, 实际结果: " << solution.maxPathSum(tree1) << endl << endl;
    
    // 测试用例2: 包含负值的树
    TreeNode* tree2 = createTree2();
    cout << "测试2 - 树: [-10,9,20,null,null,15,7]" << endl;
    cout << "预期结果: 42, 实际结果: " << solution.maxPathSum(tree2) << endl << endl;
    
    // 测试用例3: 单节点负值
    TreeNode* tree3 = createTree3();
    cout << "测试3 - 树: [-3]" << endl;
    cout << "预期结果: -3, 实际结果: " << solution.maxPathSum(tree3) << endl << endl;
    
    // 测试用例4: 复杂树结构
    TreeNode* tree4 = createTree4();
    cout << "测试4 - 复杂树结构" << endl;
    cout << "实际结果: " << solution.maxPathSum(tree4) << endl;
    
    return 0;
}

/*
学习重点：
1. 理解树形DP的基本思想和递归设计
2. 掌握"局部最优"与"全局最优"的处理方式
3. 理解路径的不同形态：拐点路径vs单边路径
4. 学会处理负值节点的剪枝策略

算法精髓：
1. 每个节点都可能是最优路径的"拐点"
2. 递归返回值服务于父节点的计算
3. 全局变量记录真正的最优解
4. 负值路径的舍弃体现了贪心思想

面试要点：
1. 清楚解释算法的核心思想
2. 准确分析时间和空间复杂度
3. 正确处理边界情况（单节点、负值节点）
4. 能够扩展到相似的树形DP问题

扩展思考：
- 如何求最长路径的节点数？
- 如何同时返回最优路径的具体节点序列？
- 如果允许路径断开（跳过某些节点）怎么处理？
*/