# 动态规划专题

本专题目录
- [70. 爬楼梯](#dp-70)
- [198. 打家劫舍](#dp-198)
- [53. 最大子数组和](#dp-53)
- [322. 零钱兑换](#dp-322)
- [300. 最长递增子序列](#dp-300)
- [1143. 最长公共子序列](#dp-1143)
- [516. 最长回文子序列](#dp-516)

<a id="dp-70"></a>
### 70. 爬楼梯 (Easy) - DP入门
**状态定义**: `dp[i]` = 爬到第i阶的方法数
**转移方程**: `dp[i] = dp[i-1] + dp[i-2]`
**四种实现**: 递归、记忆化、DP、空间优化

### 198. 打家劫舍 (Medium) - 决策类DP
**状态定义**: `dp[i]` = 偷前i+1间房的最大金额
**转移方程**: `dp[i] = max(nums[i] + dp[i-2], dp[i-1])`
**核心**: 每步做选择决策，约束影响状态转移

<a id="dp-198"></a>
### 198. 打家劫舍 (Medium)

#### 核心思想
决策类动态规划经典题，体现了**选择决策**的DP思维：每个状态面临多种选择，选择最优方案。

#### 关键逻辑
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

#### 四种实现方式

1) 递归解法 (会超时)
```cpp
int helper(vector<int>& nums, int i) {
    if (i < 0) return 0;
    return max(helper(nums, i-2) + nums[i], helper(nums, i-1));
}
```

2) 记忆化搜索 (自顶向下)
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

3) 动态规划 (自底向上) ⭐
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

4) 空间优化 (滚动变量)
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

#### 与70题的关键区别
- **70题爬楼梯**: 递推关系 `f(n) = f(n-1) + f(n-2)` (加法)
- **198题打家劫舍**: 决策关系 `f(n) = max(选择A, 选择B)` (选择)

#### 决策类DP特征
1. **多种选择**: 每个状态面临2个或更多选择
2. **约束条件**: 选择之间存在限制关系
3. **最优决策**: 使用max/min函数选择最优方案
4. **状态依赖**: 当前选择影响后续可选方案

#### 复杂度分析
- 递归: 时间O(2^n)，空间O(n)
- 记忆化: 时间O(n)，空间O(n)
- DP: 时间O(n)，空间O(n)
- 空间优化: 时间O(n)，空间O(1)

#### 关键理解
- **约束建模**: 相邻房屋不能同时偷 → 状态转移中体现为i-2而不是i-1
- **决策思维**: 每步都要问"我有哪些选择？哪个更优？"
- **记忆化精髓**: 计算 → 缓存 → 返回，三步缺一不可

#### 扩展应用
- 213. 打家劫舍II (环形数组)
- 337. 打家劫舍III (二叉树)
- 01背包问题 (物品选择决策)

---

<a id="dp-53"></a>
### 53. 最大子数组和 (Medium) - 连续子数组DP
**核心算法**: Kadane算法
**转移方程**: `dp[i] = max(nums[i], dp[i-1] + nums[i])`
**关键理解**: "继续vs重新开始"的决策

### 53. 最大子数组和 (Medium)

#### 核心思想
连续子数组DP的经典题目，使用**Kadane算法**实现O(n)最优解，同时掌握**分治算法**的三分覆盖思想。

#### 关键逻辑
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

#### 四种实现方式

1) Kadane算法 (推荐) - O(n)
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

2) 空间优化版本 - O(1)
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

3) 分治算法 - O(n log n)
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

#### 分治算法深度理解
**三分覆盖原理**：任何子数组要么完全在左半部分，要么完全在右半部分，要么跨越中点
- **左半部分最优解**：递归求解`[left, mid]`
- **右半部分最优解**：递归求解`[mid+1, right]`  
- **跨越中点最优解**：从mid向左最大延伸 + 从mid+1向右最大延伸

**关键洞察**：跨越中点的计算实际上覆盖了所有包含mid或mid+1的子数组情况！

#### 连续子数组DP特征
1. **状态定义必须包含"以i结尾"的约束**
2. **状态转移体现"继续vs重新开始"的决策**
3. **全局最优需要在所有局部最优中选择**
4. **与其他DP的区别**：
   - 爬楼梯(70题)：递推关系 `f(n) = f(n-1) + f(n-2)`
   - 打家劫舍(198题)：决策关系 `f(n) = max(选择A, 选择B)`
   - 最大子数组(53题)：连续约束 `f(n) = max(继续, 重新开始)`

#### 复杂度分析
- **Kadane算法**: 时间O(n)，空间O(1) - 最优解
- **分治算法**: 时间O(n log n)，空间O(log n) - 递归栈
- **暴力枚举**: 时间O(n²)，空间O(1) - 超时

#### 易错点
1. **全局最优解**: 需要遍历所有dp[i]取最大值，不是dp[n-1]
2. **边界条件**: 单个元素时的处理
3. **分治边界**: 循环条件应该用`>=`和`<=`包含边界

#### 扩展应用
- 152. 乘积最大子数组 (处理负数乘积)
- 718. 最长重复子数组 (长度最大值)
- 209. 长度最小的子数组 (滑动窗口变种)

#### 关键理解
连续子数组DP的精髓在于**在保持连续性约束下做最优决策**：每步都要问"我是继续之前的累积，还是从当前位置重新开始？"

---

<a id="dp-322"></a>
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

### 322. 零钱兑换 (Medium)

#### 核心思想
完全背包动态规划的经典题目，每个硬币可以使用无限次，求组成目标金额所需的最少硬币数。

#### 关键逻辑
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

#### 完全背包vs01背包
- **01背包**: 每个物品最多选择一次
- **完全背包**: 每个物品可以选择无限次
- **关键区别**: 完全背包在内层循环中可以使用已更新的dp值

#### 四种实现方式

1) 递归解法 (会超时)
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

2) 记忆化搜索 (自顶向下)
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

3) 动态规划 (自底向上) ⭐ 推荐
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

#### 关键理解点

##### 为什么初始化为amount + 1？
- **理论上界**: 组成任意金额最多需要amount个面额为1的硬币
- **避免溢出**: 比使用INT_MAX更安全
- **便于判断**: dp[amount] > amount 说明无解

##### 循环顺序为什么正确？
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

#### 易错点记录

1) 循环边界错误 ❌
```cpp
for(int i = 1; i < amount; i++) {  // 错误：应该是 i <= amount
```
**后果**: 无法计算dp[amount]，导致返回错误结果

2) 编译错误
使用C++11特性（range-based for循环、initializer list）需要编译器支持：
```bash
g++ -std=c++11 -o problem_322 problem_322_template.cpp
```

#### 复杂度分析
- **递归**: 时间O(S^n)，空间O(S) - S是金额，n是硬币种类数
- **记忆化**: 时间O(S × n)，空间O(S)
- **动态规划**: 时间O(S × n)，空间O(S) ⭐ 最优解
- **BFS**: 时间O(S × n)，空间O(S)

#### 扩展应用
- 518. 零钱兑换II (组合数问题)
- 279. 完全平方数 (最少平方数)
- 377. 组合总和Ⅳ (排列数问题)

#### 测试结果
所有测试用例通过：
- coins=[1,2,5], amount=11 → 3 (5+5+1)
- coins=[2], amount=3 → -1 (无解)
- coins=[1], amount=0 → 0 (边界情况)
- coins=[1,3,4], amount=6 → 2 (3+3)
- coins=[3,5], amount=1 → -1 (无解)

#### 关键洞察
完全背包DP的精髓在于**建模无限选择的最优化问题**：将"每个物品可以选择无限次"转化为"在状态转移中允许重复使用已计算的结果"。

---

<a id="dp-300"></a>
### 300. 最长递增子序列 (Medium) - 序列DP
**状态定义**: `dp[i]` = 以nums[i]结尾的LIS长度
**优化**: 贪心+二分查找达到O(n log n)
**易错**: 返回`max(dp)`而非`dp[n-1]`

#### 核心思想
序列动态规划的经典题目，掌握以"位置结尾"的状态定义思维，同时学习贪心+二分查找的O(n log n)优化。

#### 关键逻辑
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

#### 三种实现方式

1) 动态规划 O(n²) - 经典解法 ⭐
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

2) 记忆化搜索 O(n²) - 自顶向下
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

3) 贪心+二分查找 O(n log n) - 最优解 ⭐⭐
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

#### 贪心+二分查找深度理解

##### 核心思想
- **tails[i]** = 长度为i+1的递增子序列的最小尾元素
- **为什么要最小？** 尾元素越小，后续添加新元素的机会越大

##### 算法步骤
1. 对每个新元素num：
   - 如果num > tails中所有元素 → 直接添加到末尾（延长序列）
   - 否则 → 二分查找第一个≥num的位置并替换（保持最小尾元素）

##### 关键洞察
- **tails数组始终保持严格递增**
- **tails长度 = 最长递增子序列长度**
- **tails内容不一定是真实的LIS，但长度保证正确**

#### 易错点记录

1) DP状态转移错误 ❌
```cpp
dp[i] = max(dp[j] + 1);  // 错误：缺少dp[i]参数
```
正确：
```cpp
dp[i] = max(dp[i], dp[j] + 1);  // 需要比较当前值和新值
```

2) 二分查找语法错误 ❌
```cpp
int left = 0; right = tails.size() - 1;  // 错误：缺少类型声明
```
正确：
```cpp
int left = 0, right = tails.size() - 1;  // 逗号分隔，统一声明
```

3) 二分查找mid计算位置错误 ❌
```cpp
int mid = (left + right) / 2;  // 放在while外面
while(left <= right) {
    // 使用过时的mid值
}
```
正确：
```cpp
while(left <= right) {
    int mid = left + (right - left) / 2;  // 每次循环重新计算
}
```

4) 记忆化搜索语法错误 ❌
```cpp
if memo[i] != -1 return memo[i];  // 缺少括号
for(int j=0; j<i; i++) {          // 循环变量错误
```
正确：
```cpp
if (memo[i] != -1) return memo[i];  // 加括号
for(int j=0; j<i; j++) {            // j++而不是i++
```

5) 初始化的重要性
```cpp
int pos = tails.size();  // 🔑 关键：初始化为"未找到"标志
```
这个初始化确保了当没找到≥num的元素时，pos保持为tails.size()，从而正确执行push_back操作。

#### 序列DP特征总结
1. **状态定义必须包含"以第i个元素结尾"**
2. **需要检查前面所有可能的转移状态**
3. **最终答案需要遍历所有状态取最优值**
4. **与其他DP类型的区别**：
   - 爬楼梯：递推关系
   - 打家劫舍：决策关系  
   - 最大子数组：连续约束
   - 零钱兑换：完全背包
   - **最长递增子序列：序列关系**

#### 复杂度分析
- **DP解法**: 时间O(n²)，空间O(n)
- **记忆化**: 时间O(n²)，空间O(n) + 递归栈
- **贪心+二分**: 时间O(n log n)，空间O(n) ⭐ 最优解

#### 扩展应用
- 354. 俄罗斯套娃信封问题 (二维LIS)
- 673. 最长递增子序列的个数 (计数问题)
- 1143. 最长公共子序列 (双序列DP)
- 368. 最大整除子集 (特殊约束的LIS)

#### 测试结果
所有三种实现均通过全部测试用例：
- [10,9,2,5,3,7,101,18] → 4
- [0,1,0,3,2,3] → 4  
- [7,7,7,7,7,7,7] → 1
- [1,3,6,7,9,4,10,5,6] → 6
- [10] → 1

#### 关键洞察
序列DP的精髓在于**正确建模"以某位置结尾"的状态**，通过检查所有前驱状态来构建最优解。贪心+二分的优化体现了**维护关键信息而非完整状态**的算法设计思想。

---

<a id="dp-1143"></a>
### 1143. 最长公共子序列 (Medium) - 双序列DP
**状态定义**: `dp[i][j]` = 两序列前缀LCS长度
**转移**: 匹配时`dp[i-1][j-1]+1`，不匹配时取最优
**优化**: 滚动数组降低空间复杂度

#### 核心思想
双序列动态规划的经典题目，用二维DP表表示两个序列的匹配关系，掌握字符匹配/不匹配的状态转移。

#### 关键逻辑
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

#### 三种实现方式

1) 二维动态规划 O(mn) - 经典解法 ⭐
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

2) 记忆化搜索 O(mn) - 自顶向下
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

3) 空间优化 O(min(m,n)) - 滚动数组 ⭐⭐
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

#### 滚动数组深度理解

##### 核心思想
- **观察依赖关系**：`dp[i][j]` 只依赖于 `dp[i-1][j-1]`、`dp[i-1][j]`、`dp[i][j-1]`
- **空间优化策略**：只保存上一行和当前行，不需要整个二维表
- **滚动机制**：计算完当前行后，通过swap让当前行变成下一轮的"上一行"

##### 数组对应关系
| 二维DP | 滚动数组 | 说明 |
|--------|----------|------|
| `dp[i-1][j-1]` | `pre[j]` | 左上角：上一行的j位置 |
| `dp[i-1][j]` | `pre[j+1]` | 上边：上一行的j+1位置 |
| `dp[i][j-1]` | `curr[j]` | 左边：当前行的j位置 |
| `dp[i][j]` | `curr[j+1]` | 当前位置：当前行的j+1位置 |

##### 为什么返回pre[n]？
```cpp
// 最后一轮循环结束时
curr = [最后一行的计算结果]
swap(pre, curr);  // 交换后
pre = [最后一行的结果] ← 最终答案在这里
```

#### 双序列DP特征总结
1. **二维状态空间**：需要考虑两个序列的匹配关系
2. **匹配决策**：字符匹配时延续子问题，不匹配时选择最优方案
3. **边界处理**：空序列作为边界条件，通常结果为0
4. **空间优化**：可以用滚动数组优化，但不能构造具体序列
5. **时间复杂度**：通常为O(mn)，难以进一步优化

#### 与LIS对比分析
| 特征 | LIS (300题) | LCS (1143题) |
|------|-------------|--------------|
| 序列数量 | 单序列 | 双序列 |
| 状态定义 | `dp[i]` = 以i结尾的最长递增子序列 | `dp[i][j]` = 两序列前缀的LCS |
| 状态转移 | 检查所有前驱，选择最优 | 考虑匹配/不匹配，选择最优 |
| 复杂度 | O(n²) → O(n log n) | O(mn) → O(min(m,n)) |
| 优化方式 | 贪心+二分查找 | 滚动数组 |

#### 易错点记录

1) 记忆化搜索字符比较错误 ❌
```cpp
if(text1[i] == text2[j]) {  // 错误：参数i,j表示长度
```
正确：
```cpp
if(text1[i-1] == text2[j-1]) {  // 字符下标要减1
```

2) 滚动数组状态转移错误 ❌
```cpp
curr[j+1] = curr[j] + 1;  // 错误：应该是左上角+1
```
正确：
```cpp
curr[j+1] = pre[j] + 1;  // 左上角+1
```

#### 复杂度分析
- **二维DP**: 时间O(mn)，空间O(mn)
- **记忆化**: 时间O(mn)，空间O(mn) + 递归栈
- **滚动数组**: 时间O(mn)，空间O(min(m,n)) ⭐ 最优空间

#### 扩展应用
- 72. 编辑距离 (插入、删除、替换操作)
- 97. 交错字符串 (路径匹配问题)
- 115. 不同的子序列 (计数DP)
- 516. 最长回文子序列 (LCS变种)

#### 测试结果
所有实现均通过全部测试用例：
- "abcde" vs "ace" → 3 (LCS: "ace")
- "abc" vs "abc" → 3 (完全相同)
- "abc" vs "def" → 0 (无公共字符)
- "abcdgh" vs "aedfhr" → 3 (LCS: "adh")
- "a" vs "a" → 1 (单字符匹配)

#### 关键洞察
双序列DP的精髓在于**建模两个序列的匹配关系**，通过二维状态空间考虑所有可能的匹配组合。滚动数组优化体现了**最小化状态存储**的空间优化思想。

---

<a id="dp-516"></a>
### 516. 最长回文子序列 (Medium) - 区间DP
**状态定义**: `dp[i][j]` = s[i..j]的回文子序列长度
**关键**: 按区间长度递增遍历
**转移**: 两端匹配+2，不匹配选择最优子区间

#### 核心思想
区间动态规划的经典题目，掌握"滑动窗口式"的区间遍历思维，理解大区间依赖小区间的状态转移。

#### 关键逻辑
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

#### 核心洞察

##### 区间DP的"滑动窗口"思维
- **外层循环**: 固定窗口大小(len = 2, 3, 4, ...)
- **内层循环**: 将固定大小的窗口在字符串上滑动
- **依赖关系**: 大窗口的计算依赖小窗口的结果

##### 与LCS的巧妙联系
- **转化思想**: s的最长回文子序列 = s与reverse(s)的最长公共子序列
- **原理**: 回文序列在原串和反转串中都存在
- **优势**: 可以直接复用LCS代码

#### 三种实现方式

1) 区间DP - O(n²) ⭐ 推荐
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

2) 记忆化搜索 - O(n²)
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

3) LCS转化 - O(n²)
```cpp
int longestPalindromeSubseqLCS(string s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    return longestCommonSubsequence(s, rev_s);
}
```

#### 复杂度分析
- **时间复杂度**: O(n²) - 双重循环填充DP表
- **空间复杂度**: O(n²) - 二维DP表
- **优化可能**: 滚动数组优化空间，但实现复杂

#### 易错点
1. **遍历顺序错误**: 必须按区间长度递增，不能按坐标遍历
2. **边界条件**: `len <= n` 不是 `len < n`
3. **循环边界**: `i <= n - len` 保证j不越界
4. **公式错误**: `j = i + len - 1` 不是其他公式

#### 与其他DP类型对比
| DP类型 | 状态定义 | 遍历顺序 | 转移特点 |
|--------|----------|----------|----------|
| 序列DP | 以位置结尾 | 从前往后 | 检查所有前驱 |
| 双序列DP | 两序列前缀 | 双重递增 | 匹配/不匹配 |
| **区间DP** | 区间范围 | 按长度递增 | 端点处理 |

#### 扩展应用
- 5. 最长回文子串 (连续性约束)
- 312. 戳气球 (乘积最大化)
- 1039. 多边形三角剖分的最低得分
- 87. 扰乱字符串

#### 测试结果
所有测试用例通过：
- "bbbab" → 4 (LPS: "bbbb")
- "cbbd" → 2 (LPS: "bb")
- "a" → 1 (单字符)
- "abcba" → 5 (整个串就是回文)
- "aabaa" → 5 (整个串就是回文)

#### 关键洞察
区间DP的精髓在于**按区间长度递增的遍历策略**，确保计算大区间时所需的小区间已经计算完毕。"滑动窗口"的思维模式帮助理解这种遍历顺序的必要性。
