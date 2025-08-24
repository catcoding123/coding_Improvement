/*
LeetCode 200. 岛屿数量 (Medium)
https://leetcode.cn/problems/number-of-islands/

题目描述：
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1：
输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

示例 2：
输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

约束条件：
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 300
- grid[i][j] 的值为 '0' 或 '1'

算法分析：
时间复杂度：O(M×N) - 每个格子最多访问一次
空间复杂度：O(M×N) - 最坏情况下递归栈深度（全为陆地时）
核心难点：图的连通分量计算，DFS/BFS遍历策略

关键洞察：
1. 图论建模：二维网格→无向图，相邻陆地→图中边连接
2. 连通分量：每个岛屿就是一个连通分量
3. 遍历策略：DFS深度优先 vs BFS广度优先
4. 标记机制：避免重复访问已遍历的陆地

算法思维对比：
- 回溯算法：在解空间中搜索所有可能解
- 图论DFS：在图中搜索连通的节点集合
- 共同点：都使用递归/栈进行深度优先搜索
- 区别：回溯有撤销操作，图遍历有标记机制

与回溯算法的联系：
- 131题分割：在字符串上做决策
- 200题岛屿：在二维网格上做搜索
- 技能迁移：递归思维、边界处理、状态管理

图论核心概念：
- 节点(顶点)：网格中的每个格子
- 边：相邻格子之间的连接关系
- 连通分量：彼此连接的节点集合
- 图遍历：系统性访问图中所有节点

易错点预测：
1. 边界检查：数组越界的判断条件
2. 标记机制：如何避免重复访问同一格子
3. 方向遍历：上下左右四个方向的正确实现
4. 递归终止：何时停止DFS搜索
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        // TODO: 实现岛屿数量计算
        // 可以选择DFS或BFS实现
        // 1. 遍历整个网格
        // 2. 遇到'1'时，启动DFS/BFS标记整个岛屿
        // 3. 每次标记完一个岛屿，计数器+1
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int lands_cnt =0;

        for (int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == '1') {
                    lands_cnt++;
                    dfs(grid, i,j);
                    // bfs(grid,i,j);
                }
            }
        }
        return lands_cnt;
    }
    
private:
    // 方法1：DFS深度优先搜索
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // TODO: 实现DFS标记连通的陆地
        // 1. 边界检查和终止条件
        // 2. 标记当前格子为已访问
        // 3. 递归搜索四个方向的相邻格子
        if(i<0 || j<0 || i>=grid.size() || j >= grid[0].size() || grid[i][j] =='0') return;
        grid[i][j] = '0';
        dfs(grid, i-1,j);
        dfs(grid, i+1,j);
        dfs(grid, i,j-1);
        dfs(grid, i,j+1);
    }
    
    // 方法2：BFS广度优先搜索  
    void bfs(vector<vector<char>>& grid, int i, int j) {
        // TODO: 实现BFS标记连通的陆地
        // 1. 使用队列存储待访问的格子
        // 2. 标记起始格子并加入队列
        // 3. 循环处理队列中的格子，搜索其相邻格子
        std::queue<pair<int,int>> q;
        grid[i][j] = '0';  // 需要在这里先标记起始格子
        q.push({i,j});
        while(!q.empty()) {
            auto [i,j] = q.front();
            q.pop();
            if(i<0||j<0) continue;
            if(i>=grid.size() || j >=grid[0].size() || grid[i][j]=='0') continue;
            // if(i<0 || j<0 || i>=grid.size() || j >=grid[0].size() || grid[i][j]=='0') continue;
            grid[i][j]='0';
            q.push({i-1,j});
            q.push({i+1,j});
            q.push({i,j-1});
            q.push({i,j+1});
        }
    }
};

// 优化版Solution：使用方向数组简化代码
class SolutionOptimized {
public:
    int numIslands(vector<vector<char>>& grid) {
        // TODO: 实现优化版本
        // 可以使用方向数组等技巧简化代码
        
    }
    
private:
    // 方向数组：上、下、左、右
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    void dfsOptimized(vector<vector<char>>& grid, int i, int j) {
        // TODO: 使用方向数组的优化DFS实现
        // 1. 边界检查和终止条件
        // 2. 标记当前格子
        // 3. 使用directions数组遍历四个方向
        
    }
};

void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution solution;
    SolutionOptimized solutionOpt;
    
    // 测试用例1
    cout << "=== 测试用例1: 单个大岛屿 ===" << endl;
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    cout << "网格:" << endl;
    printGrid(grid1);
    cout << "期望输出: 1" << endl;
    cout << "实际输出: " << solution.numIslands(grid1) << endl;
    cout << endl;
    
    // 测试用例2
    cout << "=== 测试用例2: 多个独立岛屿 ===" << endl;
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "网格:" << endl;
    printGrid(grid2);
    cout << "期望输出: 3" << endl;
    cout << "实际输出: " << solution.numIslands(grid2) << endl;
    cout << endl;
    
    // 测试用例3: 边界情况
    cout << "=== 测试用例3: 全为水 ===" << endl;
    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'},
        {'0','0','0'}
    };
    cout << "网格:" << endl;
    printGrid(grid3);
    cout << "期望输出: 0" << endl;
    cout << "实际输出: " << solution.numIslands(grid3) << endl;
    cout << endl;
    
    // 测试用例4: 全为陆地
    cout << "=== 测试用例4: 全为陆地 ===" << endl;
    vector<vector<char>> grid4 = {
        {'1','1','1'},
        {'1','1','1'},
        {'1','1','1'}
    };
    cout << "网格:" << endl;
    printGrid(grid4);
    cout << "期望输出: 1" << endl;
    cout << "实际输出: " << solution.numIslands(grid4) << endl;
    cout << endl;
    
    // 测试用例5: 复杂形状岛屿
    cout << "=== 测试用例5: 复杂岛屿形状 ===" << endl;
    vector<vector<char>> grid5 = {
        {'1','1','0','1','1'},
        {'1','0','0','0','1'},
        {'0','0','1','0','0'},
        {'1','0','1','1','1'}
    };
    cout << "网格:" << endl;
    printGrid(grid5);
    cout << "期望输出: 4" << endl;
    cout << "实际输出: " << solution.numIslands(grid5) << endl;
    cout << endl;
    
    cout << "=== 图论算法与回溯算法对比 ===" << endl;
    cout << " 共同点:" << endl;
    cout << "  - 递归思维: 将大问题分解为子问题" << endl;
    cout << "  - 搜索策略: 深度优先的系统性搜索" << endl;
    cout << "  - 边界处理: 递归终止条件的精确设计" << endl;
    cout << " 核心差异:" << endl;
    cout << "  - 回溯: 解空间搜索 + 撤销操作" << endl;
    cout << "  - 图遍历: 连通性搜索 + 标记机制" << endl;
    cout << "  - 回溯: 寻找所有可能解" << endl;
    cout << "  - 图遍历: 访问所有连通节点" << endl;
    cout << endl;
    
    cout << "=== 图论算法入门总结 ===" << endl;
    cout << " 核心概念建立:" << endl;
    cout << "  - 图的建模: 现实问题 → 图结构" << endl;
    cout << "  - 连通分量: 彼此连接的节点集合" << endl;
    cout << "  - 图遍历: DFS深度优先 vs BFS广度优先" << endl;
    cout << "  - 标记机制: 避免重复访问的关键技巧" << endl;
    cout << " 技能迁移:" << endl;
    cout << "  - 从回溯算法的递归思维迁移到图遍历" << endl;
    cout << "  - 边界处理和状态管理的经验复用" << endl;
    cout << "  - 问题建模能力的进一步提升" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_200 problem_200_template.cpp && ./problem_200

学习要点：
1. 理解图论的基本概念：节点、边、连通分量
2. 掌握DFS和BFS两种图遍历策略
3. 学会二维网格问题的图论建模方法
4. 理解标记机制在图遍历中的重要作用

核心突破：
- 图论思维：从线性/树形结构扩展到图结构
- 连通性概念：理解连通分量的数学定义
- 遍历策略：掌握DFS和BFS的不同应用场景
- 建模能力：将现实问题抽象为图论问题

预期收获：
- 建立完整的图论基础概念
- 掌握图遍历的标准算法实现
- 理解DFS与回溯算法的联系和区别
- 为后续复杂图论算法打下基础

技术意义：
200题作为图论算法的经典入门题，帮助建立从回溯算法到图论算法的思维桥梁，
标志着算法学习从单一数据结构向复杂图结构的重要跃迁。
*/