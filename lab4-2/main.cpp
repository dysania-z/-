/*线性时间选择：
就是利用快排算法来寻找元素，
因此每次就只用调用一半的递归了*/

#include <iostream>
#include <random>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int partition(vector<int> &s, int p, int r) // 以p为枢轴切割数组
{
    int x = s[p];
    int i = p, j = r + 1;
    while (1)
    {
        while (s[++i] < x)
            ;
        while (s[--j] > x)
            ;
        if (i >= j)
            break;
        swap(s[i], s[j]);
    }
    s[p] = s[j];
    s[j] = x;
    return j;
}
int random(int p, int r)
{
    int i = p + rand() % (r - p + 1);
    return i;
}
int randomizedpartition(vector<int> &s, int p, int r) // 随机选择枢轴再切分
{
    int i = random(p, r);
    swap(s[i], s[p]);
    return partition(s, p, r);
}
int randomizedselect(vector<int> &s, int k, int p, int r)
{
    if (p == r)
        return s[p];
    int j = randomizedpartition(s, p, r);
    int len = j - p + 1;
    if (k <= len)
        return randomizedselect(s, k, p, j);
    else
    {
        return randomizedselect(s, k - len, j + 1, r);
    }
}
int main()
{
    ofstream out1("output1.txt");
    int n = 20000;
    while (n -= 100)
    {
        // 生成规模为n的随机数
        // cout << "请输入数据规模n：" << endl;
        // int n;
        // cin >> n;
        ofstream out("input1.txt");
        out << n << '\n';
        srand((unsigned)time(NULL));
        int a, b;
        a = 1, b = n;
        // 随机生成k
        out << (rand() % (b - a + 1)) + a << endl;
        // 随机生成数组元素
        a = 0, b = 1000;
        for (int i = 0; i < n; i++)
        {
            out << (rand() % (b - a + 1)) + a << ' ';
        }
        out.close();

        int i, maxi, mini;
        LARGE_INTEGER nFreq, nBegin, nEnd;
        double time = 0;

        ifstream in("input1.txt");
        int k;
        in >> n >> k;
        cout << "n= " << n << " k= " << k << endl;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            in >> arr[i];
        }
        // int cishu = 1;
        // int copy_cishu = cishu;
        long long result;
        // while (cishu--)
        //{
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBegin);
        result = randomizedselect(arr, k, 0, n - 1);
        QueryPerformanceCounter(&nEnd);
        time += (double)(nEnd.QuadPart - nBegin.QuadPart) / (double)nFreq.QuadPart;
        //}
        // time = time / copy_cishu;
        // for (auto &num : arr)
        //{
        //   cout << num << " ";
        //}
        // cout << endl;
        // cout << "算法-结果:" << result << "\t 查询时间:" << time << endl;
        out1 << n << ' ' << time << endl;
    }
    out1.close();
}