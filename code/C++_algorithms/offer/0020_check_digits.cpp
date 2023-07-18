class Solution
{
public:
    bool isNumber(std::string s)
    {
        int i = 0;
        // 去除前置空格
        for (; s[i] == ' '; i++)
        {
        }

        // 检查并处理正负号
        if (s[i] == '+' || s[i] == '-')
        {
            i++;
        }

        bool isNumeric = false;
        // 处理整数部分
        while (isdigit(s[i]))
        {
            i++;
            isNumeric = true;
        }

        // 处理小数部分
        if (s[i] == '.')
        {
            i++;
            while (isdigit(s[i]))
            {
                i++;
                isNumeric = true;
            }
        }

        // 处理 'e' 或 'E'
        if (isNumeric && (s[i] == 'e' || s[i] == 'E'))
        {
            i++;
            isNumeric = false; // 确保 e 或 E 后面也有数字
            if (s[i] == '+' || s[i] == '-')
            {
                i++;
            }
            while (isdigit(s[i]))
            {
                i++;
                isNumeric = true;
            }
        }

        // 去除后置空格
        while (s[i] == ' ')
        {
            i++;
        }

        // 最后，确认所有字符都已处理，并且存在至少一个数字
        return isNumeric && i == s.size();
    }
};