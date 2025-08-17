# 链表专题

## 专题概述

链表是线性数据结构的重要组成部分，在算法面试中频繁出现。本专题涵盖：
- **Floyd判圈算法**: 快慢指针检测环、寻找环入口
- **链表反转**: 局部反转、分组反转、递归反转
- **多路归并**: 合并K个有序链表、分治思想
- **双指针技巧**: 快慢指针、前后指针、滑动窗口

**核心思想**: 善用指针操作，通过改变next指向重新组织链表结构，配合双指针技巧高效解决链表问题。

## 核心题目

### 142. 环形链表 II (Medium) - Floyd判圈算法 ⭐
**核心思想**: 快慢指针检测环 + 数学推导找环入口
**算法步骤**:
1. **第一阶段**: 快慢指针检测环存在
   - 快指针每次2步，慢指针每次1步
   - 有环必相遇，无环快指针到达null
2. **第二阶段**: 定位环入口
   - 从链表头和相遇点同时出发
   - 两指针都每次1步，相遇点就是环入口

**数学证明**: 
- 设头到环入口距离a，环入口到相遇点距离b，相遇点绕环回到入口距离c
- 慢指针走过：`a + b`，快指针走过：`a + b + c + b = a + 2b + c`
- 快指针速度是慢指针2倍：`a + 2b + c = 2(a + b)` 
- 化简得：`c = a`，所以从头和相遇点同步走a步会在环入口相遇

**实现要点**:
```cpp
// 关键：在循环中检测相遇，而不是循环后
while(fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast) break;  // ✅ 循环中检测
}
```

**复杂度**: 时间O(n)，空间O(1)
**易错点**: 
1. 相遇检测时机：应在循环中而非循环后
2. 哈希表解法顺序：先检查→插入→移动，不是先移动再插入
**相关题目**: 141.环形链表、287.寻找重复数、202.快乐数

### 23. 合并K个升序链表 (Hard) - 分治算法 ⭐⭐
**核心思想**: 多路归并问题，K路分解为2路的递归思维
**三种解法对比**:
1. **分治算法**: O(n log k)时间，O(log k)空间 - 最优解
2. **优先队列**: O(n log k)时间，O(k)空间 - K路归并经典
3. **逐一合并**: O(kn)时间，O(1)空间 - 朴素但有效

**分治算法要点**:
```cpp
// 递归分解：二分思想
ListNode* mergeHelper(vector<ListNode*>& lists, int start, int end) {
    if(start == end) return lists[start];     // 单链表直接返回
    if(start > end) return nullptr;           // 安全边界
    int mid = (start + end) / 2;
    ListNode* left = mergeHelper(lists, start, mid);
    ListNode* right = mergeHelper(lists, mid+1, end);
    return mergeTwoLists(left, right);        // 复用21题解法
}
```

**优先队列要点**:
```cpp
// 关键：比较器构造
struct Cmp {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;  // 大于号构造最小堆
    }
};
// 或lambda: auto cmp = [](ListNode* a, ListNode* b) {return a->val > b->val;};
// priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
```

**复杂度分析**: 
- 分治: 每层O(n)合并，共log k层 → O(n log k)
- 优先队列: n个节点，每次堆操作O(log k) → O(n log k)
- 逐一: 第i次合并O(i×平均长度) → O(kn)

**易错点**:
1. Priority_queue比较器：`>`构造最小堆，`<`构造最大堆
2. Lambda构造问题：需要传入比较器实例`pq(cmp)`
3. 空链表处理：优先队列入堆前要检查`if(list)`
4. 分治边界：`start == end`返回单链表

**核心洞察**: 分治将复杂的K路问题转化为熟悉的2路问题，体现算法设计的化繁为简思想
**相关题目**: 21.合并两个有序链表、88.合并两个有序数组、315.计算右侧小于当前元素的个数

### 206. 反转链表 (Easy) - 链表算法基础
**核心思想**: 改变每个节点的next指针方向，从单向链表变为反向链表
**关键技巧**: 三指针协调 - prev、curr、next的同步移动
**防断裂**: 修改指针前先保存后续节点，避免链表断裂

```cpp
// 迭代法核心模板
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        ListNode* next = curr->next;  // 保存后续
        curr->next = prev;            // 反转指向
        prev = curr;                  // 指针后移
        curr = next;
    }
    return prev;
}
```

### 25. K个一组翻转链表 (Hard) - 分组处理+连接管理
**核心思想**: 模块化设计，分组检查+局部反转+连接管理
**关键步骤**:
1. **分组检查**: 确保剩余节点足够k个
2. **局部反转**: 反转k个节点的小链表
3. **连接管理**: 将反转后的小链表连接到主链表

**易错点**: 反转k个节点后，新尾节点必须连接到下一组开始位置
```cpp
// 关键：新尾连接到下一组
startNode->next = start;  // start指向下一组开始
```

## 链表核心模板

### Floyd判圈模板
```cpp
// 检测环的存在
bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 寻找环入口
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 第一阶段：检测环
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return nullptr;
    
    // 第二阶段：寻找入口
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```

### 双指针技巧模板
```cpp
// 寻找链表中点
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 寻找倒数第k个节点
ListNode* findKthFromEnd(ListNode* head, int k) {
    ListNode* first = head;
    ListNode* second = head;
    
    // first先走k步
    for (int i = 0; i < k; i++) {
        if (!first) return nullptr;
        first = first->next;
    }
    
    // 同步移动
    while (first) {
        first = first->next;
        second = second->next;
    }
    return second;
}
```

## 易错点总结

1. **指针保存**: 修改指针前先保存，防止链表断裂
2. **空指针检查**: 访问node->next前检查node是否为空
3. **边界处理**: 空链表、单节点、两节点等特殊情况
4. **相遇检测时机**: Floyd算法在循环中检测相遇
5. **连接完整性**: 局部操作后确保链表连接完整
6. **指针移动顺序**: 三指针协调时注意移动顺序

## 相关题目分类

- **Floyd判圈**: 141环形链表、142环形链表II、287寻找重复数、202快乐数
- **链表反转**: 206反转链表、92反转链表II、25K个一组翻转链表
- **双指针**: 19删除倒数第N个节点、876链表中间节点、160相交链表
- **归并合并**: 21合并两个有序链表、23合并K个升序链表、148排序链表
- **链表重构**: 83删除重复元素、82删除重复元素II、143重排链表

---
*链表问题的关键在于理清指针关系，善用双指针技巧，注意边界条件和连接完整性*