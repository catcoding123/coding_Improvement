# 字符串专题

## 专题概述

字符串是编程中常见的数据类型，字符串算法在面试中频繁出现。本专题涵盖：
- **模式匹配**: KMP算法、Rabin-Karp算法
- **字符串处理**: 反转、去重、替换、分割
- **回文字符串**: 中心扩展、马拉车算法
- **字符统计**: 滑动窗口、哈希表应用

**核心思想**: 利用字符串的有序性和字符的ASCII特性，结合滑动窗口、双指针等技巧高效处理。

## 核心题目

### 3. 无重复字符的最长子串 (Medium) - 滑动窗口经典
**核心思想**: 滑动窗口+哈希表维护无重复窗口
```cpp
int lengthOfLongestSubstring(string s) {
    unordered_set<char> window;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        while (window.count(s[right])) {
            window.erase(s[left++]);
        }
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

### 5. 最长回文子串 (Medium) - 中心扩展
**核心思想**: 以每个字符为中心向两边扩展寻找回文
```cpp
string longestPalindrome(string s) {
    string result = "";
    
    for (int i = 0; i < s.length(); i++) {
        // 奇数长度回文
        string odd = expandAroundCenter(s, i, i);
        // 偶数长度回文
        string even = expandAroundCenter(s, i, i + 1);
        
        string longer = odd.length() > even.length() ? odd : even;
        if (longer.length() > result.length()) {
            result = longer;
        }
    }
    return result;
}

string expandAroundCenter(string s, int left, int right) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    return s.substr(left + 1, right - left - 1);
}
```

### 28. 找出字符串中第一个匹配项的下标 (Easy) - KMP算法
**核心思想**: 利用已匹配信息避免重复比较
```cpp
vector<int> getNext(string pattern) {
    vector<int> next(pattern.length(), 0);
    int j = 0;
    
    for (int i = 1; i < pattern.length(); i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    
    vector<int> next = getNext(needle);
    int j = 0;
    
    for (int i = 0; i < haystack.length(); i++) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = next[j - 1];
        }
        if (haystack[i] == needle[j]) {
            j++;
        }
        if (j == needle.length()) {
            return i - j + 1;
        }
    }
    return -1;
}
```

### 76. 最小覆盖子串 (Hard) - 滑动窗口+字符计数
**核心思想**: 滑动窗口维护包含所有目标字符的最小窗口
```cpp
string minWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    
    int left = 0, right = 0, valid = 0;
    int start = 0, len = INT_MAX;
    
    while (right < s.length()) {
        char c = s[right++];
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c]) {
                valid++;
            }
        }
        
        while (valid == need.size()) {
            if (right - left < len) {
                start = left;
                len = right - left;
            }
            
            char d = s[left++];
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}
```

## 字符串处理模板

### 滑动窗口模板
```cpp
string slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    
    int left = 0, right = 0, valid = 0;
    
    while (right < s.length()) {
        char c = s[right++];
        // 更新窗口
        
        while (窗口需要收缩) {
            char d = s[left++];
            // 更新窗口
        }
    }
}
```

### 双指针模板
```cpp
// 字符串反转
void reverse(string& s, int left, int right) {
    while (left < right) {
        swap(s[left++], s[right--]);
    }
}

// 回文检查
bool isPalindrome(string s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left++] != s[right--]) {
            return false;
        }
    }
    return true;
}
```

### 字符统计模板
```cpp
// 字符频率统计
unordered_map<char, int> charCount(string s) {
    unordered_map<char, int> count;
    for (char c : s) {
        count[c]++;
    }
    return count;
}

// 字符数组统计（ASCII）
vector<int> charArray(string s) {
    vector<int> count(256, 0);
    for (char c : s) {
        count[c]++;
    }
    return count;
}
```

## 常用字符串技巧

### 1. 字符串构建
```cpp
// 高效拼接
string build(vector<string>& parts) {
    string result;
    int totalLen = 0;
    for (string& part : parts) {
        totalLen += part.length();
    }
    result.reserve(totalLen);  // 预分配空间
    
    for (string& part : parts) {
        result += part;
    }
    return result;
}
```

### 2. 字符替换
```cpp
// 原地替换
string replaceSpaces(string s) {
    int spaceCount = 0;
    for (char c : s) {
        if (c == ' ') spaceCount++;
    }
    
    int newLen = s.length() + spaceCount * 2;
    s.resize(newLen);
    
    int i = s.length() - 3 * spaceCount - 1;
    int j = newLen - 1;
    
    while (i >= 0) {
        if (s[i] == ' ') {
            s[j--] = '0';
            s[j--] = '2';
            s[j--] = '%';
        } else {
            s[j--] = s[i];
        }
        i--;
    }
    return s;
}
```

### 3. 子串查找
```cpp
// 所有子串出现位置
vector<int> findAllOccurrences(string text, string pattern) {
    vector<int> result;
    size_t pos = text.find(pattern, 0);
    
    while (pos != string::npos) {
        result.push_back(pos);
        pos = text.find(pattern, pos + 1);
    }
    return result;
}
```

## 回文相关算法

### 马拉车算法 (Manacher)
```cpp
string preprocess(string s) {
    string result = "^";
    for (char c : s) {
        result += "#" + string(1, c);
    }
    result += "#$";
    return result;
}

string longestPalindrome(string s) {
    string T = preprocess(s);
    int n = T.length();
    vector<int> P(n, 0);
    int center = 0, right = 0;
    
    for (int i = 1; i < n - 1; i++) {
        if (i < right) {
            P[i] = min(right - i, P[2 * center - i]);
        }
        
        while (T[i + P[i] + 1] == T[i - P[i] - 1]) {
            P[i]++;
        }
        
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }
    
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}
```

## 易错点总结

1. **字符串越界**: 访问字符前检查索引有效性
2. **空字符串**: 处理空字符串的边界情况
3. **字符编码**: 注意ASCII值和Unicode的区别
4. **滑动窗口**: 窗口扩展和收缩的条件判断
5. **KMP算法**: next数组的正确构建
6. **字符统计**: 使用合适的数据结构（数组vs哈希表）

## 时间复杂度分析

- **暴力匹配**: O(nm) - n是文本长度，m是模式长度
- **KMP算法**: O(n+m) - 线性时间复杂度
- **滑动窗口**: O(n) - 每个字符最多访问两次
- **中心扩展**: O(n²) - 每个中心最多扩展n次
- **马拉车算法**: O(n) - 线性时间找最长回文

## 相关题目分类

- **子串查找**: 28实现strStr、214最短回文串、459重复的子字符串
- **滑动窗口**: 3无重复字符最长子串、76最小覆盖子串、567字符串的排列
- **回文问题**: 5最长回文子串、9回文数、125验证回文串、131分割回文串
- **字符串变换**: 151翻转字符串里的单词、186翻转字符串里的单词II
- **模式匹配**: 44通配符匹配、10正则表达式匹配
- **字符统计**: 242有效的字母异位词、49字母异位词分组、438找到字符串中所有字母异位词

---
*字符串算法的核心是充分利用字符的有序性和统计性质，配合高效的搜索和匹配策略*