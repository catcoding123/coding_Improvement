/*
 * 94. 二叉树的中序遍历 (Medium)
 * 
 * LeetCode链接: https://leetcode.cn/problems/binary-tree-inorder-traversal/
 * 
 * 题目描述:
 * 给定一个二叉树的根节点 root ，返回它的中序遍历。
 * 
 * 示例1:
 * 输入: root = [1,null,2,3]
 * 输出: [1,3,2]
 * 
 *   1
 *    \
 *     2
 *    /
 *   3
 * 
 * 中序遍历顺序: 左 → 根 → 右
 * 
 * 示例2:
 * 输入: root = []
 * 输出: []
 * 
 * 示例3:
 * 输入: root = [1]
 * 输出: [1]
 * 
 * 示例4:
 * 输入: root = [1,2]
 * 输出: [2,1]
 * 
 * 示例5:
 * 输入: root = [1,null,2]
 * 输出: [1,2]
 * 
 * 约束条件:
 * - 树中节点数目在范围 [0, 100] 内
 * - -100 <= Node.val <= 100
 * 
 * 进阶: 递归算法很简单，你可以通过迭代算法来实现吗？
 * 
 * 算法分析:
 * 思路提示: 
 * 1. 递归思维：中序遍历 = 左子树中序 + 根节点 + 右子树中序
 * 2. 迭代思维：用栈模拟递归，先一路向左到底，再弹栈处理
 * 3. Morris遍历：O(1)空间复杂度，利用线索二叉树思想
 * 
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - h为树的高度
 * 
 * 易错点预测:
 * 1. 迭代版本的栈操作顺序：何时入栈、何时出栈、何时访问
 * 2. 边界条件：空树的处理
 * 3. 中序遍历在BST中的特殊性质：结果是有序序列
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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
     * 方法1: 递归实现 - 最直观
     * 核心思想: 中序遍历 = 左子树中序 + 根节点 + 右子树中序
     */
    vector<int> inorderTraversal(TreeNode* root) {
        // TODO: 实现递归中序遍历
        // 提示: 
        // 1. 处理空节点
        // 2. 递归遍历左子树
        // 3. 访问根节点
        // 4. 递归遍历右子树
        if(root == nullptr) return {};
        vector<int> result;
        vector<int> left = inorderTraversal(root->left);
        vector<int> right = inorderTraversal(root->right);

        result.insert(result.end(),left.begin(),left.end());
        result.push_back(root->val);
        result.insert(result.end(),right.begin(), right.end());
        return result;
    }
    
    /**
     * 方法2: 迭代实现 (栈模拟递归) ⭐ 重点掌握
     * 核心思想: 用栈模拟递归调用栈，先走到最左下，再依次弹栈处理
     */
    vector<int> inorderTraversalIterative(TreeNode* root) {
        // TODO: 实现迭代中序遍历
        // 提示:
        // 1. 用栈存储待处理节点
        // 2. 先一路向左，把路径上的节点都入栈
        // 3. 弹栈时访问节点，然后处理右子树
        // 4. 重复直到栈空且当前节点为空
        
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* curr = root;
        while(!st.empty() || curr != nullptr) {
            while(curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }

            auto node = st.top();
            result.push_back(node->val);
            st.pop();

            curr = node->right;  //易错

        }
        
        return result;
    }
    
    /**
     * 方法3: Morris遍历 - O(1)空间复杂度 ⭐⭐ 进阶
     * 核心思想: 利用线索二叉树，将空的右子树指向后继节点
     */
    vector<int> inorderTraversalMorris(TreeNode* root) {
        // TODO: 实现Morris中序遍历
        // 提示:
        // 1. 找到当前节点的前驱节点(左子树的最右节点)
        // 2. 如果前驱的right为空，建立线索，移动到左子树
        // 3. 如果前驱的right指向当前节点，说明左子树已遍历完，断开线索
        // 4. 访问当前节点，移动到右子树
        
        vector<int> result;
        TreeNode* curr = root;
        
        return result;
    }
    
    /**
     * 辅助函数: 递归版本的具体实现
     */
    void helper(TreeNode* root, vector<int>& result) {
        // TODO: 实现递归辅助函数
        
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

// 辅助函数：前序遍历验证树结构
void preorderPrint(TreeNode* root) {
    if (!root) {
        cout << "null ";
        return;
    }
    cout << root->val << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
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
    vector<int> vals1 = {1, -1, 2, 3};  // [1,null,2,3]
    TreeNode* root1 = buildTree(vals1);
    
    cout << "树结构(前序): ";
    preorderPrint(root1);
    cout << endl;
    
    vector<int> result1 = solution.inorderTraversal(root1);
    cout << "中序遍历: ";
    printVector(result1);
    cout << "期望结果: [1,3,2]" << endl;
    
    // 测试用例2: 空树
    cout << "\n=== 测试用例2: 空树 ===" << endl;
    TreeNode* root2 = nullptr;
    vector<int> result2 = solution.inorderTraversal(root2);
    cout << "中序遍历: ";
    printVector(result2);
    cout << "期望结果: []" << endl;
    
    // 测试用例3: 单节点
    cout << "\n=== 测试用例3: 单节点 ===" << endl;
    vector<int> vals3 = {1};
    TreeNode* root3 = buildTree(vals3);
    
    cout << "树结构(前序): ";
    preorderPrint(root3);
    cout << endl;
    
    vector<int> result3 = solution.inorderTraversal(root3);
    cout << "中序遍历: ";
    printVector(result3);
    cout << "期望结果: [1]" << endl;
    
    // 测试用例4: 只有左子树
    cout << "\n=== 测试用例4: 只有左子树 ===" << endl;
    vector<int> vals4 = {1, 2};  // [1,2]
    TreeNode* root4 = buildTree(vals4);
    
    cout << "树结构(前序): ";
    preorderPrint(root4);
    cout << endl;
    
    vector<int> result4 = solution.inorderTraversal(root4);
    cout << "中序遍历: ";
    printVector(result4);
    cout << "期望结果: [2,1]" << endl;
    
    // 测试用例5: 只有右子树
    cout << "\n=== 测试用例5: 只有右子树 ===" << endl;
    vector<int> vals5 = {1, -1, 2};  // [1,null,2]
    TreeNode* root5 = buildTree(vals5);
    
    cout << "树结构(前序): ";
    preorderPrint(root5);
    cout << endl;
    
    vector<int> result5 = solution.inorderTraversal(root5);
    cout << "中序遍历: ";
    printVector(result5);
    cout << "期望结果: [1,2]" << endl;
    
    // 测试用例6: 完全二叉树
    cout << "\n=== 测试用例6: 完全二叉树 ===" << endl;
    vector<int> vals6 = {4, 2, 6, 1, 3, 5, 7};
    TreeNode* root6 = buildTree(vals6);
    
    cout << "树结构(前序): ";
    preorderPrint(root6);
    cout << endl;
    
    vector<int> result6 = solution.inorderTraversal(root6);
    cout << "中序遍历: ";
    printVector(result6);
    cout << "期望结果: [1,2,3,4,5,6,7] (BST的中序遍历是有序的)" << endl;
    
    // 比较三种方法的结果
    cout << "\n=== 三种方法结果对比 ===" << endl;
    cout << "递归版本: ";
    printVector(solution.inorderTraversal(root6));
    
    cout << "迭代版本: ";
    printVector(solution.inorderTraversalIterative(root6));
    
    cout << "Morris版本: ";
    printVector(solution.inorderTraversalMorris(root6));
    
    cout << "\n=== 所有测试完成 ===" << endl;
    cout << "请独立实现三种中序遍历方法！" << endl;
    
    return 0;
}

/*
 * 编译运行指令:
 * g++ -std=c++11 -o problem_94 problem_94_template.cpp && ./problem_94
 * 
 * 学习重点:
 * 1. 掌握递归的中序遍历模式：左→根→右
 * 2. 理解栈模拟递归的通用思路：先深入再回溯
 * 3. 掌握Morris遍历的O(1)空间优化技巧
 * 4. 理解中序遍历在BST中的特殊意义：有序输出
 * 
 * 延伸题目:
 * - 144. 二叉树的前序遍历 (根→左→右)
 * - 145. 二叉树的后序遍历 (左→右→根)
 * - 102. 二叉树的层序遍历 (BFS)
 * - 98. 验证二叉搜索树 (利用中序遍历有序性)
 * - 230. 二叉搜索树中第K小的元素 (中序遍历应用)
 */