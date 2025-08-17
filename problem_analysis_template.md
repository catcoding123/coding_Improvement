# 题目分析模板

## 📋 题目信息卡片

### 基本信息
- **题号**: 
- **题目**: 
- **难度**: Easy/Medium/Hard
- **标签**: [数组, 双指针, 滑动窗口]
- **通过率**: %
- **频次**: ⭐⭐⭐⭐⭐

### 🎯 核心考点分析

#### 知识点考查
- **主要算法**: 
- **数据结构**: 
- **思维方式**: [贪心/分治/动态规划/回溯]
- **编程技巧**: [双指针/滑动窗口/哈希表优化]

#### 考核重点
- [ ] **基础实现能力** - 能否正确实现基本逻辑
- [ ] **边界处理** - 空数组、单元素、极值情况
- [ ] **复杂度分析** - 时间/空间复杂度优化
- [ ] **代码质量** - 可读性、简洁性
- [ ] **扩展思维** - 举一反三能力

### 🔍 解题思路框架

#### 思路分层
1. **暴力解法** 
   - 思路: 
   - 复杂度: O() / O()
   - 适用场景: 数据量小、理解题意

2. **优化解法**
   - 思路: 
   - 复杂度: O() / O() 
   - 关键优化点: 

3. **最优解法**
   - 思路: 
   - 复杂度: O() / O()
   - 核心insight: 

#### 解题步骤
1. **理解题意** - 输入输出、约束条件
2. **分析案例** - 手工模拟，找规律
3. **设计算法** - 选择合适的方法
4. **编码实现** - 注意边界和细节
5. **测试验证** - 多种测试用例

### 🚨 常见陷阱与易错点

#### 逻辑陷阱
- [ ] **边界条件遗漏** - 空输入、单元素、重复元素
- [ ] **循环条件错误** - off-by-one错误
- [ ] **返回值错误** - 返回索引vs值、多个答案vs单个

#### 实现细节
- [ ] **数组越界** - 访问不存在的索引
- [ ] **整型溢出** - 大数运算
- [ ] **指针操作** - 空指针、野指针

#### 复杂度陷阱
- [ ] **时间复杂度** - 嵌套循环导致超时
- [ ] **空间复杂度** - 额外空间使用不当

### 📝 代码模板

#### 算法框架
```python
def solution(input_params):
    # 1. 边界处理
    if not input_params:
        return default_value
    
    # 2. 初始化变量
    
    # 3. 核心算法逻辑
    
    # 4. 返回结果
    return result
```

#### 测试用例设计
```python
def test_solution():
    # 基本功能测试
    assert solution([1,2,3]) == expected_result
    
    # 边界条件测试  
    assert solution([]) == edge_case_result
    assert solution([1]) == single_element_result
    
    # 极值测试
    assert solution(max_input) == max_result
    
    print("All tests passed!")
```

### 🔗 相关题目

#### 同类型题目
- **简化版**: 
- **进阶版**: 
- **变种题**: 

#### 知识点关联
- **前置知识**: 
- **后续学习**: 

### 📊 学习记录

#### 解题过程
- **首次尝试**: ✅/❌ 用时: min
- **理解程度**: 完全理解/部分理解/需要复习
- **实现难点**: 
- **收获总结**: 

#### 复习计划
- **3天后复习**: 日期
- **1周后复习**: 日期  
- **1月后复习**: 日期

#### 笔记要点
- **关键思路**: 
- **代码要点**: 
- **易错提醒**: 

---

## 使用说明

### 刷题前准备
1. 填写基本信息和考点分析
2. 制定解题思路和测试用例
3. 预估时间和难度

### 刷题中记录
1. 记录解题过程和思路变化
2. 标记遇到的问题和解决方案
3. 记录代码实现的关键点

### 刷题后总结
1. 分析解题效果和用时
2. 总结收获和改进点
3. 制定复习计划

### 复习时使用
1. 快速回顾核心考点
2. 重做关键测试用例
3. 检查之前的易错点

DFS与回溯法的实现对比
确实，DFS和回溯法在实现上非常相似，但它们在思想和具体实现上有一些关键区别。让我们详细比较一下这两种方法的实现差异。

核心区别
回溯法实际上是DFS的一种特殊实现，主要区别在于：

回溯法显式地维护当前状态，通过"选择-递归-撤销选择"的步骤

DFS非回溯实现则通过传递状态副本，避免显式地撤销选择

实现对比
1. 回溯法实现
cpp
void backtrack(const string& s, int start, vector<string>& path, vector<vector<string>>& res) {
    if (start == s.length()) {
        res.push_back(path);
        return;
    }
    
    for (int end = start + 1; end <= s.length(); ++end) {
        string substr = s.substr(start, end - start);
        if (isPalindrome(substr)) {
            path.push_back(substr);  // 做出选择
            backtrack(s, end, path, res);  // 递归
            path.pop_back();  // 撤销选择
        }
    }
}
2. DFS非回溯实现
cpp
void dfs(const string& s, int start, vector<string> path, vector<vector<string>>& res) {
    if (start == s.length()) {
        res.push_back(path);
        return;
    }
    
    for (int end = start + 1; end <= s.length(); ++end) {
        string substr = s.substr(start, end - start);
        if (isPalindrome(substr)) {
            vector<string> newPath = path;  // 创建副本
            newPath.push_back(substr);  // 修改副本
            dfs(s, end, newPath, res);  // 传递副本
        }
    }
}
