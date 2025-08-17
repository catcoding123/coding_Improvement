# 链表专题

本专题目录
- [142. 环形链表 II](#ll-142)
- [23. 合并K个升序链表](#ll-23)
- [206. 反转链表](#ll-206)
- [24. 两两交换链表中的节点](#ll-24)
- [25. K个一组翻转链表](#ll-25)
- [92. 反转链表II](#ll-92)
- [链表算法核心模式总结](#ll-summary)
- [25题关键要点与易错点](#ll-25-pitfalls)
- [连接机制深度理解](#ll-25-connection)
- [扩展应用方向](#ll-extend)

<a id="ll-142"></a>
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

<a id="ll-23"></a>
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

<a id="ll-206"></a>
### 206. 反转链表 (Easy) - 链表算法基础
**核心思想**: 改变每个节点的next指针方向，从单向链表变为反向链表
**关键技巧**: 三指针协调 - prev、curr、next的同步移动
**防断裂**: 修改指针前先保存后续节点，避免链表断裂

#### 迭代实现 - 三指针模式 ⭐
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;  // 保存后续
        curr->next = prev;            // 反转指向
        prev = curr;                  // 指针前移
        curr = next;                  // 指针前移
    }
    return prev;  // prev成为新头节点
}
```

#### 递归实现 - 信任机制 ⭐
```cpp
ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseListRecursive(head->next);  // 信任递归
    head->next->next = head;   // 当前操作：反转连接
    head->next = nullptr;      // 防成环关键步骤
    return newHead;            // 返回新头节点
}
```

<a id="ll-24"></a>
### 24. 两两交换链表中的节点 (Medium) - 分组处理进阶
**核心思想**: 局部反转的应用，每两个节点为一组进行交换
**关键技巧**: 虚拟头节点 + 四指针协调
**模式升华**: 从整体操作到分组操作的算法思维

<a id="ll-25"></a>
### 25. K个一组翻转链表 (Hard) - 复合算法集大成
**核心思想**: 206题反转+24题分组的完美融合，任意k值的通用分组反转算法
**关键技巧**: 模块化设计 + 复合操作 + 连接管理
**算法升华**: 从特例(k=2)到通用(任意k)的抽象设计能力

<a id="ll-92"></a>
### 92. 反转链表II (Medium) - 三段式精确区间反转
**核心思想**: 三段式连接法，精确区间控制+复用已有技巧
**关键技巧**: 边界定位 + 安全断开 + 局部反转 + 三段重连
**技术融合**: 206题三指针技巧 + 25题模块化设计 + 精确边界控制

#### 24题迭代实现 - 虚拟头节点+四指针 ⭐
```cpp
ListNode* swapPairs(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    while (prev->next && prev->next->next) {
        ListNode* first = prev->next;
        ListNode* second = prev->next->next;
        ListNode* next = second->next;
        
        // 三步交换：prev→second→first→next
        second->next = first;
        first->next = next;
        prev->next = second;
        
        prev = first;  // 更新prev为交换后的末尾节点
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}
```

#### 25题迭代实现 - 模块化分组反转 ⭐⭐
```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prevGroupEnd = dummy;
    
    while (hasKNodes(prevGroupEnd->next, k)) {
        auto [newHead, newTail] = reverseKNodes(prevGroupEnd->next, k);
        prevGroupEnd->next = newHead;
        prevGroupEnd = newTail;
    }
    
    return dummy->next;
}

// 辅助函数1: 检查是否有k个节点
bool hasKNodes(ListNode* start, int k) {
    while (start && k > 0) {
        start = start->next;
        k--;
    }
    return k == 0;
}

// 辅助函数2: 反转k个节点并连接
pair<ListNode*, ListNode*> reverseKNodes(ListNode* start, int k) {
    if (!start || k == 0) return {nullptr, nullptr};
    
    ListNode* originalStart = start;  // 保存原始头，成为新尾
    ListNode* prev = nullptr;
    
    // 反转k个节点 (复用206题技巧)
    while (start && k > 0) {
        ListNode* next = start->next;
        start->next = prev;
        prev = start;
        start = next;
        k--;
    }
    
    // 关键：新尾连接到下一组
    originalStart->next = start;
    
    return {prev, originalStart};  // {新头, 新尾}
}
```

#### 92题三段式实现 - 精确区间反转 ⭐⭐
```cpp
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    // 1. 边界定位：找到关键节点
    ListNode* startPre = findPrevNode(dummy, left);    // left前驱
    ListNode* startNode = startPre->next;              // 反转段开始
    ListNode* endNode = findTargetNode(dummy, right);  // 反转段结束
    ListNode* nextNode = endNode->next;                // right后继
    
    // 2. 安全断开：避免反转时影响后续
    endNode->next = nullptr;
    
    // 3. 局部反转：复用206题技巧
    auto [newHead, newTail] = reverseSegment(startNode);
    
    // 4. 三段重连：前段→反转段→后段
    startPre->next = newHead;
    newTail->next = nextNode;
    
    return dummy->next;
}

// 辅助函数：定位前驱节点
ListNode* findPrevNode(ListNode* dummy, int pos) {
    ListNode* node = dummy;
    for(int i = 0; i < pos - 1; i++) {
        node = node->next;
    }
    return node;
}

// 辅助函数：定位目标节点  
ListNode* findTargetNode(ListNode* dummy, int pos) {
    ListNode* node = dummy;
    for(int i = 0; i < pos; i++) {
        node = node->next;
    }
    return node;
}

// 辅助函数：反转链表段（复用206题）
pair<ListNode*, ListNode*> reverseSegment(ListNode* start) {
    ListNode* pre = nullptr;
    ListNode* curr = start;
    while(curr) {
        ListNode* next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return {pre, start};  // {新头, 新尾}
}
```

#### 递归实现 - 分治思想 ⭐
```cpp
ListNode* swapPairsRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* next = head->next;
    ListNode* nextNode = swapPairsRecursive(head->next->next);  // 信任递归
    next->next = head;         // 当前操作：交换这一对
    head->next = nextNode;     // 连接到递归结果
    return next;               // 返回交换后的新头节点
}
```

<a id="ll-summary"></a>
## 链表算法核心模式总结

### 迭代 vs 递归思维对比
| 特征 | 迭代思维 | 递归思维 |
|------|----------|----------|
| **控制方式** | 主动推进，step by step | 信任机制，处理当前 |
| **状态管理** | 全局状态跟踪 | 局部操作设计 |
| **空间复杂度** | O(1) | O(h) - 递归栈 |
| **思维模式** | 从前往后构建 | 假设后面已完成 |

### 递归设计的三要素
1. **信任假设**: 相信递归会正确处理子问题
2. **专注当前**: 只处理当前层的局部操作  
3. **正确返回**: 保证返回值符合函数契约

### 指针操作进阶路径
```
206题：三指针 prev→curr→next (整体反转)
    ↓
24题：四指针 prev→first→second→next (固定k=2分组)
    ↓  
25题：模块化设计 prevGroupEnd→[k个节点分组] (任意k通用算法)
    ↓
92题：三段式设计 前段→反转段→后段 (精确区间反转)
```

### 核心技巧工具箱
1. **虚拟头节点**: 统一处理头节点变化，简化边界逻辑
2. **多指针协调**: 保存关键节点，防止链表断裂
3. **防成环处理**: 递归中必须切断旧连接
4. **边界条件**: 空链表、单节点、奇偶长度的系统处理
5. **模块化设计**: 复杂算法分解为独立的辅助函数
6. **连接管理**: 确保分组操作后链表的完整连接

### 算法模式识别
- **整体变换**: 206题类型，使用三指针迭代或信任递归
- **固定分组**: 24题类型，虚拟头节点+多指针协调
- **通用分组**: 25题类型，模块化设计+复合操作
- **精确区间**: 92题类型，三段式设计+技巧复用

### 92题关键突破
- **三段式理念**: 定位→断开→反转→重连的清晰流程
- **技巧复用**: 206题三指针 + 25题模块化 + 边界精确控制
- **模块化设计**: 三个独立辅助函数，职责分离
- **安全操作**: 先断开连接，避免反转时的相互影响

<a id="ll-25-pitfalls"></a>
## 25题关键要点与易错点

### 🎯 核心算法思想
- **复合操作**: 分组识别 + 局部反转 + 连接管理
- **模块化设计**: 将复杂问题分解为独立的辅助函数
- **连接保证**: 确保每次操作后链表的完整性

### ⚠️ 常见易错点分析

#### 1. **语法错误类**
```cpp
// ❌ 错误：结构化绑定语法错误
auto {newHead, newTail} = reverseKNodes(...);

// ✅ 正确：使用方括号
auto [newHead, newTail] = reverseKNodes(...);
```

#### 2. **变量名不匹配**
```cpp
auto [newhead, newtail] = reverseKNodes(...);
prevGroupEnd->next = newHead;  // ❌ 变量名大小写不匹配
```

#### 3. **内存管理错误**
```cpp
ListNode* dummy = ListNode(0);     // ❌ 栈对象，可能有问题
ListNode* dummy = new ListNode(0); // ✅ 堆对象更安全
```

#### 4. **连接断裂担心**
```cpp
// 担心：prevGroupEnd = newTail 会断开连接？
// 解答：不会！newTail在返回前已经连接到下一组
originalStart->next = start;  // 关键连接步骤
```

#### 5. **hasKNodes边界检查**
```cpp
// ❌ 可能的错误：检查时修改了k的值
bool hasKNodes(ListNode* start, int k) {
    while(start) {
        k--;  // 修改了参数k
        start = start->next;
    }
    return k == 0;
}

// ✅ 正确：使用局部变量或者不修改参数
bool hasKNodes(ListNode* start, int k) {
    while(start && k > 0) {
        start = start->next;
        k--;
    }
    return k == 0;
}
```

### 🔧 调试要点
1. **分步验证**: 先确保 hasKNodes 和 reverseKNodes 独立正确
2. **连接检查**: 重点验证每组反转后的连接是否完整
3. **边界测试**: 测试k=1、k=链表长度、k>链表长度等边界情况
4. **内存安全**: 确保没有野指针和内存泄漏

### 💡 设计精髓
- **单一职责**: 每个函数只负责一个明确的功能
- **接口设计**: 返回值设计要便于调用方使用
- **状态管理**: prevGroupEnd始终指向已处理部分的尾部
- **信任机制**: 主函数信任辅助函数会正确处理局部操作

<a id="ll-25-connection"></a>
### 🔑 连接机制深度理解

#### 双重连接的必要性
25题需要两个层次的连接操作：

**1. 组内连接** (reverseKNodes函数内部):
```cpp
startNode->next = start;  // 新尾连接到下一组开始
```
- **作用**: 保证当前反转组的内部完整性
- **时机**: 反转操作完成后立即执行
- **连接**: 当前组尾部 → 剩余链表头部

**2. 组间连接** (主函数执行):
```cpp
prevGroupEnd->next = newHead;  // 上一组尾部连接到当前组新头
```
- **作用**: 保证不同反转组之间的连接完整性  
- **时机**: 获得反转结果后执行
- **连接**: 上一组尾部 → 当前组新头部

#### 时序控制的关键性
```cpp
// ✅ 正确时序
while(hasKNodes(prevGroupEnd->next, k)) {
    auto [newHead, newTail] = reverseKNodes(...);  // 1. 先反转
    prevGroupEnd->next = newHead;                  // 2. 再连接
    prevGroupEnd = newTail;                        // 3. 最后更新
}
```

**为什么必须按此顺序**:
- **步骤1**: 反转操作产生newHead和newTail
- **步骤2**: 利用当前prevGroupEnd建立组间连接
- **步骤3**: 更新prevGroupEnd为新的尾部，准备下轮连接

**错误时序的后果**:
```cpp
// ❌ 如果提前更新prevGroupEnd
prevGroupEnd = newTail;           // 失去上一组尾部引用
prevGroupEnd->next = newHead;     // 错误连接！
```

#### 连接完整性验证
**完整流程示例** `[1,2,3,4,5]` k=2:

```
初始: dummy → 1 → 2 → 3 → 4 → 5
      ↑prevGroupEnd

第一轮:
- 反转[1,2] → {newHead:2, newTail:1}
- 组内连接: 1.next = 3
- 组间连接: dummy.next = 2
- 结果: dummy → 2 → 1 → 3 → 4 → 5
- 更新: prevGroupEnd = 1

第二轮:  
- 反转[3,4] → {newHead:4, newTail:3}
- 组内连接: 3.next = 5
- 组间连接: 1.next = 4  ← 关键！
- 结果: dummy → 2 → 1 → 4 → 3 → 5
- 更新: prevGroupEnd = 3
```

#### 核心洞察
- **组内连接**: 解决当前反转组的向后延续
- **组间连接**: 解决不同反转组的串联组合
- **时序控制**: prevGroupEnd作为连接桥梁，必须在正确时机更新
- **状态维护**: 每轮循环后prevGroupEnd指向已处理部分的真实尾部

<a id="ll-extend"></a>
### 扩展应用方向
- 25. K个一组翻转链表 (24题推广)
- 92. 反转链表II (指定区间反转)
- 143. 重排链表 (复杂节点重组)
- 61. 旋转链表 (整体移动)
