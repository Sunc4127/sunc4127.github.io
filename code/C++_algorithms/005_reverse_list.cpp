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