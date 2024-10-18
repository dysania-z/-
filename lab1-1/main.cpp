#include<iostream>
#include<fstream>
#include<vector>
#include<windows.h>
#include<time.h>
#include<algorithm>
using namespace std;

void find(vector<int>& arr,int& maxnum,int& minnum,int l,int r)
{
    if(l==r)
    {
        maxnum=arr[l];
        minnum=arr[l];
        return;
    }
    int mid=(l+r)>>1;
    int maxl,maxr,minl,minr;
    find(arr,maxl,minl,l,mid);
    find(arr,maxr,minr,mid+1,r);
    maxnum=max(maxl,maxr);
    minnum=min(minl,minr);
}
int main()
{
/*ofstream 是 C++ 中的类，用于写入文件。它来自 <fstream> 头文件。
 outputFile 是创建的文件流对象，用来操作文件。
"input.txt" 是要打开或创建的文件的名称。文件会被保存在当前程序的工作目录下。*/   
  
  
  //生成不同大小的输入规模(1~100000)
  int n;
  ofstream out("output.txt");
   for(int n=1;n<=100000;n*=10)
   {
    //生成input.txt
    ofstream outputFile("input.txt");
    if (!outputFile) {
        cerr << "无法创建文件!" << endl;
        return 1;
    }
    outputFile << n<< endl;
    srand((unsigned)time(NULL));
    for(int i=0;i<n;i++)
    {
        outputFile<<rand()<<" ";
        if((i+1)%10==0) outputFile<<'\n';
    }
    outputFile.close();


    //从input.txt中读取数组
    ifstream in("input.txt");
    if (!in) {
        cerr << "无法打开文件!" << endl;
        return 1;
    }
    in>>n;
    vector<int> s(n);
    for(int i=0;i<n;i++)
    {
        in>>s[i];
    }
    
    //计算函数执行时间
    int i,maxnum,minnum;
	LARGE_INTEGER nFreq,nBegin,nEnd;
	double time; 
    QueryPerformanceFrequency(&nFreq);	//频率
	QueryPerformanceCounter(&nBegin);//开始时间
	find(s,maxnum,minnum,0,n-1);
	QueryPerformanceCounter(&nEnd);//结束时间
	time=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart; 
    
    cout<<"最大值:"<<maxnum<<" 最小值:"<<minnum<<"\n 查询时间:"<<time<<"s"<<endl;

    out<<time<<" ";
    in.close();
   }
  out.close();
  return 0;
}