#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/**
 * 104. 二叉树的最大深度 (Easy)
 * 
 * 题目链接：https://leetcode.cn/problems/maximum-depth-of-binary-tree/
 * 
 * 题目描述：
 * 给定一个二叉树，找出其最大深度。
 * 
 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 * 
 * 说明: 叶子节点是指没有子节点的节点。
 * 
 * 示例：
 * 给定二叉树 [3,9,20,null,null,15,7]，
 * 
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 
 * 返回它的最大深度 3 。
 * 
 * 约束条件：
 * - 树中节点的数量在 [0, 10^4] 范围内
 * - -100 <= Node.val <= 100
 */

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
    // 方法1: 递归DFS (推荐 - 最直观)
    int maxDepthRecursive(TreeNode* root) {
        // TODO: 实现递归解法
        // 思路提示：
        // 1. 递归出口：空节点深度为0
        // 2. 递归关系：当前节点深度 = max(左子树深度, 右子树深度) + 1
        // 3. 这就是一个典型的后序遍历模式
        if(!root) return 0;
        return  max(maxDepthRecursive(root->left), maxDepthRecursive(root->right)) +1;
    }
    
    // 方法2: 迭代BFS - 层序遍历 (经典)
    int maxDepthBFS(TreeNode* root) {
        // TODO: 实现BFS层序遍历解法
        // 思路提示：
        // 1. 使用队列进行层序遍历
        // 2. 记录遍历的层数就是最大深度
        // 3. 每层处理完所有节点后，深度+1
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int line_cnt = 0;
        while(!q.empty()) {
            int q_size = q.size();
            for(int i=0; i<q_size; i++) {
                TreeNode* currNode = q.front();
                q.pop();
                if(currNode->left !=nullptr) q.push(currNode->left);
                if(currNode->right != nullptr) q.push(currNode->right);
            }
            line_cnt++;
        } 
        return line_cnt; // 临时返回
    }
    
    // 方法3: 迭代DFS - 使用栈模拟递归 (进阶)
    int maxDepthDFS(TreeNode* root) {
        // TODO: 实现DFS栈模拟解法
        // 思路提示：
        // 1. 使用栈存储(节点, 当前深度)对
        // 2. 模拟递归过程，记录最大深度
        if(root == nullptr) return 0;
        stack<pair<TreeNode*, int>> st;
        st.push({root, 1});
        int maxDepth = 1;
        while(!st.empty()) {
            auto [node, depth] = st.top();
            st.pop();
            maxDepth = max(maxDepth, depth);
            if(node->left) st.push({node->left, depth+1});
            if(node->right) st.push({node->right, depth+1});
        }
        return maxDepth; // 临时返回
    }
};

// 辅助函数：构建测试用的二叉树
TreeNode* buildTree() {
    // 构建示例树: [3,9,20,null,null,15,7]
    //     3
    //    / \
    //   9  20
    //     /  \
    //    15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* buildSingleNode() {
    // 单节点树
    return new TreeNode(1);
}

TreeNode* buildEmptyTree() {
    // 空树
    return nullptr;
}

TreeNode* buildLeftSkewed() {
    // 左偏树: 1->2->3
    //   1
    //  /
    // 2
    ///
    //3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    return root;
}

// 测试用例
void testMaxDepth() {
    Solution solution;
    
    // 测试用例1: 标准二叉树
    TreeNode* tree1 = buildTree();
    int result1 = solution.maxDepthRecursive(tree1);
    cout << "Test 1 - Standard Tree [3,9,20,null,null,15,7]" << endl;
    cout << "Expected: 3, Got: " << result1 << endl;
    cout << "Result: " << (result1 == 3 ? "PASS" : "FAIL") << endl << endl;
    
    // 测试用例2: 单节点
    TreeNode* tree2 = buildSingleNode();
    int result2 = solution.maxDepthRecursive(tree2);
    cout << "Test 2 - Single Node [1]" << endl;
    cout << "Expected: 1, Got: " << result2 << endl;
    cout << "Result: " << (result2 == 1 ? "PASS" : "FAIL") << endl << endl;
    
    // 测试用例3: 空树
    TreeNode* tree3 = buildEmptyTree();
    int result3 = solution.maxDepthRecursive(tree3);
    cout << "Test 3 - Empty Tree []" << endl;
    cout << "Expected: 0, Got: " << result3 << endl;
    cout << "Result: " << (result3 == 0 ? "PASS" : "FAIL") << endl << endl;
    
    // 测试用例4: 左偏树
    TreeNode* tree4 = buildLeftSkewed();
    int result4 = solution.maxDepthRecursive(tree4);
    cout << "Test 4 - Left Skewed Tree [1,2,3]" << endl;
    cout << "Expected: 3, Got: " << result4 << endl;
    cout << "Result: " << (result4 == 3 ? "PASS" : "FAIL") << endl << endl;
    
    // 测试方法2和方法3 (当实现后)
    cout << "=== Testing BFS Method ===" << endl;
    int resultBFS = solution.maxDepthBFS(tree1);
    cout << "BFS Result: " << resultBFS << endl;
    cout << "BFS vs Recursive: " << (resultBFS == result1 ? "CONSISTENT" : "INCONSISTENT") << endl << endl;
    
    cout << "=== Testing DFS Stack Method ===" << endl;
    int resultDFS = solution.maxDepthDFS(tree1);
    cout << "DFS Result: " << resultDFS << endl;
    cout << "DFS vs Recursive: " << (resultDFS == result1 ? "CONSISTENT" : "INCONSISTENT") << endl;
}

// 辅助函数：释放内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== 104. 二叉树的最大深度 测试 ===" << endl << endl;
    testMaxDepth();
    
    // 清理内存 (简化版，实际应该在每个测试后清理)
    cout << "\n注意：在实际使用中应该适当释放内存" << endl;
    return 0;
}

/*
 * 算法分析：
 * 
 * 核心思想：
 * - 二叉树问题通常用递归解决，符合树的递归结构
 * - 深度 = max(左子树深度, 右子树深度) + 1
 * - 可以用DFS(递归/栈)或BFS(队列)实现
 * 
 * 时间复杂度：O(n) - 需要访问每个节点
 * 空间复杂度：
 * - 递归: O(h) - h是树的高度，最坏O(n)
 * - BFS: O(w) - w是树的最大宽度，最坏O(n)
 * 
 * 与DP的联系：
 * - 递归结构类似，都有最优子结构
 * - 区别：二叉树是树形结构，DP通常是线性/二维结构
 * 
 * 易错点预测：
 * 1. 空节点处理：返回0而不是1
 * 2. 递归出口：要先检查空节点
 * 3. BFS层数计算：要正确区分层与层
 * 4. 内存管理：C++中要注意释放树节点内存
 */