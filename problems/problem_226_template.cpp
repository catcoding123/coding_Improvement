/*
 * 226. 翻转二叉树 (Easy)
 * 
 * LeetCode链接: https://leetcode.cn/problems/invert-binary-tree/
 * 
 * 题目描述:
 * 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
 * 
 * 示例1:
 * 输入: root = [4,2,7,1,3,6,9]
 * 输出: [4,7,2,9,6,3,1]
 * 
 *     4                4
 *   /   \            /   \
 *  2     7    =>    7     2
 * / \   / \        / \   / \
 *1   3 6   9      9   6 3   1
 * 
 * 示例2:
 * 输入: root = [2,1,3]
 * 输出: [2,3,1]
 * 
 * 示例3:
 * 输入: root = []
 * 输出: []
 * 
 * 约束条件:
 * - 树中节点数目范围在 [0, 100] 内
 * - -100 <= Node.val <= 100
 * 
 * 算法分析:
 * 思路提示: 
 * 1. 递归思维：翻转一棵树 = 交换左右子树 + 递归翻转左右子树
 * 2. 迭代思维：使用队列或栈遍历每个节点，逐个交换其左右子树
 * 
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度，h为树的高度
 * 
 * 易错点预测:
 * 1. 空树处理：要先判断root是否为nullptr
 * 2. 交换顺序：交换左右子树后，需要递归处理交换后的子树
 * 3. 返回值：要返回根节点
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
     * 方法1: 递归DFS
     * 核心思想: 翻转树 = 交换左右子树 + 递归翻转子树
     */
    TreeNode* invertTree(TreeNode* root) {
        // TODO: 实现递归翻转
        // 提示: 
        // 1. 处理空节点
        // 2. 交换左右子树
        // 3. 递归翻转左右子树
        // 4. 返回根节点
        if(root == nullptr) return nullptr;
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
    
    /**
     * 方法2: 迭代BFS (层序遍历)
     * 核心思想: 用队列层序遍历，逐个交换每个节点的左右子树
     */
    TreeNode* invertTreeBFS(TreeNode* root) {
        // TODO: 实现BFS翻转
        // 提示:
        // 1. 使用队列存储待处理节点
        // 2. 对每个节点交换其左右子树
        // 3. 将非空子节点加入队列
        // 只需要关注自己的左右子树的交换情况

        if(root == nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            // swap(node->left,node->right);
            // 执行交换
            TreeNode* tmp = node->left;
            node->left = node->right;
            node->right = tmp;

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }

        return root;
    }
    
    /**
     * 方法3: 迭代DFS (栈)
     * 核心思想: 用栈模拟递归，逐个交换每个节点的左右子树
     */
    TreeNode* invertTreeDFS(TreeNode* root) {
        // TODO: 实现DFS栈翻转
        // 提示:
        // 1. 使用栈存储待处理节点
        // 2. 对每个节点交换其左右子树
        // 3. 将非空子节点压入栈
        
        // 节点不变性，约等于BFS
        if(root == nullptr) return nullptr;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()) {
            TreeNode* node = st.top();
            st.pop();

            TreeNode* left = node->left;
            TreeNode* right = node->right;
            node->left = right;
            node->right = left;
            
            if(node->left) st.push(node->left);
            if(node->right) st.push(node->right);
        }

        return root;
    }
};

// 辅助函数：从数组构建二叉树（层序）
TreeNode* buildTree(vector<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (i < vals.size() && vals[i] != -1) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        
        if (i < vals.size() && vals[i] != -1) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// 辅助函数：层序遍历打印树
vector<int> levelOrder(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        result.push_back(node->val);
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return result;
}

// 辅助函数：打印数组
void printVector(const vector<int>& nums) {
    cout << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1: 标准二叉树
    cout << "=== 测试用例1: 标准二叉树 ===" << endl;
    vector<int> vals1 = {4, 2, 7, 1, 3, 6, 9};
    TreeNode* root1 = buildTree(vals1);
    
    cout << "原树(层序): ";
    printVector(levelOrder(root1));
    
    TreeNode* inverted1 = solution.invertTree(root1);
    cout << "翻转后: ";
    printVector(levelOrder(inverted1));
    cout << "期望结果: [4,7,2,9,6,3,1]" << endl;
    
    // 测试用例2: 简单树
    cout << "\n=== 测试用例2: 简单树 ===" << endl;
    vector<int> vals2 = {2, 1, 3};
    TreeNode* root2 = buildTree(vals2);
    
    cout << "原树(层序): ";
    printVector(levelOrder(root2));
    
    TreeNode* inverted2 = solution.invertTree(root2);
    cout << "翻转后: ";
    printVector(levelOrder(inverted2));
    cout << "期望结果: [2,3,1]" << endl;
    
    // 测试用例3: 空树
    cout << "\n=== 测试用例3: 空树 ===" << endl;
    TreeNode* root3 = nullptr;
    TreeNode* inverted3 = solution.invertTree(root3);
    cout << "翻转后: " << (inverted3 ? "非空" : "空") << endl;
    cout << "期望结果: 空" << endl;
    
    // 测试用例4: 单节点
    cout << "\n=== 测试用例4: 单节点 ===" << endl;
    vector<int> vals4 = {1};
    TreeNode* root4 = buildTree(vals4);
    
    cout << "原树(层序): ";
    printVector(levelOrder(root4));
    
    TreeNode* inverted4 = solution.invertTree(root4);
    cout << "翻转后: ";
    printVector(levelOrder(inverted4));
    cout << "期望结果: [1]" << endl;
    
    // 测试用例5: 偏斜树（只有左子树）
    cout << "\n=== 测试用例5: 偏斜树 ===" << endl;
    vector<int> vals5 = {1, 2, -1, 3};
    TreeNode* root5 = buildTree(vals5);
    
    cout << "原树(层序): ";
    printVector(levelOrder(root5));
    
    TreeNode* inverted5 = solution.invertTree(root5);
    cout << "翻转后: ";
    printVector(levelOrder(inverted5));
    cout << "期望结果: [1,-1,2,-1,3] (左偏变右偏)" << endl;
    
    cout << "\n=== 所有测试完成 ===" << endl;
    cout << "请独立实现 invertTree 方法！" << endl;
    
    return 0;
}

/*
 * 编译运行指令:
 * g++ -std=c++11 -o problem_226 problem_226_template.cpp && ./problem_226
 * 
 * 学习重点:
 * 1. 掌握二叉树递归的核心思维：大问题分解为子问题
 * 2. 理解递归与迭代两种实现方式的本质区别
 * 3. 熟练掌握二叉树的基本操作：遍历、构建、输出
 * 4. 建立树形变换的思维模式
 * 
 * 延伸题目:
 * - 101. 对称二叉树 (判断树是否对称)
 * - 100. 相同的树 (判断两树是否相同)
 * - 572. 另一个树的子树 (子树匹配)
 * - 951. 翻转等价二叉树 (翻转后是否相等)
 */