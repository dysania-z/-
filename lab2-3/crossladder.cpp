#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
double x, y, c, mid, l, r;
double f(double m)
{
    return (1 / sqrt(x * x - m * m) + 1 / sqrt(y * y - m * m) - 1 / c);
}
int main()
{
    while (scanf("%lf%lf%lf", &x, &y, &c) == 3)
    {
        mid = 0;
        l = 0;
        r = min(x, y);
        while (r - l >= 1e-9)
        {
            mid = (l + r) / 2.0;
            if (f(mid) > 0)
            {
                r = mid;
            }
            if (f(mid) < 0)
            {
                l = mid;
            }
        }
        printf("%0.3f\n", mid);
    }
    return 0;
}
