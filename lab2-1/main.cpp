#include<iostream>
#include<algorithm>
#include<fstream>
#include<windows.h>
#include<vector>
using namespace std;
int solve(int n,int maxw,vector<int> weight,vector<int> value)
{
	vector<vector<int>> dp(n, vector<int>(maxw + 1, 0));
	//创建一个dp数组，n为物品，maxw为最大装载容量【0~maxw】
	for(int w=0;w<=maxw;w++)
	{
		if(weight[0]<=w)
			dp[0][w]=value[0];
	}//初始化dp数组，对于第0种物品，只有最大容量【0~maxw】大于等于weight【0】时才有可能获得价值
	//由于状态转移函数的特性，初始化dp就是初始化dp[0][].（前0件物品的最优解）
	for(int nu=1;nu<n;nu++)
	{
		for(int w=0;w<=maxw;w++)
		{	//若容量w小于当前
			if(w<=weight[nu])
				dp[nu][w]=dp[nu-1][w];
			else
				dp[nu][w]=max(dp[nu-1][w],dp[nu-1][w-weight[nu]]+value[nu]);
				//dp[nu][j]是已知的，要有这种意识，本质上就是一个二维数组不断按照某种规则推进。
				//所以w-weight[nu]的值小于weight【n-1】也没有关系
		}
	}//状态转移
	return dp[n-1][maxw];
	
}
int main()
{
	ofstream out1("output.txt");
	while(1)
	{
	//格式： n，maxw，value[],weight[]
	cout<<"请输入数据规模n:"<<endl; 
	int n,c;
	cin>>n;
	ofstream out("input1.txt");
	out<<n<<'\n';
	srand((unsigned)time(NULL));
	// c
	int a=0,b=100;//因为要建成的数组为f[n+1][c+1]，
	//所以c如果不做限制的话，这个数组会很大，一开始没做限制时，即使我设置和输入规模n为1，也会运行很长时间。
	out<< (rand() % (b-a))+ a + 1<<'\n';//c的范围：a+1~b:1~100
	// v数组 
	for(int i=0;i<n;i++){
		out<<rand()<<' ';
		if((i+1)%10==0) out<<'\n';
	}
	out<<'\n';
	// w数组 
	for(int i=0;i<n;i++){
			//相应于上面的受限制的c，在这里对w也做相同限制。
		out<< (rand() % (b-a))+ a + 1<<' ';
		if((i+1)%10==0) out<<'\n';
	}
	out.close();
	

	ifstream in("input1.txt");
	in>>n>>c;

	vector<int> w(n),v(n);
	for(int i=0;i<n;i++){
		in>>v[i];
		//cout<<v[i]<<" ";
	}

	for(int i=0;i<n;i++){
		in>>w[i];
		//cout<<w[i]<<" ";
	}

	LARGE_INTEGER nFreq,nBegin,nEnd;
	double time; 
	//cout<< n<<" "<<c<<endl;
	QueryPerformanceFrequency(&nFreq);	
	QueryPerformanceCounter(&nBegin);
	int result=solve(n,c,w,v);
	QueryPerformanceCounter(&nEnd);
	time=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart;

	out1<<n<<' '<<time<<endl;
	//cout<<"结果:"<<result<<"\n查询时间:"<<time<<endl<<endl;
	in.close();	
	}	
	out1.close();
 	return 0;
}
