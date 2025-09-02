/*
LeetCode 695. 岛屿的最大面积 (Medium)
https://leetcode.cn/problems/max-area-of-island/

题目描述：
给你一个大小为 m x n 的二进制矩阵 grid 。

岛屿是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。

岛屿的面积是岛上值为 1 的单元格的数目。

计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。

示例 1：
输入：grid = [
  [0,0,1,0,0,0,0,1,0,0,0,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,1,1,0,1,0,0,0,0,0,0,0,0],
  [0,1,0,0,1,1,0,0,1,0,1,0,0],
  [0,1,0,0,1,1,0,0,1,1,1,0,0],
  [0,0,0,0,0,0,0,0,0,0,1,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,0,0,0,0,0,0,1,1,0,0,0,0]
]
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直四个方向上相邻的陆地。

示例 2：
输入：grid = [[0,0,0,0,0,0,0,0]]
输出：0

约束条件：
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 50
- grid[i][j] 为 0 或 1

算法分析：
时间复杂度：O(M×N) - 每个格子最多访问一次
空间复杂度：O(M×N) - 最坏情况下递归栈深度（全为陆地时）
核心难点：图的连通分量面积计算，DFS/BFS遍历 + 计数返回

关键洞察：
1. 图论建模：与200题相同的网格→图的抽象
2. 连通分量计算：不仅找到岛屿，还要计算每个岛屿的面积
3. 面积累计策略：DFS递归返回值累计 vs 全局变量计数
4. 最大值维护：遍历过程中实时更新最大面积

算法思维对比：
- 200题岛屿数量：计算连通分量个数
- 695题岛屿面积：计算连通分量最大大小
- 共同点：图论建模、DFS/BFS遍历、标记机制
- 区别：返回值类型(计数 vs 面积)、聚合方式(累加 vs 最大值)

与200题的技能迁移：
- 图遍历技术：DFS/BFS实现直接复用
- 标记机制：避免重复访问的策略相同
- 边界处理：数组越界检查逻辑一致
- 新增能力：面积计算和最大值维护

DFS面积计算策略：
1. 递归返回值：每次DFS返回当前连通区域的面积
2. 累计策略：1(当前格子) + 四个方向DFS返回值之和
3. 优化思考：是否可以用全局变量替代返回值累计？

BFS面积计算策略：
1. 队列遍历：用队列实现广度优先搜索
2. 计数器：在队列循环中累计访问的格子数
3. 实现对比：BFS计数 vs DFS返回值的不同风格

易错点预测：
1. 面积计算：忘记返回当前格子的贡献(+1)
2. 递归累计：四个方向返回值的正确累加
3. 最大值更新：每个岛屿面积与全局最大值的比较时机
4. 边界处理：DFS递归终止条件要包含面积返回逻辑
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        // TODO: 实现最大岛屿面积计算
        // 1. 遍历整个网格
        // 2. 遇到'1'时，启动DFS/BFS计算当前岛屿面积
        // 3. 维护全局最大面积，与当前岛屿面积比较更新
        
    }
    
private:
    // 方法1：DFS深度优先搜索 + 递归返回面积
    int dfs(vector<vector<int>>& grid, int i, int j) {
        // TODO: 实现DFS计算连通岛屿面积
        // 1. 边界检查和终止条件
        // 2. 标记当前格子为已访问
        // 3. 递归搜索四个方向，累计返回的面积
        // 4. 返回当前连通区域的总面积
        
    }
    
    // 方法2：BFS广度优先搜索 + 计数器累计面积
    int bfs(vector<vector<int>>& grid, int i, int j) {
        // TODO: 实现BFS计算连通岛屿面积
        // 1. 使用队列存储待访问的格子
        // 2. 标记起始格子并加入队列
        // 3. 循环处理队列中的格子，累计计数器
        // 4. 返回当前连通区域的总面积
        std::queue<pair<int,int>> q;
        q.push({i,j});
        int area = 0;
        while(!q.empty()) {
            quto [i,j] = q.front();
            grid[i][j] = '0';
            q.pop();
            area++;
            if(i<0||j<0) continue;
            if(i>=grid.size()||j>=grid[0].size()||grid[i][j]=='0') continue;
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
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        // TODO: 实现优化版本
        // 可以使用方向数组等技巧简化代码
        
    }
    
private:
    // 方向数组：上、下、左、右
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int dfsOptimized(vector<vector<int>>& grid, int i, int j) {
        // TODO: 使用方向数组的优化DFS实现
        // 1. 边界检查和终止条件
        // 2. 标记当前格子
        // 3. 使用directions数组遍历四个方向
        // 4. 返回累计面积
        
    }
};

void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution solution;
    SolutionOptimized solutionOpt;
    
    // 测试用例1：示例1 - 复杂岛屿
    cout << "=== 测试用例1: 复杂岛屿形状 ===" << endl;
    vector<vector<int>> grid1 = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    cout << "网格:" << endl;
    printGrid(grid1);
    cout << "期望输出: 6" << endl;
    cout << "实际输出: " << solution.maxAreaOfIsland(grid1) << endl;
    cout << endl;
    
    // 测试用例2：全为水
    cout << "=== 测试用例2: 全为水 ===" << endl;
    vector<vector<int>> grid2 = {{0,0,0,0,0,0,0,0}};
    cout << "网格:" << endl;
    printGrid(grid2);
    cout << "期望输出: 0" << endl;
    cout << "实际输出: " << solution.maxAreaOfIsland(grid2) << endl;
    cout << endl;
    
    // 测试用例3：单个格子岛屿
    cout << "=== 测试用例3: 单个格子岛屿 ===" << endl;
    vector<vector<int>> grid3 = {
        {0,0,0},
        {0,1,0},
        {0,0,0}
    };
    cout << "网格:" << endl;
    printGrid(grid3);
    cout << "期望输出: 1" << endl;
    cout << "实际输出: " << solution.maxAreaOfIsland(grid3) << endl;
    cout << endl;
    
    // 测试用例4：全为陆地
    cout << "=== 测试用例4: 全为陆地 ===" << endl;
    vector<vector<int>> grid4 = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    cout << "网格:" << endl;
    printGrid(grid4);
    cout << "期望输出: 9" << endl;
    cout << "实际输出: " << solution.maxAreaOfIsland(grid4) << endl;
    cout << endl;
    
    // 测试用例5：多个岛屿面积对比
    cout << "=== 测试用例5: 多个岛屿大小对比 ===" << endl;
    vector<vector<int>> grid5 = {
        {1,1,0,1,1,1},
        {0,0,0,1,1,1},
        {1,0,0,0,0,0},
        {1,1,0,1,0,1},
        {1,1,0,1,0,1}
    };
    cout << "网格:" << endl;
    printGrid(grid5);
    cout << "期望输出: 6 (右上角的岛屿)" << endl;
    cout << "实际输出: " << solution.maxAreaOfIsland(grid5) << endl;
    cout << endl;
    
    cout << "=== 695题与200题对比总结 ===" << endl;
    cout << " 共同点:" << endl;
    cout << "  - 图论建模: 二维网格→无向图的抽象思维" << endl;
    cout << "  - 遍历策略: DFS/BFS图遍历的核心技术" << endl;
    cout << "  - 标记机制: 避免重复访问的关键技巧" << endl;
    cout << "  - 边界处理: 数组越界检查的一致逻辑" << endl;
    cout << " 技术进阶:" << endl;
    cout << "  - 200题: 连通分量计数 → 695题: 连通分量面积" << endl;
    cout << "  - 200题: void函数标记 → 695题: int函数返回面积" << endl;
    cout << "  - 200题: 简单计数 → 695题: 面积累计+最大值维护" << endl;
    cout << "  - 聚合策略: 个数累加 → 面积比较的算法设计差异" << endl;
    cout << endl;
    
    cout << "=== 图论算法进阶总结 ===" << endl;
    cout << " 技术栈扩展:" << endl;
    cout << "  - 连通分量计算: 从存在性判断到量化分析" << endl;
    cout << "  - 递归返回值: 从void标记到int累计的设计进化" << endl;
    cout << "  - 聚合算法: 计数、求和、最值的不同处理策略" << endl;
    cout << "  - 算法复用: 核心遍历逻辑的成功迁移和扩展" << endl;
    cout << " 解题思维:" << endl;
    cout << "  - 问题抽象: 面积计算→连通区域大小统计" << endl;
    cout << "  - 算法设计: 在已有框架基础上的功能扩展" << endl;
    cout << "  - 代码复用: 图遍历核心逻辑的高效迁移" << endl;
    
    return 0;
}

/*
编译运行命令：
g++ -std=c++11 -o problem_695 problem_695_template.cpp && ./problem_695

学习要点：
1. 理解连通分量的面积计算算法设计
2. 掌握DFS递归返回值累计的编程技巧
3. 学会在图遍历基础上扩展功能的方法
4. 理解不同聚合策略(计数vs面积)的算法差异

核心突破：
- 算法扩展思维：在200题基础上的功能增强
- 递归设计进阶：从void标记到int累计的跃升
- 聚合策略掌握：计数、面积、最值的不同处理
- 代码复用能力：图遍历核心逻辑的成功迁移

预期收获：
- 巩固图论基础概念和遍历技术
- 掌握连通分量面积计算的标准方法
- 理解算法功能扩展的设计思路
- 为更复杂图论问题积累技术基础

技术意义：
695题作为200题的完美进阶，在巩固图论基础的同时引入面积计算新要求，
展现了算法设计的扩展性和复用性，为后续复杂图论算法奠定扎实基础。
*/