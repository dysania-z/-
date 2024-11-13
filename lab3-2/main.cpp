#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <random>
using namespace std;

int maxw, n, maxvalue;
vector<int> value;             // 物品价值数组
vector<int> weight;            // 物品重量数组
vector<bool> bestSelection;    // 最优选择物品的记录
vector<bool> currentSelection; // 当前物品选择的记录

void traceback(int currweight, int currvalue, int index)
{
    // 剪枝1：如果当前背包的重量超过最大容量，剪枝
    if (currweight > maxw)
        return;
    // 剪枝2：如果当前价值加上剩余物品的最大价值都无法超过最优解，剪枝
    int remainv = currvalue;
    int remainw = currweight;
    for (int i = index; i < n; i++)
    {
        remainv += value[i];
        remainw += weight[i];
        if (remainw > maxw)
            break;
    }
    if (remainv < maxvalue)
        return;
    // 如果到达了叶子节点，更新最优解
    if (index == n)
    {
        if (currvalue > maxvalue)
        {
            maxvalue = currvalue;
            bestSelection = currentSelection; // 记录当前选择的物品
        }
        return;
    }
    // 不选当前物品
    currentSelection[index] = false;
    traceback(currweight, currvalue, index + 1);
    // 选当前物品
    currentSelection[index] = true;
    traceback(currweight + weight[index], currvalue + value[index], index + 1);
}

int main()
{
    ofstream out1("output.txt");
    while (1)
    {
        // 生成规模为n的随机数
        cout << "请输入数据规模n：" << endl;
        cin >> n;
        // 在每次新的n输入后，重置maxvalue和bestSelection
        maxvalue = 0;
        bestSelection.clear();
        bestSelection.resize(n, false);
        currentSelection.resize(n, false);
        // 初始化value和weight数组
        value.resize(n);
        weight.resize(n);
        ofstream out("input1.txt");
        out << n << '\n';
        // 背包最大容量maxw【0~100】
        srand((unsigned)time(NULL));
        int a = 0, b = 100;
        out << (rand() % (b - a)) + a + 1 << '\n';
        // v数组
        for (int i = 0; i < n; i++)
        {
            out << rand() % 1000 + 1 << ' '; // 生成较小的随机数，避免溢出
            if ((i + 1) % 10 == 0)
                out << '\n';
        }
        out << '\n';
        // w数组 (a,b]
        for (int i = 0; i < n; i++)
        {
            out << (rand() % (b - a)) + a + 1 << ' ';
            if ((i + 1) % 10 == 0)
                out << '\n';
        }
        out.close();
        LARGE_INTEGER nFreq, nBegin, nEnd;
        double time;
        ifstream in("input1.txt");
        // 物品数量 背包容量
        in >> n >> maxw;
        for (int i = 0; i < n; i++)
            in >> value[i];
        for (int i = 0; i < n; i++)
            in >> weight[i];
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBegin);
        traceback(0, 0, 0); // 开始回溯
        QueryPerformanceCounter(&nEnd);
        time = (double)(nEnd.QuadPart - nBegin.QuadPart) / (double)nFreq.QuadPart;
        // cout << "最大价值：" << maxvalue << endl;
        // 输出最优选择的物品
        // cout << "最优选择的物品（编号从1开始）：" << endl;
        // for (int i = 0; i < n; i++)
        // {
        //     if (bestSelection[i])
        //     {
        //         cout << "物品" << i + 1 << " ";
        //     }
        // }
        // cout << endl;
        out1 << n << ' ' << time << endl;
        in.close();
    }
    out1.close();
    return 0;
}
