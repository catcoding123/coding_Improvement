/**
 * 108. 将有序数组转换为二叉搜索树 (Easy)
 * 
 * LeetCode链接: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
 * 
 * 题目描述:
 * 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 的二叉搜索树。
 * 高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。
 * 
 * 示例 1:
 * 输入: nums = [-10,-3,0,5,9]
 * 输出: [0,-3,9,-10,null,5]
 *        0
 *       / \
 *     -3   9
 *     /   /
 *   -10  5
 * 
 * 示例 2:
 * 输入: nums = [1,3]
 * 输出: [3,1] 或者 [1,null,3]
 *      3     1
 *     /       \
 *    1         3
 * 
 * 约束条件:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums 按 严格递增 顺序排列
 * 
 * 算法分析:
 * 这道题完美结合了你已掌握的多个核心概念：
 * 1. BST性质：中序遍历有序 (你在98/99题中深度理解)
 * 2. 分治思想：将大问题分解为子问题
 * 3. 递归构建：类似你在二叉树专题中掌握的递归模式
 * 4. 平衡性保证：每次选择中点作为根节点
 * 
 * 核心洞察:
 * - 有序数组的中序遍历 = BST的中序遍历
 * - 选择中点作为根，保证左右子树大小相近 → 平衡性
 * - 递归构建左右子树，每个子问题都是相同的结构
 * 
 * 时间复杂度: O(n) - 每个节点创建一次
 * 空间复杂度: O(log n) - 递归栈深度，树的高度
 * 
 * 知识链接:
 * - 98题验证BST → 理解BST性质
 * - 99题恢复BST → 掌握BST结构调整
 * - 230题BST应用 → 熟练BST操作
 * - 108题构建BST → 完成BST知识闭环
 * 
 * 易错点预测:
 * 1. 边界处理：左右区间的正确性
 * 2. 中点选择：mid计算公式
 * 3. 递归参数：区间传递的准确性
 * 4. 空树处理：left > right时的返回
 */

#include <iostream>
#include <vector>
#include <queue>
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
     * 方法1: 分治递归构建 (推荐实现)
     * 
     * 核心思路:
     * 1. 选择数组中点作为根节点 → 保证平衡性
     * 2. 左半部分递归构建左子树
     * 3. 右半部分递归构建右子树
     * 4. 连接根节点与左右子树
     * 
     * 分治思想:
     * - 大问题: 将整个数组转换为BST
     * - 子问题: 将子数组转换为子BST
     * - 组合: 根节点连接左右子BST
     * 
     * TODO: 实现分治递归算法
     */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // TODO: 实现你的解法
        
        // 提示：需要一个辅助递归函数
        // TreeNode* buildTree(vector<int>& nums, int left, int right)
        
        // 思考要点：
        // 1. 递归终止条件是什么？
        // 2. 如何选择根节点？
        // 3. 如何划分左右区间？
        // 4. 如何连接根节点与子树？
        return buildTree(nums, 0, nums.size()-1); // 替换为你的实现
    }
    
private:
    /**
     * 辅助递归函数: 构建BST
     * TODO: 实现区间递归构建
     */
    TreeNode* buildTree(vector<int>& nums, int left, int right) {
        // TODO: 实现递归构建逻辑
        
        // 思考框架：
        // 1. 边界条件检查
        // 2. 计算中点位置
        // 3. 创建根节点
        // 4. 递归构建左子树
        // 5. 递归构建右子树
        // 6. 返回根节点
        if(left > right) return nullptr;

        int mid = (left + right) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = buildTree(nums, left, mid-1);
        node->right = buildTree(nums, mid+1, right);

        return node; // 替换为你的实现
    }
};

/**
 * 扩展思考: 其他构建方式
 * 
 * 你可以尝试的其他方法：
 * 1. 迭代方式构建 (使用栈或队列)
 * 2. 不同的中点选择策略
 * 3. 优化空间复杂度的方法
 */
class SolutionAdvanced {
public:
    /**
     * 方法2: 中序遍历模拟 (挑战实现)
     * 
     * 思路: 按照中序遍历的顺序构建节点
     * 这种方法更抽象，但展示了BST构建的另一种思维
     * 
     * TODO: 如果有兴趣可以尝试实现
     */
    TreeNode* sortedArrayToBSTInorder(vector<int>& nums) {
        // 挑战任务：使用中序遍历的思路构建
        return nullptr;
    }
};

// 测试用例和验证
class TestRunner {
public:
    // 创建测试用例1: [-10,-3,0,5,9]
    vector<int> createTestCase1() {
        return {-10, -3, 0, 5, 9};
    }
    
    // 创建测试用例2: [1,3]
    vector<int> createTestCase2() {
        return {1, 3};
    }
    
    // 创建测试用例3: 单元素数组
    vector<int> createTestCase3() {
        return {0};
    }
    
    // 创建测试用例4: 空数组
    vector<int> createTestCase4() {
        return {};
    }
    
    // 创建测试用例5: 连续数组
    vector<int> createTestCase5() {
        return {1, 2, 3, 4, 5, 6, 7};
    }
    
    // 验证BST性质 (复用98题的验证逻辑)
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        return inorderCheck(root, prev);
    }
    
    bool inorderCheck(TreeNode* node, TreeNode*& prev) {
        if (!node) return true;
        if (!inorderCheck(node->left, prev)) return false;
        if (prev && prev->val >= node->val) return false;
        prev = node;
        return inorderCheck(node->right, prev);
    }
    
    // 验证平衡性
    bool isBalanced(TreeNode* root) {
        return checkBalance(root) != -1;
    }
    
    int checkBalance(TreeNode* node) {
        if (!node) return 0;
        
        int leftHeight = checkBalance(node->left);
        if (leftHeight == -1) return -1;
        
        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1) return -1;
        
        if (abs(leftHeight - rightHeight) > 1) return -1;
        
        return max(leftHeight, rightHeight) + 1;
    }
    
    // 层序遍历打印树结构
    void printLevelOrder(TreeNode* root, const string& prefix = "") {
        if (!root) {
            cout << prefix << "空树" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        cout << prefix << "层序遍历: ";
        
        while (!q.empty()) {
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
    
    // 中序遍历验证
    void printInorder(TreeNode* root, const string& prefix = "") {
        vector<int> result;
        inorderTraversal(root, result);
        cout << prefix << "中序遍历: ";
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
    
    // 运行所有测试
    void runAllTests() {
        Solution solution;
        
        cout << "=== 108. 将有序数组转换为BST 测试 ===" << endl;
        
        // 测试用例1: 标准情况
        cout << "\n测试用例1: 标准5元素数组 [-10,-3,0,5,9]" << endl;
        vector<int> test1 = createTestCase1();
        cout << "输入数组: ";
        for (int num : test1) cout << num << " ";
        cout << endl;
        
        TreeNode* result1 = solution.sortedArrayToBST(test1);
        printLevelOrder(result1, "构建结果: ");
        printInorder(result1, "中序验证: ");
        cout << "BST验证: " << (isValidBST(result1) ? "✓ 有效" : "✗ 无效") << endl;
        cout << "平衡验证: " << (isBalanced(result1) ? "✓ 平衡" : "✗ 不平衡") << endl;
        
        // 测试用例2: 简单情况
        cout << "\n测试用例2: 简单2元素数组 [1,3]" << endl;
        vector<int> test2 = createTestCase2();
        TreeNode* result2 = solution.sortedArrayToBST(test2);
        printLevelOrder(result2, "构建结果: ");
        cout << "BST验证: " << (isValidBST(result2) ? "✓ 有效" : "✗ 无效") << endl;
        cout << "平衡验证: " << (isBalanced(result2) ? "✓ 平衡" : "✗ 不平衡") << endl;
        
        // 测试用例3: 边界情况
        cout << "\n测试用例3: 单元素数组 [0]" << endl;
        vector<int> test3 = createTestCase3();
        TreeNode* result3 = solution.sortedArrayToBST(test3);
        printLevelOrder(result3, "构建结果: ");
        cout << "BST验证: " << (isValidBST(result3) ? "✓ 有效" : "✗ 无效") << endl;
        cout << "平衡验证: " << (isBalanced(result3) ? "✓ 平衡" : "✗ 不平衡") << endl;
        
        // 测试用例4: 连续数组
        cout << "\n测试用例4: 连续7元素数组 [1,2,3,4,5,6,7]" << endl;
        vector<int> test4 = createTestCase5();
        TreeNode* result4 = solution.sortedArrayToBST(test4);
        printLevelOrder(result4, "构建结果: ");
        printInorder(result4, "中序验证: ");
        cout << "BST验证: " << (isValidBST(result4) ? "✓ 有效" : "✗ 无效") << endl;
        cout << "平衡验证: " << (isBalanced(result4) ? "✓ 平衡" : "✗ 不平衡") << endl;
        
        cout << "\n所有测试完成！" << endl;
        cout << "重点观察：构建的树是否满足BST性质且高度平衡" << endl;
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
 * 1. **分治思想的应用**:
 *    - 选择中点作为根节点保证平衡
 *    - 递归处理左右子数组
 *    - 组合子结果形成完整BST
 * 
 * 2. **BST构建的核心原理**:
 *    - 有序数组 → 选中点为根 → 平衡BST
 *    - 中序遍历的逆向思维应用
 *    - 递归边界的正确设置
 * 
 * 3. **与之前学习的知识联系**:
 *    - 98题BST验证：验证构建结果的正确性
 *    - 99题BST恢复：理解BST结构的重要性
 *    - 230题BST应用：构建后可进行高效查找
 * 
 * 4. **算法设计模式**:
 *    - 递归设计：参数定义、边界条件、递归关系
 *    - 分治策略：问题分解、子问题求解、结果合并
 *    - 平衡保证：通过中点选择确保树的平衡性
 * 
 * 5. **扩展思考**:
 *    - 不同中点选择对树形状的影响
 *    - 如何扩展到链表转BST
 *    - 平衡BST的其他构建方法
 * 
 * 延伸题目:
 * - 109. 有序链表转换BST（类似思路）
 * - 110. 平衡二叉树（验证平衡性）
 * - 1382. 将BST转换为大根堆（BST变换）
 */