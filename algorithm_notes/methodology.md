# 算法方法论与通用设计模式

算法学习的系统化方法论和跨专题的通用设计模式总结。

## 本专题目录
- [递归设计模式进化](#recursive-patterns)
- [复杂度分析方法论](#complexity-analysis)
- [数据结构选择决策](#data-structure-selection)
- [调试与优化方法论](#debugging-optimization)
- [易错点系统总结](#common-pitfalls)
- [代码模板库](#template-library)

---

<a id="recursive-patterns"></a>
## 递归设计模式进化

### 模式演进路径
```
基础递归 (104/111): f(node) → 单节点操作
    ↓
状态传递 (98/230): f(node, &state) → 单节点+全局状态维护
    ↓  
双节点递归 (101/100): f(left, right) → 同步比较两棵树
    ↓
路径递归 (112/113): f(node, target) → 路径约束条件
    ↓
构造递归 (105/106): f(array, range) → 从数组构造树
```

### 核心模式详解

#### 1. 单节点递归模式
**适用场景**: 树的属性计算(深度、节点数、路径和)
```cpp
// 标准模板
int process(TreeNode* node) {
    if (!node) return base_case;  // 递归出口
    int left = process(node->left);   // 左子树结果
    int right = process(node->right); // 右子树结果
    return combine(left, right, node->val); // 合并逻辑
}

// 实际应用(104题最大深度)
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
```

#### 2. 状态传递递归模式
**适用场景**: 需要维护全局信息(中序遍历、路径记录)
```cpp
// 标准模板
bool helper(TreeNode* node, StateType& state) {
    if (!node) return true;
    if (!helper(node->left, state)) return false;
    
    // 关键：访问当前节点，更新全局状态
    if (!updateState(node, state)) return false;
    
    return helper(node->right, state);
}

// 实际应用(98题BST验证)
bool isValidBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    return inorder(root, prev);
}
bool inorder(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    if (!inorder(node->left, prev)) return false;
    if (prev && prev->val >= node->val) return false;
    prev = node; // 状态更新
    return inorder(node->right, prev);
}
```

#### 3. 双节点递归模式
**适用场景**: 两棵树的同步比较(对称性、相同性)
```cpp
// 标准模板
bool compare(TreeNode* node1, TreeNode* node2) {
    if (!node1 && !node2) return true;
    if (!node1 || !node2) return false;
    if (condition_check(node1, node2)) return false;
    
    return compare(node1->left, node2->target_left) && 
           compare(node1->right, node2->target_right);
}

// 实际应用(101题对称二叉树)
bool isSymmetric(TreeNode* root) {
    return compare(root->left, root->right);
}
bool compare(TreeNode* left, TreeNode* right) {
    if (!left && !right) return true;
    if (!left || !right) return false;
    return left->val == right->val && 
           compare(left->left, right->right) && 
           compare(left->right, right->left);
}
```

---

<a id="complexity-analysis"></a>
## 复杂度分析方法论

### 时间复杂度分析框架

#### 1. 递归算法分析
```cpp
// 递归复杂度分析三步法
// 1. 确定递归关系: T(n) = a*T(n/b) + f(n)
// 2. 应用主定理或递归树方法
// 3. 验证基本操作的复杂度

// 示例：二叉树遍历
// T(n) = T(left) + T(right) + O(1)
// 每个节点访问一次 → O(n)

// 示例：分治算法
// T(n) = 2*T(n/2) + O(n) → O(n log n)
```

#### 2. 迭代算法分析
```cpp
// 循环分析方法
for (int i = 0; i < n; i++) {      // O(n)
    for (int j = i; j < n; j++) {  // O(n-i)
        // O(1) operations
    }
}
// 总复杂度: ∑(n-i) = n + (n-1) + ... + 1 = O(n²)

// 双指针技巧
int left = 0, right = n-1;
while (left < right) {  // O(n)
    // O(1) operations
    // 每次循环至少一个指针移动
}
// 总复杂度: O(n)
```

### 空间复杂度分析

#### 递归栈空间
```cpp
// 递归深度 = 空间复杂度
// 平衡二叉树: O(log n)
// 倾斜二叉树: O(n)
// 分治算法: O(log n) 典型情况
```

#### 辅助数据结构
```cpp
// 数组/哈希表: O(n)
// 栈/队列: 最大存储量决定空间复杂度
// DP数组: 状态空间大小
```

---

<a id="data-structure-selection"></a>
## 数据结构选择决策框架

### 选择决策树
```
问题分析
├── 需要快速查找?
│   ├── 是 → Hash Table (O(1)平均) / TreeMap (O(log n))
│   └── 否 → 考虑其他需求
├── 需要有序性?
│   ├── 是 → TreeMap / 有序数组 / 优先队列
│   └── 否 → Hash Table / 数组
├── 需要动态插入删除?
│   ├── 频繁 → 链表 / 平衡树
│   └── 较少 → 数组
└── 有特殊访问模式?
    ├── LIFO → 栈 (Stack)
    ├── FIFO → 队列 (Queue)
    ├── 优先级 → 优先队列 (Heap)
    └── 范围查询 → 线段树 / 前缀和
```

### 常见场景与最优选择

#### 场景1: 两数之和类问题
```cpp
// 问题特征: 查找配对、去重
// 最优选择: unordered_map<int, int>
// 原因: O(1)查找，支持计数
for (int i = 0; i < nums.size(); i++) {
    if (map.count(target - nums[i])) {
        return {map[target - nums[i]], i};
    }
    map[nums[i]] = i;
}
```

#### 场景2: 滑动窗口最值
```cpp
// 问题特征: 动态维护区间最值
// 最优选择: deque<int> (单调队列)
// 原因: 两端操作O(1)，维护单调性
deque<int> dq;
for (int i = 0; i < nums.size(); i++) {
    while (!dq.empty() && nums[i] >= nums[dq.back()]) 
        dq.pop_back();
    dq.push_back(i);
    if (dq.front() <= i - k) dq.pop_front();
}
```

#### 场景3: 前K个高频元素
```cpp
// 问题特征: 频率统计 + Top-K
// 最优选择: unordered_map + priority_queue
// 原因: 统计O(n) + 堆操作O(n log k)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
for (auto& p : freq_map) {
    pq.push({p.second, p.first});
    if (pq.size() > k) pq.pop();
}
```
记忆关键：
最小堆找最大的k个元素
最大堆找最小的k个元素
堆中存储{比较键, 实际数据}

---

<a id="debugging-optimization"></a>
## 调试与优化方法论

### 系统化调试流程

#### 1. 错误定位策略
```cpp
// 调试检查清单
// □ 边界条件: 空输入、单元素、最大值
// □ 数组越界: 循环边界、递归终止
// □ 整型溢出: long long、模运算
// □ 逻辑错误: 条件判断、循环不变量

// 调试技巧
#ifdef DEBUG
    #define dbg(x) cout << #x << " = " << x << endl
#else
    #define dbg(x)
#endif

void printTree(TreeNode* root, string prefix = "") {
    if (!root) return;
    cout << prefix << root->val << endl;
    printTree(root->left, prefix + "L-");
    printTree(root->right, prefix + "R-");
}
```

#### 2. 性能优化策略

**优化层次结构**:
```
算法层面 (最重要)
├── 时间复杂度优化: O(n²) → O(n log n) → O(n)
├── 空间复杂度优化: 状态压缩、滚动数组
└── 算法选择: 贪心 vs DP vs 分治

实现层面
├── 数据结构优化: 数组 vs 链表 vs 哈希表
├── 常数优化: 循环展开、位运算
└── 编译器优化: -O2、inline函数

系统层面  
├── 内存局部性: 顺序访问、缓存友好
├── 并行化: 分治算法的并行实现
└── 硬件特性: SIMD指令、分支预测
```

**具体优化技巧**:
```cpp
// 1. 位运算优化
n % 2 == 0  →  (n & 1) == 0    // 奇偶判断
n / 2       →  n >> 1          // 除2操作
n * 4       →  n << 2          // 乘4操作

// 2. 循环优化
// 坏：频繁计算size()
for (int i = 0; i < vec.size(); i++) { ... }
// 好：缓存size值
int n = vec.size();
for (int i = 0; i < n; i++) { ... }

// 3. 内存访问优化
// 坏：跳跃访问
for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
        matrix[i][j] = ...;  // 列遍历，缓存不友好
    }
}
// 好：顺序访问  
for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        matrix[i][j] = ...;  // 行遍历，缓存友好
    }
}
```

---

<a id="common-pitfalls"></a>
## 易错点系统总结

### 按算法类型分类

#### 动态规划易错点
```cpp
// 1. 状态定义混淆
// 错误：dp[i]表示前i个元素的结果
// 正确：dp[i]表示以第i个元素结尾的结果
// 示例：最大子数组和
dp[i] = max(nums[i], dp[i-1] + nums[i]); // 以i结尾
result = max(result, dp[i]);             // 全局最大

// 2. 转移方程遗漏比较
// 错误：dp[i] = dp[i-1] + cost
// 正确：dp[i] = min(dp[i], dp[i-1] + cost)

// 3. 边界条件处理
// 错误：for (int i = 1; i < amount; i++)
// 正确：for (int i = 1; i <= amount; i++)

// 4. 记忆化递归模板
int memo[MAX_N];
int dfs(int state) {
    if (base_condition) return base_value;
    if (memo[state] != -1) return memo[state]; // 检查缓存
    
    int result = calculate(state);
    return memo[state] = result; // 存储并返回
}
```

#### 二叉树易错点
```cpp
// 1. 引用传递错误
// 错误：void inorder(TreeNode* node, TreeNode* prev)
// 正确：void inorder(TreeNode* node, TreeNode*& prev)
// 原因：需要修改prev指针本身

// 2. 递归中的指针操作
// 错误：直接修改node指针
node->left = node->right;
node->right = temp;  // temp是什么？未定义
// 正确：先保存再交换
TreeNode* temp = node->left;
node->left = node->right;
node->right = temp;

// 3. 双节点递归的对应关系
// 对称树：left->left vs right->right, left->right vs right->left
// 相同树：left->left vs right->left, left->right vs right->right

// 4. 栈模拟递归的指针驱动
while (!stack.empty() || curr) {
    while (curr) {
        stack.push(curr);
        curr = curr->left;    // 一路向左
    }
    curr = stack.top(); stack.pop();
    process(curr);            // 处理节点
    curr = curr->right;       // 转向右子树
}
```

#### 图论算法易错点
```cpp
// 1. DFS标记时机
// 错误：访问时才标记
if (grid[i][j] == '1') {
    grid[i][j] = '0';  // 标记过晚
    dfs(grid, i, j);
}
// 正确：进入函数立即标记
void dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') return;
    grid[i][j] = '0';  // 立即标记
    dfs(grid, i-1, j); dfs(grid, i+1, j);
    dfs(grid, i, j-1); dfs(grid, i, j+1);
}

// 2. BFS队列处理
// 错误：先检查再标记
while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    if (grid[x][y] == '0') continue;  // 可能重复处理
    grid[x][y] = '0';
}
// 正确：入队时标记
if (grid[nx][ny] == '1') {
    grid[nx][ny] = '0';  // 入队时标记
    q.push({nx, ny});
}
```

### 语言特性易错点

#### C++语法陷阱
```cpp
// 1. 变量声明语法
// 错误：int left, right = 0; // 只有right被初始化
// 正确：int left = 0, right = 0;

// 2. 条件判断优先级
// 错误：if (a && b || c)  // 优先级不明确
// 正确：if ((a && b) || c)

// 3. 自增操作的副作用
int depth = 0;
func(depth++);  // 传入0，depth变为1
func(depth+1);  // 传入depth+1，depth不变

// 4. 容器API差异
queue<int> q; q.pop();     // 无返回值
stack<int> s; s.pop();     // 无返回值
deque<int> d; d.pop_front(); // 无返回值
// 必须先取值再弹出
int val = q.front(); q.pop();
```

---

<a id="template-library"></a>
## 核心算法模板库

### 递归模板

```cpp
// 1. 基础递归模板
ReturnType recursiveFunction(TreeNode* node) {
    // 递归出口
    if (!node) return baseCase;
    
    // 递归调用
    ReturnType leftResult = recursiveFunction(node->left);
    ReturnType rightResult = recursiveFunction(node->right);
    
    // 合并结果
    return combineResults(leftResult, rightResult, node->val);
}

// 2. 状态传递递归模板  
bool helperWithState(TreeNode* node, StateType& state) {
    if (!node) return true;
    
    if (!helperWithState(node->left, state)) return false;
    
    // 处理当前节点，更新状态
    if (!processNode(node, state)) return false;
    
    return helperWithState(node->right, state);
}

// 3. 双节点递归模板
bool compareTwoNodes(TreeNode* node1, TreeNode* node2) {
    if (!node1 && !node2) return true;
    if (!node1 || !node2) return false;
    
    if (node1->val != node2->val) return false;
    
    return compareTwoNodes(node1->left, node2->left) && 
           compareTwoNodes(node1->right, node2->right);
}
```

### 迭代模板

```cpp
// 1. 栈模拟中序遍历
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (!st.empty() || curr) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    return result;
}

// 2. BFS层序遍历
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front(); q.pop();
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(currentLevel);
    }
    return result;
}
```

### 动态规划模板

```cpp
// 1. 一维DP模板
int dp1D(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    
    // 初始化
    dp[0] = baseValue;
    
    // 状态转移
    for (int i = 1; i < n; i++) {
        dp[i] = max/min(dp[i-1] + nums[i], nums[i]);
    }
    
    return *max_element(dp.begin(), dp.end());
}

// 2. 二维DP模板
int dp2D(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    // 边界初始化
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    // 状态转移
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
            }
        }
    }
    
    return dp[m][n];
}

// 3. 记忆化递归模板
class Solution {
private:
    unordered_map<string, int> memo;
    
public:
    int dfs(int state1, int state2) {
        // 递归出口
        if (baseCondition) return baseValue;
        
        // 检查缓存
        string key = to_string(state1) + "," + to_string(state2);
        if (memo.count(key)) return memo[key];
        
        // 计算结果
        int result = 0;
        for (choice in choices) {
            result = max/min(result, dfs(newState1, newState2) + cost);
        }
        
        // 存储并返回
        return memo[key] = result;
    }
};
```

### 图论算法模板

```cpp
// 1. DFS模板
void dfs(vector<vector<char>>& grid, int i, int j) {
    // 边界检查
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || 
        grid[i][j] == '0') return;
    
    // 标记已访问
    grid[i][j] = '0';
    
    // 递归访问四个方向
    dfs(grid, i-1, j); // 上
    dfs(grid, i+1, j); // 下
    dfs(grid, i, j-1); // 左
    dfs(grid, i, j+1); // 右
}

// 2. BFS模板
int bfs(vector<vector<int>>& grid, int startX, int startY) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int, int>> q;
    
    q.push({startX, startY});
    visited[startX][startY] = true;
    
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int steps = 0;
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front(); q.pop();
            
            if (isTarget(x, y)) return steps;
            
            for (auto& dir : directions) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && 
                    !visited[nx][ny] && isValid(nx, ny)) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        steps++;
    }
    return -1;
}
```

## 方法论总结

1. **系统性思维**: 从问题抽象到算法选择到代码实现的完整链条
2. **模式识别**: 训练对常见算法模式的快速识别能力
3. **复杂度意识**: 时刻关注算法的时空复杂度，追求最优解
4. **调试能力**: 建立系统化的错误定位和性能优化方法
5. **模板驱动**: 掌握核心算法模板，提高编码效率和正确性

通过以上方法论的系统学习和实践，可以建立起完整的算法解题框架，提升解题效率和代码质量。
