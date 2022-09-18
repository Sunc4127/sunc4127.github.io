//
// Created by Cheng Sun on 2022/8/26.
//

#include<iostream>
using namespace std;

//抽象CPU类
class CPU
{
public:
    //抽象的计算函数
    virtual void calculate() = 0;
};

//抽象显卡类
class VideoCard
{
public:
    //抽象的显示函数
    virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
    //抽象的存储函数
    virtual void store() = 0;
};

//电脑类
class Computer
{
public:
    Computer(CPU * cpu, VideoCard * vc, Memory * mem)
    {
        m_cpu = cpu;
        m_vc = vc;
        m_mem = mem;
    }

    //提供工作的函数
    void work()
    {
        //让零件工作起来，调用接口
        m_cpu->calculate();

        m_vc->display();

        m_mem->store();
    }


private:

    CPU * m_cpu; //CPU的零件指针
    VideoCard * m_vc; //显卡零件指针
    Memory * m_mem; //内存条零件指针
};

//具体厂商
//Intel厂商
class IntelCPU :public CPU
{
public:
    void calculate() override
    {
        cout << "Intel的CPU开始计算了！" << endl;
    }
};

class IntelVideoCard :public VideoCard
{
public:
    void display() override
    {
        cout << "Intel的显卡开始显示了！" << endl;
    }
};

class IntelMemory :public Memory
{
public:
    void store() override
    {
        cout << "Intel的内存条开始存储了！" << endl;
    }
};

//Lenovo厂商
class LenovoCPU :public CPU
{
public:
    void calculate() override
    {
        cout << "Lenovo的CPU开始计算了！" << endl;
    }
};

class LenovoVideoCard :public VideoCard
{
public:
    void display() override
    {
        cout << "Lenovo的显卡开始显示了！" << endl;
    }
};

class LenovoMemory :public Memory
{
public:
    void store() override
    {
        cout << "Lenovo的内存条开始存储了！" << endl;
    }
};


void test01()
{
    //第一台电脑零件
    CPU * intelCpu = new IntelCPU;
    VideoCard * intelCard = new IntelVideoCard;
    Memory * intelMem = new IntelMemory;

    cout << "第一台电脑开始工作：" << endl;
    //创建第一台电脑
    auto * computer1 = new Computer(intelCpu, intelCard, intelMem);
    computer1->work();


    cout << "-----------------------" << endl;
    cout << "第二台电脑开始工作：" << endl;
    //第二台电脑组装
    auto * computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);
    computer2->work();


    cout << "-----------------------" << endl;
    cout << "第三台电脑开始工作：" << endl;
    //第三台电脑组装
    auto * computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemory);
    computer3->work();

    delete computer1;
    delete computer2;
    delete computer3;

}

int main() {
    test01();
}