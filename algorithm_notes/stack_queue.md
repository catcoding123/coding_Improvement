# 栈与队列专题

本专题目录
- [239. 滑动窗口最大值](#sq-239)
- [155. 最小栈](#sq-155)
- [84. 柱状图中最大矩形](#sq-84)
- [42. 接雨水](#sq-42)

<a id="sq-239"></a>
### 239. 滑动窗口最大值 (Hard) - 单调队列 ⭐⭐⭐
**核心思想**: 单调双端队列维护窗口最大值，存储下标，保持递减序列
**算法本质**: 滑动窗口 + 单调数据结构的完美结合

#### 题目链接
https://leetcode.cn/problems/sliding-window-maximum/

#### 核心算法原理

**问题分析**: 
- 需要在O(1)时间内获取滑动窗口的最大值
- 暴力解法每个窗口都要O(k)时间找最大值，总时间O(nk)
- 单调队列可以将时间复杂度优化到O(n)

**单调队列核心机制**:
1. **存储策略**: 队列存储数组下标，而非数值
2. **单调性维护**: 保持队列中下标对应的值严格递减
3. **过期清理**: 及时移除超出窗口范围的过期元素

#### 算法核心实现

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;  // 存储下标，保持递减顺序
    
    for (int i = 0; i < nums.size(); i++) {
        // 步骤1: 移除过期元素
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // 步骤2: 维护单调性(递减)
        while (!dq.empty() && nums[i] >= nums[dq.back()]) {
            dq.pop_back();
        }
        
        // 步骤3: 添加当前元素
        dq.push_back(i);
        
        // 步骤4: 收集结果(窗口满时)
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
```

#### 关键理解突破

**1. 为什么存储下标而非数值？**
```cpp
// ❌ 存储数值 - 无法判断元素是否过期
deque<int> dq_values;

// ✅ 存储下标 - 可以通过下标判断位置关系
deque<int> dq_indices;
if (dq.front() <= i - k) dq.pop_front();  // 过期判断
```

**2. 为什么使用`<=`而非`<`判断过期？**
```cpp
// 窗口大小为k，当前位置为i
// 窗口范围: [i-k+1, i]
// 过期条件: index < i-k+1  =>  index <= i-k
while (!dq.empty() && dq.front() <= i - k) {
    dq.pop_front();
}
```

**3. 为什么维护递减而非递增？**
```cpp
// 递减队列确保队首始终是最大值
// 当新元素更大时，移除所有较小的元素
while (!dq.empty() && nums[i] >= nums[dq.back()]) {
    dq.pop_back();  // 移除较小元素
}
```

#### 算法特点总结

**时间复杂度**: O(n) - 每个元素最多入队出队一次
**空间复杂度**: O(k) - 队列最多存储k个元素
**核心优势**: 
1. 时间最优：避免每个窗口重复计算最大值
2. 实现优雅：单调队列的经典应用
3. 扩展性强：可推广到滑动窗口最小值等问题

#### 易错点总结

1. **过期判断**: 使用`<=`不是`<`
2. **窗口满判断**: `i >= k - 1`确保窗口大小达到k
3. **单调性维护**: 使用`>=`处理重复值情况
4. **边界处理**: 空队列和单元素的特殊情况

#### 扩展应用
- **滑动窗口最小值**: 维护递增单调队列
- **滑动窗口中位数**: 结合大小堆
- **约束滑动窗口**: 加入额外约束条件

---

<a id="sq-155"></a>
### 155. 最小栈 (Medium) - 双栈设计 ⭐⭐⭐
**核心思想**: 主栈+辅助栈，辅助栈维护最小值
**算法本质**: 空间换时间，用额外栈维护全局状态

#### 题目链接
https://leetcode.cn/problems/min-stack/

#### 核心算法原理

**问题分析**:
- 普通栈只能O(1)访问栈顶，获取最小值需要O(n)
- 需要设计数据结构使所有操作都是O(1)
- 当最小元素被pop时，要能快速获取下一个最小值

**双栈设计思想**:
1. **主栈**: 存储所有元素，维护栈的基本功能
2. **辅助栈**: 只存储最小值，与主栈同步变化
3. **同步机制**: 两个栈协调工作，确保一致性

#### 算法核心实现

```cpp
class MinStack {
private:
    stack<int> mainStack;    // 主栈：存储所有元素
    stack<int> minStack;     // 辅助栈：存储对应的最小值
    
public:
    void push(int val) {
        mainStack.push(val);
        
        // 关键：<=确保重复最小值也会入栈
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        // 如果主栈顶是最小值，辅助栈也要同步pop
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();  // O(1)获取最小值
    }
};
```

#### 关键理解突破

**1. 为什么push时使用`<=`而非`<`？**
```cpp
// 场景：连续push相同的最小值
push(1); push(1); push(1);

// 使用 < ：只有第一个1进入辅助栈
// pop()后：辅助栈为空，无法获取最小值 ❌

// 使用 <=：所有重复最小值都进入辅助栈
// pop()后：辅助栈仍有最小值，正确 ✅
```

**2. pop时的同步机制**:
```cpp
// 只有当主栈顶等于最小值时，辅助栈才pop
if (mainStack.top() == minStack.top()) {
    minStack.pop();
}
mainStack.pop();
```

**3. 辅助栈的状态变化**:
```
操作序列: push(-2) → push(0) → push(-3) → pop() → getMin()

主栈:    [-2]     [-2,0]     [-2,0,-3]   [-2,0]    [-2,0]
辅助栈:  [-2]     [-2]       [-2,-3]     [-2]      [-2]
最小值:   -2        -2          -3         -2        -2
```

#### 算法优化版本

**单栈存储差值法**（高级）:
```cpp
class MinStackOptimized {
private:
    stack<long long> st;  // 存储差值
    long long minVal;     // 当前最小值
    
public:
    void push(int val) {
        if (st.empty()) {
            minVal = val;
            st.push(0);
        } else {
            st.push(val - minVal);
            if (val < minVal) {
                minVal = val;
            }
        }
    }
    
    void pop() {
        long long top = st.top();
        st.pop();
        if (top < 0) {  // 恢复之前的最小值
            minVal -= top;
        }
    }
    
    int top() {
        long long topDiff = st.top();
        return topDiff >= 0 ? minVal + topDiff : minVal;
    }
    
    int getMin() {
        return minVal;
    }
};
```

#### 算法特点总结

**时间复杂度**: O(1) - 所有操作
**空间复杂度**: O(n) - 最坏情况两个栈都存n个元素
**核心优势**:
1. 操作简单：所有操作都是O(1)
2. 思路清晰：双栈协作容易理解
3. 扩展性好：可推广到最大栈等问题

#### 错误分析
根据error_tracking_system.md中的记录，容器API使用容易混淆：
- ❌ `queue.pop_front()` - queue没有此方法
- ✅ `queue.pop()` + `queue.front()` - 正确的FIFO操作

#### 扩展应用
- **最大栈**: 维护最大值而非最小值
- **中位数栈**: 结合大小堆维护中位数
- **频率栈**: 维护出现频率最高的元素

---

<a id="sq-84"></a>
### 84. 柱状图中最大矩形 (Hard) - 单调栈 ⭐⭐⭐⭐
**核心思想**: 单调递增栈，弹栈时计算面积
**算法本质**: 将二维面积问题转化为一维边界问题

#### 题目链接
https://leetcode.cn/problems/largest-rectangle-in-histogram/

#### 核心算法原理

**问题分析**:
- 对每个柱子，需要找到以它为高度的最大矩形
- 关键是找到左右两边第一个比它矮的柱子（边界）
- 暴力解法对每个柱子都要O(n)时间找边界，总时间O(n²)

**单调栈解决思路**:
1. **维护递增栈**: 栈中存储柱子下标，对应高度严格递增
2. **遇小元素弹栈**: 当前元素比栈顶小时，为栈中元素找到了右边界
3. **计算面积**: 弹出元素为高度，计算对应矩形面积

#### 算法核心实现

```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    
    // 技巧：在数组两端添加0，简化边界处理
    heights.insert(heights.begin(), 0);
    heights.push_back(0);
    
    for (int i = 0; i < heights.size(); i++) {
        // 当前高度小于栈顶高度时，弹栈计算面积
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];  // 矩形高度
            st.pop();
            int w = i - st.top() - 1;   // 矩形宽度
            maxArea = max(maxArea, h * w);
        }
        st.push(i);
    }
    
    return maxArea;
}
```

#### 关键理解突破

**1. 为什么维护递增栈？**
```cpp
// 递增栈确保能快速找到左边界
// 当遇到更小元素时，栈中所有比它大的元素都找到了右边界
// 栈中剩余元素就是左边界
```

**2. 面积计算公式推导**:
```cpp
// 弹出栈顶index，高度为heights[index]
// 右边界：当前位置i（第一个比它小的）
// 左边界：新的栈顶st.top()（左边第一个比它小的）
// 宽度 = 右边界 - 左边界 - 1 = i - st.top() - 1
int area = heights[index] * (i - st.top() - 1);
```

**3. 为什么要在两端添加0？**
```cpp
// 左边加0：确保所有元素都能找到左边界
// 右边加0：确保栈中剩余元素都能被处理
heights.insert(heights.begin(), 0);  // 左端加0
heights.push_back(0);                // 右端加0
```

#### 算法过程演示

以`heights = [2,1,5,6,2,3]`为例：

```
添加哨兵后: [0,2,1,5,6,2,3,0]

i=0: push(0), stack=[0]
i=1: push(1), stack=[0,1]  
i=2: 1>heights[2]=1, 弹出index=1, h=2, w=2-0-1=1, area=2
     push(2), stack=[0,2]
i=3: push(3), stack=[0,2,3]
i=4: push(4), stack=[0,2,3,4]
i=5: 6>heights[5]=2, 弹出index=4, h=6, w=5-3-1=1, area=6
     5>heights[5]=2, 弹出index=3, h=5, w=5-2-1=2, area=10 ⭐
     push(5), stack=[0,2,5]
...
```

最大面积为10（高度5，宽度2）。

#### 算法特点总结

**时间复杂度**: O(n) - 每个元素最多入栈出栈一次
**空间复杂度**: O(n) - 栈的空间
**核心优势**:
1. 时间最优：将O(n²)优化到O(n)
2. 思路优雅：单调栈的经典应用
3. 边界简化：哨兵技巧简化边界处理

#### 易错点总结

1. **面积计算公式**: `w = i - st.top() - 1`，注意减1
2. **边界处理**: 添加哨兵0简化处理
3. **栈空判断**: 弹栈前要检查栈是否为空
4. **下标存储**: 栈中存储下标而非高度值

#### 扩展应用
- **85. 最大矩形**: 二维矩阵中的最大矩形
- **42. 接雨水**: 单调栈的另一个经典应用
- **496. 下一个更大元素**: 单调栈找下一个更大元素

---

<a id="sq-42"></a>
### 42. 接雨水 (Hard) - 单调栈变种 ⭐⭐⭐⭐
**核心思想**: 单调递减栈，按层计算雨水
**算法本质**: 多种解法的集大成，展现算法思维进化

#### 题目链接
https://leetcode.cn/problems/trapping-rain-water/

#### 核心算法原理

**问题分析**:
- 对每个位置，能接的雨水 = `min(左边最高, 右边最高) - 当前高度`
- 关键是如何高效计算每个位置的左边最高和右边最高
- 有多种解法：暴力、DP、双指针、单调栈

#### 四种解法对比

**方法1: 动态规划 - O(n)时间，O(n)空间**
```cpp
int trapDP(vector<int>& height) {
    int n = height.size();
    vector<int> leftMax(n), rightMax(n);
    
    // 预计算左边最高
    leftMax[0] = 0;
    for (int i = 1; i < n; i++) {
        leftMax[i] = max(leftMax[i-1], height[i-1]);
    }
    
    // 预计算右边最高
    rightMax[n-1] = 0;
    for (int i = n-2; i >= 0; i--) {
        rightMax[i] = max(rightMax[i+1], height[i+1]);
    }
    
    // 计算雨水
    int result = 0;
    for (int i = 0; i < n; i++) {
        int waterLevel = min(leftMax[i], rightMax[i]);
        if (waterLevel > height[i]) {
            result += waterLevel - height[i];
        }
    }
    
    return result;
}
```

**方法2: 双指针 - O(n)时间，O(1)空间** ⭐ 最优
```cpp
int trapTwoPointers(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int result = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                result += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                result += rightMax - height[right];
            }
            right--;
        }
    }
    
    return result;
}
```

**方法3: 单调栈 - O(n)时间，O(n)空间**
```cpp
int trapMonotonicStack(vector<int>& height) {
    stack<int> st;
    int result = 0;
    
    for (int i = 0; i < height.size(); i++) {
        // 维护递减栈，遇到更高的柱子时计算接水量
        while (!st.empty() && height[i] > height[st.top()]) {
            int bottom = st.top();  // 底部高度
            st.pop();
            
            if (st.empty()) break;
            
            int left = st.top();    // 左边界
            int width = i - left - 1;
            int h = min(height[i], height[left]) - height[bottom];
            result += width * h;
        }
        st.push(i);
    }
    
    return result;
}
```

#### 双指针解法深度解析

**核心洞察**: 不需要知道确切的左右最高值，只需要知道哪边更小

**关键理解**:
```cpp
if (height[left] < height[right]) {
    // 此时可以确定：right边一定比leftMax高
    // 所以left位置的积水只取决于leftMax
    // 不用管rightMax的具体值
    if (height[left] >= leftMax) {
        leftMax = height[left];  // 更新左边最高
    } else {
        result += leftMax - height[left];  // 计算积水
    }
    left++;
}
```

**为什么这样可行？**
- 当`height[left] < height[right]`时，右边至少有`height[right]`这么高
- 即使右边更高，也不会影响left位置的积水量
- 积水量只取决于较小的那一边（leftMax）

#### 单调栈解法深度解析

**与84题的区别**:
- **84题**: 维护递增栈，计算矩形面积（垂直方向）
- **42题**: 维护递减栈，计算雨水体积（水平方向）

**按层计算思想**:
```cpp
// 遇到更高柱子时，形成"凹槽"可以接水
// 左边界: st.top() (已经比bottom高)
// 右边界: i (当前比bottom高)  
// 底部: bottom (被弹出的栈顶)
int h = min(height[i], height[left]) - height[bottom];
```

#### 算法特点对比

| 方法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| **暴力** | O(n²) | O(1) | 简单但低效 |
| **DP** | O(n) | O(n) | 预计算，思路清晰 |
| **双指针** | O(n) | O(1) | **最优解**，空间效率最高 |
| **单调栈** | O(n) | O(n) | 思路独特，按层计算 |

#### 算法进化轨迹

```
暴力解法: 对每个位置单独计算
    ↓ (空间换时间)
DP解法: 预计算左右最高值
    ↓ (双指针优化)
双指针: 动态维护左右最高值
    ↓ (换个思路)
单调栈: 按层计算，从不同角度解决
```

#### 易错点总结

1. **边界处理**: 数组两端通常无法积水
2. **积水条件**: 只有`waterLevel > height[i]`时才有积水
3. **双指针移动**: 根据高度比较决定移动方向
4. **单调栈维护**: 递减栈的维护和弹栈时机

#### 学习价值

42题是算法思维进化的典型代表：
1. **多解法掌握**: 展现不同算法思维
2. **优化思路**: 从O(n²)到O(n)，从O(n)空间到O(1)空间
3. **模式识别**: 双指针和单调栈的经典应用
4. **思维拓展**: 同一问题的不同解决角度

---

## 🎯 专题总结：栈与队列核心技能体系

### 学习路径回顾

```
📚 基础建立阶段
155题最小栈 → 双栈设计思想，辅助数据结构概念

🔄 单调结构阶段  
239题滑动窗口 → 单调队列，维护区间极值
84题柱状图矩形 → 单调栈，寻找边界问题

🎯 综合应用阶段
42题接雨水 → 多解法融合，算法思维进化
```

### 核心技能掌握矩阵

| 技能维度 | 掌握程度 | 代表题目 | 核心洞察 |
|---------|---------|----------|----------|
| **辅助栈设计** | ✅ 精通 | 155题最小栈 | 空间换时间，同步维护全局状态 |
| **单调队列** | ✅ 精通 | 239题滑动窗口 | 维护区间极值，滑动窗口优化 |
| **单调栈应用** | ✅ 精通 | 84题矩形面积 | 寻找边界，面积计算优化 |
| **多解法融合** | ✅ 精通 | 42题接雨水 | 双指针、DP、单调栈的综合应用 |

### 算法设计思维升华

#### 1. 单调数据结构设计哲学
```cpp
// 单调栈/队列的核心思想：用有序性换取效率
// 维护单调性 → 快速查找 → O(1)极值访问
```

#### 2. 辅助数据结构设计
```cpp
// 主数据结构 + 辅助数据结构 = 功能增强
// 155题: 主栈 + 辅助栈 = 常数时间最小值查询
```

#### 3. 多解法思维模式
```cpp
// 42题展现的算法进化：
// 暴力 → DP → 双指针 → 单调栈
// 体现算法优化的不同方向
```

### 核心模板库建立

#### 单调队列标准模板
```cpp
deque<int> dq;  // 存储下标
for (int i = 0; i < n; i++) {
    // 1. 移除过期元素
    while (!dq.empty() && dq.front() <= i - k) {
        dq.pop_front();
    }
    
    // 2. 维护单调性
    while (!dq.empty() && nums[i] >= nums[dq.back()]) {
        dq.pop_back();
    }
    
    // 3. 添加当前元素
    dq.push_back(i);
    
    // 4. 收集结果
    if (i >= k - 1) {
        result.push_back(nums[dq.front()]);
    }
}
```

#### 单调栈标准模板
```cpp
stack<int> st;
for (int i = 0; i < n; i++) {
    while (!st.empty() && condition(st.top(), i)) {
        int index = st.top();
        st.pop();
        // 计算以index为关键位置的结果
        process(index, st.empty() ? -1 : st.top(), i);
    }
    st.push(i);
}
```

#### 双栈辅助模板
```cpp
class AuxiliaryStack {
private:
    stack<int> mainStack;
    stack<int> auxStack;  // 维护某种全局性质
    
public:
    void push(int val) {
        mainStack.push(val);
        if (auxStack.empty() || condition(val, auxStack.top())) {
            auxStack.push(val);
        }
    }
    
    void pop() {
        if (mainStack.top() == auxStack.top()) {
            auxStack.pop();
        }
        mainStack.pop();
    }
    
    int getProperty() {
        return auxStack.top();  // O(1)获取全局性质
    }
};
```

### 学习成果评估

#### 技术突破
- ✅ 掌握单调数据结构的设计和应用
- ✅ 理解辅助数据结构的设计思想
- ✅ 具备多解法分析和比较能力
- ✅ 建立完整的栈队列算法知识体系

#### 思维升华
- ✅ 从"单一数据结构"到"组合数据结构"的设计思维
- ✅ 从"暴力搜索"到"单调性优化"的效率意识
- ✅ 从"固定解法"到"多角度思考"的灵活性
- ✅ 从"实现功能"到"分析权衡"的工程思维

### 专题价值与意义

栈与队列专题的学习建立了**高效数据结构设计**的核心思维：

1. **单调性利用**: 通过维护数据的有序性获得查询效率
2. **辅助结构设计**: 用额外空间换取功能增强
3. **多解法权衡**: 不同算法在时空复杂度上的权衡选择
4. **模式识别能力**: 识别何时使用单调栈/队列解决问题
5. **优化设计思维**: 从多个角度分析和优化同一问题

这些思维模式为后续的高级数据结构学习和复杂算法设计奠定了坚实基础。

---

*最后更新: 2025-08-30*
