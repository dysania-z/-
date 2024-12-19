#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class Object
{
public:
    int id;
    int weight;
    int price;
    float d;
};
class MaxHeapQNode
{
public:
    MaxHeapQNode *parent;
    int lchild;
    int upprofit;
    int profit;
    int weight;
    int lev;
};
// 当前价值 当前重量 最优值  总重量 总价值
int cp, cw, bestp;
bool compare(const Object &a, const Object &b)
{
    return a.d >= b.d;
}
struct cmp
{
    bool operator()(MaxHeapQNode *&a, MaxHeapQNode *&b) const
    {
        return a->upprofit < b->upprofit;
    }
};
// 计算up值
int Bound(int i, int n, int c, vector<Object> &obj)
{
    int tmp_cleft = c - cw;
    int tmp_cp = cp;
    while (tmp_cleft >= obj[i].weight && i <= n)
    {
        tmp_cleft -= obj[i].weight;
        tmp_cp += obj[i].price;
        i++;
    }
    // 装满背包
    if (i <= n)
    {
        tmp_cp += tmp_cleft * obj[i].d;
    }
    return tmp_cp;
}

// 加入活性队列
void AddAliveNode(priority_queue<MaxHeapQNode *, vector<MaxHeapQNode *>, cmp> &q, MaxHeapQNode *E, int up, int wt, int curp, int i, int ch)
{
    MaxHeapQNode *p = new MaxHeapQNode;
    p->parent = E;
    p->lchild = ch;
    p->weight = wt;
    p->upprofit = up;
    p->profit = curp;
    p->lev = i + 1;
    q.push(p);
}

void MaxKnapsack(int n, int c, vector<int> &bestx, vector<Object> &obj)
{
    priority_queue<MaxHeapQNode *, vector<MaxHeapQNode *>, cmp> q; // 大顶堆
    MaxHeapQNode *E = NULL;
    cw = cp = bestp = 0;
    int i = 1;
    int up = Bound(1, n, c, obj); // Bound(i)函数计算的是i还未处理时候的上限值
    while (i != n + 1)
    {
        int wt = cw + obj[i].weight;
        if (wt <= c)
        {
            if (bestp < cp + obj[i].price)
                bestp = cp + obj[i].price;
            AddAliveNode(q, E, up, cw + obj[i].weight, cp + obj[i].price, i, 1);
        }
        up = Bound(i + 1, n, c, obj); // 注意这里 up != up - obj[i].price而且 up >= up - obj[i].price
        if (up >= bestp)              // 注意这里必须是大于等于
        {
            AddAliveNode(q, E, up, cw, cp, i, 0);
        }
        E = q.top();
        q.pop();
        cw = E->weight;
        cp = E->profit;
        up = E->upprofit;
        i = E->lev;
    }
    for (int j = n; j > 0; --j)
    {
        bestx[obj[E->lev - 1].id] = E->lchild;
        E = E->parent;
    }
}
void OutPut(int n, vector<int> best_x)
{
    cout << "bestp = " << bestp << endl;
    ;
    cout << "选取的物品为 : ";
    for (int i = 1; i <= n; ++i)
    {
        if (best_x[i] == 1)
            cout << i << " ";
    }
}

class Object1
{
public:
    int p;  // 价值
    int w;  // 重量
    int id; // 物品的id
};

// 当前价值 当前重量 最优值  总重量 总价值
int cp1, cw1, bestp1, total_w1, total_p1;
bool cmp1(const Object1 &a, const Object1 &b)
{
    return a.p / a.w > b.p / b.w;
}

// 计算up值
int Bound1(int i, int n, int c, vector<Object1> &O)
{
    int temp_cw = c - cw1;
    int temp_cp = cp1;
    while (i <= n && temp_cw >= O[i].w)
    {
        temp_cw -= O[i].w;
        temp_cp += O[i].p;
        ++i;
    }
    // 装满背包
    if (i <= n)
        temp_cp += O[i].p / O[i].w * temp_cw;
    return temp_cp;
}

void Backtrack(int i, int n, int c, vector<int> &x, vector<int> &best_x, vector<Object1> &O)
{
    if (i > n)
    {
        bestp1 = cp1;
        for (int i = 1; i <= n; ++i)
            best_x[i] = x[i];
        return;
    }
    if (cw1 + O[i].w <= c)
    {
        x[O[i].id] = 1;
        cw1 += O[i].w;
        cp1 += O[i].p;
        Backtrack(i + 1, n, c, x, best_x, O);
        cp1 -= O[i].p;
        cw1 -= O[i].w;
        x[O[i].id] = 0;
    }
    // 向右求解的约束条件
    if (Bound1(i + 1, n, c, O) > bestp1)
    {
        x[O[i].id] = 0;
        Backtrack(i + 1, n, c, x, best_x, O);
    }
}

void OutPut1(int n, vector<int> best_x)
{
    cout << "bestp = " << bestp1 << endl;
    ;
    cout << "选取的物品为 : ";
    for (int i = 1; i <= n; ++i)
    {
        if (best_x[i] == 1)
            cout << i << " ";
    }
}
int main(int argc, char **argv)
{
    ofstream out1("output1.txt");
    ofstream out2("output2.txt");
    // int n = 20000, c;
    while (1)
    {
        //		//生成规模为n的随机数
        cout << "请输入数据规模n：" << endl;
        int n, c;
        cin >> n;
        ofstream out("input1.txt");
        out << n << '\n';
        srand((unsigned)time(NULL));
        // c (a,b]
        int a = 0, b = 100;
        out << (rand() % (b - a)) + a + 1 << '\n';
        // v数组
        for (int i = 0; i < n; i++)
        {
            out << rand() << ' ';
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

        int i, maxi, mini;
        LARGE_INTEGER nFreq, nBegin, nEnd;
        double time;

        ifstream in("input1.txt");
        // 物品数量 背包容量
        in >> n >> c;
        vector<Object> o(n + 1);
        for (i = 1; i <= n; i++)
        {
            in >> o[i].price;
            o[i].id = i;
        }
        for (i = 1; i <= n; i++)
        {
            in >> o[i].weight;
            o[i].d = 1.0 * o[i].price / o[i].weight;
        }
        vector<int> best_x(n + 1); // 记录暂时选取状态  记录最优选取状态

        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBegin);
        // 依照物品单位重量价值排序
        sort(o.begin() + 1, o.end(), compare);
        MaxKnapsack(n, c, best_x, o);
        OutPut(n, best_x);
        QueryPerformanceCounter(&nEnd);
        time = (double)(nEnd.QuadPart - nBegin.QuadPart) / (double)nFreq.QuadPart;

        cout << "查询时间-分支限界:" << time << endl
             << endl;
        out1 << n << ' ' << time << endl;
        in.close();

        ifstream in1("input1.txt");
        // 物品数量 背包容量
        in1 >> n >> c;
        vector<Object1> o1(n + 1);
        for (i = 1; i <= n; i++)
        {
            in1 >> o1[i].p;
            o1[i].id = i;
        }
        for (i = 1; i <= n; i++)
        {
            in1 >> o1[i].w;
        }

        cp1 = cw1 = total_w1 = total_p1 = bestp1 = 0;
        for (int i = 1; i <= n; ++i)
        {
            total_p1 += o1[i].p;
            total_w1 += o1[i].w;
        }
        vector<int> x1(n + 1);
        vector<int> best_x1(n + 1); // 记录暂时选取状态  记录最优选取状态
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBegin);
        // 依照物品单位重量价值排序
        sort(o1.begin() + 1, o1.end(), cmp1);
        Backtrack(1, n, c, x1, best_x1, o1);
        OutPut1(n, best_x1);
        QueryPerformanceCounter(&nEnd);
        time = (double)(nEnd.QuadPart - nBegin.QuadPart) / (double)nFreq.QuadPart;

        cout << "查询时间:" << time << endl
             << endl;
        out2 << n << ' ' << time << endl;
        in.close();
    }
    out1.close();
    return 0;
}