#include <iostream>
#include <stack>
using namespace std;

class Solution
{
public:
    vector<int> reversePrint(ListNode *head)
    {
        stack<int> stk;
        while (head != nullptr)
        {
            stk.push(head->val);
            head = head->next;
        }
        vector<int> res;
        while (!stk.empty())
        {
            res.push_back(stk.top());
            stk.pop();
        }
        return res;
    }
};
