/*
 * 101. 对称二叉树 (Symmetric Tree)
 * 
 * 链接: https://leetcode.cn/problems/symmetric-tree/
 * 难度: Easy
 * 
 * 题目描述：
 * 给你一个二叉树的根节点 root ，检查它是否轴对称。
 * 
 * 示例 1:
 * 输入：root = [1,2,2,3,4,4,3]
 * 输出：true
 * 解释：
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * 
 * 示例 2:
 * 输入：root = [1,2,2,null,3,null,3]
 * 输出：false
 * 解释：
 *     1
 *    / \
 *   2   2
 *    \   \
 *     3   3
 * 
 * 约束条件：
 * - 树中节点数目在范围 [1, 1000] 内
 * - -100 <= Node.val <= 100
 * 
 * 进阶：你可以运用递归和迭代两种方法解决这个问题吗？
 * 
 * 算法分析：
 * 这道题引入了全新的递归模式：双节点同步递归！
 * 
 * 核心洞察：对称二叉树 = 左子树和右子树互为镜像
 * - 镜像定义：左子树的左孩子 对应 右子树的右孩子
 * - 镜像定义：左子树的右孩子 对应 右子树的左孩子
 * - 对应节点的值必须相等
 * 
 * 方法1: 双节点递归 (推荐) ⭐⭐⭐
 * - 思路: 定义helper(left, right)判断两个子树是否镜像对称
 * - 时间复杂度: O(n) - 每个节点访问一次
 * - 空间复杂度: O(h) - 递归栈深度
 * - 优势: 逻辑清晰，代码简洁
 * 
 * 方法2: 迭代 + 队列/栈模拟
 * - 思路: 用队列保存成对的节点，逐一比较
 * - 时间复杂度: O(n)
 * - 空间复杂度: O(n) - 队列存储
 * - 优势: 避免递归栈溢出
 * 
 * 方法3: 中序遍历对比 (错误思路!)
 * - 陷阱: 单纯的中序遍历不能判断对称性
 * - 反例: [1,2,2,2,null,2] 中序遍历对称但结构不对称
 * - 教训: 必须同时考虑结构和值
 * 
 * 算法思维突破：
 * 从之前学过的"单节点递归"升级到"双节点同步递归"
 * - 104题深度：f(node) = max(f(left), f(right)) + 1
 * - 226题翻转：f(node) = swap(f(left), f(right))
 * - 98题验证：f(node, &prev) 单节点+状态传递
 * - 101题对称：f(left, right) 双节点同步比较 ← 全新模式！
 * 
 * 易错点预测：
 * 1. 镜像对应关系：left->left对应right->right容易搞混
 * 2. 空节点处理：两个都为空返回true，一个为空返回false
 * 3. 递归调用参数：(left->left, right->right)和(left->right, right->left)
 * 4. 边界条件：根节点为空的特殊处理
 */

#include <iostream>
#include <queue>
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
    // 方法1: 双节点递归 (推荐实现)
    // 核心思想：对称 = 左右子树互为镜像
    bool isSymmetric(TreeNode* root) {
        // TODO: 实现双节点递归版本
        // 提示: 空根节点特殊处理，然后调用helper(root->left, root->right)
        // 关键: 理解镜像的递归定义
        if (!root) return true;  // 空树对称
        return isMirror(root->left, root->right);
    }
    
private:
    // 辅助函数：判断两个子树是否镜像对称
    bool isMirror(TreeNode* left, TreeNode* right) {
        // TODO: 实现双节点递归核心逻辑
        // 递归终止条件:
        // 1. 两个都为空 -> true
        // 2. 一个为空一个不为空 -> false
        // 3. 值不相等 -> false
        // 递归调用:
        // 镜像条件: left->left对应right->right, left->right对应right->left
        if(!left && !right) return true;
        if (!left || !right) return false;

        if(left->val != right->val) return false;
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }
    
public:
    // 方法2: 迭代 + 队列模拟双节点递归
    bool isSymmetricIterative(TreeNode* root) {
        // TODO: 实现迭代版本
        // 提示: 用队列存储成对的节点(left, right)
        // 每次取出一对节点进行比较，并将子节点按镜像顺序入队
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        // 每次弹出两个就可以实现类似pair

        while (!q.empty()) {
            // TODO: 完成队列处理逻辑
            // 1. 取出一对节点
            // 2. 比较节点值和空状态
            // 3. 将子节点按镜像顺序入队
            TreeNode* left = q.front();
            q.pop();  // 和双端队列dequeue区别，这个也记录到错题集里面
            TreeNode* right = q.front();
            q.pop();

            //比较
            if(!left && !right) continue; // 这个容易错
            if(!left || !right) return false; // 以上这两句细节漏掉了

            if(left->val != right->val) return false;

            //写入queue
            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);

        }
        
        return true;
    }
    
    // 方法3: 错误示例 - 中序遍历对比 (展示错误思路)
    bool isSymmetricWrong(TreeNode* root) {
        // TODO: 实现错误版本用于学习
        // 这个方法为什么错误？
        // 反例: [1,2,2,2,null,2] 会被误判为对称
        return false;
    }
};

// 辅助函数：构建测试用的二叉树
TreeNode* buildSymmetricTree1() {
    // 构建示例1: [1,2,2,3,4,4,3] - 对称
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    return root;
}

TreeNode* buildAsymmetricTree1() {
    // 构建示例2: [1,2,2,null,3,null,3] - 不对称
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(3);
    return root;
}

TreeNode* buildSingleNode() {
    // 构建单节点: [1] - 对称
    return new TreeNode(1);
}

TreeNode* buildSymmetricTree2() {
    // 构建复杂对称树: [5,4,4,3,null,null,3,2,null,null,2]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(4);
    root->left->left = new TreeNode(3);
    root->right->right = new TreeNode(3);
    root->left->left->left = new TreeNode(2);
    root->right->right->right = new TreeNode(2);
    return root;
}

TreeNode* buildTrapTree() {
    // 构建陷阱案例: [1,2,2,2,null,2] - 值对称但结构不对称
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(2);
    root->right->right = new TreeNode(2);
    return root;
}

// 清理内存的辅助函数
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 可视化辅助：层序遍历打印(便于观察对称性)
void levelOrderPrint(TreeNode* root) {
    if (!root) {
        cout << "Empty tree" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "null ";
            }
        }
        cout << endl;
    }
}

int main() {
    Solution solution;
    
    cout << "=== 101. 对称二叉树 测试 ===" << endl;
    
    // 测试用例1: 对称树 [1,2,2,3,4,4,3]
    cout << "\n测试1 - 对称树 [1,2,2,3,4,4,3]:" << endl;
    TreeNode* tree1 = buildSymmetricTree1();
    cout << "层序遍历:" << endl;
    levelOrderPrint(tree1);
    cout << "是否对称: " << (solution.isSymmetric(tree1) ? "true" : "false") << endl;
    cout << "预期结果: true" << endl;
    
    // 测试用例2: 不对称树 [1,2,2,null,3,null,3]
    cout << "\n测试2 - 不对称树 [1,2,2,null,3,null,3]:" << endl;
    TreeNode* tree2 = buildAsymmetricTree1();
    cout << "层序遍历:" << endl;
    levelOrderPrint(tree2);
    cout << "是否对称: " << (solution.isSymmetric(tree2) ? "true" : "false") << endl;
    cout << "预期结果: false" << endl;
    
    // 测试用例3: 单节点 [1]
    cout << "\n测试3 - 单节点 [1]:" << endl;
    TreeNode* tree3 = buildSingleNode();
    cout << "层序遍历:" << endl;
    levelOrderPrint(tree3);
    cout << "是否对称: " << (solution.isSymmetric(tree3) ? "true" : "false") << endl;
    cout << "预期结果: true" << endl;
    
    // 测试用例4: 复杂对称树
    cout << "\n测试4 - 复杂对称树:" << endl;
    TreeNode* tree4 = buildSymmetricTree2();
    cout << "层序遍历:" << endl;
    levelOrderPrint(tree4);
    cout << "是否对称: " << (solution.isSymmetric(tree4) ? "true" : "false") << endl;
    cout << "预期结果: true" << endl;
    
    // 测试用例5: 陷阱案例 - 值对称但结构不对称
    cout << "\n测试5 - 陷阱案例 [1,2,2,2,null,2]:" << endl;
    TreeNode* tree5 = buildTrapTree();
    cout << "层序遍历:" << endl;
    levelOrderPrint(tree5);
    cout << "是否对称: " << (solution.isSymmetric(tree5) ? "true" : "false") << endl;
    cout << "预期结果: false (结构不对称)" << endl;
    
    // 清理内存
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(tree3);
    deleteTree(tree4);
    deleteTree(tree5);
    
    cout << "\n=== 学习重点 ===" << endl;
    cout << "1. 掌握双节点同步递归：全新的递归思维模式" << endl;
    cout << "2. 理解镜像对称定义：left->left对应right->right" << endl;
    cout << "3. 对比单节点递归差异：f(left,right) vs f(node)" << endl;
    cout << "4. 递归边界条件处理：空节点的四种组合情况" << endl;
    cout << "5. 算法思维扩展：从单一操作到配对比较" << endl;
    
    cout << "\n=== 算法思维进化 ===" << endl;
    cout << "• 单节点递归 (104深度/226翻转): 操作单个节点" << endl;
    cout << "• 状态传递递归 (98验证/230查找): 单节点+全局状态" << endl;
    cout << "• 双节点递归 (101对称): 同步比较两个节点 ← 新突破!" << endl;
    cout << "• 为后续学习铺路: 树的相似性、路径问题、构建问题" << endl;
    
    return 0;
}