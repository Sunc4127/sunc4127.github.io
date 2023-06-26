class Solution
{
public:
    int strToInt(string str)
    {
        int i = 0, flag = 1;
        long res = 0; // 用 long 类型来存储结果，避免溢出
        while (str[i] == ' ')
        {
            i++;
        } // 跳过前面的空格
        if (str[i] == '-' || str[i] == '+')
        {
            flag = (str[i++] == '-') ? -1 : 1; // 判断符号
        }
        while ('0' <= str[i] && str[i] <= '9')
        {
            res = res * 10 + (str[i++] - '0');
            if (res >= INT_MAX && flag == 1)
            {
                return INT_MAX;
            } // 判断正数是否溢出
            if (res > INT_MAX && flag == -1)
            {
                return INT_MIN;
            } // 判断负数是否溢出
        }
        return flag * res;
    }
};

class Solution
{
public:
    int strToInt(string str)
    {
        int res = 0, bndry = INT_MAX / 10;
        int i = 0, sign = 1, length = str.size();
        if (length == 0)
            return 0;
        while (str[i] == ' ')
            if (++i == length)
                return 0;
        if (str[i] == '-')
            sign = -1;
        if (str[i] == '-' || str[i] == '+')
            i++;
        for (int j = i; j < length; j++)
        {
            if (str[j] < '0' || str[j] > '9')
                break;
            if (res > bndry || res == bndry && str[j] > '7')
                return sign == 1 ? INT_MAX : INT_MIN;
            res = res * 10 + (str[j] - '0');
        }
        return sign * res;
    }
};
