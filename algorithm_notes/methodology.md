# 方法论与通用

本专题目录
- [递归设计模式进化](#meta-recursive)
- [易错点总结](#meta-pitfalls)

<a id="meta-recursive"></a>
## 递归设计模式进化
```
单节点递归 (104/226): f(node) → 操作单个节点
    ↓
状态传递递归 (98/230): f(node, &state) → 单节点+全局状态  
    ↓
双节点递归 (101): f(left, right) → 同步比较两个节点
```




---

<a id="meta-pitfalls"></a>
## 易错点总结

### DP类易错点
1. **状态定义混淆**: "以位置结尾"需要返回全局最大值
2. **转移方程遗漏**: 忘记比较当前值 `max(dp[i], newValue)`
3. **边界条件**: 循环范围`i <= amount`不是`i < amount`
4. **记忆化三步骤**: 检查缓存→计算→存储缓存→返回

### 二叉树类易错点
1. **引用传递**: 跨递归维护状态必须用`TreeNode*&`
2. **递归指针混乱**: 先保存子树指针再交换
3. **双节点递归**: 镜像对应关系，逻辑表达式用`&&`
4. **栈模拟递归**: curr指针驱动，`curr = node->right`
5. **BST定义**: 子树整体约束，不是简单父子关系

### 技术细节易错点
1. **C++语法**: 变量声明用逗号分隔，条件判断加括号
2. **循环控制**: 避免在循环中使用动态变化的条件
3. **容器API**: `queue.pop()` vs `deque.pop_front()`
4. **自增操作**: `depth++`改变原值，`depth+1`不改变

### 核心算法模板

```cpp
// DP基础模板
dp[i] = max/min(dp[i], f(dp[j]) + cost)

// BST中序验证模板
bool inorder(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    if (!inorder(node->left, prev)) return false;
    if (prev && prev->val >= node->val) return false;
    prev = node;
    return inorder(node->right, prev);
}

// 双节点递归模板
bool compare(TreeNode* left, TreeNode* right) {
    if (!left && !right) return true;
    if (!left || !right) return false;
    if (left->val != right->val) return false;
    return compare(left->left, right->?) && 
           compare(left->right, right->?);
}

// 栈模拟递归模板
while (!st.empty() || curr) {
    while (curr) {
        st.push(curr);
        curr = curr->left;
    }
    curr = st.top(); st.pop();
    process(curr);
    curr = curr->right;
}
```
