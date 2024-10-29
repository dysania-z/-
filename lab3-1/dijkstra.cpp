#include<iostream>
#include<vector>
#include<windows.h>
#include<fstream>
#include<time.h>
using namespace std;
void dijkstra(vector<vector<int>> gragh,vector<int>& dist,vector<int>& prev,int n,int s)
{
    vector<bool> visited(n+1);
    //初始化dist，prev，visited数组
    for(int i=1;i<=n;i++)
    {
  
        if(gragh[s][i]!=INT_MAX)
        {
            dist[i]=gragh[s][i];
            prev[i]=s;
        }
        else
        {
            dist[i]=INT_MAX;
            prev[i]=0;
        }
    }
    visited[s]=true;
    dist[s]=0;
    prev[s]=0;
    //通过n-1次循环实现dijkstra算法
    
    for(int i=1;i<n;i++)
    {
        int temp=INT_MAX;
        int u=s;//若没有找到最小节点
        //找到当前s中未被访问的，dist最小的那个节点
        for(int j=1;j<=n;j++)
        {
            if(!visited[j]&&dist[j]<temp)
            {
                temp=dist[j];
                u=j;
            }
        }
        visited[u]=true;
        // if(temp=INT_MAX)
        //     break;
        //更新经过过u的路径的长度；
        for(int j=1;j<=n;j++)
        {
            if(!visited[j])
            {
                if(gragh[u][j]+dist[u]<dist[j]&&gragh[u][j]+dist[u]>=0)
                {
                    dist[j]=gragh[u][j]+dist[u];
                     prev[j]=u;
                }
                
            }
        }
    }
}

int main(){
	ofstream out1("output.txt");
	while(1){
		//生成规模为n的随机数 
		cout<<"请输入顶点个数n："<<endl; 
		int n;
		cin>>n;
		ofstream out("input1.txt");
		out<<n<<'\n';
		srand((unsigned)time(NULL));
		//time()返回一个一直在变化的时间作为随机数种子来生成随机数
 
    	// 设置概率值，矩阵中不可达边的概率 
        double probability=(double)(rand()) / RAND_MAX;
   		 //double probability = 0.1;
 
		// c数组 不妨设置权重范围为(a,b] 
		 int a=0,b=100;
		
		LARGE_INTEGER nFreq,nBegin,nEnd;
		double time1; 
		QueryPerformanceFrequency(&nFreq);	
		QueryPerformanceCounter(&nBegin);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
             {
				 // 生成一个介于0到1之间的随机小数
    			double randomValue = (double)(rand()) / RAND_MAX;
                //如果srand（）的种子一样，就会导致rand（）产生的随机数一样
                if(i==j)
                {
                    out<<0<<' ';
                   // cout<<0<<" ";
                }
    			else if (randomValue < probability) {
                    //cout<<randomValue<<" "<<probability<<endl;
        			// 有probability的概率输出MAXINT,一定不能设置为-1，因为这样会被当做一条有值的边加入计算！
       				 out<< INT_MAX <<' ';
                    // cout<<INT_MAX<<" ";
   				}
				else {
			        // 有(1 - probability)的概率输出(a,b]间的整数
			        int randomWeight = (rand() % (b - a)) + a + 1;
                    out << randomWeight << ' ';
                   // cout << randomWeight << ' ';
    			}
                
			}
			out<<'\n';
            //cout<<endl;.
            
		}
		QueryPerformanceCounter(&nEnd);
		time1=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart; 
		
		cout<<"生成时间:"<<time<<endl;
		out.close();
	
 
		
		ifstream in("input1.txt");
		
		in>>n;
	//	cout<<"n= "<<n<<endl; 
		vector<vector<int> > c(n+1, vector<int>(n+1));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				in>>c[i][j];
			    //cout<<c[i][j]<<" ";
			}
			//cout<<endl;
		}
 
		vector<int> dist(n+1);
		vector<int> prev(n+1);
 
		a=0;
		b=n;
		int v=(rand() % (b-a))+ a + 1;//源 [1,n]
		cout<<"v:"<<v<<endl;
        double time2;
		QueryPerformanceFrequency(&nFreq);	
		QueryPerformanceCounter(&nBegin);

		dijkstra(c, dist, prev, n,v);

		QueryPerformanceCounter(&nEnd);
		time2=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart; 
        // cout<<"dist: "<<endl;
		// for(int i=1;i<=n;i++)
        // {
        //     cout<<dist[i]<<" ";
        // }
        // cout<<endl<<"prev: "<<endl;
		// for(int i=1;i<=n;i++)
        // {
        //     cout<<prev[i]<<" ";
        // }
		cout<<"查询时间:"<<time2<<endl<<endl;
		out1<<n<<' '<<time2<<endl;
		in.close();		
	}
	out1.close();
	return 0;
}
