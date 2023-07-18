/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *left = nullptr;
        ListNode *right = head;
        while (right != nullptr)
        {
            ListNode *tmp = right->next;
            right->next = left;
            left = right;
            right = tmp;
        }

        return left;
    }
};

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        return recur(nullptr, head); // 调用递归并返回
    }

private:
    ListNode *recur(ListNode *left, ListNode *right)
    {
        if (right == nullptr)
            return left;                           // 终止条件
        ListNode *res = recur(right, right->next); // 递归后继节点
        right->next = left;                        // 修改节点引用指向
        return res;                                // 返回反转链表的头节点
    }
};
