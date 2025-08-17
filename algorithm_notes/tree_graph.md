# 树和图专题

## 专题概述

树和图是重要的非线性数据结构，在算法面试中占据重要地位。本专题涵盖：
- **二叉树遍历**: 前序、中序、后序、层序遍历
- **二叉搜索树**: BST性质、验证、操作
- **树的构造**: 数组转BST、序列化反序列化
- **图算法**: DFS、BFS、拓扑排序、最短路径

**核心思想**: 递归思维、分治策略、层次遍历、图的搜索算法。

## 核心题目

### 104. 二叉树最大深度 (Easy) - 递归入门
**核心思想**: 大树问题分解为子树问题
**递归公式**: `max(左深度, 右深度) + 1`
**三种实现**: 递归DFS、BFS层序、DFS栈模拟

### 226. 翻转二叉树 (Easy) - 树形变换
**核心洞察**: 算法局部独立性，每个节点只管自己的左右交换
**重要**: BFS≈DFS适用于局部独立操作
**易错**: 递归时先保存子树指针再交换

### 94. 二叉树中序遍历 (Medium) - 栈模拟递归
**核心模式**: "向左深入→弹栈访问→右转重复"
**关键**: curr指针驱动，栈保存回溯路径
**应用**: BST中序遍历有序，可用于验证和查找

### 98. 验证BST (Medium) - 引用传递+中序遍历
**核心思想**: 利用BST中序遍历严格递增性质
**关键突破**: 引用传递`TreeNode*& prev`维护全局前驱状态
**BST定义**: 不是简单父子关系，而是整体子树约束

### 230. BST第K小元素 (Medium) - 知识融合+提前终止
**核心思想**: 中序遍历+计数器+提前终止优化
**知识融合**: 98题BST性质 + 94题中序遍历 + 引用传递
**效率优化**: O(H+k) vs O(n)，提前终止避免无效遍历

### 101. 对称二叉树 (Easy) - 双节点递归突破
**算法革命**: 从单节点递归到双节点同步递归的思维跃迁
**对称关系**: 左左↔右右、左右↔右左的交叉对应
**递归设计**: 双参数、边界处理、镜像调用的系统思考

### 108. 将有序数组转换为BST (Easy) - 分治构建+平衡保证
**核心思想**: 分治递归构建，选择中点作为根节点保证平衡性
**算法流程**: 选择中点→构建根节点→递归构建左右子树
**平衡保证**: 中点选择使左右子树节点数差不超过1

## 树遍历核心模板

### 递归遍历模板
```cpp
// 前序遍历：根→左→右
void preorder(TreeNode* root) {
    if (!root) return;
    visit(root);           // 访问根节点
    preorder(root->left);  // 遍历左子树
    preorder(root->right); // 遍历右子树
}

// 中序遍历：左→根→右
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);   // 遍历左子树
    visit(root);           // 访问根节点
    inorder(root->right);  // 遍历右子树
}

// 后序遍历：左→右→根
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);  // 遍历左子树
    postorder(root->right); // 遍历右子树
    visit(root);            // 访问根节点
}
```

### 迭代遍历模板
```cpp
// 中序遍历迭代版
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (curr || !st.empty()) {
        // 向左深入
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        // 弹栈访问
        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        
        // 转向右子树
        curr = curr->right;
    }
    return result;
}
```

### 层序遍历模板
```cpp
// BFS层序遍历
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            level.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
    }
    return result;
}
```

## BST核心模板

### BST验证模板
```cpp
// 中序遍历验证BST
bool isValidBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    return inorder(root, prev);
}

bool inorder(TreeNode* root, TreeNode*& prev) {
    if (!root) return true;
    
    if (!inorder(root->left, prev)) return false;
    
    if (prev && prev->val >= root->val) return false;
    prev = root;
    
    return inorder(root->right, prev);
}
```

### BST查找模板
```cpp
// BST查找
TreeNode* searchBST(TreeNode* root, int val) {
    while (root && root->val != val) {
        root = (val < root->val) ? root->left : root->right;
    }
    return root;
}

// BST插入
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}
```

## 图算法基础

### DFS模板
```cpp
// 图DFS
void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}
```

### BFS模板
```cpp
// 图BFS
void bfs(vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

## 易错点总结

1. **空节点检查**: 递归前检查节点是否为空
2. **引用传递**: BST验证中prev需要引用传递
3. **遍历顺序**: 中序遍历BST得到有序序列
4. **双节点递归**: 对称树需要同时递归两个节点
5. **层序遍历**: 每层处理前记录当前队列大小
6. **递归边界**: 正确处理叶子节点和空节点

## 相关题目分类

- **树遍历**: 94中序遍历、144前序遍历、145后序遍历、102层序遍历
- **BST相关**: 98验证BST、99恢复BST、230BST第K小元素、108数组转BST
- **树构造**: 105前中序构造、106中后序构造、297序列化反序列化
- **树性质**: 101对称树、104最大深度、111最小深度、543二叉树直径
- **图搜索**: 200岛屿数量、207课程表、210课程表II
- **最短路径**: 743网络延迟时间、787K站中转内最便宜的航班

---
*树的问题关键在于选择合适的遍历方式，图的问题重点是DFS/BFS的灵活应用*