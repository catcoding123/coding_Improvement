/**
 * 322. 零钱兑换 - 专项记忆强化训练
 * 
 * 🎯 专门针对 "helpResult != -1" 检查的遗忘问题
 * 
 * 问题根源：
 * - 忘记检查无解状态 (-1)
 * - 直接使用子问题结果进行运算
 * - 导致无解状态被误认为最优解
 * 
 * 记忆口诀：无解传递毁全局，-1检查是关键 ⭐⭐⭐
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /**
     * 🔥 记忆化搜索版本 - 重点掌握无解检查
     */
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, -2);  // -2表示未计算，-1表示无解
        int result = helper(coins, amount, memo);
        return result == -1 ? -1 : result;
    }
    
private:
    int helper(vector<int>& coins, int amount, vector<int>& memo) {
        // 边界条件
        if (amount == 0) return 0;
        if (amount < 0) return -1;
        
        // 检查缓存
        if (memo[amount] != -2) return memo[amount];
        
        int result = INT_MAX;
        
        for (int coin : coins) {
            // ⭐⭐⭐ 关键步骤：无解检查模式
            // 步骤1: 先获取子问题结果
            int helpResult = helper(coins, amount - coin, memo);
            
            // 步骤2: 检查子问题是否有解 (防止-1参与运算!)
            if (helpResult != -1) {
                // 步骤3: 只有有解时才参与最值比较
                result = min(result, helpResult + 1);
            }
            
            /* ❌ 错误写法 - 忘记检查会导致严重问题:
             * int subResult = helper(coins, amount - coin, memo) + 1;
             * result = min(result, subResult);
             * 
             * 问题: 当helper返回-1时，-1+1=0，被误认为最优解！
             */
        }
        
        // 缓存结果：如果没有找到解决方案，返回-1
        memo[amount] = (result == INT_MAX) ? -1 : result;
        return memo[amount];
    }
};

/**
 * 🧠 记忆强化练习
 */
class MemoryDrill {
public:
    /**
     * 练习1: 识别错误代码
     */
    void identifyErrors() {
        cout << "=== 错误识别训练 ===" << endl;
        cout << "以下代码有什么问题？" << endl;
        cout << endl;
        cout << "int helpResult = helper(amount - coin) + 1;" << endl;
        cout << "result = min(result, helpResult);" << endl;
        cout << endl;
        cout << "答案: 忘记检查helper返回值是否为-1(无解)" << endl;
        cout << "后果: -1+1=0被误认为最优解" << endl;
        cout << endl;
    }
    
    /**
     * 练习2: 默写正确模式
     */
    void writeCorrectPattern() {
        cout << "=== 正确模式默写 ===" << endl;
        cout << "请默写无解检查的三步模式:" << endl;
        cout << "1. int helpResult = helper(...);" << endl;
        cout << "2. if (helpResult != -1) {" << endl;
        cout << "3.     result = min(result, helpResult + 1);" << endl;
        cout << "4. }" << endl;
        cout << endl;
        cout << "记忆要点:" << endl;
        cout << "- 先取结果，再检查，后运算" << endl;
        cout << "- -1是状态标记，不是数值" << endl;
        cout << "- 无解会传递，必须阻断" << endl;
        cout << endl;
    }
    
    /**
     * 练习3: 口诀强化
     */
    void reciteSlogan() {
        cout << "=== 记忆口诀强化 ===" << endl;
        cout << "🎯 核心口诀: 无解传递毁全局，-1检查是关键" << endl;
        cout << endl;
        cout << "扩展理解:" << endl;
        cout << "- 无解传递: -1状态会在递归中传递" << endl;
        cout << "- 毁全局: 一个无解被当作有效值会破坏整个结果" << endl;
        cout << "- -1检查: 必须检查返回值的有效性" << endl;
        cout << "- 是关键: 这是记忆化搜索的核心环节" << endl;
        cout << endl;
    }
    
    /**
     * 练习4: 场景应用
     */
    void scenarioApplication() {
        cout << "=== 应用场景扩展 ===" << endl;
        cout << "以下题目都需要无解检查:" << endl;
        cout << "- 322. 零钱兑换 (金额无法组成)" << endl;
        cout << "- 279. 完全平方数 (理论上都有解)" << endl;
        cout << "- 518. 零钱兑换II (组合数问题)" << endl;
        cout << "- 背包问题变种 (容量无法填满)" << endl;
        cout << endl;
        cout << "通用模式: 凡是可能返回"无解"的递归，都要检查!" << endl;
        cout << endl;
    }
    
    /**
     * 运行所有练习
     */
    void runAllDrills() {
        identifyErrors();
        writeCorrectPattern();
        reciteSlogan();
        scenarioApplication();
        
        cout << "=== 总结 ===" << endl;
        cout << "下次写322题记忆化版本时，在写helper调用的瞬间就要想到:" << endl;
        cout << "1. 这个调用可能返回-1吗？" << endl;
        cout << "2. 我需要检查helpResult != -1吗？" << endl;
        cout << "3. 如果忘记检查会发生什么？" << endl;
        cout << endl;
        cout << "🎯 目标: 形成条件反射，看到helper调用就想到无解检查！" << endl;
    }
};

// 测试用例
int main() {
    // 先进行记忆强化训练
    MemoryDrill drill;
    drill.runAllDrills();
    
    // 再进行实际测试
    Solution solution;
    
    cout << "\n=== 实际测试 ===" << endl;
    
    // 测试用例1: 有解情况
    vector<int> coins1 = {1, 3, 4};
    int amount1 = 6;
    cout << "coins=[1,3,4], amount=6: " << solution.coinChange(coins1, amount1) << endl;
    
    // 测试用例2: 无解情况 (重点测试)
    vector<int> coins2 = {2};
    int amount2 = 3;
    cout << "coins=[2], amount=3: " << solution.coinChange(coins2, amount2) << endl;
    
    // 测试用例3: 边界情况
    vector<int> coins3 = {1};
    int amount3 = 0;
    cout << "coins=[1], amount=0: " << solution.coinChange(coins3, amount3) << endl;
    
    cout << "\n如果输出正确(2, -1, 0)，说明无解检查工作正常！" << endl;
    
    return 0;
}

/**
 * 🎯 学习要点总结:
 * 
 * 1. 问题本质:
 *    - -1是"无解标记"，不是数值
 *    - 无解状态参与运算会产生错误结果
 * 
 * 2. 记忆化搜索三步法:
 *    - 取结果: int helpResult = helper(...)
 *    - 检查: if (helpResult != -1)
 *    - 运算: result = combine(result, helpResult + cost)
 * 
 * 3. 记忆口诀:
 *    - "无解传递毁全局，-1检查是关键"
 * 
 * 4. 预防措施:
 *    - 看到helper调用立即想到无解检查
 *    - 对特殊返回值保持敏感
 *    - 建立模板化编程习惯
 * 
 * 5. 扩展应用:
 *    - 任何可能返回"无效状态"的递归都需要检查
 *    - 不仅限于-1，还包括INT_MAX等特殊值
 */