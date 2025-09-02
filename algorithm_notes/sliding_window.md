# 滑动窗口专题

滑动窗口算法的系统化学习路径，从基础双指针到高级窗口优化的完整覆盖。

## 本专题目录
- [滑动窗口学习路径导图](#sw-roadmap)
- [核心算法模式分析](#sw-patterns)
- [核心题目分析](#sw-problems)
  - [3. 无重复字符的最长子串](#sw-3) - 经典滑动窗口入门
- [滑动窗口核心模式总结](#sw-summary)
- [调试技巧与优化](#sw-debugging)

---

<a id="sw-roadmap"></a>
## 滑动窗口学习路径导图

### 技能进阶矩阵
```
基础阶段 (双指针入门)
├── 3. 无重复字符的最长子串 (经典入门) ⭐⭐
├── 76. 最小覆盖子串 (模板题目) ⭐⭐⭐
└── 209. 长度最小的子数组 (基础应用) ⭐⭐

进阶阶段 (窗口优化)
├── 424. 替换后的最长重复字符 (状态维护) ⭐⭐⭐
├── 438. 找到字符串中所有字母异位词 (固定窗口) ⭐⭐⭐
└── 567. 字符串的排列 (排列匹配) ⭐⭐⭐

高级阶段 (复杂窗口)
├── 992. K个不同整数的子数组 (双窗口技巧) ⭐⭐⭐⭐
├── 1004. 最大连续1的个数III (状态转换) ⭐⭐⭐⭐
└── 1438. 绝对差不超过限制的最长连续子数组 (数据结构优化) ⭐⭐⭐⭐⭐
```

### 核心技能树
```
滑动窗口基础技能
├── 双指针控制 (left, right指针协调)
├── 窗口状态维护 (哈希表、计数器)
├── 收缩策略 (何时移动left指针)
└── 扩展策略 (何时移动right指针)

滑动窗口进阶技能
├── 窗口有效性判断 (满足条件的判断逻辑)
├── 状态更新策略 (进入/离开窗口的状态变化)
├── 优化技巧 (快速跳转、预处理等)
└── 复杂约束处理 (多重条件的滑动窗口)

滑动窗口高级技能
├── 双窗口技巧 (同时维护两个窗口)
├── 数据结构优化 (单调队列、平衡树等)
├── 状态压缩 (位运算、状态机等)
└── 算法融合 (滑动窗口+其他算法)
```

---

<a id="sw-patterns"></a>
## 核心算法模式分析

### 📊 滑动窗口两大核心模式

#### 模式一：渐进收缩型 (Gradual Shrinking)
**特点**: right指针探索，left指针逐步收缩
**适用**: 需要精确控制窗口状态的问题

```cpp
// 模式一：渐进收缩模板
int slidingWindowGradual(string s) {
    int left = 0, right = 0;
    unordered_set<char> window;
    int maxLen = 0;
    
    while (right < s.length()) {
        // 扩展窗口：right指针探索
        while (right < s.length() && window.find(s[right]) == window.end()) {
            window.insert(s[right]);
            right++;
            maxLen = max(maxLen, right - left);
        }
        
        // 收缩窗口：left指针逐步移动直到满足条件
        if (right < s.length()) {
            while (left < right && window.find(s[right]) != window.end()) {
                window.erase(s[left]);
                left++;
            }
        }
    }
    return maxLen;
}
```

#### 模式二：跳跃重置型 (Jump Reset)
**特点**: 遇到冲突时left指针直接跳转
**适用**: 可以快速跳过无效区间的问题

```cpp
// 模式二：跳跃重置模板
int slidingWindowJump(string s) {
    unordered_map<char, int> charIndex;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // 如果遇到重复字符，直接跳转left到冲突位置+1
        if (charIndex.find(s[right]) != charIndex.end() && 
            charIndex[s[right]] >= left) {
            left = charIndex[s[right]] + 1;
        }
        
        charIndex[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

### 🎯 两种模式的深度对比

| 特征 | 渐进收缩型 | 跳跃重置型 |
|------|------------|------------|
| **left移动方式** | 逐步递增，精确控制 | 直接跳转，快速重置 |
| **状态维护** | 精确状态，逐步更新 | 索引记录，快速查找 |
| **时间复杂度** | O(n) 但常数较大 | O(n) 常数较小 |
| **空间复杂度** | O(k) k为字符集大小 | O(k) k为字符集大小 |
| **实现难度** | 中等，需要仔细处理状态 | 简单，逻辑清晰 |
| **适用场景** | 需要精确状态维护 | 可以快速跳过无效区间 |

### 💡 模式选择指南

**选择渐进收缩型的情况**:
- 需要精确跟踪窗口内的状态变化
- 收缩过程中需要进行复杂的状态更新
- 窗口约束条件复杂，不能简单跳跃

**选择跳跃重置型的情况**:
- 可以通过索引快速定位冲突位置
- 跳跃后不需要维护复杂的中间状态
- 追求更优的时间常数

---

<a id="sw-problems"></a>
## 核心题目分析

<a id="sw-3"></a>
### 3. 无重复字符的最长子串 (Medium) - 滑动窗口经典入门 ⭐⭐

**核心思想**: 维护一个无重复字符的滑动窗口，动态调整窗口边界
**算法难点**: 如何高效处理重复字符的出现和窗口状态更新

#### 方法一：渐进收缩型实现 ⭐⭐
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        unordered_set<char> window;
        int maxLen = 0;
        
        while (right < s.length()) {
            // 扩展阶段：right指针不断探索
            while (right < s.length() && window.find(s[right]) == window.end()) {
                window.insert(s[right]);
                right++;
                maxLen = max(maxLen, right - left);
            }
            
            // 收缩阶段：left指针逐步收缩直到移除重复字符
            if (right < s.length()) {
                while (left < right && window.find(s[right]) != window.end()) {
                    window.erase(s[left]);
                    left++;
                }
            }
        }
        return maxLen;
    }
};
```

**实现要点**:
- **双阶段处理**: 扩展阶段探索，收缩阶段调整
- **状态维护**: 使用unordered_set精确跟踪窗口内字符
- **边界控制**: right < s.length()的边界检查
- **最优更新**: 在扩展阶段实时更新最大长度

#### 方法二：跳跃重置型实现 ⭐⭐⭐
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charIndex;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // 如果当前字符已存在且在当前窗口内
            if (charIndex.find(s[right]) != charIndex.end() && 
                charIndex[s[right]] >= left) {
                // 直接跳转left到重复字符的下一位置
                left = charIndex[s[right]] + 1;
            }
            
            // 更新字符的最新位置
            charIndex[s[right]] = right;
            
            // 更新最大长度
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};
```

**实现要点**:
- **索引记录**: 使用unordered_map记录每个字符的最新位置
- **跳跃逻辑**: `charIndex[s[right]] >= left`确保跳转有效性
- **状态简化**: 无需维护复杂的窗口状态，仅需索引信息
- **一次遍历**: 单层循环，时间常数更优

#### 深度技术对比

**渐进收缩型优势**:
- **状态精确**: 窗口状态始终准确，便于调试
- **逻辑清晰**: 扩展和收缩阶段分离，容易理解
- **扩展性强**: 容易修改以适应更复杂的约束条件

**跳跃重置型优势**:
- **效率更高**: 避免了逐步收缩的开销
- **代码简洁**: 单层循环，逻辑直观
- **实现优雅**: 利用索引信息实现快速跳转

#### 复杂度分析
| 方法 | 时间复杂度 | 空间复杂度 | 实现难度 | 推荐指数 |
|------|------------|------------|----------|----------|
| 渐进收缩型 | O(n) | O(min(m,n)) | ⭐⭐ | ⭐⭐⭐⭐ |
| 跳跃重置型 | O(n) | O(min(m,n)) | ⭐ | ⭐⭐⭐⭐⭐ |

*注：m为字符集大小，n为字符串长度*

#### 易错点与调试技巧

**渐进收缩型常见错误**:
1. **边界检查遗漏**: 忘记`right < s.length()`检查
2. **状态更新时机**: 在错误的位置更新maxLen
3. **循环终止条件**: 内外循环的终止条件混乱

**跳跃重置型常见错误**:
1. **跳转条件错误**: 忘记检查`charIndex[s[right]] >= left`
2. **索引更新顺序**: 在跳转前更新索引导致逻辑错误
3. **边界情况处理**: 空字符串等特殊情况

**调试技巧**:
```cpp
// 添加调试输出
void debugWindow(int left, int right, const unordered_set<char>& window) {
    cout << "Window [" << left << "," << right << "): ";
    for (char c : window) cout << c << " ";
    cout << endl;
}
```

#### 扩展应用与相关题目
- **76. 最小覆盖子串**: 滑动窗口+字符匹配 (已完成深度实现)
- **438. 找到字符串中所有字母异位词**: 固定长度滑动窗口
- **567. 字符串的排列**: 排列检测的滑动窗口应用
- **424. 替换后的最长重复字符**: 状态维护的高级应用

<a id="sw-76"></a>
### 76. 最小覆盖子串 (Hard) - 滑动窗口巅峰应用 ⭐⭐⭐⭐⭐

**核心思想**: 在字符串s中找到包含字符串t所有字符的最小子串
**算法难点**: 处理重复字符、维护复杂约束条件、窗口动态调整

#### 高效实现：正负值计数策略 ⭐⭐⭐⭐⭐

这是一个比标准模板更优雅的实现，通过巧妙的计数策略简化了状态管理：

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int count = t.size(); // 剩余需要满足的字符总数
        unordered_map<char, int> char_map;
        
        // 初始化：记录目标字符的需要数量
        for(auto& c : t) {
            char_map[c] += 1;
        }
        
        int left = 0, right = 0;
        int min_len = INT_MAX, start = 0;
        
        while(right < s.size()) {
            // 扩展窗口：处理右边界字符
            if(char_map[s[right]] > 0) {  // 只有目标字符才减少count
                count--;
            }
            char_map[s[right]]--;  // 所有字符都更新频次
            right++;
            
            // 收缩窗口：当窗口满足条件时寻找最小窗口
            while(count == 0) {
                if((right - left) < min_len) {
                    min_len = right - left;
                    start = left;
                }
                
                char_map[s[left]]++;
                if(char_map[s[left]] > 0) {  // 失去目标字符时增加count
                    count++;
                }
                left++;
            }
        }
        
        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};
```

#### 🔍 核心机制深度解析

**1. 正负值计数策略**

通过char_map的正负值巧妙区分字符状态：
- **正值**: 还需要的字符数量
- **零值**: 刚好满足需求  
- **负值**: 多余的字符（超出需求）

```cpp
// 三类字符的处理：
// 类别1：t中的目标字符 (初始为正数)
for(auto& c : t) {
    char_map[c] += 1;  // A:2, B:1, C:1
}

// 类别2：t中未出现字符 (始终≤0，不影响count)
// char_map[其他字符] = 0 → -1 → -2 → ...

// 类别3：已满足或多余字符 (≤0)
// char_map[目标字符] = 正数 → 0 → -1 → -2 → ...
```

**2. 多重出现字符的精确处理**

```cpp
// 示例：t = "AABC" (A需要2个，B需要1个，C需要1个)
初始：char_map = {A:2, B:1, C:1}, count = 4

处理第1个'A'：
- char_map[A] = 2 > 0 ✓ → count-- (count=3)
- char_map[A]-- → char_map[A] = 1

处理第2个'A'：  
- char_map[A] = 1 > 0 ✓ → count-- (count=2)
- char_map[A]-- → char_map[A] = 0

处理第3个'A'：
- char_map[A] = 0 ≤ 0 ❌ → count不变 (count=2)
- char_map[A]-- → char_map[A] = -1 (多余的A)
```

**3. 窗口边界的数学原理**

使用**[left, right)**左闭右开区间表示：

```cpp
while(right < s.size()) {
    // 先处理s[right]字符
    char_map[s[right]]--;
    right++;  // right移动到下一位
    
    // 此时窗口是[left, right)
    // 窗口长度 = right - left (不是right-left+1)
}
```

**边界计算示例**：
```
字符串: "BANC"  
索引:    0123

处理完'C'后：
- left = 0, right = 4 (指向末尾)
- 窗口内容：s[0]到s[3] = "BANC"  
- 窗口长度：right - left = 4 - 0 = 4 ✓
```

**4. 自动字符过滤机制**

```cpp
// 关键判断：只有>0的字符才影响count
if(char_map[s[right]] > 0) {
    count--;
}

// 等价于：
if(s[right]是t中需要的字符 && 当前窗口中该字符还不够) {
    count--;  // 满足了一个需求
}
```

**字符分类处理**：
- **t中未出现字符**: `char_map[c] = 0 → -1 → -2...` (永远≤0，不影响count)
- **t中目标字符**: `正数 → 0 → 负数` (只有正数→0时影响count)
- **已满足字符**: `≤0` (不再影响count，直到窗口收缩)

#### 🎯 算法优势分析

**与标准双哈希表模板对比**：

| 特征 | 标准模板 | 正负值策略 |
|------|----------|------------|
| **数据结构** | need + window + valid | 单个char_map + count |
| **状态跟踪** | 双表对比 + 计数器 | 正负值直接判断 |
| **代码复杂度** | 较复杂 | 更简洁 |
| **性能** | O(m+n) | O(m+n) |
| **空间使用** | 2个哈希表 | 1个哈希表 |
| **理解难度** | 中等 | 需要理解正负值含义 |

#### 🚨 关键技术细节

**1. count的精确含义**
```cpp
int count = t.size();  // 不是t中不同字符的个数，而是总字符数
// 例如：t="AABC" → count=4 (不是3)
```

**2. 判断条件的时机**
```cpp
// 扩展时：先判断再更新
if(char_map[s[right]] > 0) count--;  // 判断
char_map[s[right]]--;                // 更新

// 收缩时：先更新再判断  
char_map[s[left]]++;                 // 更新
if(char_map[s[left]] > 0) count++;   // 判断
```

**3. 窗口满足条件**
```cpp
while(count == 0) {  // count==0 表示所有目标字符都已满足
    // 更新最小窗口
    // 收缩窗口
}
```

#### 💡 学习价值与扩展

这个实现展现了算法优化的高水平思维：
- **状态压缩**: 用单一变量代替复杂状态跟踪
- **语义设计**: 正负值的巧妙语义区分
- **自动过滤**: 通过数学性质自动处理无关字符
- **边界统一**: 左闭右开区间的一致性处理

**核心洞察**: 通过巧妙的计数策略，将复杂的多状态管理问题转化为简单的数值比较，体现了算法设计中"化繁为简"的精髓。

---

<a id="sw-summary"></a>
## 滑动窗口核心模式总结

### 🎯 算法设计原则

#### 1. 双指针协调原则
- **right指针**: 负责探索和扩展窗口
- **left指针**: 负责收缩和维护窗口有效性
- **状态同步**: 指针移动与窗口状态必须同步更新

#### 2. 窗口状态维护原则
- **进入窗口**: right指针移动时的状态更新
- **离开窗口**: left指针移动时的状态清理
- **状态查询**: 高效判断当前窗口是否满足条件

#### 3. 优化策略选择原则
- **渐进收缩**: 适合需要精确状态控制的场景
- **跳跃重置**: 适合可以快速跳过无效区间的场景
- **混合策略**: 根据具体问题特点灵活组合

### 🛠️ 通用模板框架

#### 基础滑动窗口模板
```cpp
int slidingWindow(vector<int>& nums, int target) {
    int left = 0, result = 0;
    WindowState state;  // 窗口状态维护
    
    for (int right = 0; right < nums.size(); right++) {
        // 1. 扩展窗口：处理right指针进入
        state.add(nums[right]);
        
        // 2. 收缩窗口：维护窗口有效性
        while (left <= right && !state.isValid()) {
            state.remove(nums[left]);
            left++;
        }
        
        // 3. 更新结果：在有效窗口时更新答案
        if (state.isValid()) {
            result = max(result, right - left + 1);
        }
    }
    return result;
}
```

#### 高级滑动窗口模板
```cpp
int advancedSlidingWindow(string s, string pattern) {
    unordered_map<char, int> need, window;
    for (char c : pattern) need[c]++;
    
    int left = 0, right = 0;
    int valid = 0;  // 已匹配的字符种类数
    int result = INT_MAX;
    
    while (right < s.size()) {
        // 扩展窗口
        char c = s[right];
        right++;
        
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c]) {
                valid++;
            }
        }
        
        // 收缩窗口
        while (valid == need.size()) {
            // 更新结果
            result = min(result, right - left);
            
            char d = s[left];
            left++;
            
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return result == INT_MAX ? 0 : result;
}
```

### 🔍 模式识别指南

**如何选择合适的滑动窗口模式**:

1. **分析问题特征**:
   - 是否需要精确的状态控制？→ 渐进收缩型
   - 是否可以快速跳过无效区间？→ 跳跃重置型
   - 是否有复杂的约束条件？→ 基础模板扩展

2. **评估实现复杂度**:
   - 状态维护的复杂程度
   - 窗口收缩的逻辑复杂度
   - 边界条件的处理难度

3. **考虑性能要求**:
   - 时间复杂度的常数优化需求
   - 空间复杂度的限制
   - 实际数据规模和特征

---

<a id="sw-debugging"></a>
## 调试技巧与优化

### 🔧 常见错误类型与解决方案

#### 错误类型1: 指针边界错误
```cpp
// ❌ 错误：没有检查边界
while (right < s.length() && condition) {
    // 处理逻辑
    right++;  // 可能越界
}

// ✅ 正确：先检查再处理
while (right < s.length()) {
    if (!condition) break;
    // 处理逻辑
    right++;
}
```

#### 错误类型2: 状态更新不同步
```cpp
// ❌ 错误：状态更新与指针移动不同步
left++;
window.erase(s[left]);  // 错误：应该先erase再移动

// ✅ 正确：同步更新
window.erase(s[left]);
left++;
```

#### 错误类型3: 重复计算最优值
```cpp
// ❌ 错误：在循环外更新结果
for (int right = 0; right < s.length(); right++) {
    // 窗口操作
}
result = right - left;  // 错误：只计算了最后状态

// ✅ 正确：在循环内实时更新
for (int right = 0; right < s.length(); right++) {
    // 窗口操作
    result = max(result, right - left + 1);
}
```

### 🎯 性能优化技巧

#### 优化1: 数据结构选择
```cpp
// 基础版本：使用set/map (O(log n)操作)
unordered_set<char> window;

// 优化版本：使用数组 (O(1)操作，适用于ASCII字符)
bool window[256] = {false};

// 进一步优化：位运算 (适用于小字符集)
int windowMask = 0;  // 使用位掩码
```

#### 优化2: 早期终止
```cpp
// 添加早期终止条件
if (s.length() < pattern.length()) return 0;
if (maxPossibleLength <= currentResult) break;
```

#### 优化3: 预处理优化
```cpp
// 预处理字符频率
unordered_map<char, int> need;
int uniqueChars = 0;
for (char c : pattern) {
    if (need[c] == 0) uniqueChars++;
    need[c]++;
}
```

### 📊 调试工具函数

```cpp
class SlidingWindowDebugger {
public:
    // 窗口状态可视化
    void printWindow(const string& s, int left, int right, const string& info = "") {
        cout << info << " Window[" << left << "," << right << "): ";
        for (int i = left; i < right && i < s.length(); i++) {
            cout << s[i];
        }
        cout << " (length=" << right - left << ")" << endl;
    }
    
    // 状态变化追踪
    void logStateChange(char op, char ch, int pos, const string& action) {
        cout << "[" << op << "] char='" << ch << "' pos=" << pos 
             << " action=" << action << endl;
    }
    
    // 性能统计
    struct Stats {
        int totalIterations = 0;
        int windowExpansions = 0;
        int windowShrinks = 0;
        int maxWindowSize = 0;
    };
};
```

## 扩展应用方向

### 进阶题目推荐
- **76. 最小覆盖子串** - 字符匹配的滑动窗口
- **209. 长度最小的子数组** - 数值条件的滑动窗口
- **424. 替换后的最长重复字符** - 状态维护的高级应用
- **992. K个不同整数的子数组** - 双窗口技巧
- **1004. 最大连续1的个数III** - 状态转换的滑动窗口

### 实际应用场景
- **网络编程**: TCP滑动窗口协议
- **数据分析**: 时间序列数据的移动平均
- **图像处理**: 卷积操作和滤波器
- **搜索引擎**: 文本匹配和索引
- **系统监控**: 实时数据流的状态监控

## 总结与进阶

滑动窗口作为一种重要的算法技巧，其核心价值在于**双指针协调控制**和**状态高效维护**。通过系统学习本专题：

1. **掌握双指针技巧** - left/right指针的协调控制
2. **理解状态维护** - 窗口状态的高效更新机制
3. **掌握模式选择** - 渐进收缩vs跳跃重置的适用场景
4. **建立优化思维** - 从基础实现到性能优化的进阶路径

滑动窗口算法的精髓在于**动态调整窗口边界以维护特定约束**，为解决区间相关问题提供了高效的算法框架。