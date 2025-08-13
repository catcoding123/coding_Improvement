# 算法核心笔记

## 栈队列专题

### 239. 滑动窗口最大值 (Hard) - 单调队列
**核心思想**: 单调双端队列维护窗口最大值，存储下标，保持递减序列
**关键操作**: 移除过期元素 → 维护单调性 → 添加当前元素
**复杂度**: O(n) - 每个元素最多入队出队一次
**易错点**: 存储下标不是值，过期判断`<=`，窗口满判断`i >= k - 1`

### 155. 最小栈 (Medium) - 双栈设计
**核心思想**: 主栈+辅助栈，辅助栈维护最小值
**关键技巧**: push时用`<=`处理重复最小值
**复杂度**: O(1)所有操作

### 84. 柱状图中最大矩形 (Hard) - 单调栈
**核心思想**: 单调递增栈，弹栈时计算面积
**关键公式**: `面积 = 高度 × (右边界 - 左边界 - 1)`
**技巧**: 数组两端加0简化边界处理

### 42. 接雨水 (Hard) - 单调栈变种
**核心思想**: 单调递减栈，按层计算雨水
**关键要素**: 左边界(栈中剩余) + 底部(弹出元素) + 右边界(当前元素)

## 动态规划专题

### 70. 爬楼梯 (Easy) - DP入门
**状态定义**: `dp[i]` = 爬到第i阶的方法数
**转移方程**: `dp[i] = dp[i-1] + dp[i-2]`
**四种实现**: 递归、记忆化、DP、空间优化

### 198. 打家劫舍 (Medium) - 决策类DP
**状态定义**: `dp[i]` = 偷前i+1间房的最大金额
**转移方程**: `dp[i] = max(nums[i] + dp[i-2], dp[i-1])`
**核心**: 每步做选择决策，约束影响状态转移

### 53. 最大子数组和 (Medium) - 连续子数组DP
**核心算法**: Kadane算法
**转移方程**: `dp[i] = max(nums[i], dp[i-1] + nums[i])`
**关键理解**: "继续vs重新开始"的决策

### 322. 零钱兑换 (Medium) - 完全背包
**状态定义**: `dp[i]` = 组成金额i的最少硬币数
**转移方程**: `dp[i] = min(dp[i-coin] + 1)`
**关键**: 完全背包允许重复使用，内层循环可用已更新值
**易错点**: 记忆化搜索必须检查 `helpResult != -1`，防止将无解状态累加
**记忆口诀**: "无解传递毁全局，-1检查是关键"
```cpp
// ❌ 错误：忘记无解检查
int result = helper(amount - coin) + 1;

// ✅ 正确：检查无解状态
int helpResult = helper(amount - coin);
if (helpResult != -1) {
    result = min(result, helpResult + 1);
}
```

### 300. 最长递增子序列 (Medium) - 序列DP
**状态定义**: `dp[i]` = 以nums[i]结尾的LIS长度
**优化**: 贪心+二分查找达到O(n log n)
**易错**: 返回`max(dp)`而非`dp[n-1]`

### 1143. 最长公共子序列 (Medium) - 双序列DP
**状态定义**: `dp[i][j]` = 两序列前缀LCS长度
**转移**: 匹配时`dp[i-1][j-1]+1`，不匹配时取最优
**优化**: 滚动数组降低空间复杂度

### 516. 最长回文子序列 (Medium) - 区间DP
**状态定义**: `dp[i][j]` = s[i..j]的回文子序列长度
**关键**: 按区间长度递增遍历
**转移**: 两端匹配+2，不匹配选择最优子区间

## 二叉树专题

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
**通用模式**: BST+中序遍历可扩展到99、108、173等题

### 101. 对称二叉树 (Easy) - 双节点递归突破
**算法革命**: 从单节点递归到双节点同步递归的思维跃迁
**对称关系**: 左左↔右右、左右↔右左的交叉对应
**递归设计**: 双参数、边界处理、镜像调用的系统思考
**实现对比**: 递归版本vs迭代队列的双重掌握

### 99. 恢复BST (Hard) - 逆序对识别+状态管理
**核心算法**: 中序遍历+逆序对识别+节点值交换
**逆序对模式**: 
- 相邻交换: 一个逆序对 `[1,3,2,4]` → 同时设置firstError/secondError
- 不相邻交换: 两个逆序对 `[1,4,3,2,5]` → 第二次仅更新secondError
**状态管理**: 三指针协调 - prev、firstError、secondError
**进阶扩展**: Morris遍历实现O(1)空间复杂度
**易错点**: 相邻交换需同时设置两个错误节点，不相邻交换分两次设置

### 108. 将有序数组转换为BST (Easy) - 分治构建+平衡保证
**核心思想**: 分治递归构建，选择中点作为根节点保证平衡性
**算法流程**: 
- 选择中点: `mid = (left + right) / 2` 
- 创建根节点: `root = new TreeNode(nums[mid])`
- 递归构建: 左子树`[left, mid-1]`，右子树`[mid+1, right]`
**平衡原理**: 中点选择保证左右子树大小相近，高度差≤1
**知识闭环**: 验证(98)→应用(230)→恢复(99)→构建(108)完整BST生命周期
**时间复杂度**: O(n) - 每个节点创建一次
**空间复杂度**: O(log n) - 递归栈深度
**易错点**: 创建节点用`nums[mid]`不是`mid`，边界条件`left > right`
**技术突破**: 引用传递维护全局前驱状态
**经典陷阱**: BST不是简单父子关系，而是子树整体约束
```cpp
bool inorderCheck(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    if (!inorderCheck(node->left, prev)) return false;
    if (prev && prev->val >= node->val) return false;
    prev = node;
    return inorderCheck(node->right, prev);
}
```

### 230. BST第K小元素 (Medium) - 知识融合+提前终止
**核心思想**: BST中序遍历+计数器，O(H+k)优化
**知识融合**: 98题BST性质 + 94题中序遍历 + 引用传递
**关键**: `k==0`时提前终止，避免继续递归

### 101. 对称二叉树 (Easy) - 双节点递归
**算法突破**: 从单节点递归跃升到双节点同步递归
**镜像定义**: 左左↔右右，左右↔右左的交叉对应
**边界处理**: 四种空节点组合的完整处理
```cpp
bool isMirror(TreeNode* left, TreeNode* right) {
    if (!left && !right) return true;
    if (!left || !right) return false;
    if (left->val != right->val) return false;
    return isMirror(left->left, right->right) && 
           isMirror(left->right, right->left);
}
```

## 递归设计模式进化
```
单节点递归 (104/226): f(node) → 操作单个节点
    ↓
状态传递递归 (98/230): f(node, &state) → 单节点+全局状态  
    ↓
双节点递归 (101): f(left, right) → 同步比较两个节点
```




---

## 198. 打家劫舍 (Medium)

### 核心思想
决策类动态规划经典题，体现了**选择决策**的DP思维：每个状态面临多种选择，选择最优方案。

### 关键逻辑
1. **状态定义**:
   - `dp[i]` = 偷前i+1间房能获得的最大金额
   
2. **决策分析**:
   对于第i间房，小偷面临两种选择：
   - **偷第i间房**: 获得 `nums[i] + dp[i-2]` (不能偷相邻房屋)
   - **不偷第i间房**: 获得 `dp[i-1]` (保持前一状态)

3. **状态转移方程**:
   ```
   dp[i] = max(nums[i] + dp[i-2], dp[i-1])
   ```

4. **边界条件**:
   ```cpp
   dp[0] = nums[0]                    // 只有1间房
   dp[1] = max(nums[0], nums[1])      // 2间房选金额大的
   ```

### 四种实现方式

#### 1. 递归解法 (会超时)
```cpp
int helper(vector<int>& nums, int i) {
    if (i < 0) return 0;
    return max(helper(nums, i-2) + nums[i], helper(nums, i-1));
}
```

#### 2. 记忆化搜索 (自顶向下)
```cpp
int helperMemo(vector<int>& nums, int i, vector<int>& memo) {
    if (i < 0) return 0;
    if (i == 0) return nums[0];
    if (memo[i] != -1) return memo[i];
    
    memo[i] = max(helperMemo(nums,i-2,memo) + nums[i], 
                  helperMemo(nums,i-1,memo));
    return memo[i];
}
```

#### 3. 动态规划 (自底向上) ⭐
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
    }
    return dp[n-1];
}
```

#### 4. 空间优化 (滚动变量)
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int curr = max(nums[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

### 与70题的关键区别
- **70题爬楼梯**: 递推关系 `f(n) = f(n-1) + f(n-2)` (加法)
- **198题打家劫舍**: 决策关系 `f(n) = max(选择A, 选择B)` (选择)

### 决策类DP特征
1. **多种选择**: 每个状态面临2个或更多选择
2. **约束条件**: 选择之间存在限制关系
3. **最优决策**: 使用max/min函数选择最优方案
4. **状态依赖**: 当前选择影响后续可选方案

### 复杂度分析
- **递归**: 时间O(2^n)，空间O(n)
- **记忆化**: 时间O(n)，空间O(n)
- **DP**: 时间O(n)，空间O(n)
- **空间优化**: 时间O(n)，空间O(1)

### 关键理解
- **约束建模**: 相邻房屋不能同时偷 → 状态转移中体现为i-2而不是i-1
- **决策思维**: 每步都要问"我有哪些选择？哪个更优？"
- **记忆化精髓**: 计算 → 缓存 → 返回，三步缺一不可

### 扩展应用
- 213. 打家劫舍II (环形数组)
- 337. 打家劫舍III (二叉树)
- 01背包问题 (物品选择决策)

---

## 53. 最大子数组和 (Medium)

### 核心思想
连续子数组DP的经典题目，使用**Kadane算法**实现O(n)最优解，同时掌握**分治算法**的三分覆盖思想。

### 关键逻辑
1. **连续性约束的DP建模**:
   - 状态定义：`dp[i]` = 以nums[i]结尾的最大子数组和
   - 决策选择：继续之前的子数组 vs 重新开始
   
2. **Kadane算法核心**:
   ```cpp
   dp[i] = max(nums[i], dp[i-1] + nums[i])
   ```
   直观理解：如果之前累计是负数就抛弃，否则继续累加

3. **全局vs局部最优**:
   - 局部最优：dp[i] (以i结尾的最大和)
   - 全局最优：max(dp[0], dp[1], ..., dp[n-1])

4. **分治算法思想**:
   - 三分覆盖：左半部分、右半部分、跨越中点
   - 递归关系：`T(n) = 2T(n/2) + O(n)`，时间复杂度O(n log n)

### 四种实现方式

#### 1. Kadane算法 (推荐) - O(n)
```cpp
int maxSubArrayDP(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    vector<int> dp(n);
    dp[0] = nums[0];
    int max_result = dp[0];
    for(int i = 1; i < n; i++) {
        dp[i] = max(nums[i], nums[i] + dp[i-1]);
        max_result = max(max_result, dp[i]);
    }
    return max_result;
}
```

#### 2. 空间优化版本 - O(1)
```cpp
int maxSubArrayOptimized(vector<int>& nums) {
    int currentSum = nums[0];
    int maxSum = nums[0];
    for(int i = 1; i < nums.size(); i++) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(currentSum, maxSum);
    }
    return maxSum;
}
```

#### 3. 分治算法 - O(n log n)
```cpp
int divideConquer(vector<int>& nums, int left, int right) {
    if(left == right) return nums[left];
    int mid = (left + right) / 2;
    int leftMax = divideConquer(nums, left, mid);
    int rightMax = divideConquer(nums, mid+1, right);
    
    // 计算跨越中点的最大子数组和
    int sumLeft = nums[mid], maxSumLeft = sumLeft;
    for(int i = mid-1; i >= left; i--) {
        sumLeft += nums[i];
        maxSumLeft = max(maxSumLeft, sumLeft);
    }
    
    int sumRight = nums[mid+1], maxSumRight = sumRight;
    for(int i = mid+2; i <= right; i++) {
        sumRight += nums[i];
        maxSumRight = max(maxSumRight, sumRight);
    }
    
    int crossSum = maxSumLeft + maxSumRight;
    return max({leftMax, rightMax, crossSum});
}
```

### 分治算法深度理解
**三分覆盖原理**：任何子数组要么完全在左半部分，要么完全在右半部分，要么跨越中点
- **左半部分最优解**：递归求解`[left, mid]`
- **右半部分最优解**：递归求解`[mid+1, right]`  
- **跨越中点最优解**：从mid向左最大延伸 + 从mid+1向右最大延伸

**关键洞察**：跨越中点的计算实际上覆盖了所有包含mid或mid+1的子数组情况！

### 连续子数组DP特征
1. **状态定义必须包含"以i结尾"的约束**
2. **状态转移体现"继续vs重新开始"的决策**
3. **全局最优需要在所有局部最优中选择**
4. **与其他DP的区别**：
   - 爬楼梯(70题)：递推关系 `f(n) = f(n-1) + f(n-2)`
   - 打家劫舍(198题)：决策关系 `f(n) = max(选择A, 选择B)`
   - 最大子数组(53题)：连续约束 `f(n) = max(继续, 重新开始)`

### 复杂度分析
- **Kadane算法**: 时间O(n)，空间O(1) - 最优解
- **分治算法**: 时间O(n log n)，空间O(log n) - 递归栈
- **暴力枚举**: 时间O(n²)，空间O(1) - 超时

### 易错点
1. **全局最优解**: 需要遍历所有dp[i]取最大值，不是dp[n-1]
2. **边界条件**: 单个元素时的处理
3. **分治边界**: 循环条件应该用`>=`和`<=`包含边界

### 扩展应用
- 152. 乘积最大子数组 (处理负数乘积)
- 718. 最长重复子数组 (长度最大值)
- 209. 长度最小的子数组 (滑动窗口变种)

### 关键理解
连续子数组DP的精髓在于**在保持连续性约束下做最优决策**：每步都要问"我是继续之前的累积，还是从当前位置重新开始？"

---

## 322. 零钱兑换 (Medium)

### 核心思想
完全背包动态规划的经典题目，每个硬币可以使用无限次，求组成目标金额所需的最少硬币数。

### 关键逻辑
1. **状态定义**:
   - `dp[i]` = 组成金额i所需的最少硬币数
   
2. **状态转移方程**:
   ```
   dp[i] = min(dp[i-coin] + 1) for all valid coins
   ```
   逻辑：对于金额i，尝试使用每种硬币，选择最优方案

3. **边界条件**:
   ```cpp
   dp[0] = 0                    // 组成金额0需要0个硬币
   dp[i] = amount + 1           // 初始化为不可能的大值
   ```

4. **无解判断**:
   ```cpp
   return dp[amount] > amount ? -1 : dp[amount];
   ```

### 完全背包vs01背包
- **01背包**: 每个物品最多选择一次
- **完全背包**: 每个物品可以选择无限次
- **关键区别**: 完全背包在内层循环中可以使用已更新的dp值

### 四种实现方式

#### 1. 递归解法 (会超时)
```cpp
int helper(vector<int>& coins, int amount) {
    if(amount == 0) return 0;
    if(amount < 0) return -1;
    
    int minCoins = INT_MAX;
    for(int coin : coins) {
        int subResult = helper(coins, amount - coin);
        if(subResult != -1) {
            minCoins = min(minCoins, subResult + 1);
        }
    }
    return minCoins == INT_MAX ? -1 : minCoins;
}
```
**问题**: 指数级时间复杂度O(S^n)，大量重复计算

#### 2. 记忆化搜索 (自顶向下)
```cpp
int helperMemo(vector<int>& coins, int amount, vector<int>& memo) {
    if(amount == 0) return 0;
    if(amount < 0) return -1;
    if(memo[amount] != -2) return memo[amount];
    
    int minCoins = INT_MAX;
    for(int coin : coins) {
        int subResult = helperMemo(coins, amount - coin, memo);
        if(subResult != -1) {
            minCoins = min(minCoins, subResult + 1);
        }
    }
    memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins;
    return memo[amount];
}
```

#### 3. 动态规划 (自底向上) ⭐ 推荐
```cpp
int coinChangeDP(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);  // 初始化为不可能的大值
    dp[0] = 0;  // 边界条件
    
    for(int i = 1; i <= amount; i++) {
        for(int coin : coins) {
            if(coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount];
}
```


### 关键理解点

#### 为什么初始化为amount + 1？
- **理论上界**: 组成任意金额最多需要amount个面额为1的硬币
- **避免溢出**: 比使用INT_MAX更安全
- **便于判断**: dp[amount] > amount 说明无解

#### 循环顺序为什么正确？
```cpp
for(int i = 1; i <= amount; i++) {        // 外层：金额
    for(int coin : coins) {               // 内层：硬币
        if(coin <= i) {
            dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
}
```
完全背包允许重复使用，所以内层循环使用已更新的dp值是正确的。

### 易错点记录

#### 1. 循环边界错误 ❌
```cpp
for(int i = 1; i < amount; i++) {  // 错误：应该是 i <= amount
```
**后果**: 无法计算dp[amount]，导致返回错误结果

#### 2. 编译错误
使用C++11特性（range-based for循环、initializer list）需要编译器支持：
```bash
g++ -std=c++11 -o problem_322 problem_322_template.cpp
```

### 复杂度分析
- **递归**: 时间O(S^n)，空间O(S) - S是金额，n是硬币种类数
- **记忆化**: 时间O(S × n)，空间O(S)
- **动态规划**: 时间O(S × n)，空间O(S) ⭐ 最优解
- **BFS**: 时间O(S × n)，空间O(S)

### 扩展应用
- 518. 零钱兑换II (组合数问题)
- 279. 完全平方数 (最少平方数)
- 377. 组合总和Ⅳ (排列数问题)

### 测试结果
所有测试用例通过：
- coins=[1,2,5], amount=11 → 3 (5+5+1)
- coins=[2], amount=3 → -1 (无解)
- coins=[1], amount=0 → 0 (边界情况)
- coins=[1,3,4], amount=6 → 2 (3+3)
- coins=[3,5], amount=1 → -1 (无解)

### 关键洞察
完全背包DP的精髓在于**建模无限选择的最优化问题**：将"每个物品可以选择无限次"转化为"在状态转移中允许重复使用已计算的结果"。

---

## 300. 最长递增子序列 (Medium)

### 核心思想
序列动态规划的经典题目，掌握以"位置结尾"的状态定义思维，同时学习贪心+二分查找的O(n log n)优化。

### 关键逻辑
1. **状态定义**:
   - `dp[i]` = 以nums[i]结尾的最长递增子序列长度
   
2. **状态转移方程**:
   ```
   dp[i] = max(dp[j] + 1) for all j < i and nums[j] < nums[i]
   ```
   逻辑：对于每个位置i，检查所有前面更小的元素，选择最优转移

3. **边界条件**:
   ```cpp
   dp[i] = 1  // 每个元素自己构成长度为1的序列
   ```

4. **最终答案**:
   ```cpp
   return max(dp[i]) for all i  // 需要遍历所有位置取最大值
   ```

### 三种实现方式

#### 1. 动态规划 O(n²) - 经典解法 ⭐
```cpp
int lengthOfLISDP(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    
    vector<int> dp(n, 1);  // 初始化为1
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}
```

#### 2. 记忆化搜索 O(n²) - 自顶向下
```cpp
int lengthOfLISMemo(vector<int>& nums) {
    int n = nums.size();
    vector<int> memo(n, -1);
    int maxResult = 1;
    for(int i = 0; i < n; i++) {
        maxResult = max(maxResult, helper(nums, i, memo));
    }
    return maxResult;
}

int helper(vector<int>& nums, int i, vector<int>& memo) {
    if (memo[i] != -1) return memo[i];  // 缓存命中
    memo[i] = 1;  // 基础情况
    for(int j = 0; j < i; j++) {
        if (nums[j] < nums[i]) {
            memo[i] = max(memo[i], helper(nums, j, memo) + 1);
        }
    }
    return memo[i];
}
```

#### 3. 贪心+二分查找 O(n log n) - 最优解 ⭐⭐
```cpp
int lengthOfLISBinary(vector<int>& nums) {
    vector<int> tails;
    for (int num : nums) {
        int pos = tails.size();
        int left = 0, right = tails.size() - 1;
        
        // 二分查找第一个 >= num 的位置
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(tails[mid] >= num) {
                pos = mid;
                right = mid - 1;
            } else {
                left = mid + 1; 
            }
        }
        
        if(pos == tails.size()) {
            tails.push_back(num);  // 添加到末尾
        } else {
            tails[pos] = num;      // 替换
        }
    }
    return tails.size();
}
```

### 贪心+二分查找深度理解

#### 核心思想
- **tails[i]** = 长度为i+1的递增子序列的最小尾元素
- **为什么要最小？** 尾元素越小，后续添加新元素的机会越大

#### 算法步骤
1. 对每个新元素num：
   - 如果num > tails中所有元素 → 直接添加到末尾（延长序列）
   - 否则 → 二分查找第一个≥num的位置并替换（保持最小尾元素）

#### 关键洞察
- **tails数组始终保持严格递增**
- **tails长度 = 最长递增子序列长度**
- **tails内容不一定是真实的LIS，但长度保证正确**

### 易错点记录

#### 1. DP状态转移错误 ❌
```cpp
dp[i] = max(dp[j] + 1);  // 错误：缺少dp[i]参数
```
**正确写法**:
```cpp
dp[i] = max(dp[i], dp[j] + 1);  // 需要比较当前值和新值
```

#### 2. 二分查找语法错误 ❌
```cpp
int left = 0; right = tails.size() - 1;  // 错误：缺少类型声明
```
**正确写法**:
```cpp
int left = 0, right = tails.size() - 1;  // 逗号分隔，统一声明
```

#### 3. 二分查找mid计算位置错误 ❌
```cpp
int mid = (left + right) / 2;  // 放在while外面
while(left <= right) {
    // 使用过时的mid值
}
```
**正确写法**:
```cpp
while(left <= right) {
    int mid = left + (right - left) / 2;  // 每次循环重新计算
}
```

#### 4. 记忆化搜索语法错误 ❌
```cpp
if memo[i] != -1 return memo[i];  // 缺少括号
for(int j=0; j<i; i++) {          // 循环变量错误
```
**正确写法**:
```cpp
if (memo[i] != -1) return memo[i];  // 加括号
for(int j=0; j<i; j++) {            // j++而不是i++
```

#### 5. 初始化的重要性
```cpp
int pos = tails.size();  // 🔑 关键：初始化为"未找到"标志
```
这个初始化确保了当没找到≥num的元素时，pos保持为tails.size()，从而正确执行push_back操作。

### 序列DP特征总结
1. **状态定义必须包含"以第i个元素结尾"**
2. **需要检查前面所有可能的转移状态**
3. **最终答案需要遍历所有状态取最优值**
4. **与其他DP类型的区别**：
   - 爬楼梯：递推关系
   - 打家劫舍：决策关系  
   - 最大子数组：连续约束
   - 零钱兑换：完全背包
   - **最长递增子序列：序列关系**

### 复杂度分析
- **DP解法**: 时间O(n²)，空间O(n)
- **记忆化**: 时间O(n²)，空间O(n) + 递归栈
- **贪心+二分**: 时间O(n log n)，空间O(n) ⭐ 最优解

### 扩展应用
- 354. 俄罗斯套娃信封问题 (二维LIS)
- 673. 最长递增子序列的个数 (计数问题)
- 1143. 最长公共子序列 (双序列DP)
- 368. 最大整除子集 (特殊约束的LIS)

### 测试结果
所有三种实现均通过全部测试用例：
- [10,9,2,5,3,7,101,18] → 4
- [0,1,0,3,2,3] → 4  
- [7,7,7,7,7,7,7] → 1
- [1,3,6,7,9,4,10,5,6] → 6
- [10] → 1

### 关键洞察
序列DP的精髓在于**正确建模"以某位置结尾"的状态**，通过检查所有前驱状态来构建最优解。贪心+二分的优化体现了**维护关键信息而非完整状态**的算法设计思想。

---

## 1143. 最长公共子序列 (Medium)

### 核心思想
双序列动态规划的经典题目，用二维DP表表示两个序列的匹配关系，掌握字符匹配/不匹配的状态转移。

### 关键逻辑
1. **状态定义**:
   - `dp[i][j]` = text1前i个字符和text2前j个字符的最长公共子序列长度
   
2. **状态转移方程**:
   ```cpp
   if (text1[i-1] == text2[j-1]):
       dp[i][j] = dp[i-1][j-1] + 1      // 字符匹配：左上角+1
   else:
       dp[i][j] = max(dp[i-1][j],       // 上边：不使用text1[i-1]
                      dp[i][j-1])       // 左边：不使用text2[j-1]
   ```

3. **边界条件**:
   ```cpp
   dp[0][j] = 0  // 空字符串与任何字符串的LCS为0
   dp[i][0] = 0  // 任何字符串与空字符串的LCS为0
   ```

4. **哨兵技巧**:
   - 创建`(m+1) x (n+1)`的DP表，多出的一行一列作为边界处理
   - 避免特殊判断，简化代码逻辑

### 三种实现方式

#### 1. 二维动态规划 O(mn) - 经典解法 ⭐
```cpp
int longestCommonSubsequenceDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    
    // 哨兵技巧：多一行一列处理边界
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(text1[i] == text2[j]) {
                dp[i+1][j+1] = dp[i][j] + 1;        // 左上角+1
            } else {
                dp[i+1][j+1] = max(dp[i+1][j],      // 左边
                                   dp[i][j+1]);     // 上边
            }
        }
    }
    
    return dp[m][n];
}
```

#### 2. 记忆化搜索 O(mn) - 自顶向下
```cpp
int longestCommonSubsequenceMemo(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return helper(text1, text2, m, n, memo);
}

int helper(string& text1, string& text2, int i, int j, vector<vector<int>>& memo) {
    if(i == 0 || j == 0) return 0;  // 边界条件
    if(memo[i][j] != -1) return memo[i][j];  // 缓存命中
    
    int result;
    if(text1[i-1] == text2[j-1]) {
        result = helper(text1, text2, i-1, j-1, memo) + 1;
    } else {
        result = max(helper(text1, text2, i, j-1, memo),
                    helper(text1, text2, i-1, j, memo));
    }
    
    memo[i][j] = result;  // 缓存结果
    return result;
}
```

#### 3. 空间优化 O(min(m,n)) - 滚动数组 ⭐⭐
```cpp
int longestCommonSubsequenceOptimized(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    if(m == 0 || n == 0) return 0;

    // 两行滚动数组
    vector<int> pre(n + 1, 0);   // 上一行
    vector<int> curr(n + 1, 0);  // 当前行

    for(int i = 0; i < m; i++) {
        curr[0] = 0;  // 边界条件
        for(int j = 0; j < n; j++) {
            if(text1[i] == text2[j]) {
                curr[j+1] = pre[j] + 1;         // 左上角+1
            } else {
                curr[j+1] = max(pre[j+1],       // 上边
                               curr[j]);        // 左边
            }
        }
        swap(pre, curr);  // 滚动：高效交换
    }
    
    return pre[n];  // 最终结果在pre[n]
}
```

### 滚动数组深度理解

#### 核心思想
- **观察依赖关系**：`dp[i][j]` 只依赖于 `dp[i-1][j-1]`、`dp[i-1][j]`、`dp[i][j-1]`
- **空间优化策略**：只保存上一行和当前行，不需要整个二维表
- **滚动机制**：计算完当前行后，通过swap让当前行变成下一轮的"上一行"

#### 数组对应关系
| 二维DP | 滚动数组 | 说明 |
|--------|----------|------|
| `dp[i-1][j-1]` | `pre[j]` | 左上角：上一行的j位置 |
| `dp[i-1][j]` | `pre[j+1]` | 上边：上一行的j+1位置 |
| `dp[i][j-1]` | `curr[j]` | 左边：当前行的j位置 |
| `dp[i][j]` | `curr[j+1]` | 当前位置：当前行的j+1位置 |

#### 为什么返回pre[n]？
```cpp
// 最后一轮循环结束时
curr = [最后一行的计算结果]
swap(pre, curr);  // 交换后
pre = [最后一行的结果] ← 最终答案在这里
```

### 双序列DP特征总结
1. **二维状态空间**：需要考虑两个序列的匹配关系
2. **匹配决策**：字符匹配时延续子问题，不匹配时选择最优方案
3. **边界处理**：空序列作为边界条件，通常结果为0
4. **空间优化**：可以用滚动数组优化，但不能构造具体序列
5. **时间复杂度**：通常为O(mn)，难以进一步优化

### 与LIS对比分析
| 特征 | LIS (300题) | LCS (1143题) |
|------|-------------|--------------|
| 序列数量 | 单序列 | 双序列 |
| 状态定义 | `dp[i]` = 以i结尾的最长递增子序列 | `dp[i][j]` = 两序列前缀的LCS |
| 状态转移 | 检查所有前驱，选择最优 | 考虑匹配/不匹配，选择最优 |
| 复杂度 | O(n²) → O(n log n) | O(mn) → O(min(m,n)) |
| 优化方式 | 贪心+二分查找 | 滚动数组 |

### 易错点记录

#### 1. 记忆化搜索字符比较错误 ❌
```cpp
if(text1[i] == text2[j]) {  // 错误：参数i,j表示长度
```
**正确写法**:
```cpp
if(text1[i-1] == text2[j-1]) {  // 字符下标要减1
```

#### 2. 滚动数组状态转移错误 ❌
```cpp
curr[j+1] = curr[j] + 1;  // 错误：应该是左上角+1
```
**正确写法**:
```cpp
curr[j+1] = pre[j] + 1;  // 左上角+1
```

### 复杂度分析
- **二维DP**: 时间O(mn)，空间O(mn)
- **记忆化**: 时间O(mn)，空间O(mn) + 递归栈
- **滚动数组**: 时间O(mn)，空间O(min(m,n)) ⭐ 最优空间

### 扩展应用
- 72. 编辑距离 (插入、删除、替换操作)
- 97. 交错字符串 (路径匹配问题)
- 115. 不同的子序列 (计数DP)
- 516. 最长回文子序列 (LCS变种)

### 测试结果
所有实现均通过全部测试用例：
- "abcde" vs "ace" → 3 (LCS: "ace")
- "abc" vs "abc" → 3 (完全相同)
- "abc" vs "def" → 0 (无公共字符)
- "abcdgh" vs "aedfhr" → 3 (LCS: "adh")
- "a" vs "a" → 1 (单字符匹配)

### 关键洞察
双序列DP的精髓在于**建模两个序列的匹配关系**，通过二维状态空间考虑所有可能的匹配组合。滚动数组优化体现了**最小化状态存储**的空间优化思想。

---

## 516. 最长回文子序列 (Medium)

### 核心思想
区间动态规划的经典题目，掌握"滑动窗口式"的区间遍历思维，理解大区间依赖小区间的状态转移。

### 关键逻辑
1. **状态定义**:
   - `dp[i][j]` = 字符串s[i..j]范围内的最长回文子序列长度
   
2. **状态转移方程**:
   ```cpp
   if (s[i] == s[j]):
       dp[i][j] = dp[i+1][j-1] + 2    // 两端匹配，长度+2
   else:
       dp[i][j] = max(dp[i+1][j], dp[i][j-1])  // 选择更优的子区间
   ```

3. **边界条件**:
   ```cpp
   dp[i][i] = 1  // 单个字符的回文长度为1
   ```

4. **遍历顺序**: 按区间长度从小到大（关键！）
   ```cpp
   for(int len = 2; len <= n; len++) {        // 区间长度
       for(int i = 0; i <= n - len; i++) {    // 左端点
           int j = i + len - 1;               // 右端点
           // 状态转移...
       }
   }
   ```

### 核心洞察

#### 区间DP的"滑动窗口"思维
- **外层循环**: 固定窗口大小(len = 2, 3, 4, ...)
- **内层循环**: 将固定大小的窗口在字符串上滑动
- **依赖关系**: 大窗口的计算依赖小窗口的结果

#### 与LCS的巧妙联系
- **转化思想**: s的最长回文子序列 = s与reverse(s)的最长公共子序列
- **原理**: 回文序列在原串和反转串中都存在
- **优势**: 可以直接复用LCS代码

### 三种实现方式

#### 1. 区间DP - O(n²) ⭐ 推荐
```cpp
int longestPalindromeSubseqDP(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // 初始化：单个字符
    for(int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // 按区间长度填充
    for(int len = 2; len <= n; len++) {
        for(int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if(s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    return dp[0][n-1];
}
```

#### 2. 记忆化搜索 - O(n²)
```cpp
int helper(string& s, int i, int j, vector<vector<int>>& memo) {
    if(i > j) return 0;
    if(i == j) return 1;
    if(memo[i][j] != -1) return memo[i][j];
    
    if(s[i] == s[j]) {
        memo[i][j] = helper(s, i+1, j-1, memo) + 2;
    } else {
        memo[i][j] = max(helper(s, i+1, j, memo), helper(s, i, j-1, memo));
    }
    return memo[i][j];
}
```

#### 3. LCS转化 - O(n²)
```cpp
int longestPalindromeSubseqLCS(string s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    return longestCommonSubsequence(s, rev_s);
}
```

### 复杂度分析
- **时间复杂度**: O(n²) - 双重循环填充DP表
- **空间复杂度**: O(n²) - 二维DP表
- **优化可能**: 滚动数组优化空间，但实现复杂

### 易错点
1. **遍历顺序错误**: 必须按区间长度递增，不能按坐标遍历
2. **边界条件**: `len <= n` 不是 `len < n`
3. **循环边界**: `i <= n - len` 保证j不越界
4. **公式错误**: `j = i + len - 1` 不是其他公式

### 与其他DP类型对比
| DP类型 | 状态定义 | 遍历顺序 | 转移特点 |
|--------|----------|----------|----------|
| 序列DP | 以位置结尾 | 从前往后 | 检查所有前驱 |
| 双序列DP | 两序列前缀 | 双重递增 | 匹配/不匹配 |
| **区间DP** | 区间范围 | 按长度递增 | 端点处理 |

### 扩展应用
- 5. 最长回文子串 (连续性约束)
- 312. 戳气球 (乘积最大化)
- 1039. 多边形三角剖分的最低得分
- 87. 扰乱字符串

### 测试结果
所有测试用例通过：
- "bbbab" → 4 (LPS: "bbbb")
- "cbbd" → 2 (LPS: "bb")
- "a" → 1 (单字符)
- "abcba" → 5 (整个串就是回文)
- "aabaa" → 5 (整个串就是回文)

### 关键洞察
区间DP的精髓在于**按区间长度递增的遍历策略**，确保计算大区间时所需的小区间已经计算完毕。"滑动窗口"的思维模式帮助理解这种遍历顺序的必要性。

---

## 104. 二叉树的最大深度 (Easy)

### 核心思想
二叉树深度问题的入门经典，体现了**树形递归**的基本思维模式：大树的问题分解为子树的问题。

### 关键逻辑
1. **递归结构**:
   - 树的深度 = max(左子树深度, 右子树深度) + 1
   - 空节点深度为0
   
2. **三种实现方式**:
   ```cpp
   // 1. 递归DFS - 最直观
   int maxDepthRecursive(TreeNode* root) {
       if (!root) return 0;
       return max(maxDepthRecursive(root->left), 
                  maxDepthRecursive(root->right)) + 1;
   }
   
   // 2. BFS层序遍历 - 按层计数
   int maxDepthBFS(TreeNode* root) {
       if (!root) return 0;
       queue<TreeNode*> q;
       q.push(root);
       int depth = 0;
       
       while (!q.empty()) {
           int size = q.size();
           for (int i = 0; i < size; i++) {
               TreeNode* node = q.front();
               q.pop();
               if (node->left) q.push(node->left);
               if (node->right) q.push(node->right);
           }
           depth++;
       }
       return depth;
   }
   
   // 3. DFS栈模拟 - 手动管理深度
   int maxDepthDFS(TreeNode* root) {
       if (!root) return 0;
       stack<pair<TreeNode*, int>> st;
       st.push({root, 1});
       int maxDepth = 1;
       
       while (!st.empty()) {
           auto [node, depth] = st.top();
           st.pop();
           maxDepth = max(maxDepth, depth);
           
           if (node->left) st.push({node->left, depth + 1});
           if (node->right) st.push({node->right, depth + 1});
       }
       return maxDepth;
   }
   ```

3. **遍历模式对比**:
   - **递归DFS**: 后序遍历模式，自底向上返回结果
   - **BFS**: 层序遍历，逐层处理，层数即深度
   - **栈DFS**: 自顶向下传递深度值，记录最大值

### 时间复杂度分析
- **所有方法**: 时间O(n) - 每个节点访问一次
- **空间复杂度差异**:
  - 递归: O(h) - h是树高度，最坏O(n)（退化为链表）
  - BFS: O(w) - w是最大宽度，最坏O(n)（完全二叉树）
  - 栈DFS: O(h) - 同递归

### 易错点
1. **递归出口**: 空节点返回0，不是1
2. **BFS层数计算**: 要在处理完整一层后才+1
3. **栈中深度传递**: 使用`depth + 1`而不是`depth++`
4. **指针访问**: `node->left`而不是`node.left`
5. **循环条件**: BFS中使用预存的`size`避免队列大小变化

### 扩展应用
- 111. 二叉树的最小深度 (修改为min)
- 110. 平衡二叉树 (比较左右子树深度差)
- 543. 二叉树的直径 (每个节点的左右深度和)

### 关键理解
二叉树递归的精髓：**将树形问题转化为子树问题**，通过递归的自然结构解决复杂的树形遍历。

---

## 226. 翻转二叉树 (Easy)

### 核心思想
二叉树变换的经典题目，体现了**树形递归**的核心思维和**局部独立性**的算法特征。

### 关键逻辑
1. **树形递归思维**:
   - 翻转大树 = 交换左右子树 + 递归翻转左右子树
   - 每个节点只需要管理自己的直接子节点
   
2. **三种实现方式的本质**:
   ```cpp
   // 1. 递归DFS - 最直观的实现
   TreeNode* invertTree(TreeNode* root) {
       if (!root) return nullptr;
       TreeNode* left = invertTree(root->left);
       TreeNode* right = invertTree(root->right);
       root->left = right;
       root->right = left;
       return root;
   }
   
   // 2. BFS层序遍历 - 按层处理
   TreeNode* invertTreeBFS(TreeNode* root) {
       if (!root) return nullptr;
       queue<TreeNode*> q;
       q.push(root);
       while (!q.empty()) {
           TreeNode* node = q.front();
           q.pop();
           swap(node->left, node->right);
           if (node->left) q.push(node->left);
           if (node->right) q.push(node->right);
       }
       return root;
   }
   
   // 3. DFS栈模拟 - 手动管理栈
   TreeNode* invertTreeDFS(TreeNode* root) {
       if (!root) return nullptr;
       stack<TreeNode*> st;
       st.push(root);
       while (!st.empty()) {
           TreeNode* node = st.top();
           st.pop();
           swap(node->left, node->right);
           if (node->left) st.push(node->left);
           if (node->right) st.push(node->right);
       }
       return root;
   }
   ```

### 深层洞察：算法的"局部独立性"

#### 核心发现
在翻转二叉树中，**BFS ≈ DFS**，三种方法本质相同：
- **为什么？** 每个节点的操作是独立的，只需交换自己的左右子树
- **关键特征**: 节点间没有复杂依赖关系，处理顺序不影响最终结果

#### 算法分类框架

**类型A：局部独立操作** (BFS ≈ DFS)
- 翻转二叉树 - 每个节点独立交换左右子树
- 二叉树层序遍历 - 每个节点独立输出
- 节点值修改 - 每个节点独立处理
→ **选择原则**: 选择最简洁的实现（通常是递归）

**类型B：全局依赖操作** (BFS ≠ DFS)
- 路径搜索 - DFS回溯 vs BFS最短路径
- 二叉树序列化 - 遍历顺序直接影响结果
- 拓扑排序 - 不同遍历可能产生不同合法序列
→ **选择原则**: 根据具体需求选择遍历方式

#### 栈版本的微妙细节
```cpp
// 交换后再入栈，会改变访问顺序
swap(node->left, node->right);  // 交换了！
if (node->left) st.push(node->left);   // 入栈的实际是原来的right
if (node->right) st.push(node->right); // 入栈的实际是原来的left
```
**关键洞察**: 虽然访问顺序改变了，但在局部独立操作中不影响最终结果！

### 时间复杂度分析
- **所有方法**: 时间O(n) - 每个节点访问一次
- **空间复杂度**:
  - 递归: O(h) - 递归栈深度
  - BFS: O(w) - 队列最大宽度  
  - 栈DFS: O(h) - 栈深度

### 选择建议
**推荐递归版本**，因为：
1. 代码最简洁，逻辑最直观
2. 完美体现树形递归思维
3. 在"局部独立"问题中，简洁性最重要

### 易错点
1. **递归指针混乱**: 先保存子树指针，再交换
3. **边界处理**: 空节点检查

### 扩展应用
- 101. 对称二叉树 (判断镜像对称)
- 100. 相同的树 (递归比较)
- 951. 翻转等价二叉树 (翻转后判断相等)

### 关键理解
1. **树形递归精髓**: 大问题分解为子问题的自然递归结构
2. **算法分类思维**: 识别问题的"局部独立性"特征
3. **实现选择策略**: 在等效算法中选择最简洁的版本

这道题的价值不仅在于掌握树形递归，更在于建立**算法分类的思维框架**，学会识别不同问题类型的本质特征。

---

## 94. 二叉树的中序遍历 (Medium)

### 核心思想
二叉树遍历的经典问题，掌握**栈模拟递归**的通用模式，理解中序遍历在BST中的特殊性质。

### 关键逻辑
1. **中序遍历顺序**:
   - 递归模式：左子树 → 根节点 → 右子树
   - 对于BST：结果必然是有序序列

2. **两种实现方式对比**:
   ```cpp
   // 1. 递归实现 - 最直观
   vector<int> inorderTraversal(TreeNode* root) {
       if(root == nullptr) return {};
       vector<int> result;
       vector<int> left = inorderTraversal(root->left);
       vector<int> right = inorderTraversal(root->right);
       
       result.insert(result.end(), left.begin(), left.end());
       result.push_back(root->val);
       result.insert(result.end(), right.begin(), right.end());
       return result;
   }
   
   // 2. 迭代实现 - 栈模拟递归 ⭐ 核心掌握
   vector<int> inorderTraversalIterative(TreeNode* root) {
       vector<int> result;
       stack<TreeNode*> st;
       TreeNode* curr = root;
       
       while(!st.empty() || curr != nullptr) {
           // 阶段1: 一路向左，沿途节点入栈
           while(curr != nullptr) {
               st.push(curr);
               curr = curr->left;
           }
           
           // 阶段2: 弹栈访问，然后转向右子树
           curr = st.top();
           st.pop();
           result.push_back(curr->val);
           curr = curr->right;  // 触发右子树的向左遍历
       }
       return result;
   }
   ```

### 栈模拟递归的核心模式

#### 深层理解：为什么用curr驱动？
- **curr是状态指针**：控制"向左深入"和"右子树转移"
- **栈保存回溯路径**：存储从根到当前位置的路径
- **三阶段循环**：
  1. 向左深入 → 路径入栈
  2. 到达叶子 → 弹栈访问  
  3. 转向右子树 → 重复循环

#### 关键洞察
```cpp
// ❌ 错误理解
while(curr->left != nullptr) {
    st.push(curr->left);  // 丢失了当前节点！
}

// ✅ 正确理解
while(curr != nullptr) {
    st.push(curr);        // 保存当前节点用于回溯
    curr = curr->left;    // 继续向左深入
}
```

**为什么必须保存当前节点？**
- 中序遍历需要在处理完左子树后回到父节点
- 栈中存储的是"待访问的父节点序列"
- `curr = node->right` 让右子树也经历完整的遍历过程

### 算法模式总结

#### 栈模拟递归的通用框架
```cpp
while(!st.empty() || curr != nullptr) {
    // 1. 深入阶段：向某个方向探索，沿途保存状态
    while(curr != nullptr) {
        st.push(curr);           // 保存当前状态
        curr = curr->next_dir;   // 继续探索
    }
    
    // 2. 处理阶段：到达边界，开始处理
    curr = st.top();
    st.pop();
    process(curr);               // 处理当前节点
    
    // 3. 转移阶段：转向其他方向继续
    curr = curr->other_dir;      // 转向其他分支
}
```

#### 三种遍历的时机差异
| 遍历类型 | 访问时机 | 模式特点 |
|----------|----------|----------|
| **前序** | 入栈时访问 | 根→左→右 |
| **中序** | 弹栈时访问 | 左→根→右 |
| **后序** | 需要状态标记 | 左→右→根 |

### 中序遍历的特殊应用

#### BST中的重要性质
```cpp
// 验证BST：中序遍历必须严格递增
bool isValidBST(TreeNode* root) {
    vector<int> inorder = inorderTraversal(root);
    for(int i = 1; i < inorder.size(); i++) {
        if(inorder[i] <= inorder[i-1]) return false;
    }
    return true;
}

// BST中第K小元素：中序遍历的第K个
int kthSmallest(TreeNode* root, int k) {
    vector<int> inorder = inorderTraversal(root);
    return inorder[k-1];
}
```

### 时间复杂度分析
- **递归版本**: 时间O(n)，空间O(h)递归栈 + O(n)结果存储
- **迭代版本**: 时间O(n)，空间O(h)显式栈 + O(n)结果存储
- **Morris遍历**: 时间O(n)，空间O(1) - 进阶技巧

### 易错点
1. **迭代版本循环条件**: `!st.empty() || curr != nullptr` 缺一不可
2. **状态更新**: `curr = node->right` 而不是 `node = node->right`
3. **入栈时机**: 向左时入栈，而不是访问时入栈

### 扩展应用
- 144. 二叉树的前序遍历 (调整访问时机)
- 145. 二叉树的后序遍历 (需要状态标记)
- 98. 验证二叉搜索树 (利用有序性)
- 230. 二叉搜索树中第K小的元素 (提前终止遍历)

### 关键理解
1. **栈模拟递归的本质**: 显式管理调用栈，控制执行流程
2. **中序遍历的数学性质**: 在BST中产生有序序列
3. **迭代vs递归的权衡**: 避免栈溢出 vs 代码简洁性

这道题建立了对**栈模拟递归**的深度理解，这个模式可以推广到很多树形递归问题的迭代实现中。

---


---

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

## 链表专题

### 206. 反转链表 (Easy) - 链表算法基础
**核心思想**: 改变每个节点的next指针方向，从单向链表变为反向链表
**关键技巧**: 三指针协调 - prev、curr、next的同步移动
**防断裂**: 修改指针前先保存后续节点，避免链表断裂

#### 迭代实现 - 三指针模式 ⭐
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;  // 保存后续
        curr->next = prev;            // 反转指向
        prev = curr;                  // 指针前移
        curr = next;                  // 指针前移
    }
    return prev;  // prev成为新头节点
}
```

#### 递归实现 - 信任机制 ⭐
```cpp
ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseListRecursive(head->next);  // 信任递归
    head->next->next = head;   // 当前操作：反转连接
    head->next = nullptr;      // 防成环关键步骤
    return newHead;            // 返回新头节点
}
```

### 24. 两两交换链表中的节点 (Medium) - 分组处理进阶
**核心思想**: 局部反转的应用，每两个节点为一组进行交换
**关键技巧**: 虚拟头节点 + 四指针协调
**模式升华**: 从整体操作到分组操作的算法思维

### 25. K个一组翻转链表 (Hard) - 复合算法集大成
**核心思想**: 206题反转+24题分组的完美融合，任意k值的通用分组反转算法
**关键技巧**: 模块化设计 + 复合操作 + 连接管理
**算法升华**: 从特例(k=2)到通用(任意k)的抽象设计能力

### 92. 反转链表II (Medium) - 三段式精确区间反转
**核心思想**: 三段式连接法，精确区间控制+复用已有技巧
**关键技巧**: 边界定位 + 安全断开 + 局部反转 + 三段重连
**技术融合**: 206题三指针技巧 + 25题模块化设计 + 精确边界控制

#### 24题迭代实现 - 虚拟头节点+四指针 ⭐
```cpp
ListNode* swapPairs(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    while (prev->next && prev->next->next) {
        ListNode* first = prev->next;
        ListNode* second = prev->next->next;
        ListNode* next = second->next;
        
        // 三步交换：prev→second→first→next
        second->next = first;
        first->next = next;
        prev->next = second;
        
        prev = first;  // 更新prev为交换后的末尾节点
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}
```

#### 25题迭代实现 - 模块化分组反转 ⭐⭐
```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prevGroupEnd = dummy;
    
    while (hasKNodes(prevGroupEnd->next, k)) {
        auto [newHead, newTail] = reverseKNodes(prevGroupEnd->next, k);
        prevGroupEnd->next = newHead;
        prevGroupEnd = newTail;
    }
    
    return dummy->next;
}

// 辅助函数1: 检查是否有k个节点
bool hasKNodes(ListNode* start, int k) {
    while (start && k > 0) {
        start = start->next;
        k--;
    }
    return k == 0;
}

// 辅助函数2: 反转k个节点并连接
pair<ListNode*, ListNode*> reverseKNodes(ListNode* start, int k) {
    if (!start || k == 0) return {nullptr, nullptr};
    
    ListNode* originalStart = start;  // 保存原始头，成为新尾
    ListNode* prev = nullptr;
    
    // 反转k个节点 (复用206题技巧)
    while (start && k > 0) {
        ListNode* next = start->next;
        start->next = prev;
        prev = start;
        start = next;
        k--;
    }
    
    // 关键：新尾连接到下一组
    originalStart->next = start;
    
    return {prev, originalStart};  // {新头, 新尾}
}
```

#### 92题三段式实现 - 精确区间反转 ⭐⭐
```cpp
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    // 1. 边界定位：找到关键节点
    ListNode* startPre = findPrevNode(dummy, left);    // left前驱
    ListNode* startNode = startPre->next;              // 反转段开始
    ListNode* endNode = findTargetNode(dummy, right);  // 反转段结束
    ListNode* nextNode = endNode->next;                // right后继
    
    // 2. 安全断开：避免反转时影响后续
    endNode->next = nullptr;
    
    // 3. 局部反转：复用206题技巧
    auto [newHead, newTail] = reverseSegment(startNode);
    
    // 4. 三段重连：前段→反转段→后段
    startPre->next = newHead;
    newTail->next = nextNode;
    
    return dummy->next;
}

// 辅助函数：定位前驱节点
ListNode* findPrevNode(ListNode* dummy, int pos) {
    ListNode* node = dummy;
    for(int i = 0; i < pos - 1; i++) {
        node = node->next;
    }
    return node;
}

// 辅助函数：定位目标节点  
ListNode* findTargetNode(ListNode* dummy, int pos) {
    ListNode* node = dummy;
    for(int i = 0; i < pos; i++) {
        node = node->next;
    }
    return node;
}

// 辅助函数：反转链表段（复用206题）
pair<ListNode*, ListNode*> reverseSegment(ListNode* start) {
    ListNode* pre = nullptr;
    ListNode* curr = start;
    while(curr) {
        ListNode* next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return {pre, start};  // {新头, 新尾}
}
```

#### 递归实现 - 分治思想 ⭐
```cpp
ListNode* swapPairsRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* next = head->next;
    ListNode* nextNode = swapPairsRecursive(head->next->next);  // 信任递归
    next->next = head;         // 当前操作：交换这一对
    head->next = nextNode;     // 连接到递归结果
    return next;               // 返回交换后的新头节点
}
```

## 链表算法核心模式总结

### 迭代 vs 递归思维对比
| 特征 | 迭代思维 | 递归思维 |
|------|----------|----------|
| **控制方式** | 主动推进，step by step | 信任机制，处理当前 |
| **状态管理** | 全局状态跟踪 | 局部操作设计 |
| **空间复杂度** | O(1) | O(h) - 递归栈 |
| **思维模式** | 从前往后构建 | 假设后面已完成 |

### 递归设计的三要素
1. **信任假设**: 相信递归会正确处理子问题
2. **专注当前**: 只处理当前层的局部操作  
3. **正确返回**: 保证返回值符合函数契约

### 指针操作进阶路径
```
206题：三指针 prev→curr→next (整体反转)
    ↓
24题：四指针 prev→first→second→next (固定k=2分组)
    ↓  
25题：模块化设计 prevGroupEnd→[k个节点分组] (任意k通用算法)
    ↓
92题：三段式设计 前段→反转段→后段 (精确区间反转)
```

### 核心技巧工具箱
1. **虚拟头节点**: 统一处理头节点变化，简化边界逻辑
2. **多指针协调**: 保存关键节点，防止链表断裂
3. **防成环处理**: 递归中必须切断旧连接
4. **边界条件**: 空链表、单节点、奇偶长度的系统处理
5. **模块化设计**: 复杂算法分解为独立的辅助函数
6. **连接管理**: 确保分组操作后链表的完整连接

### 算法模式识别
- **整体变换**: 206题类型，使用三指针迭代或信任递归
- **固定分组**: 24题类型，虚拟头节点+多指针协调
- **通用分组**: 25题类型，模块化设计+复合操作
- **精确区间**: 92题类型，三段式设计+技巧复用

### 92题关键突破
- **三段式理念**: 定位→断开→反转→重连的清晰流程
- **技巧复用**: 206题三指针 + 25题模块化 + 边界精确控制
- **模块化设计**: 三个独立辅助函数，职责分离
- **安全操作**: 先断开连接，避免反转时的相互影响

## 25题关键要点与易错点

### 🎯 核心算法思想
- **复合操作**: 分组识别 + 局部反转 + 连接管理
- **模块化设计**: 将复杂问题分解为独立的辅助函数
- **连接保证**: 确保每次操作后链表的完整性

### ⚠️ 常见易错点分析

#### 1. **语法错误类**
```cpp
// ❌ 错误：结构化绑定语法错误
auto {newHead, newTail} = reverseKNodes(...);

// ✅ 正确：使用方括号
auto [newHead, newTail] = reverseKNodes(...);
```

#### 2. **变量名不匹配**
```cpp
auto [newhead, newtail] = reverseKNodes(...);
prevGroupEnd->next = newHead;  // ❌ 变量名大小写不匹配
```

#### 3. **内存管理错误**
```cpp
ListNode* dummy = ListNode(0);     // ❌ 栈对象，可能有问题
ListNode* dummy = new ListNode(0); // ✅ 堆对象更安全
```

#### 4. **连接断裂担心**
```cpp
// 担心：prevGroupEnd = newTail 会断开连接？
// 解答：不会！newTail在返回前已经连接到下一组
originalStart->next = start;  // 关键连接步骤
```

#### 5. **hasKNodes边界检查**
```cpp
// ❌ 可能的错误：检查时修改了k的值
bool hasKNodes(ListNode* start, int k) {
    while(start) {
        k--;  // 修改了参数k
        start = start->next;
    }
    return k == 0;
}

// ✅ 正确：使用局部变量或者不修改参数
bool hasKNodes(ListNode* start, int k) {
    while(start && k > 0) {
        start = start->next;
        k--;
    }
    return k == 0;
}
```

### 🔧 调试要点
1. **分步验证**: 先确保 hasKNodes 和 reverseKNodes 独立正确
2. **连接检查**: 重点验证每组反转后的连接是否完整
3. **边界测试**: 测试k=1、k=链表长度、k>链表长度等边界情况
4. **内存安全**: 确保没有野指针和内存泄漏

### 💡 设计精髓
- **单一职责**: 每个函数只负责一个明确的功能
- **接口设计**: 返回值设计要便于调用方使用
- **状态管理**: prevGroupEnd始终指向已处理部分的尾部
- **信任机制**: 主函数信任辅助函数会正确处理局部操作

### 🔑 连接机制深度理解

#### 双重连接的必要性
25题需要两个层次的连接操作：

**1. 组内连接** (reverseKNodes函数内部):
```cpp
startNode->next = start;  // 新尾连接到下一组开始
```
- **作用**: 保证当前反转组的内部完整性
- **时机**: 反转操作完成后立即执行
- **连接**: 当前组尾部 → 剩余链表头部

**2. 组间连接** (主函数执行):
```cpp
prevGroupEnd->next = newHead;  // 上一组尾部连接到当前组新头
```
- **作用**: 保证不同反转组之间的连接完整性  
- **时机**: 获得反转结果后执行
- **连接**: 上一组尾部 → 当前组新头部

#### 时序控制的关键性
```cpp
// ✅ 正确时序
while(hasKNodes(prevGroupEnd->next, k)) {
    auto [newHead, newTail] = reverseKNodes(...);  // 1. 先反转
    prevGroupEnd->next = newHead;                  // 2. 再连接
    prevGroupEnd = newTail;                        // 3. 最后更新
}
```

**为什么必须按此顺序**:
- **步骤1**: 反转操作产生newHead和newTail
- **步骤2**: 利用当前prevGroupEnd建立组间连接
- **步骤3**: 更新prevGroupEnd为新的尾部，准备下轮连接

**错误时序的后果**:
```cpp
// ❌ 如果提前更新prevGroupEnd
prevGroupEnd = newTail;           // 失去上一组尾部引用
prevGroupEnd->next = newHead;     // 错误连接！
```

#### 连接完整性验证
**完整流程示例** `[1,2,3,4,5]` k=2:

```
初始: dummy → 1 → 2 → 3 → 4 → 5
      ↑prevGroupEnd

第一轮:
- 反转[1,2] → {newHead:2, newTail:1}
- 组内连接: 1.next = 3
- 组间连接: dummy.next = 2
- 结果: dummy → 2 → 1 → 3 → 4 → 5
- 更新: prevGroupEnd = 1

第二轮:  
- 反转[3,4] → {newHead:4, newTail:3}
- 组内连接: 3.next = 5
- 组间连接: 1.next = 4  ← 关键！
- 结果: dummy → 2 → 1 → 4 → 3 → 5
- 更新: prevGroupEnd = 3
```

#### 核心洞察
- **组内连接**: 解决当前反转组的向后延续
- **组间连接**: 解决不同反转组的串联组合
- **时序控制**: prevGroupEnd作为连接桥梁，必须在正确时机更新
- **状态维护**: 每轮循环后prevGroupEnd指向已处理部分的真实尾部

### 扩展应用方向
- 25. K个一组翻转链表 (24题推广)
- 92. 反转链表II (指定区间反转)
- 143. 重排链表 (复杂节点重组)
- 61. 旋转链表 (整体移动)

*最后更新: 2025-08-12*