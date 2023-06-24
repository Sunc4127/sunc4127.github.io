class CQueue
{
public:
    stack<int> A, B;
    CQueue() {}
    void appendTail(int value)
    {
        A.push(value);
    }
    int deleteHead()
    {
        if (!B.empty())
        {
            int tmp = B.top();
            B.pop();
            return tmp;
        }
        if (A.empty())
            return -1;
        while (!A.empty())
        {
            int tmp = A.top();
            A.pop();
            B.push(tmp);
        }
        int tmp = B.top();
        B.pop();
        return tmp;
    }
};
