# 二叉树与图论专题

## 二叉树算法体系

本专题目录
- [104. 二叉树最大深度](#bt-104)
- [226. 翻转二叉树](#bt-226)
- [94. 二叉树中序遍历](#bt-94)
- [98. 验证BST](#bt-98)
- [230. BST第K小元素](#bt-230)
- [101. 对称二叉树](#bt-101)
- [99. 恢复BST](#bt-99)
- [108. 将有序数组转换为BST](#bt-108)

## 图论算法体系

本专题目录
- [200. 岛屿数量](#graph-200)

---

<a id="bt-104"></a>
### 104. 二叉树最大深度 (Easy) - 递归入门 ⭐⭐⭐
**核心思想**: 大树问题分解为子树问题，递归思维的经典入门
**算法本质**: 后序遍历的递归模式，子树结果决定父树结果

#### 题目链接
https://leetcode.cn/problems/maximum-depth-of-binary-tree/

#### 核心算法原理

**问题分析**:
- 二叉树深度 = 根节点到最远叶子节点的最长路径上的节点数
- 递归关系：当前节点深度 = max(左子树深度, 右子树深度) + 1
- 递归出口：空节点深度为0

#### 三种经典实现

**方法1: 递归DFS - 最直观** ⭐ 推荐
```cpp
int maxDepthRecursive(TreeNode* root) {
    // 递归出口：空节点深度为0
    if (!root) return 0;
    
    // 递归关系：当前深度 = max(左深度, 右深度) + 1
    return max(maxDepthRecursive(root->left), 
               maxDepthRecursive(root->right)) + 1;
}
```

**方法2: 迭代BFS - 层序遍历**
```cpp
int maxDepthBFS(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    
    while (!q.empty()) {
        int levelSize = q.size();  // 当前层的节点数
        
        // 处理当前层的所有节点
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        depth++;  // 处理完一层，深度+1
    }
    
    return depth;
}
```

**方法3: 迭代DFS - 栈模拟递归**
```cpp
int maxDepthDFS(TreeNode* root) {
    if (!root) return 0;
    
    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});
    int maxDepth = 1;
    
    while (!st.empty()) {
        auto [node, depth] = st.top();
        st.pop();
        
        maxDepth = max(maxDepth, depth);
        
        // 子节点入栈，深度+1
        if (node->left) st.push({node->left, depth + 1});
        if (node->right) st.push({node->right, depth + 1});
    }
    
    return maxDepth;
}
```

#### 错误分析与改进

根据error_tracking_system.md中的记录，此题常见错误：

**错误1: 指针访问语法错误**
```cpp
// ❌ 错误使用
node.val     // 对象访问语法
node.left    // 应该用于对象

// ✅ 正确使用  
node->val    // 指针访问语法
node->left   // 用于指针
```

**错误2: 自增操作副作用**
```cpp
// ❌ 错误：depth++会改变原值
st.push({node->left, depth++});

// ✅ 正确：depth+1不改变原值
st.push({node->left, depth + 1});
```

**错误3: 循环条件动态变化**
```cpp
// ❌ 错误：q.size()在循环中动态变化
for (int i = 0; i < q.size(); i++) {
    // q.size()会在循环中改变
}

// ✅ 正确：提前固定循环边界
int levelSize = q.size();
for (int i = 0; i < levelSize; i++) {
    // 使用固定的levelSize
}
```

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点访问一次
**空间复杂度**: 
- 递归: O(h) - 递归栈深度，h为树高
- BFS: O(w) - 队列最大宽度，w为树的最大宽度
- DFS栈: O(h) - 栈的最大深度

**核心优势**:
1. **递归版本**: 代码简洁，思路直观
2. **BFS版本**: 层次化处理，便于扩展
3. **DFS栈版本**: 避免递归栈溢出

#### 扩展应用
- **111. 二叉树最小深度**: 找到最近叶子节点的深度
- **543. 二叉树直径**: 任意两节点间的最长路径
- **124. 二叉树最大路径和**: 路径权值和最大值

---

<a id="bt-226"></a>
### 226. 翻转二叉树 (Easy) - 树形变换 ⭐⭐⭐
**核心思想**: 算法局部独立性，每个节点只管自己的左右交换
**算法本质**: 前序遍历的应用，先处理当前节点再递归子树

#### 题目链接
https://leetcode.cn/problems/invert-binary-tree/

#### 核心算法原理

**问题分析**:
- 翻转二叉树就是交换每个节点的左右子树
- 操作具有局部独立性：每个节点的翻转不依赖其他节点
- 可以用递归或迭代两种方式实现

#### 算法核心实现

**方法1: 递归实现** ⭐ 推荐
```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    // 关键：先保存子树指针，避免递归时指针混乱
    TreeNode* left = invertTree(root->left);   // 翻转左子树
    TreeNode* right = invertTree(root->right); // 翻转右子树
    
    // 交换左右子树
    root->left = right;
    root->right = left;
    
    return root;
}
```

**方法2: 迭代实现（队列）**
```cpp
TreeNode* invertTreeIterative(TreeNode* root) {
    if (!root) return nullptr;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        // 交换当前节点的左右子树
        swap(node->left, node->right);
        
        // 将非空子节点加入队列
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    
    return root;
}
```

#### 错误分析与改进

根据error_tracking_system.md中的记录，此题容易出现递归指针混乱：

**错误实现**:
```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    root->left = invertTree(root->right);   // 先把右子树赋给左边
    root->right = invertTree(root->left);   // ❌ 这里root->left已经是原来的右子树了！
    
    return root;
}
```

**问题分析**:
- 第二行递归调用时，`root->left`已经被修改为原来的`root->right`
- 导致实际上递归调用了`invertTree(原右子树)`两次，而原左子树被忽略
- 造成无限递归或逻辑错误

**正确解决方案**:
```cpp
// 方案1: 先保存指针再交换
TreeNode* left = invertTree(root->left);
TreeNode* right = invertTree(root->right);
root->left = right;
root->right = left;

// 方案2: 先交换再递归
swap(root->left, root->right);
invertTree(root->left);
invertTree(root->right);
```

#### 关键理解突破

**1. 算法局部独立性**
- 每个节点的翻转操作相互独立
- BFS和DFS都适用于局部独立的操作
- 不需要考虑全局状态或依赖关系

**2. 前序遍历模式**
- 先处理当前节点（交换左右子树）
- 再递归处理子树（继续翻转）
- 符合"根→左→右"的前序遍历顺序

**3. 指针管理技巧**
- 交换指针时要注意保存原始值
- 避免在递归过程中丢失子树信息
- 使用临时变量或swap函数确保安全

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点访问一次
**空间复杂度**: 
- 递归: O(h) - 递归栈深度
- 迭代: O(w) - 队列最大宽度

**核心优势**:
1. **操作简单**: 只需要交换左右子树
2. **思路清晰**: 局部独立性使算法易理解
3. **实现灵活**: 递归和迭代都容易实现

#### 扩展应用
- **100. 相同的树**: 比较两棵树是否相同
- **101. 对称二叉树**: 判断树是否对称（镜像）
- **951. 翻转等价二叉树**: 判断两棵树是否翻转等价

---

<a id="bt-94"></a>
### 94. 二叉树中序遍历 (Medium) - 栈模拟递归 ⭐⭐⭐
**核心思想**: "向左深入→弹栈访问→右转重复"的迭代模式
**算法本质**: 将递归过程显式化，用栈保存回溯路径

#### 题目链接
https://leetcode.cn/problems/binary-tree-inorder-traversal/

#### 核心算法原理

**中序遍历定义**: 左子树 → 根节点 → 右子树的访问顺序
**递归思维**: 对每个节点，先处理左子树，再访问自己，最后处理右子树
**栈模拟**: 用显式栈替代递归栈，手动控制遍历流程

#### 两种经典实现

**方法1: 递归实现 - 基础版本**
```cpp
vector<int> inorderTraversalRecursive(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

void inorderHelper(TreeNode* node, vector<int>& result) {
    if (!node) return;
    
    inorderHelper(node->left, result);   // 左子树
    result.push_back(node->val);         // 根节点
    inorderHelper(node->right, result);  // 右子树
}
```

**方法2: 迭代实现 - 栈模拟** ⭐ 重点掌握
```cpp
vector<int> inorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (!st.empty() || curr) {
        // 阶段1: 向左深入，所有左节点入栈
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        // 阶段2: 弹栈访问节点
        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        
        // 阶段3: 转向右子树
        curr = curr->right;
    }
    
    return result;
}
```

#### 错误分析与改进

根据error_tracking_system.md中的记录，此题常见状态变量混用错误：

**错误实现**:
```cpp
// 错误：混用临时变量node和控制变量curr
TreeNode* node = st.top();
st.pop();
result.push_back(node->val);
node = node->right;  // ❌ 应该更新curr而非node
```

**问题分析**:
- `node`是临时变量，用于获取栈顶元素
- `curr`是循环驱动变量，负责控制整个遍历流程
- 更新错误变量导致循环逻辑混乱

**正确实现**:
```cpp
curr = st.top();     // ✅ 更新curr，获取栈顶
st.pop();
result.push_back(curr->val);
curr = curr->right;  // ✅ 更新curr，转向右子树
```

#### 关键理解突破

**1. 三阶段循环模式**
```cpp
while (!st.empty() || curr) {
    // 阶段1: 向左深入 - 找到最左节点
    while (curr) {
        st.push(curr);
        curr = curr->left;
    }
    
    // 阶段2: 弹栈访问 - 处理当前节点
    curr = st.top();
    st.pop();
    result.push_back(curr->val);
    
    // 阶段3: 右转重复 - 处理右子树
    curr = curr->right;
}
```

**2. 状态变量作用**
- `curr`: 当前处理的节点，驱动整个遍历流程
- `st`: 栈，保存从根到当前节点路径上的所有节点
- 栈中节点按照"从根到叶"的顺序存储

**3. 循环不变式**
- 进入循环时：curr为待处理节点，栈中保存当前路径
- 循环结束时：curr为空且栈为空，所有节点已访问

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点恰好入栈出栈一次
**空间复杂度**: O(h) - 栈的最大深度等于树的高度

**核心优势**:
1. **避免递归**: 适用于深度很大的树，避免栈溢出
2. **控制灵活**: 可以在遍历过程中暂停、恢复或修改逻辑
3. **模式通用**: 同样的模式可扩展到前序、后序遍历

#### BST应用扩展

**中序遍历在BST中的特殊性质**:
- BST的中序遍历结果是有序序列
- 可用于BST验证、查找第K小元素等问题
- 是98题验证BST和230题第K小元素的核心技术

```cpp
// BST验证的中序遍历应用
bool isValidBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    return inorderValidate(root, prev);
}

bool inorderValidate(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    
    if (!inorderValidate(node->left, prev)) return false;
    
    // 中序遍历的关键检查
    if (prev && prev->val >= node->val) return false;
    prev = node;
    
    return inorderValidate(node->right, prev);
}
```

#### 扩展应用
- **98. 验证BST**: 利用中序遍历的有序性
- **230. BST第K小元素**: 中序遍历找第K个节点
- **99. 恢复BST**: 中序遍历识别逆序对
- **173. BST迭代器**: 中序遍历的迭代器实现

---

<a id="bt-98"></a>
### 98. 验证BST (Medium) - 引用传递+中序遍历 ⭐⭐⭐⭐
**核心思想**: 利用BST中序遍历严格递增性质
**算法本质**: 全局状态维护 + 中序遍历的深度融合

#### 题目链接
https://leetcode.cn/problems/validate-binary-search-tree/

#### 核心算法原理

**BST定义深度理解**:
- ❌ 错误理解：每个节点只需满足"左孩子 < 根 < 右孩子"
- ✅ 正确理解：**左子树所有节点 < 根 < 右子树所有节点**

**经典反例**:
```
    10
   /  \
  5   15
     /  \
    6   20
```
- 局部看：6 < 15 ✓（符合父子关系）
- 全局看：6 < 10 ❌（违反BST定义，6在右子树但小于根10）

#### 核心算法实现

**方法1: 中序遍历 + 引用传递** ⭐ 推荐
```cpp
bool isValidBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    return inorderValidate(root, prev);
}

bool inorderValidate(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;  // 空子树是有效BST
    
    // 验证左子树
    if (!inorderValidate(node->left, prev)) return false;
    
    // 关键检查：当前节点必须大于前驱节点
    if (prev && prev->val >= node->val) return false;
    prev = node;  // 更新前驱状态
    
    // 验证右子树
    return inorderValidate(node->right, prev);
}
```

**方法2: 范围验证递归**
```cpp
bool isValidBST(TreeNode* root) {
    return validateRange(root, LLONG_MIN, LLONG_MAX);
}

bool validateRange(TreeNode* node, long long minVal, long long maxVal) {
    if (!node) return true;
    
    // 当前节点必须在有效范围内
    if (node->val <= minVal || node->val >= maxVal) return false;
    
    // 递归验证左右子树，更新范围约束
    return validateRange(node->left, minVal, node->val) &&
           validateRange(node->right, node->val, maxVal);
}
```

#### 错误分析与深度理解

根据error_tracking_system.md中的记录，此题多个关键错误：

**错误1: BST定义理解错误**
```cpp
// ❌ 错误理解：只检查父子关系
if (root->left && root->left->val >= root->val) return false;
if (root->right && root->right->val <= root->val) return false;

// ✅ 正确理解：需要全局约束检查
// 用中序遍历或范围验证确保整个子树的约束
```

**错误2: 忘记使用引用传递**
```cpp
// ❌ 错误：值传递无法维护全局状态
bool helper(TreeNode* node, TreeNode* prev) {
    // prev的修改不会影响其他递归调用
}

// ✅ 正确：引用传递维护全局前驱状态
bool helper(TreeNode* node, TreeNode*& prev) {
    // prev的修改会在所有递归调用中共享
}
```

**错误3: 空节点理解困惑**
```cpp
// 疑问：为什么空节点返回true？
if (!node) return true;

// 解释：空子树本身就是有效BST，符合所有约束条件
// 这是递归边界的正确处理
```

#### 关键技术突破

**1. 引用传递的本质作用**
```cpp
TreeNode*& prev  // 引用传递，所有递归调用共享同一个prev变量
vs
TreeNode* prev   // 值传递，每次递归都有独立的prev副本
```

**2. 中序遍历的BST性质**
```cpp
// BST中序遍历必须严格递增
1 → 3 → 4 → 6 → 8 → 10 → 14  // 有效BST
1 → 3 → 4 → 6 → 5 → 10 → 14  // 无效BST（6 > 5）
```

**3. 状态管理的复杂性**
- `prev`指针需要在整个中序遍历过程中保持一致
- 每次访问节点时更新`prev`，为下个节点做准备
- 引用传递确保状态在递归调用间正确传递

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点访问一次
**空间复杂度**: O(h) - 递归栈深度

**方法对比**:
| 方法 | 优势 | 劣势 |
|------|------|------|
| **中序遍历** | 代码简洁，利用BST性质 | 需要理解引用传递 |
| **范围验证** | 直接验证BST定义，易理解 | 需要处理边界值 |

#### 学习价值与技能迁移

**核心突破**:
1. **BST定义深度理解**: 从局部约束到全局约束的认知升级
2. **引用传递掌握**: 跨递归调用的状态传递机制
3. **中序遍历应用**: 从基础遍历到BST验证的技能迁移

**知识闭环建立**:
- 94题中序遍历 → 98题BST验证 → 230题第K小元素 → 99题BST恢复
- 形成完整的BST算法技能链

#### 扩展应用
- **230. BST第K小元素**: 中序遍历+计数+提前终止
- **99. 恢复BST**: 中序遍历+逆序对识别
- **108. 有序数组转BST**: BST构建的逆向操作
- **173. BST迭代器**: 中序遍历的迭代器实现

---

<a id="bt-230"></a>
### 230. BST第K小元素 (Medium) - 知识融合+提前终止 ⭐⭐⭐
**核心思想**: BST中序遍历+计数器，O(H+k)优化
**算法本质**: 98题BST性质 + 94题中序遍历 + 引用传递的技术融合

#### 题目链接
https://leetcode.cn/problems/kth-smallest-element-in-a-bst/

#### 核心算法原理

**问题分析**:
- BST的中序遍历结果是递增序列
- 第k小元素就是中序遍历的第k个节点
- 可以提前终止，无需遍历完整棵树

**知识技能复用**:
- **98题技巧**: 引用传递维护全局状态
- **94题技巧**: 中序遍历的递归实现
- **优化思维**: 提前终止避免无效遍历

#### 核心算法实现

**方法1: 递归中序遍历 + 提前终止** ⭐ 推荐
```cpp
int kthSmallest(TreeNode* root, int k) {
    int result = 0;
    inorderTraversal(root, k, result);
    return result;
}

void inorderTraversal(TreeNode* node, int& k, int& result) {
    if (!node || k == 0) return;  // 提前终止条件
    
    // 遍历左子树
    inorderTraversal(node->left, k, result);
    
    // 访问当前节点
    k--;
    if (k == 0) {
        result = node->val;
        return;  // 找到目标，立即返回
    }
    
    // 遍历右子树
    inorderTraversal(node->right, k, result);
}
```

**方法2: 迭代中序遍历**
```cpp
int kthSmallestIterative(TreeNode* root, int k) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    int count = 0;
    
    while (!st.empty() || curr) {
        // 向左深入
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        // 弹栈访问
        curr = st.top();
        st.pop();
        count++;
        
        if (count == k) return curr->val;  // 找到第k个
        
        // 转向右子树
        curr = curr->right;
    }
    
    return -1;  // 不应该到达这里
}
```

#### 关键技术突破

**1. 引用传递的双重作用**
```cpp
void inorderTraversal(TreeNode* node, int& k, int& result) {
    // k: 剩余需要找的元素个数（递减计数器）
    // result: 存储最终答案（找到时设置）
    // 两个引用确保状态在递归间正确传递
}
```

**2. 提前终止优化**
```cpp
// 关键：k==0时立即返回，避免继续递归
if (!node || k == 0) return;

// 找到目标后立即设置结果并返回
if (k == 0) {
    result = node->val;
    return;
}
```

**3. 复杂度优化分析**
- **传统方法**: O(n) - 遍历所有节点
- **提前终止**: O(H+k) - 只遍历到第k个节点
- **最佳情况**: k=1时，只需找到最左节点，O(H)
- **最坏情况**: k=n时，退化为O(n)

#### 算法特点总结

**时间复杂度**: O(H + k) - H是树高，k是目标位置
**空间复杂度**: O(H) - 递归栈深度

**核心优势**:
1. **效率优化**: 提前终止，平均情况下远优于O(n)
2. **技术融合**: 综合运用多个已学技巧
3. **实现灵活**: 递归和迭代两种实现方式

#### 知识融合展示

```cpp
// 98题贡献: 引用传递技巧
void helper(TreeNode* node, int& globalState) { ... }

// 94题贡献: 中序遍历模式  
// 左 → 根 → 右的递归结构

// 230题创新: 提前终止优化
if (k == 0) return;  // 避免无效递归
```

**技能迁移路径**:
```
94题中序遍历 → 掌握基础遍历技巧
       ↓
98题BST验证 → 学会引用传递+BST性质
       ↓  
230题第K小 → 融合技巧+优化思维
```

#### 扩展应用
- **99. 恢复BST**: 中序遍历+逆序对识别
- **173. BST迭代器**: 按需遍历的迭代器设计
- **285. BST中序后继**: 找到指定节点的下一个节点
- **510. BST中序后继II**: 无父指针情况下的后继查找

---

<a id="bt-101"></a>
### 101. 对称二叉树 (Easy) - 双节点递归突破 ⭐⭐⭐
**核心思想**: 从单节点递归到双节点同步递归的思维跃迁
**算法本质**: 镜像关系的递归建模，双参数协调的设计模式

#### 题目链接
https://leetcode.cn/problems/symmetric-tree/

#### 核心算法原理

**对称定义理解**:
- 二叉树对称 ⟺ 左子树和右子树互为镜像
- 镜像关系：左左↔右右、左右↔右左的交叉对应
- 需要同时比较两个节点的值和结构

**递归设计突破**:
- 传统递归：f(node) → 处理单个节点
- 对称递归：f(left, right) → 同步比较两个节点
- 这是递归思维的重要进化

#### 核心算法实现

**方法1: 递归实现** ⭐ 推荐
```cpp
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

bool isMirror(TreeNode* left, TreeNode* right) {
    // 边界情况：四种空节点组合
    if (!left && !right) return true;   // 都为空，对称
    if (!left || !right) return false;  // 一空一非空，不对称
    
    // 值比较 + 结构递归
    if (left->val != right->val) return false;
    
    // 镜像递归：左左↔右右，左右↔右左
    return isMirror(left->left, right->right) && 
           isMirror(left->right, right->left);
}
```

**方法2: 迭代实现（队列）**
```cpp
bool isSymmetricIterative(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    
    while (!q.empty()) {
        TreeNode* left = q.front(); q.pop();
        TreeNode* right = q.front(); q.pop();
        
        // 边界处理
        if (!left && !right) continue;
        if (!left || !right) return false;
        if (left->val != right->val) return false;
        
        // 镜像关系入队：左左↔右右，左右↔右左
        q.push(left->left);
        q.push(right->right);
        q.push(left->right);
        q.push(right->left);
    }
    
    return true;
}
```

#### 错误分析与改进

根据error_tracking_system.md中的记录，此题常见逻辑错误：

**错误1: 逻辑表达式混淆**
```cpp
// ❌ 错误：使用或运算符
return isMirror(left->left, right->right) || 
       isMirror(left->right, right->left);

// ✅ 正确：必须使用且运算符
return isMirror(left->left, right->right) && 
       isMirror(left->right, right->left);
```

**错误2: 迭代返回逻辑错误**
```cpp
// ❌ 错误：一对节点为空就返回true
if (!left && !right) return true;

// ✅ 正确：一对节点为空应该continue继续检查
if (!left && !right) continue;
```

**错误3: 容器API混淆**
```cpp
// ❌ 错误：queue没有pop_front方法
q.pop_front();

// ✅ 正确：queue使用pop()方法
q.pop();
```

#### 关键理解突破

**1. 双节点递归模式**
```cpp
// 单节点递归：处理一个节点
bool processNode(TreeNode* node) {
    if (!node) return true;
    return processNode(node->left) && processNode(node->right);
}

// 双节点递归：同时处理两个节点
bool compareNodes(TreeNode* node1, TreeNode* node2) {
    if (!node1 && !node2) return true;
    if (!node1 || !node2) return false;
    return compareNodes(node1->left, node2->right) && 
           compareNodes(node1->right, node2->left);
}
```

**2. 镜像关系的交叉对应**
```
对称树的镜像关系：
        1
       / \
      2   2        ← 根节点值相同
     / \ / \
    3  4 4  3      ← 交叉对应：左3↔右3，左4↔右4
    
镜像递归调用：
isMirror(左2的左子树, 右2的右子树)  ← 左左↔右右
isMirror(左2的右子树, 右2的左子树)  ← 左右↔右左
```

**3. 边界条件的完整处理**
```cpp
// 四种边界情况的系统处理
if (!left && !right) return true;   // 情况1：都为空
if (!left && right) return false;   // 情况2：左空右非空  
if (left && !right) return false;   // 情况3：左非空右空
// 情况4：都非空，继续比较值和结构
```

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点最多访问一次
**空间复杂度**: 
- 递归: O(h) - 递归栈深度
- 迭代: O(w) - 队列最大宽度

**核心优势**:
1. **思维跃迁**: 从单节点到双节点递归的思维提升
2. **模式通用**: 双节点递归可扩展到其他比较问题
3. **实现灵活**: 递归和迭代都有清晰的实现

#### 学习价值与技能迁移

**递归思维进化**:
```
单节点递归 (104/226): f(node) → 操作单个节点
    ↓
状态传递递归 (98/230): f(node, &state) → 单节点+全局状态  
    ↓
双节点递归 (101): f(left, right) → 同步比较两个节点
```

**技能迁移应用**:
- **100. 相同的树**: 比较两棵树是否完全相同
- **572. 另一个树的子树**: 判断子树关系
- **951. 翻转等价二叉树**: 判断翻转等价关系

#### 扩展应用
- **100. 相同的树**: 双节点递归的直接应用
- **572. 子树判断**: 双节点递归+单节点递归的组合
- **951. 翻转等价二叉树**: 更复杂的双节点递归

---

<a id="bt-99"></a>
### 99. 恢复BST (Hard) - 逆序对识别+状态管理 ⭐⭐⭐⭐
**核心思想**: 中序遍历+逆序对识别+节点值交换
**算法本质**: BST性质的逆向应用，错误检测与修复的算法设计

#### 题目链接
https://leetcode.cn/problems/recover-binary-search-tree/

#### 核心算法原理

**问题分析**:
- BST中有且仅有两个节点的值被错误交换
- BST的中序遍历本应严格递增
- 错误交换会在中序遍历中产生1-2个逆序对
- 通过识别逆序对可以定位错误节点

**逆序对模式分析**:
1. **相邻节点交换**: 产生1个逆序对
   - 例如：[1,3,2,4] → 逆序对(3,2)
   - 第一次发现逆序对时，同时设置firstError和secondError
   
2. **不相邻节点交换**: 产生2个逆序对  
   - 例如：[1,4,3,2,5] → 逆序对(4,3)和(3,2)
   - 第一次设置firstError，第二次仅更新secondError

#### 核心算法实现

```cpp
void recoverTree(TreeNode* root) {
    TreeNode* firstError = nullptr;
    TreeNode* secondError = nullptr;
    TreeNode* prev = nullptr;
    
    // 中序遍历识别逆序对
    inorderTraversal(root, prev, firstError, secondError);
    
    // 交换错误节点的值
    if (firstError && secondError) {
        swap(firstError->val, secondError->val);
    }
}

void inorderTraversal(TreeNode* node, TreeNode*& prev, 
                     TreeNode*& firstError, TreeNode*& secondError) {
    if (!node) return;
    
    // 遍历左子树
    inorderTraversal(node->left, prev, firstError, secondError);
    
    // 处理当前节点：检查逆序对
    if (prev && prev->val > node->val) {
        if (!firstError) {
            // 第一次发现逆序对
            firstError = prev;    // 逆序对的前一个元素
            secondError = node;   // 逆序对的后一个元素
        } else {
            // 第二次发现逆序对（仅更新secondError）
            secondError = node;
        }
    }
    prev = node;
    
    // 遍历右子树
    inorderTraversal(node->right, prev, firstError, secondError);
}
```

#### 关键理解突破

**1. 逆序对识别策略**
```cpp
// 相邻交换场景：[1,3,2,4]
// 中序遍历：1 → 3 → 2 → 4
// 发现 3 > 2：firstError=3, secondError=2
// 只有一个逆序对，交换3和2

// 不相邻交换场景：[1,4,3,2,5]  
// 中序遍历：1 → 4 → 3 → 2 → 5
// 发现 4 > 3：firstError=4, secondError=3
// 发现 3 > 2：保持firstError=4, 更新secondError=2
// 两个逆序对，交换4和2
```

**2. 状态管理的三指针协调**
```cpp
TreeNode* prev;        // 中序遍历的前驱节点
TreeNode* firstError;  // 第一个错误节点（逆序对的较大值）
TreeNode* secondError; // 第二个错误节点（最后一个逆序对的较小值）
```

**3. 逆序对的数学性质**
- **1个逆序对**: 两个错误节点相邻，直接交换即可
- **2个逆序对**: 两个错误节点不相邻，交换第一个逆序对的大值和第二个逆序对的小值

#### 算法优化：Morris遍历

**O(1)空间复杂度版本**:
```cpp
void recoverTreeMorris(TreeNode* root) {
    TreeNode* firstError = nullptr;
    TreeNode* secondError = nullptr;
    TreeNode* prev = nullptr;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            // 处理当前节点
            if (prev && prev->val > curr->val) {
                if (!firstError) {
                    firstError = prev;
                    secondError = curr;
                } else {
                    secondError = curr;
                }
            }
            prev = curr;
            curr = curr->right;
        } else {
            // 找到左子树的最右节点
            TreeNode* predecessor = curr->left;
            while (predecessor->right && predecessor->right != curr) {
                predecessor = predecessor->right;
            }
            
            if (!predecessor->right) {
                // 建立线索
                predecessor->right = curr;
                curr = curr->left;
            } else {
                // 拆除线索，处理节点
                predecessor->right = nullptr;
                
                if (prev && prev->val > curr->val) {
                    if (!firstError) {
                        firstError = prev;
                        secondError = curr;
                    } else {
                        secondError = curr;
                    }
                }
                prev = curr;
                curr = curr->right;
            }
        }
    }
    
    if (firstError && secondError) {
        swap(firstError->val, secondError->val);
    }
}
```

#### 算法特点总结

**时间复杂度**: O(n) - 每个节点访问一次
**空间复杂度**: 
- 递归版本: O(h) - 递归栈深度
- Morris版本: O(1) - 常数空间

**核心优势**:
1. **问题建模**: 将BST恢复转化为逆序对识别
2. **状态管理**: 三指针协调处理复杂状态
3. **空间优化**: Morris遍历实现O(1)空间

#### 易错点总结

1. **逆序对识别**: 相邻vs不相邻交换的不同处理逻辑
2. **状态更新**: 第二次发现逆序对时只更新secondError
3. **边界处理**: 只有一个逆序对时的特殊情况
4. **空间优化**: Morris遍历的线索建立和拆除

#### 扩展应用
- **98. 验证BST**: BST性质的正向验证
- **230. BST第K小**: 中序遍历的直接应用
- **173. BST迭代器**: 中序遍历的迭代器包装
- **285. BST中序后继**: 中序遍历的导航应用

---

<a id="bt-108"></a>
### 108. 将有序数组转换为BST (Easy) - 分治构建+平衡保证 ⭐⭐⭐
**核心思想**: 分治递归构建，选择中点作为根节点保证平衡性
**算法本质**: BST构建的逆向工程，从有序序列到平衡树的转换

#### 题目链接
https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/

#### 核心算法原理

**问题分析**:
- 有序数组 → 平衡BST的转换
- 平衡要求：左右子树高度差≤1
- 关键insight：选择中点作为根节点可保证平衡性

**分治策略**:
1. **选择根节点**: 取区间中点`mid = (left + right) / 2`
2. **分割数组**: 左半部分构建左子树，右半部分构建右子树  
3. **递归构建**: 对子区间重复相同过程
4. **平衡保证**: 中点选择确保左右子树大小相近

#### 核心算法实现

```cpp
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return buildBST(nums, 0, nums.size() - 1);
}

TreeNode* buildBST(vector<int>& nums, int left, int right) {
    // 递归终止条件
    if (left > right) return nullptr;
    
    // 选择中点作为根节点
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    // 递归构建左右子树
    root->left = buildBST(nums, left, mid - 1);
    root->right = buildBST(nums, mid + 1, right);
    
    return root;
}
```

#### 关键理解突破

**1. 平衡性的数学保证**
```cpp
// 中点选择的平衡原理
int mid = left + (right - left) / 2;

// 区间[left, right]长度为n = right - left + 1
// 左子树：[left, mid-1]，长度 ≈ n/2
// 右子树：[mid+1, right]，长度 ≈ n/2
// 高度差：|左子树高度 - 右子树高度| ≤ 1
```

**2. 分治递归的边界处理**
```cpp
// 边界条件：left > right
// 表示区间为空，返回nullptr

// 单元素情况：left == right  
// mid = left，左右子树都为nullptr
```

**3. BST性质的自动满足**
```cpp
// 由于原数组有序，分治构建自动满足BST性质：
// 左子树元素 < 根节点 < 右子树元素
```

#### 算法优化与变种

**优化1: 避免整数溢出**
```cpp
// ❌ 可能溢出
int mid = (left + right) / 2;

// ✅ 避免溢出
int mid = left + (right - left) / 2;
```

**优化2: 选择不同中点策略**
```cpp
// 偏左中点（默认）
int mid = left + (right - left) / 2;

// 偏右中点  
int mid = left + (right - left + 1) / 2;

// 两种策略都能保证平衡性，但构建的树形状略有不同
```

#### 算法特点总结

**时间复杂度**: O(n) - 每个数组元素创建一个节点
**空间复杂度**: O(log n) - 递归栈深度等于树的高度

**核心优势**:
1. **平衡保证**: 构建的BST高度平衡，查找效率最优
2. **实现简洁**: 分治递归思路清晰，代码简洁
3. **性质满足**: 自动满足BST性质，无需额外验证

#### 知识闭环建立

**BST算法技能链的完整闭环**:
```
108题构建BST → 98题验证BST → 230题应用BST → 99题恢复BST
     ↑                                                     ↓
     ←――――――――――― 完整的BST生命周期管理 ―――――――――――→
```

**技能迁移矩阵**:
- **108题贡献**: 分治构建，平衡性设计
- **98题贡献**: BST验证，中序遍历性质
- **230题贡献**: BST应用，查找优化
- **99题贡献**: BST修复，错误检测

#### 易错点总结

1. **创建节点**: 使用`nums[mid]`而非`mid`
2. **边界条件**: `left > right`表示空区间
3. **递归参数**: 左子树`[left, mid-1]`，右子树`[mid+1, right]`
4. **溢出预防**: 使用`left + (right - left) / 2`

#### 扩展应用
- **109. 有序链表转BST**: 链表版本的BST构建
- **1008. 前序遍历构造BST**: 从前序遍历构建BST
- **106. 中序后序构造二叉树**: 更一般的树构建问题
- **105. 前序中序构造二叉树**: 双序列构建二叉树

---

## 图论算法核心体系

<a id="graph-200"></a>
### 200. 岛屿数量 (Medium) - 图论算法入门 ⭐⭐⭐

#### 题目链接
https://leetcode.cn/problems/number-of-islands/

#### 核心概念建立

**图论建模突破**: 二维网格 → 无向图的思维转换
- **节点(顶点)**: 网格中的每个格子
- **边**: 相邻格子之间的连接关系(上下左右四方向)
- **连通分量**: 彼此连接的节点集合(每个岛屿就是一个连通分量)

**与回溯算法的思维对比**:
- **共同点**: 都使用递归进行深度优先搜索，边界处理，状态管理
- **核心差异**: 
  - 回溯算法: 解空间搜索 + 撤销操作，寻找所有可能解
  - 图遍历: 连通性搜索 + 标记机制，访问所有连通节点

**技能迁移路径**: 从131题字符串分割的递归思维成功迁移到200题二维网格搜索

#### 双重遍历策略

**方法1: DFS深度优先搜索** ⭐ 推荐
```cpp
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size(), n = grid[0].size();
    int islandCount = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                islandCount++;
                dfs(grid, i, j);  // 标记整个岛屿
            }
        }
    }
    
    return islandCount;
}

void dfs(vector<vector<char>>& grid, int i, int j) {
    // 边界检查和终止条件
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || 
        grid[i][j] == '0') {
        return;
    }
    
    // 标记当前格子为已访问
    grid[i][j] = '0';
    
    // 递归搜索四个方向的相邻格子
    dfs(grid, i - 1, j);  // 上
    dfs(grid, i + 1, j);  // 下  
    dfs(grid, i, j - 1);  // 左
    dfs(grid, i, j + 1);  // 右
}
```

**方法2: BFS广度优先搜索**
```cpp
void bfs(vector<vector<char>>& grid, int startI, int startJ) {
    queue<pair<int, int>> q;
    grid[startI][startJ] = '0';  // 标记起始格子
    q.push({startI, startJ});
    
    // 方向数组：上、下、左、右
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        
        // 探索四个方向的相邻格子
        for (auto& dir : directions) {
            int newI = i + dir[0];
            int newJ = j + dir[1];
            
            // 边界检查和有效性验证
            if (newI >= 0 && newI < grid.size() && 
                newJ >= 0 && newJ < grid[0].size() && 
                grid[newI][newJ] == '1') {
                
                grid[newI][newJ] = '0';  // 标记为已访问
                q.push({newI, newJ});
            }
        }
    }
}
```

#### 关键技术突破

**1. 标记机制的设计选择**
```cpp
// 方案1: 原地标记（推荐）
grid[i][j] = '0';  // 直接修改原数组，空间O(1)

// 方案2: 额外标记数组
vector<vector<bool>> visited(m, vector<bool>(n, false));
// 需要额外O(m×n)空间，但保持原数组不变
```

**2. 方向遍历的编程技巧**
```cpp
// 方案1: 直接四次调用（简单直观）
dfs(grid, i-1, j); dfs(grid, i+1, j);
dfs(grid, i, j-1); dfs(grid, i, j+1);

// 方案2: 方向数组（可扩展）
vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
for (auto& dir : directions) {
    dfs(grid, i + dir[0], j + dir[1]);
}
```

**3. BFS中的并发标记策略**
```cpp
// 关键：在入队时就标记，而非出队时标记
if (grid[newI][newJ] == '1') {
    grid[newI][newJ] = '0';  // 立即标记，避免重复入队
    q.push({newI, newJ});
}
```

#### 算法特点对比

| 特征 | DFS深度优先 | BFS广度优先 |
|------|-------------|-------------|
| **实现方式** | 递归（或显式栈） | 队列 |
| **搜索路径** | 深入到底再回溯 | 逐层扩展 |
| **空间复杂度** | O(深度) ≈ O(min(m,n)) | O(宽度) ≈ O(max(m,n)) |
| **编程复杂度** | 简单（递归自然） | 稍复杂（队列管理） |
| **应用场景** | 连通性检测 | 最短路径 |

#### 算法分析

**时间复杂度**: O(M×N) - 每个格子最多访问一次
**空间复杂度**: 
- DFS: O(M×N) - 最坏情况下递归栈深度（全为陆地时）
- BFS: O(min(M,N)) - 队列最大长度

#### 学习里程碑意义

**算法思维跃迁**:
```
回溯算法(131题) → 图论算法(200题)
解空间搜索    → 连通分量搜索
撤销机制      → 标记机制  
所有可能解    → 连通节点集合
```

**技术技能迁移**:
1. **递归思维**: 边界处理、状态管理的直接复用
2. **搜索策略**: DFS深度优先的思想延续
3. **问题建模**: 从一维字符串到二维网格的维度扩展

#### 算法扩展体系

**岛屿类问题族群**:
- **695. 最大岛屿面积**: 在连通分量基础上计算面积
- **463. 岛屿周长**: 计算岛屿边界长度
- **994. 腐烂的橘子**: BFS时间扩散问题

**连通分量问题**:
- **547. 朋友圈**: 人际关系的连通分量
- **130. 被围绕的区域**: 条件性连通分量处理

**图遍历进阶**:
- **542. 01矩阵**: 多源BFS最短距离
- **1162. 地图分析**: 最远海洋格子问题

#### 为后续算法铺路

**图论基础建立**:
1. **图的表示**: 邻接矩阵（二维网格）的自然理解
2. **遍历策略**: DFS/BFS两种核心遍历方法的实战应用
3. **连通性**: 连通分量概念的直观建立
4. **复杂度分析**: 图算法复杂度分析的基础训练

**为复杂图算法做准备**:
- **最短路径**: BFS是无权图最短路径的基础
- **最小生成树**: 连通性概念的扩展应用
- **拓扑排序**: 有向图遍历的进阶应用

---

## 🎯 专题总结：二叉树与图论核心技能体系

### 学习路径回顾

```
📚 二叉树基础建立阶段
104题最大深度 → 递归思维入门，树的基本概念
226题翻转二叉树 → 树形变换，前序遍历应用

🔄 遍历技巧掌握阶段  
94题中序遍历 → 栈模拟递归，迭代实现技巧
98题验证BST → 引用传递，BST性质深度理解

🎯 高级技巧融合阶段
230题第K小元素 → 知识融合，提前终止优化
101题对称二叉树 → 双节点递归，思维跃迁突破

🏆 算法设计精通阶段
99题恢复BST → 状态管理，逆序对识别
108题数组转BST → 分治构建，平衡性保证

🌐 图论思维建立阶段
200题岛屿数量 → 图论入门，连通分量计算
```

### 核心技能掌握矩阵

| 技能维度 | 掌握程度 | 代表题目 | 核心洞察 |
|---------|---------|----------|----------|
| **递归思维建立** | ✅ 精通 | 104题最大深度 | 大问题分解为小问题，递归关系建立 |
| **栈模拟递归** | ✅ 精通 | 94题中序遍历 | 显式栈替代递归栈，迭代实现 |
| **引用传递技巧** | ✅ 精通 | 98题验证BST | 跨递归调用的状态传递机制 |
| **双节点递归** | ✅ 精通 | 101题对称树 | 从单节点到双节点的思维跃迁 |
| **状态管理设计** | ✅ 精通 | 99题恢复BST | 复杂状态的协调管理 |
| **分治算法应用** | ✅ 精通 | 108题数组转BST | 分治构建，平衡性保证 |
| **图论建模思维** | ✅ 精通 | 200题岛屿数量 | 二维网格到图结构的思维转换 |

### 算法设计思维升华

#### 1. 递归模式的进化轨迹
```cpp
// 单节点递归 (104/226): f(node) → 操作单个节点
int maxDepth(TreeNode* node) {
    if (!node) return 0;
    return max(maxDepth(node->left), maxDepth(node->right)) + 1;
}

// 状态传递递归 (98/230): f(node, &state) → 单节点+全局状态  
bool validate(TreeNode* node, TreeNode*& prev) {
    // 引用传递维护全局状态
}

// 双节点递归 (101): f(left, right) → 同步比较两个节点
bool isMirror(TreeNode* left, TreeNode* right) {
    // 同时处理两个节点的对称关系
}
```

#### 2. BST算法技能链
```cpp
// 完整的BST生命周期管理
108题构建 → 98题验证 → 230题应用 → 99题修复
    ↑                                         ↓
    ←―――――――― 知识技能的螺旋式上升 ――――――――→
```

#### 3. 图论思维建立
```cpp
// 从树到图的思维扩展
二叉树遍历 → 有根树DFS → 无向图DFS → 连通分量计算
```

### 核心模板库建立

#### 递归遍历标准模板
```cpp
// 前序遍历模板（根→左→右）
void preorder(TreeNode* node) {
    if (!node) return;
    process(node);           // 处理当前节点
    preorder(node->left);    // 递归左子树
    preorder(node->right);   // 递归右子树
}

// 中序遍历模板（左→根→右）
void inorder(TreeNode* node) {
    if (!node) return;
    inorder(node->left);     // 递归左子树
    process(node);           // 处理当前节点
    inorder(node->right);    // 递归右子树
}

// 后序遍历模板（左→右→根）
void postorder(TreeNode* node) {
    if (!node) return;
    postorder(node->left);   // 递归左子树
    postorder(node->right);  // 递归右子树
    process(node);           // 处理当前节点
}
```

#### 迭代遍历标准模板
```cpp
// 中序遍历迭代模板
vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (!st.empty() || curr) {
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

#### BST操作标准模板
```cpp
// BST验证模板
bool validateBST(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    
    if (!validateBST(node->left, prev)) return false;
    
    if (prev && prev->val >= node->val) return false;
    prev = node;
    
    return validateBST(node->right, prev);
}

// BST分治构建模板
TreeNode* buildBST(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    root->left = buildBST(nums, left, mid - 1);
    root->right = buildBST(nums, mid + 1, right);
    
    return root;
}
```

#### 图遍历标准模板
```cpp
// DFS图遍历模板
void dfs(vector<vector<char>>& grid, int i, int j) {
    // 边界检查
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || 
        grid[i][j] == '0') return;
    
    // 标记已访问
    grid[i][j] = '0';
    
    // 四方向递归
    dfs(grid, i-1, j); dfs(grid, i+1, j);
    dfs(grid, i, j-1); dfs(grid, i, j+1);
}

// BFS图遍历模板
void bfs(vector<vector<char>>& grid, int startI, int startJ) {
    queue<pair<int, int>> q;
    grid[startI][startJ] = '0';
    q.push({startI, startJ});
    
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        
        for (auto& dir : directions) {
            int newI = i + dir[0], newJ = j + dir[1];
            if (newI >= 0 && newI < grid.size() && 
                newJ >= 0 && newJ < grid[0].size() && 
                grid[newI][newJ] == '1') {
                grid[newI][newJ] = '0';
                q.push({newI, newJ});
            }
        }
    }
}
```

### 学习成果评估

#### 技术突破
- ✅ 建立完整的二叉树算法知识体系
- ✅ 掌握从递归到迭代的实现转换
- ✅ 精通BST的验证、构建、修复全流程
- ✅ 理解图论基础概念和遍历策略
- ✅ 具备复杂状态管理和算法设计能力

#### 思维升华
- ✅ 从"单点处理"到"全局状态管理"的设计思维
- ✅ 从"简单递归"到"多种递归模式"的技巧掌握
- ✅ 从"树结构"到"图结构"的抽象能力提升
- ✅ 从"实现功能"到"优化设计"的工程思维

### 专题价值与意义

二叉树与图论专题的学习建立了**递归思维和图抽象**的核心能力：

1. **递归思维成熟**: 从简单递归到复杂状态管理的递归设计能力
2. **数据结构抽象**: 从具体实现到抽象模型的思维转换
3. **算法设计模式**: 分治、状态传递、双节点递归等设计模式
4. **图论基础建立**: 为后续复杂图算法学习奠定基础
5. **工程实践能力**: 递归转迭代、状态管理、性能优化的实践技巧

这些核心能力为后续的高级算法学习（如动态规划、图论算法、复杂数据结构）提供了坚实的思维基础和技术储备。

---

*最后更新: 2025-08-30*
