# 数组与双指针算法专题

## 📚 专题概览

**核心思想**: 用两个指针在数组中移动，通过指针的协同工作解决复杂的数组问题。

**适用场景**:
- 有序数组的搜索问题
- 数组的原地修改
- 子数组/子序列问题
- 去重和合并操作
- 连续序列问题

**时间复杂度**: 通常能将O(n²)优化到O(n)
**空间复杂度**: O(1)，原地操作

## 🎯 本专题题目
- [11. 盛最多水的容器](#problem-11) - 对撞指针经典
- [15. 三数之和](#problem-15) - 多指针协作
- [283. 移动零](#problem-283) - 快慢指针原地修改
- [128. 最长连续序列](#problem-128) - 哈希表+序列识别

---

## 🎯 核心算法模式

### 1. 对撞型双指针

**适用**: 有序数组的目标查找、三数之和等

```cpp
// 标准模板
int left = 0, right = nums.size() - 1;
while (left < right) {
    int sum = nums[left] + nums[right];
    if (sum == target) {
        // 找到目标，处理结果
        // ⚠️ 关键：处理后必须移动指针
        left++;
        right--;
    } else if (sum < target) {
        left++;   // 需要增大sum
    } else {
        right--;  // 需要减小sum
    }
}
```

**核心原则**:
1. **收敛性**: 每次循环必须缩小搜索空间
2. **完备性**: 每个分支都必须有指针移动
3. **终止性**: 确保循环能够终止

### 2. 快慢指针

**适用**: 数组的原地修改、去重等

```cpp
// 标准模板
int slow = 0;
for (int fast = 0; fast < nums.size(); fast++) {
    if (/* 满足条件 */) {
        nums[slow] = nums[fast];
        slow++;
    }
}
return slow; // 返回新数组长度
```

### 3. 固定窗口双指针

**适用**: 滑动窗口问题

```cpp
// 标准模板
int left = 0;
for (int right = 0; right < nums.size(); right++) {
    // 扩大窗口
    addToWindow(nums[right]);
    
    // 收缩窗口（如果需要）
    while (windowInvalid()) {
        removeFromWindow(nums[left]);
        left++;
    }
    
    // 更新结果
    updateResult();
}
```

---

## 📋 重点题目解析

### 🏆 [15] 三数之和 - 双指针经典应用

**核心思路**: 排序 + 固定一个数 + 双指针查找另外两个数

**关键技术点**:
1. **排序的作用**: 使双指针移动有方向性
2. **三层去重**: 避免重复的三元组
3. **指针移动**: 确保循环收敛

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // 第一层去重：跳过重复的i
        if (i > 0 && nums[i] == nums[i-1]) continue;
        
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                // 第二层去重：跳过重复的left
                while (left < right && nums[left] == nums[left+1]) left++;
                // 第三层去重：跳过重复的right  
                while (left < right && nums[right] == nums[right-1]) right--;
                
                // ⚠️ 关键：去重后必须移动指针
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}
```

**常见错误** ⚠️:
```cpp
// ❌ 错误：忘记移动指针导致死循环
if (sum == 0) {
    result.push_back({nums[i], nums[left], nums[right]});
    while (left < right && nums[left] == nums[left+1]) left++;
    while (left < right && nums[right] == nums[right-1]) right--;
    // 缺少 left++; right--; 导致无限循环
}
```

### 🏆 [11] 盛最多水的容器 - 双指针贪心

**核心思路**: 双指针从两端向中间收缩，总是移动较矮的指针

```cpp
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxArea = 0;
    
    while (left < right) {
        int currentArea = min(height[left], height[right]) * (right - left);
        maxArea = max(maxArea, currentArea);
        
        // 贪心策略：移动较矮的指针
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}
```

**贪心正确性**: 移动较高的指针不可能得到更优解，因为面积受限于较矮的高度且宽度变小。

---

<a id="problem-283"></a>
### 🏆 [283] 移动零 - 快慢指针原地修改

**核心思路**: 快慢指针分离非零元素和零元素，保持相对顺序

```cpp
void moveZeroes(vector<int>& nums) {
    int slow = 0;  // 指向下一个非零元素应该放置的位置
    
    // 第一遍：移动所有非零元素到前面
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    // 第二遍：将剩余位置填零
    for (; slow < nums.size(); slow++) {
        nums[slow] = 0;
    }
}
```

**算法精髓**:
1. **分离思想**: 将数组分为非零区域和零区域
2. **相对顺序**: slow指针确保非零元素的原始顺序
3. **原地修改**: O(1)空间复杂度，符合题目要求

---

<a id="problem-128"></a>
### 🏆 [128] 最长连续序列 - 哈希表优化

**核心思路**: 哈希表实现O(1)查找，起点优化避免重复计算

```cpp
int longestConsecutive(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLen = 1;
    
    for (int num : numSet) {
        // 关键优化：只从连续序列起点开始计算
        if (numSet.find(num - 1) == numSet.end()) {
            int currentNum = num;
            int currentLen = 1;
            
            // 向右扩展连续序列
            while (numSet.find(currentNum + 1) != numSet.end()) {
                currentNum++;
                currentLen++;
            }
            
            maxLen = max(maxLen, currentLen);
        }
    }
    return maxLen;
}
```

**算法精髓**:
1. **起点识别**: 只有`num-1`不存在时，`num`才是起点
2. **时间复杂度**: 虽有嵌套循环，但每个数字最多访问2次，总体O(n)
3. **空间换时间**: 哈希表实现O(1)查找，满足题目O(n)要求

---

## 🚨 关键错误分析与预防

### 死循环问题

**错误类型**: 双指针循环控制错误
**典型场景**: 找到目标后忘记移动指针

**根本原因**:
1. 对双指针收敛原理理解不深
2. 混淆去重操作和指针移动的作用
3. 忽视循环不变量的维护

**预防策略**:
1. **代码模板化**: 建立标准的双指针模板
2. **分支检查**: 确保每个条件分支都有指针移动
3. **简单测试**: 用简单用例快速验证循环能否终止

### 去重策略

**三层去重模式** (以三数之和为例):
```cpp
// 第一层：固定数去重
if (i > 0 && nums[i] == nums[i-1]) continue;

// 第二层：左指针去重
while (left < right && nums[left] == nums[left+1]) left++;

// 第三层：右指针去重
while (left < right && nums[right] == nums[right-1]) right--;
```

**去重原则**:
- 只在首次遇到重复元素时处理
- 去重后仍需要正常的指针移动
- 边界检查防止数组越界

---

## 🎨 算法设计模式

### 1. 收缩搜索空间模式

**核心思想**: 每次操作都要缩小问题规模
**适用题目**: 两数之和、三数之和、最接近的三数之和

**设计要点**:
- 建立搜索空间的数学表示
- 设计收缩策略（通常基于贪心思想）
- 确保每次收缩都朝着最优解方向

### 2. 原地修改模式

**核心思想**: 用双指针实现数组的原地重排
**适用题目**: 移动零、删除重复元素、颜色分类

**设计要点**:
- 快指针遍历，慢指针维护结果
- 明确每个指针的语义和职责
- 处理边界情况（空数组、全满足条件等）

### 3. 滑动窗口模式

**核心思想**: 维护一个动态窗口，根据条件扩大或收缩
**适用题目**: 最长子串、最小覆盖子串

**设计要点**:
- 定义窗口的有效性条件
- 设计窗口的扩大和收缩策略
- 在合适的时机更新全局最优解

---

## 📊 复杂度分析技巧

### 时间复杂度分析

**对撞型双指针**: O(n)
- 两个指针最多各移动n次
- 每次移动的操作是O(1)

**快慢指针**: O(n)  
- 快指针遍历一次数组
- 慢指针最多移动n次

**注意**: 双指针前的排序操作通常是O(n log n)，需要计入总复杂度

### 空间复杂度优化

**原地操作的优势**:
- 双指针通常能实现O(1)额外空间
- 相比哈希表等数据结构有空间优势
- 适合对内存要求严格的场景

---

## 🔄 算法变形与扩展

### 多指针技术

**四数之和**: 固定两个数 + 双指针
**K数之和**: 递归固定 + 双指针作为终止情况

### 双指针 + 其他技术

**双指针 + 哈希表**: 两数之和的多种解法对比
**双指针 + 滑动窗口**: 复杂的子数组问题
**双指针 + 分治**: 归并排序中的合并操作

---

## 🎯 面试要点总结

### 必须掌握的技能

1. **基础模板**: 三种双指针模式的标准代码
2. **去重策略**: 多层去重的正确实现
3. **边界处理**: 空数组、单元素、全相同等情况
4. **复杂度分析**: 准确分析时间和空间复杂度

### 常见面试问题

1. **为什么双指针能优化时间复杂度？**
   - 避免了嵌套循环的重复计算
   - 利用了数组的有序性或单调性

2. **什么时候使用双指针？**
   - 有序数组的搜索问题
   - 需要原地修改的数组问题
   - 寻找数组中满足特定关系的元素对

3. **双指针与哈希表的选择？**
   - 双指针：空间O(1)，适用于有序数组
   - 哈希表：时间O(1)查找，适用于无序数组

### 扩展思考方向

- 如何将双指针扩展到二维数组？
- 双指针在字符串问题中的应用？
- 双指针与动态规划的结合使用？

---

*最后更新：2025-09-03*
*重点关注：双指针循环控制的正确性*