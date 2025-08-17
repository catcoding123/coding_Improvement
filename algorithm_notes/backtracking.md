# 回溯算法专题

## 专题概述

回溯算法是一种通过系统性试错来寻找解的算法，本质是深度优先搜索的应用。本专题涵盖：
- **子集生成**: 所有可能的子集、组合
- **排列生成**: 全排列、带重复的排列
- **路径搜索**: N皇后、解数独、单词搜索
- **组合优化**: 组合总和、分割回文串

**核心思想**: 构建决策树，通过"做选择→递归→撤销选择"的三步模式，系统性地搜索解空间。

## 回溯算法三要素

1. **路径(Path)**: 已经做出的选择序列
2. **选择列表(Choices)**: 当前状态下可以做的选择
3. **结束条件(End)**: 到达决策树底层，无法再做选择

## 回溯算法框架

```cpp
void backtrack(路径, 选择列表) {
    if (满足结束条件) {
        result.add(路径);
        return;
    }
    
    for (选择 : 选择列表) {
        做选择;                // 将选择加入路径
        backtrack(路径, 选择列表); // 递归
        撤销选择;              // 将选择从路径中移除
    }
}
```

## 核心题目

### 78. 子集 (Medium) - 回溯算法入门经典 ⭐⭐⭐
**核心思想**: 回溯算法的经典入门题，建立"选择/不选择"的决策树思维
**算法本质**: 穷举所有可能的组合，对每个元素做二选一决策

**决策树结构**:
```
                    []
                 /      \
            选择1         不选1
           [1]              []
         /    \           /    \
     选择2    不选2    选择2    不选2
    [1,2]    [1]      [2]      []
```

**实现要点**:
```cpp
void backtrack(vector<int>& nums, int start, vector<int>& path) {
    result.push_back(path);  // 每个节点都是一个解
    
    for (int i = start; i < nums.size(); i++) {
        path.push_back(nums[i]);      // 做选择
        backtrack(nums, i + 1, path); // 递归
        path.pop_back();              // 撤销选择
    }
}
```

### 46. 全排列 (Medium) - 排列生成基础
**核心思想**: 生成所有可能的排列，每个位置都有n种选择
**关键技巧**: 使用visited数组记录已使用的元素

```cpp
void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& visited) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        if (visited[i]) continue;       // 跳过已使用元素
        
        path.push_back(nums[i]);        // 做选择
        visited[i] = true;
        backtrack(nums, path, visited); // 递归
        visited[i] = false;             // 撤销选择
        path.pop_back();
    }
}
```

### 47. 全排列 II (Medium) - 去重策略
**核心思想**: 处理重复元素的排列，需要去重策略
**关键技巧**: 排序+剪枝，跳过重复的相邻元素

```cpp
void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& visited) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        if (visited[i]) continue;
        
        // 去重关键：跳过重复元素
        if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) {
            continue;
        }
        
        path.push_back(nums[i]);
        visited[i] = true;
        backtrack(nums, path, visited);
        visited[i] = false;
        path.pop_back();
    }
}
```

### 90. 子集 II (Medium) - 子集去重
**核心思想**: 生成无重复的子集，处理数组中的重复元素
**去重策略**: 排序后跳过重复的相邻元素

```cpp
void backtrack(vector<int>& nums, int start, vector<int>& path) {
    result.push_back(path);
    
    for (int i = start; i < nums.size(); i++) {
        // 去重：跳过同一层的重复元素
        if (i > start && nums[i] == nums[i-1]) {
            continue;
        }
        
        path.push_back(nums[i]);
        backtrack(nums, i + 1, path);
        path.pop_back();
    }
}
```

### 39. 组合总和 (Medium) - 完全背包变种
**核心思想**: 找到所有和为target的组合，数字可重复使用
**关键点**: 递归时start不变，允许重复选择当前元素

```cpp
void backtrack(vector<int>& candidates, int target, int start, vector<int>& path) {
    if (target == 0) {
        result.push_back(path);
        return;
    }
    
    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] > target) break; // 剪枝
        
        path.push_back(candidates[i]);
        // 关键：i不变，允许重复使用
        backtrack(candidates, target - candidates[i], i, path);
        path.pop_back();
    }
}
```

### 40. 组合总和 II (Medium) - 01背包变种
**核心思想**: 每个数字只能使用一次，需要去重
**关键点**: 递归时start=i+1，跳过重复元素

```cpp
void backtrack(vector<int>& candidates, int target, int start, vector<int>& path) {
    if (target == 0) {
        result.push_back(path);
        return;
    }
    
    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] > target) break;
        
        // 去重：跳过同一层的重复元素
        if (i > start && candidates[i] == candidates[i-1]) {
            continue;
        }
        
        path.push_back(candidates[i]);
        // 关键：i+1，每个数字只用一次
        backtrack(candidates, target - candidates[i], i + 1, path);
        path.pop_back();
    }
}
```

## 剪枝策略

### 1. 边界剪枝
```cpp
if (target < 0) return;           // 超出目标
if (path.size() > limit) return;  // 超出长度限制
```

### 2. 重复剪枝
```cpp
// 跳过重复元素（需要先排序）
if (i > start && nums[i] == nums[i-1]) continue;
```

### 3. 单调性剪枝
```cpp
// 如果数组有序，可以提前终止
if (candidates[i] > target) break;
```

### 4. 可行性剪枝
```cpp
// 剩余元素不足以构成解
if (nums.size() - i < k - path.size()) break;
```

## 状态管理技巧

### 1. 引用传递 vs 值传递
```cpp
// 引用传递：需要撤销操作
void backtrack(vector<int>& path) {
    path.push_back(x);      // 做选择
    backtrack(path);        // 递归
    path.pop_back();        // 撤销选择
}

// 值传递：自动撤销
void backtrack(vector<int> path) {
    path.push_back(x);      // 自动拷贝
    backtrack(path);        // 递归后自动恢复
}
```

### 2. 全局状态 vs 局部状态
```cpp
// 全局状态：使用成员变量
class Solution {
    vector<vector<int>> result;
    vector<int> path;
public:
    void backtrack() {
        result.push_back(path);  // 直接使用全局状态
    }
};
```

## 易错点总结

1. **结果收集时机**: 有些题目在叶子节点收集，有些在每个节点收集
2. **去重逻辑**: `i > start` vs `i > 0`，区分同一层和不同层
3. **递归参数**: `i` vs `i+1`，决定是否可重复使用
4. **撤销操作**: 引用传递时必须撤销，值传递时自动撤销
5. **剪枝条件**: 提前终止可以大幅提升效率
6. **排序预处理**: 去重和剪枝通常需要先排序

## 时间复杂度分析

- **子集问题**: O(2^n) - 每个元素有选/不选两种状态
- **排列问题**: O(n!) - n个位置的排列数
- **组合问题**: O(C(n,k)) - 从n个元素中选k个的组合数
- **一般情况**: O(答案个数 × 构造每个答案的时间)

## 相关题目分类

- **子集生成**: 78子集、90子集II
- **排列生成**: 46全排列、47全排列II、31下一个排列
- **组合问题**: 77组合、39组合总和、40组合总和II、216组合总和III
- **分割问题**: 93复原IP地址、131分割回文串
- **路径搜索**: 79单词搜索、212单词搜索II
- **数独问题**: 36有效数独、37解数独
- **N皇后**: 51N皇后、52N皇后II

---
*回溯算法的核心是系统性试错，通过决策树的深度优先搜索找到所有可能解*