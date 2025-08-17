# 二分搜索专题

## 专题概述

二分搜索是基于分治思想的高效查找算法，时间复杂度O(log n)。本专题涵盖：
- **基础二分**: 在有序数组中查找目标值
- **边界搜索**: 查找第一个/最后一个满足条件的位置
- **二分答案**: 在答案空间中二分搜索最优解
- **旋转数组**: 在部分有序数组中搜索

**核心思想**: 通过比较中点值与目标值，每次排除一半搜索空间，直到找到答案或确认不存在。

## 二分搜索模板

### 基础模板
```cpp
// 标准二分查找
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
```

### 左边界模板
```cpp
// 查找第一个大于等于target的位置
int leftBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}
```

### 右边界模板
```cpp
// 查找最后一个小于等于target的位置
int rightBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left - 1;
}
```

## 核心题目

### 704. 二分查找 (Easy) - 基础模板
**核心思想**: 在有序数组中查找目标值
**关键点**: 边界条件、中点计算、搜索空间更新

### 34. 在排序数组中查找元素的第一个和最后一个位置 (Medium)
**核心思想**: 使用左右边界模板分别查找起始和结束位置
**关键技巧**: 两次二分，分别找左边界和右边界

### 33. 搜索旋转排序数组 (Medium)
**核心思想**: 在旋转有序数组中查找目标值
**关键判断**: 确定哪一半是有序的，再判断目标值是否在有序部分

```cpp
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) return mid;
        
        // 判断哪一半是有序的
        if (nums[left] <= nums[mid]) {  // 左半部分有序
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {  // 右半部分有序
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}
```

### 153. 寻找旋转排序数组中的最小值 (Medium)
**核心思想**: 在旋转数组中找到最小值（旋转点）
**关键比较**: 中点与右端点比较，确定最小值在哪一半

```cpp
int findMin(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;  // 最小值在右半部分
        } else {
            right = mid;     // 最小值在左半部分（包括mid）
        }
    }
    return nums[left];
}
```

### 875. 爱吃香蕉的珂珂 (Medium) - 二分答案
**核心思想**: 在答案空间中二分搜索最优解
**关键转换**: 将"最小速度"问题转换为"给定速度能否在时间内吃完"的判定问题

```cpp
bool canFinish(vector<int>& piles, int speed, int H) {
    int hours = 0;
    for (int pile : piles) {
        hours += (pile + speed - 1) / speed;  // 向上取整
    }
    return hours <= H;
}

int minEatingSpeed(vector<int>& piles, int H) {
    int left = 1, right = *max_element(piles.begin(), piles.end());
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canFinish(piles, mid, H)) {
            right = mid;      // 可以完成，尝试更小的速度
        } else {
            left = mid + 1;   // 不能完成，需要更大的速度
        }
    }
    return left;
}
```

## 二分答案模式

二分答案适用于"最大值最小化"或"最小值最大化"问题：

### 通用模板
```cpp
bool check(int candidate) {
    // 检查candidate是否满足条件
}

int binarySearchAnswer(int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (check(mid)) {
            right = mid;      // 满足条件，尝试更小值
        } else {
            left = mid + 1;   // 不满足，需要更大值
        }
    }
    return left;
}
```

## 细节注意事项

### 1. 中点计算
```cpp
// 避免溢出
int mid = left + (right - left) / 2;
// 而不是 (left + right) / 2
```

### 2. 边界条件
```cpp
// 闭区间 [left, right]
while (left <= right)

// 左闭右开 [left, right)
while (left < right)
```

### 3. 搜索空间更新
```cpp
// 找到目标继续搜索（查找边界）
if (nums[mid] == target) {
    right = mid;     // 或 left = mid + 1
}

// 找到目标直接返回（查找存在性）
if (nums[mid] == target) {
    return mid;
}
```

### 4. 向上取整技巧
```cpp
// 向上取整：(a + b - 1) / b
int ceiling = (pile + speed - 1) / speed;
```

## 易错点总结

1. **死循环**: 边界更新错误导致死循环
2. **溢出**: 中点计算时可能整数溢出
3. **边界条件**: `<=` vs `<`，`[left, right]` vs `[left, right)`
4. **旋转数组**: 判断有序部分的边界条件
5. **二分答案**: check函数的逻辑正确性
6. **精度问题**: 浮点数二分的精度控制

## 复杂度分析

- **时间复杂度**: O(log n) - 每次排除一半搜索空间
- **空间复杂度**: O(1) - 只使用常数额外空间
- **二分答案**: O(log(max-min) × check函数复杂度)

## 相关题目分类

- **基础二分**: 704二分查找、35搜索插入位置
- **边界搜索**: 34查找首末位置、278第一个错误版本
- **旋转数组**: 33搜索旋转数组、153寻找最小值、81搜索旋转数组II
- **二分答案**: 875爱吃香蕉的珂珂、1011在D天内送达包裹的能力
- **矩阵搜索**: 74搜索二维矩阵、240搜索二维矩阵II
- **平方根**: 69x的平方根、367有效的完全平方数

---
*二分搜索的关键在于正确维护搜索空间的不变性，确保答案始终在搜索范围内*