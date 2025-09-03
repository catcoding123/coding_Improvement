/*
146. LRU 缓存 (Medium)
https://leetcode.cn/problems/lru-cache/

题目描述：
请你设计并实现一个满足 LRU (最近最少使用) 缓存约束的数据结构。
实现 LRUCache 类：
- LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
- int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
- void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；
  如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，
  则应该 逐出 最近最少使用的关键字。

函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

示例：
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4

约束条件：
- 1 <= capacity <= 3000
- 0 <= key <= 10000
- 0 <= value <= 10^5
- 最多调用 2 * 10^5 次 get 和 put

专题归属：数据结构设计 - 哈希表+双向链表
相关题目：460.LFU缓存、432.全O(1)的数据结构

算法分析：
思路提示：
1. 核心思想：哈希表 + 双向链表的组合
2. 哈希表：实现O(1)的查找
3. 双向链表：实现O(1)的插入、删除、移动操作
4. LRU策略：最近使用的放在链表头，最少使用的在链表尾

时间复杂度：O(1) - get和put操作
空间复杂度：O(capacity) - 哈希表和链表的空间

易错点：
1. 双向链表的插入、删除操作的指针处理
2. get操作后需要将节点移到链表头（更新使用时间）
3. 容量满时的淘汰策略
4. 更新已存在key时的处理逻辑
*/

#include <unordered_map>
#include <iostream>
using namespace std;

// 双向链表节点定义
struct DListNode {
    int key, value;
    DListNode* prev;
    DListNode* next;
    DListNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DListNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, DListNode*> cache; // key -> node
    DListNode* head; // 虚拟头节点
    DListNode* tail; // 虚拟尾节点
    
    // TODO: 实现双向链表的基本操作
    
    // 在链表头部添加节点
    void addToHead(DListNode* node) {
        // TODO: 实现添加到头部的逻辑
        // 提示：在head和head->next之间插入node
    }
    
    // 删除指定节点
    void removeNode(DListNode* node) {
        // TODO: 实现删除节点的逻辑
        // 提示：修改前后节点的指针连接
    }
    
    // 将节点移动到头部
    void moveToHead(DListNode* node) {
        // TODO: 实现移动到头部的逻辑
        // 提示：先删除，再添加到头部
    }
    
    // 删除尾部节点
    DListNode* removeTail() {
        // TODO: 实现删除尾部节点的逻辑
        // 提示：删除tail->prev节点并返回
        return nullptr;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        // TODO: 初始化虚拟头尾节点
        // 提示：创建head和tail节点，并建立连接
    }
    
    int get(int key) {
        // TODO: 实现get操作
        // 提示：
        // 1. 在哈希表中查找key
        // 2. 如果存在，将节点移动到头部（标记为最近使用）
        // 3. 返回value或-1
        
        return -1;
    }
    
    void put(int key, int value) {
        // TODO: 实现put操作
        // 提示：
        // 1. 如果key已存在：更新value，移动到头部
        // 2. 如果key不存在：
        //    - 创建新节点
        //    - 如果容量已满，删除尾部节点
        //    - 将新节点添加到头部
        //    - 更新哈希表
    }
    
    // 辅助函数：打印当前缓存状态
    void printCache() {
        cout << "Cache: ";
        DListNode* curr = head->next;
        while (curr != tail) {
            cout << "{" << curr->key << "=" << curr->value << "} ";
            curr = curr->next;
        }
        cout << endl;
    }
};

// 测试用例
int main() {
    // 测试用例1: 基本操作
    cout << "=== 测试用例1: 基本操作 ===" << endl;
    LRUCache lRUCache(2);
    
    lRUCache.put(1, 1);
    lRUCache.printCache(); // {1=1}
    
    lRUCache.put(2, 2);
    lRUCache.printCache(); // {2=2} {1=1}
    
    cout << "get(1): " << lRUCache.get(1) << endl; // 返回 1
    lRUCache.printCache(); // {1=1} {2=2}
    
    lRUCache.put(3, 3); // 淘汰key=2
    lRUCache.printCache(); // {3=3} {1=1}
    
    cout << "get(2): " << lRUCache.get(2) << endl; // 返回 -1
    
    lRUCache.put(4, 4); // 淘汰key=1
    lRUCache.printCache(); // {4=4} {3=3}
    
    cout << "get(1): " << lRUCache.get(1) << endl; // 返回 -1
    cout << "get(3): " << lRUCache.get(3) << endl; // 返回 3
    cout << "get(4): " << lRUCache.get(4) << endl; // 返回 4
    
    // 测试用例2: 更新已存在的key
    cout << "\n=== 测试用例2: 更新已存在的key ===" << endl;
    LRUCache cache2(2);
    cache2.put(1, 1);
    cache2.put(2, 2);
    cache2.put(1, 10); // 更新key=1的值
    cache2.printCache(); // {1=10} {2=2}
    cout << "get(1): " << cache2.get(1) << endl; // 返回 10
    
    return 0;
}

/*
学习重点：
1. 理解LRU缓存的基本原理和应用场景
2. 掌握哈希表+双向链表的经典组合
3. 熟练处理双向链表的指针操作
4. 理解虚拟头尾节点简化边界处理的技巧

设计要点：
1. 为什么选择双向链表？（支持O(1)删除任意节点）
2. 为什么需要虚拟头尾节点？（简化边界情况处理）
3. 如何保证O(1)时间复杂度？（哈希表查找+链表操作）

面试扩展：
1. 如何实现LFU缓存？
2. 如何处理多线程环境下的并发访问？
3. 实际系统中LRU缓存的应用场景？
4. 相比其他缓存淘汰策略的优缺点？
*/