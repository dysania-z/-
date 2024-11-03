#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long use;
use n, m, a, b, x[2][3], y[2][3], c[3][3], e[3][3], d[3][3];

int main()
{
    while (cin >> a >> b >> n >> m)
    {
        x[1][1] = (a + a) % m;
        x[1][2] = (2 * a * a + 2 * b) % m;
        memset(y, 0, sizeof(y));
        c[1][1] = 0;
        c[1][2] = (m + (b - a * a) % m) % m;
        c[2][1] = 1;
        c[2][2] = (a + a) % m;
        e[1][1] = e[2][2] = 1;
        e[1][2] = e[2][1] = 0;
        for (int u = n - 1; u; u >>= 1)
        {
            if (u & 1) // 快速幂算法，在当前位有值时才计算
            {
                memset(d, 0, sizeof(d));
                for (int i = 1; i < 3; i++)
                    for (int j = 1; j < 3; j++)
                        for (int k = 1; k < 3; k++)
                            (d[i][k] += c[i][j] * e[j][k]) %= m;
                memcpy(e, d, sizeof(d));
            };
            // 矩阵c自身平方，为下一次乘法做准备
            memset(d, 0, sizeof(d));
            for (int i = 1; i < 3; i++)
                for (int j = 1; j < 3; j++)
                    for (int k = 1; k < 3; k++)
                        (d[i][k] += c[i][j] * c[j][k]) %= m;
            memcpy(c, d, sizeof(d));
        }
        // 最后一次计算
        for (int i = 1; i < 2; i++)
            for (int j = 1; j < 3; j++)
                for (int k = 1; k < 3; k++)
                    (y[i][k] += x[i][j] * e[j][k]) %= m;
        cout << y[1][1] << endl;
    }
    return 0;
}