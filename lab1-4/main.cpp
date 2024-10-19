 #include<iostream>
 using namespace std;
 int f(int n)
 {
     int i,j,ans;
  for(i=1;i<=n;i++)
  {
      for(j=1;j<=n;j++)
   {
       ans=((i+j+(n-3)/2)%n)*n+(i-j+(3*n-1)/2)%n+1;
       /**/
    if(j<n)
    {
     printf("%d ",ans);
    }
    else
     printf("%d\n",ans);
   }
  }
  return 0;
 }
 
 int main()
 {
   int n;
  while(scanf("%d",&n) && n)
  {
     f(n);
     printf("\n");
  }
 }