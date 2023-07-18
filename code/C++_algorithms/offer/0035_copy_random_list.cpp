#include <iostream>
using namespace std;
// 普通链表的节点定义如下：
// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node(int _val)
    {
        val = _val;
        next = NULL;
    }
};

// 本题链表的节点定义如下：
// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node *random;
    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 方法一：哈希表
// 解决这个问题的一种策略是，我们可以使用一个哈希表来保存旧节点到新节点的映射。
// 这样在设置新节点的random指针时，我们可以在哈希表中查找对应的新节点。
// 注意，我们是先完全将所有 node 都重新拷贝到 map 中，再去做映射，这才叫拷贝
class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;
        Node *cur = head;
        unordered_map<Node *, Node *> map;
        // 3. 复制各节点，并建立 “原节点 -> 新节点” 的 Map 映射
        while (cur != nullptr)
        {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        // 4. 构建新链表的 next 和 random 指向
        while (cur != nullptr)
        {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        // 5. 返回新链表的头节点
        return map[head];
    }
};
