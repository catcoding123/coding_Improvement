/*
LeetCode 20. 有效的括号
Difficulty: Easy
Link: https://leetcode.cn/problems/valid-parentheses/

题目描述：
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：
1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

示例 1：
输入：s = "()"
输出：true

示例 2：
输入：s = "()[]{}"
输出：true

示例 3：
输入：s = "(]"
输出：false

约束条件：
- 1 <= s.length <= 10^4
- s 仅由括号 '()[]{}' 组成

算法分析：
时间复杂度：O(n) - 遍历字符串
空间复杂度：O(n) - 栈存储左括号

核心思想：
1. 栈的经典应用：后进先出(LIFO)
2. 遇到左括号时入栈
3. 遇到右括号时检查栈顶是否匹配
4. 最后检查栈是否为空

易错点：
1. 栈为空时遇到右括号：直接返回false
2. 括号类型不匹配：检查配对关系
3. 遍历结束后栈非空：存在未配对的左括号
4. 字符串为空：应该返回true

相关题目：
- 22. 括号生成
- 32. 最长有效括号 
- 921. 使括号有效的最少添加
- 1541. 平衡括号字符串的最少插入次数
*/

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // TODO: 实现栈匹配算法
        // 提示1: 使用stack<char>存储左括号
        // 提示2: 使用哈希表建立括号配对关系
        // 提示3: 遇到左括号入栈，遇到右括号检查栈顶配对
        
        return false;
    }
    
    // 参考实现(隐藏)
    bool isValidReference(string s) {
            stack<char> st;
            for(char c:s) {
                 if(c == '{' || c == '[' || c == '(') {
                     st.push(c);
                 } else {
                     // ❌ 修复：必须先检查栈是否为空
                     if(st.empty()) return false;
                     char top = st.top();
                     if(c =='}' && top !='{') return false;
                     if(c ==']' && top !='[') return false;
                     if(c ==')' && top !='(') return false;
                     st.pop();
                 }
            }
            return st.empty(); 
    }
};

// 测试用例
void testSolution() {
    Solution sol;
    
    cout << "🧪 测试 20. 有效的括号" << endl;
    cout << "===================" << endl;
    
    // 测试用例1: 基本情况
    string s1 = "()";
    cout << "Test 1: \"" << s1 << "\" -> " << (sol.isValidReference(s1) ? "true" : "false") << " (Expected: true)" << endl;
    
    // 测试用例2: 多种括号
    string s2 = "()[]{}" ;
    cout << "Test 2: \"" << s2 << "\" -> " << (sol.isValidReference(s2) ? "true" : "false") << " (Expected: true)" << endl;
    
    // 测试用例3: 不匹配
    string s3 = "(]";
    cout << "Test 3: \"" << s3 << "\" -> " << (sol.isValidReference(s3) ? "true" : "false") << " (Expected: false)" << endl;
    
    // 测试用例4: 嵌套括号
    string s4 = "([{}])";
    cout << "Test 4: \"" << s4 << "\" -> " << (sol.isValidReference(s4) ? "true" : "false") << " (Expected: true)" << endl;
    
    // 测试用例5: 顺序错误
    string s5 = "([)]";
    cout << "Test 5: \"" << s5 << "\" -> " << (sol.isValidReference(s5) ? "true" : "false") << " (Expected: false)" << endl;
    
    // 测试用例6: 单个字符
    string s6 = "(";
    cout << "Test 6: \"" << s6 << "\" -> " << (sol.isValidReference(s6) ? "true" : "false") << " (Expected: false)" << endl;
    
    // 测试用例7: 空字符串
    string s7 = "";
    cout << "Test 7: \"\" -> " << (sol.isValidReference(s7) ? "true" : "false") << " (Expected: true)" << endl;
    
    // 测试用例8: 复杂嵌套
    string s8 = "{[()]}";
    cout << "Test 8: \"" << s8 << "\" -> " << (sol.isValidReference(s8) ? "true" : "false") << " (Expected: true)" << endl;
}

// 算法演示
void demonstrateAlgorithm() {
    cout << "\n📚 栈匹配算法演示" << endl;
    cout << "=================" << endl;
    
    string s = "([{}])";
    cout << "字符串: \"" << s << "\"" << endl;
    cout << "目标: 判断括号是否有效匹配" << endl << endl;
    
    stack<char> st;
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    
    cout << "栈匹配过程:" << endl;
    bool valid = true;
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        cout << "步骤 " << (i + 1) << ": 处理字符 '" << c << "'" << endl;
        
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
            cout << "  左括号 -> 入栈" << endl;
        } else {
            if (st.empty()) {
                cout << "  右括号但栈为空 -> 无效" << endl;
                valid = false;
                break;
            }
            
            char top = st.top();
            if (top == pairs[c]) {
                st.pop();
                cout << "  右括号 '" << c << "' 与栈顶 '" << top << "' 匹配 -> 出栈" << endl;
            } else {
                cout << "  右括号 '" << c << "' 与栈顶 '" << top << "' 不匹配 -> 无效" << endl;
                valid = false;
                break;
            }
        }
        
        cout << "  当前栈大小: " << st.size() << endl << endl;
    }
    
    if (valid) {
        if (st.empty()) {
            cout << "🎯 所有括号匹配完成，栈为空 -> 有效" << endl;
        } else {
            cout << "🎯 存在未匹配的左括号 -> 无效" << endl;
        }
    }
}

// 栈的基本操作演示
void demonstrateStack() {
    cout << "\n📖 栈(Stack)基本操作" << endl;
    cout << "==================" << endl;
    cout << R"(
栈的特点：后进先出(LIFO - Last In First Out)

基本操作：
1. push(x)  : 将元素x压入栈顶
2. pop()    : 弹出栈顶元素
3. top()    : 获取栈顶元素(不弹出)
4. empty()  : 判断栈是否为空
5. size()   : 获取栈的大小

C++ STL 栈的使用：
```cpp
#include <stack>

stack<char> st;
st.push('(');           // 入栈
char top = st.top();    // 获取栈顶
st.pop();               // 出栈
bool isEmpty = st.empty(); // 判空
```

括号匹配算法模板：
```cpp
bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> pairs = {
        {')', '('}, {']', '['}, {'}', '{'}
    };
    
    for (char c : s) {
        if (isLeft(c)) {
            st.push(c);
        } else {
            if (st.empty() || st.top() != pairs[c]) {
                return false;
            }
            st.pop();
        }
    }
    
    return st.empty();
}
```
)" << endl;
}

int main() {
    cout << "🚀 LeetCode 20. 有效的括号" << endl;
    cout << "=========================" << endl;
    cout << "🎯 这是栈(Stack)数据结构的经典应用！" << endl;
    cout << "💡 重点理解后进先出(LIFO)的匹配机制" << endl << endl;
    
    testSolution();
    demonstrateAlgorithm();
    demonstrateStack();
    
    return 0;
}

/*
算法模板总结：

栈匹配模板：
```cpp
bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> closeToOpen = {
        {')', '('}, {']', '['}, {'}', '{'}
    };
    
    for (char c : s) {
        if (closeToOpen.count(c)) {
            // 右括号
            if (st.empty() || st.top() != closeToOpen[c]) {
                return false;
            }
            st.pop();
        } else {
            // 左括号
            st.push(c);
        }
    }
    
    return st.empty();
}
```

解题要点：
1. 识别左右括号的配对关系
2. 遇到左括号入栈，右括号检查匹配
3. 处理三种异常：栈空、不匹配、栈非空
4. 栈在括号匹配、表达式求值、递归模拟中应用广泛

专题归属：栈 + 字符串
难度评估：⭐⭐ (Easy难度，栈的经典入门题)
*/