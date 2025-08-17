# 数组专题

## 专题概述

数组是最基础的数据结构，许多高级算法都建立在数组操作之上。本专题涵盖：
- **双指针技巧**: 快慢指针、前后指针、相向指针
- **滑动窗口**: 固定窗口、可变窗口、最大最小窗口
- **前缀和**: 一维前缀和、二维前缀和、差分数组
- **数组重排**: 原地算法、环形替换、标记技巧

**核心思想**: 利用数组的随机访问特性，通过指针技巧和数学方法高效解决问题。

## 双指针技巧

### 相向双指针
适用于有序数组的查找问题：

```cpp
// 两数之和（有序数组）
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {};
}
```

### 快慢双指针
适用于链表环检测、数组去重等：

```cpp
// 删除有序数组中的重复项
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0;
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            nums[++slow] = nums[fast];
        }
    }
    return slow + 1;
}
```

## 滑动窗口

### 固定窗口
```cpp
// 大小为k的子数组平均数
vector<double> findAverages(vector<int>& nums, int k) {
    vector<double> result;
    int sum = 0;
    
    // 初始化窗口
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    result.push_back(sum / (double)k);
    
    // 滑动窗口
    for (int i = k; i < nums.size(); i++) {
        sum = sum - nums[i-k] + nums[i];
        result.push_back(sum / (double)k);
    }
    return result;
}
```

### 可变窗口
```cpp
// 最小覆盖子串长度
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0, minLen = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum >= target) {
            minLen = min(minLen, right - left + 1);
            sum -= nums[left++];
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}
```

## 前缀和技巧

### 一维前缀和
```cpp
class PrefixSum {
private:
    vector<int> prefix;
    
public:
    PrefixSum(vector<int>& nums) {
        prefix.resize(nums.size() + 1);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};
```

### 二维前缀和
```cpp
class NumMatrix {
private:
    vector<vector<int>> prefix;
    
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        prefix.assign(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] + 
                              prefix[i-1][j] + 
                              prefix[i][j-1] - 
                              prefix[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - 
               prefix[r1][c2+1] - 
               prefix[r2+1][c1] + 
               prefix[r1][c1];
    }
};
```

## 核心题目

### 283. 移动零 (Easy) - 双指针基础
**核心思想**: 快慢指针，慢指针维护非零元素边界
```cpp
void moveZeroes(vector<int>& nums) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            swap(nums[slow++], nums[fast]);
        }
    }
}
```

### 11. 盛最多水的容器 (Medium) - 相向双指针
**核心思想**: 相向双指针，每次移动较短的边
```cpp
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int area = min(height[left], height[right]) * (right - left);
        maxWater = max(maxWater, area);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxWater;
}
```

### 560. 和为K的子数组 (Medium) - 前缀和+哈希表
**核心思想**: 前缀和差值等于目标值
```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // 前缀和为0的情况
    
    int prefixSum = 0, count = 0;
    for (int num : nums) {
        prefixSum += num;
        if (prefixCount.count(prefixSum - k)) {
            count += prefixCount[prefixSum - k];
        }
        prefixCount[prefixSum]++;
    }
    return count;
}
```

### 41. 缺失的第一个正数 (Hard) - 原地哈希
**核心思想**: 利用数组索引作为哈希表，原地标记
```cpp
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    
    // 将nums[i]放到索引nums[i]-1的位置
    for (int i = 0; i < n; i++) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    
    // 找第一个不匹配的位置
    for (int i = 0; i < n; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return n + 1;
}
```

### 56. 合并区间 (Medium) - 排序+贪心
**核心思想**: 排序后贪心合并重叠区间
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> result;
    for (auto& interval : intervals) {
        if (result.empty() || result.back()[1] < interval[0]) {
            result.push_back(interval);
        } else {
            result.back()[1] = max(result.back()[1], interval[1]);
        }
    }
    return result;
}
```

## 原地算法技巧

### 1. 标记技巧
```cpp
// 使用特殊值标记已访问
for (int i = 0; i < nums.size(); i++) {
    int index = abs(nums[i]) - 1;
    if (nums[index] > 0) {
        nums[index] = -nums[index];  // 标记为负数
    }
}
```

### 2. 环形替换
```cpp
// 旋转数组
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}
```

### 3. 双指针交换
```cpp
// 反转数组
void reverse(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        swap(nums[left++], nums[right--]);
    }
}
```

## 时间复杂度优化

### 从O(n²)到O(n)
```cpp
// O(n²) 暴力解法
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        // 处理nums[i]和nums[j]
    }
}

// O(n) 双指针优化
int left = 0, right = n - 1;
while (left < right) {
    // 根据条件移动指针
    if (condition) left++;
    else right--;
}
```

## 易错点总结

1. **边界检查**: 数组访问前检查索引有效性
2. **指针更新**: 双指针移动时注意更新条件
3. **窗口维护**: 滑动窗口的扩展和收缩逻辑
4. **前缀和**: 注意下标偏移和边界情况
5. **原地算法**: 避免额外空间时的数据覆盖问题
6. **整数溢出**: 大数相加时的溢出处理

## 相关题目分类

- **双指针**: 1两数之和、15三数之和、16最接近的三数之和、18四数之和
- **滑动窗口**: 3无重复字符最长子串、76最小覆盖子串、209长度最小子数组
- **前缀和**: 303区域和检索、304二维区域和检索、525连续数组
- **数组操作**: 48旋转图像、54螺旋矩阵、59螺旋矩阵II
- **原地算法**: 41缺失的第一个正数、287寻找重复数、448找到所有消失的数字
- **区间问题**: 56合并区间、57插入区间、252会议室

---
*数组问题的关键是选择合适的指针技巧和数学方法，善用空间换时间或时间换空间的策略*