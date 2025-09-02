/*
LeetCode 49. 字母异位词分组
Difficulty: Medium
Link: https://leetcode.cn/problems/group-anagrams/

题目描述：
给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。

字母异位词是通过重新排列不同单词或短语的字母而形成的单词或短语，通常只使用所有原字母恰好一次。

示例 1:
输入: strs = ["eat","tea","tan","ate","nat","bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

示例 2:
输入: strs = [""]
输出: [[""]]

示例 3:
输入: strs = ["a"]
输出: [["a"]]

约束条件：
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] 仅包含小写字母

算法分析：
时间复杂度：O(NK log K) - N个字符串，每个长度K需要排序
空间复杂度：O(NK) - 哈希表存储所有字符串

核心思想：
1. 异位词的特点：字符种类和数量相同，顺序不同
2. 方法1：排序作为key - 异位词排序后结果相同
3. 方法2：字符计数作为key - 统计每个字符出现次数

思考要点：
1. 如何判断两个字符串是异位词？
2. 如何设计哈希表的key来分组？
3. 排序和计数两种方法的优缺点？

易错点：
1. 空字符串的处理
2. 哈希表key的设计（排序字符串 vs 字符计数字符串）
3. 返回结果的格式（vector<vector<string>>）

相关题目：
- 242. 有效的字母异位词
- 438. 找到字符串中所有字母异位词
- 567. 字符串的排列
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 方法1：排序分组法
    vector<vector<string>> groupAnagramsSort(vector<string>& strs) {
            unordered_map<string, vector<string>> str_map;
            for(auto& str:strs) {
                auto key = str;
                sort(key.begin(),key.end());
                str_map[key].push_back(str);
            }
            vector<vector<string>> result;
            for(auto& pair : str_map) {
                result.push_back(pair.second);
            }
            return result;
    }
    
    // 方法2：字符计数分组法
    vector<vector<string>> groupAnagramsCount(vector<string>& strs) {
        // TODO: 使用字符计数字符串作为哈希表的key
        // 提示1: 统计每个字符串中a-z的出现次数
        // 提示2: 将计数数组转换为字符串作为key
        // 提示3: 相同计数的字符串为异位词
        
        vector<vector<string>> result;
        return result;
    }
    
    // 辅助函数：生成字符计数key
    string getCountKey(string& str) {
        // TODO: 实现字符计数key生成
        // 提示: 创建长度26的计数数组，转换为字符串
        
        return "";
    }
    
    // 主函数
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 推荐先实现排序方法，再尝试计数方法
        return groupAnagramsSort(strs);
    }
};

// 测试用例
void testSolution() {
    Solution sol;
    
    cout << "🧪 测试 49. 字母异位词分组" << endl;
    cout << "========================" << endl;
    
    // 测试用例1: 基本情况
    vector<string> strs1 = {"eat","tea","tan","ate","nat","bat"};
    auto result1 = sol.groupAnagrams(strs1);
    cout << "Test 1: [\"eat\",\"tea\",\"tan\",\"ate\",\"nat\",\"bat\"]" << endl;
    cout << "Result: [";
    for (auto& group : result1) {
        cout << "[";
        for (int i = 0; i < group.size(); i++) {
            cout << "\"" << group[i] << "\"";
            if (i < group.size() - 1) cout << ",";
        }
        cout << "]";
    }
    cout << "]" << endl << endl;
    
    // 测试用例2: 空字符串
    vector<string> strs2 = {""};
    auto result2 = sol.groupAnagrams(strs2);
    cout << "Test 2: [\"\"]" << endl;
    cout << "Expected: [[\"\"]]" << endl << endl;
    
    // 测试用例3: 单个字符
    vector<string> strs3 = {"a"};
    auto result3 = sol.groupAnagrams(strs3);
    cout << "Test 3: [\"a\"]" << endl;
    cout << "Expected: [[\"a\"]]" << endl << endl;
}

// 算法思路提示
void showHints() {
    cout << "\n💡 算法思路提示" << endl;
    cout << "===============" << endl;
    cout << R"(
异位词的关键特征：
- 包含相同的字符
- 每个字符出现次数相同
- 只是字符顺序不同

方法1：排序分组法
1. 对每个字符串进行排序
2. 排序后的字符串作为哈希表的key
3. 异位词排序后的结果相同
4. 将原字符串加入对应的分组

方法2：字符计数分组法
1. 统计每个字符串中a-z的出现次数
2. 将计数数组转换为字符串作为key
3. 相同计数的字符串是异位词
4. 这种方法避免了排序，在某些情况下更高效

实现要点：
- 使用unordered_map<string, vector<string>>存储分组
- 注意处理空字符串的情况
- 最后需要将map的值转换为vector<vector<string>>格式

时间复杂度对比：
- 排序法：O(NK log K)，K是字符串平均长度
- 计数法：O(NK)，但常数因子较大

选择建议：
- 字符串较短时，排序法更简洁
- 字符串较长时，计数法更高效
)" << endl;
}

int main() {
    cout << "🚀 LeetCode 49. 字母异位词分组" << endl;
    cout << "==============================" << endl;
    cout << "🎯 哈希表分组的经典应用！" << endl;
    cout << "💡 重点理解如何设计合适的key来识别异位词" << endl << endl;
    
    testSolution();
    showHints();
    
    return 0;
}

/*
专题归属：哈希表 + 字符串
难度评估：⭐⭐⭐ (Medium难度，哈希表分组经典题)
核心技能：异位词识别、哈希表key设计、分组算法
*/