#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

// 内联交换函数
inline void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int select(vector<int> a, int l, int r, int k)
{
    while (true)
    {
        if (l >= r)
        {
            return a[l];
        }
        // 随机选择划分基准
        int i = l, j = l + rand() % (r - l + 1);
        Swap(a[i], a[j]);
        j = r + 1;
        int pivot = a[l];
        // 以划分基准为轴做元素交换
        while (true)
        {
            while (i < r && a[++i] < pivot)
                ;
            while (j > l && a[--j] > pivot)
                ;
            if (i >= j)
            {
                break;
            }
            Swap(a[i], a[j]);
        }
        // 如果最后基准元素在第k个元素的位置，则找到了第k小的元素
        if (j - l + 1 == k)
        {
            return pivot;
        }
        // a[j]必然小于pivot,做最后一次交换，满足左侧比pivot小，右侧比pivot大
        a[l] = a[j];
        a[j] = pivot;
        // 对子数组重复划分过程
        if (j - l + 1 < k)
        {
            k = k - (j - l + 1); // 基准元素右侧,求出相对位置
            l = j + 1;
        }
        else
        { // 基准元素左侧
            r = j - 1;
        }
    }
}

int Select(vector<int> a, int n, int k)
{
    if (k < 1 || k > n)
    {
        printf("Index out of bounds\n");
        exit(0);
    }
    return select(a, 0, n - 1, k);
}

int main()
{
    ofstream out1("output1.txt");
    int n = 50000;
    while (n -= 100)
    {
        // 生成规模为n的随机数
        // cout<<"请输入数据规模n："<<endl;
        // int n;
        // cin>>n;
        ofstream out("input1.txt");
        out << n << '\n';
        srand((unsigned)time(NULL));
        int a, b;
        a = 1, b = n;
        // k
        out << (rand() % (b - a + 1)) + a << endl;
        // 随机生成数组元素
        a = 0, b = 100000;
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
        int cishu = 1;
        int copy_cishu = cishu;
        long long result;
        while (cishu--)
        {
            QueryPerformanceFrequency(&nFreq);
            QueryPerformanceCounter(&nBegin);
            result = Select(arr, n, k);
            ;
            QueryPerformanceCounter(&nEnd);
            time += (double)(nEnd.QuadPart - nBegin.QuadPart) / (double)nFreq.QuadPart;
        }
        time = time / copy_cishu;
        // cout<<"算法-结果:"<<result<<"\t 查询时间:"<<time<<endl;
        out1 << n << ' ' << time << endl;
    }
    out1.close();
}