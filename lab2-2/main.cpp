#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<windows.h>
#include<fstream>
using namespace std;

struct Item {
    double weight;
    double value;
    double unitValue; // 每单位重量的价值
};

bool compare(Item a, Item b) {
    return a.unitValue > b.unitValue; // 按单位价值降序排列
}

double greedypack(int capacity,vector<Item> items)
{
    double totalValue = 0.0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value; // 可以放下整个物品
            capacity -= item.weight;
        } else {
            totalValue += item.unitValue * capacity; // 放下部分物品
            break;
        }
    }
    return totalValue;
}

int main() 
{
    ofstream out1("output.txt");
	while(1){
        //input.txt
        int n,c;
		cout<<"请输入数据规模n："<<endl; 
		cin>>n;
		ofstream out("input1.txt");
        //生成规模为n
		out<<n<<'\n';
		srand((unsigned)time(NULL));
		// 容量c (a,b]
		int a=0,b=100;
		out<< (rand() % (b-a))+ a + 1<<'\n';
		// 价值-重量-价值-重量-
		for(int i=0;i<n;i++){
			out<<rand()<<' ';
            out<< (rand() % (b-a))+ a + 1<<' ';
			if((i+1)%10==0) out<<'\n';
		}
		out<<'\n';
		out.close();
//读入输入
    ifstream in("input1.txt");
    
    in>>n>>c;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        in >> items[i].value>> items[i].weight;
        items[i].unitValue = items[i].value / items[i].weight; // 计算单位价值
    }

    LARGE_INTEGER nFreq,nBegin,nEnd;
    double time; 
    QueryPerformanceFrequency(&nFreq);	
	QueryPerformanceCounter(&nBegin);
    // 按单位价值排序
    sort(items.begin(), items.end(), compare);
    double ans=greedypack(c,items);
    
    QueryPerformanceCounter(&nEnd);
	time=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart; 
		
	// cout<<"结果:"<<ans<<"\n查询时间:"<<time<<endl<<endl;
	out1<<n<<' '<<time<<endl;
	in.close();		
    }
    out1.close();
    return 0;
}
