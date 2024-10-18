 #include<iostream>
 #include<fstream>
 #include<windows.h>
 #include<time.h>
 #include<vector>

 using namespace std;

vector<int> temp;//用temp来储存合并后的临时数组
void half(vector<int>& nums,int left,int right)
{
    if(left>=right)
        return;//只剩一个元素时返回
    int m=(left+right)>>1;//分治
    half(nums,left,m);
    half(nums,m+1,right);//递归
    int cnt=0,i=left,j=m+1;//分别是temp数组，左子数组，右子数组的起始下标
    while(i<=m&&j<=right)
    {
        if(nums[i]<=nums[j])
            temp[cnt++]=nums[i++];
        else
            temp[cnt++]=nums[j++];
    }//将左右子数组中的元素按升序储存至temp数组中
    while(i<=m)
    {
        temp[cnt++]=nums[i++];
    }
    while(j<=right)
    {
        temp[cnt++]=nums[j++];
    }//处理左右数组中未处理完的元素
    for(int k=0;k<right-left+1;k++)
    {
        nums[k+left]=temp[k];//将temp内排好的顺序赋值给nums
    }    
}
vector<int> sortArray(vector<int>& nums) {
    temp.resize((int)nums.size(),0);//初始化temp
    int right=nums.size()-1;
    half(nums,0,right);
    return nums;
}
int main()
{
    int n;
    ofstream out("output.txt");
    for(int n=1;n<=100000;n*=10)
    {//生成不同数据规模的input.txt

    // cout<<"请输入生成数组大小： ";
    // cin>>n;

        ofstream outfile("input.txt");
        if (!outfile) 
        {
        cerr << "无法创建文件!" << endl;
        return 1;
        }
        outfile<<n<<'\n';
        srand((unsigned)time(NULL));
        for(int i=0;i<n;i++)
        {
            outfile<<rand()<<' ';
            if((i+1)%10==0) outfile<<'\n';
        }
        outfile.close();
        
        //读入input.txt
        ifstream in("input.txt");
        if (!in) 
        {
        cerr << "无法打开文件!" << endl;
        return 1;
        }
        int length;
        in>>length;
        vector<int> nums(length);
        for(int i=0;i<length;i++)
            in>>nums[i];
        in.close();
        // cout<<"排序前："<<endl;
        // for(int i=0;i<length;i++)
        //     cout<<nums[i]<<" ";

        LARGE_INTEGER nFreq,nBegin,nEnd;
        double time; 
        QueryPerformanceFrequency(&nFreq);	
        QueryPerformanceCounter(&nBegin);
        sortArray(nums);
        QueryPerformanceCounter(&nEnd);
        time=(double)(nEnd.QuadPart-nBegin.QuadPart)/(double)nFreq.QuadPart; 

        // cout<<endl;
        // cout<<"排序后："<<endl;
        // for(int i=0;i<length;i++)
        //     cout<<nums[i]<<" ";
        // cout<<endl;
        // cout<<"用时为";
        // cout<<time<<" "<<"s";
        out<<time<<" ";
        
		}
        out.close();
        return 0;
}