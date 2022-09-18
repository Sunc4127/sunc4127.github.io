#include <iostream> 
using namespace std;

# define WeekDay 7 // 宏常量

/* 有且只有一个 main */
int main() {
    // 1. 单行注释
    /* 2. 多行注释 */

    // output string to window
    cout << "Hello World" << endl;
    cout << "Hello C++" << endl;

    /* ====================================================================== */

    /* 变量 存在的意义：方便我们管理内存空间 */
    int a = 10;
    cout << "a = " << a << endl;

    /* ====================================================================== */

    /* 常量 */
    cout << "一周里有" << WeekDay << "天" << endl;

    // const 修饰的变量是常量
    const int month = 12;
    cout << "一年有" << month << "个月" << endl;

    /* ====================================================================== */

    for (int i = 1; i < 10; i++) {
        for (int j = 1; j <= i; j++)
            cout << j << " * " << i << " = " << i * j << "   ";
        cout << endl;
    }
        
    system("pause");
    return 0;
}