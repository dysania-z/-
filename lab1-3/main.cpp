#include<cstdio>
using namespace std;
//const double eps=1e-8;
//#define zero(x)(((x)>0?(x):(-x))<eps)
const int maxn = 1000000 + 10;
long long a[maxn];
int n;
long long INF = 0x7FFFFFFF;
 
int main() {
  int T;
  scanf("%d", &T);
  while(T --) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
      scanf("%lld", &a[i]);
    }
    long long ans = 0;
    long long num;
    int pos1 = -1, pos2 = -1;
 
    for(int i = 1; i <= n; i ++) {
      if(pos1 == -1) pos1 = i;
      if(a[i] < a[pos1]) pos1 = i;
    }
    for(int i = 1; i <= n; i ++) {
      if(pos1 == i) continue;
      if(pos2 == -1) pos2 = i;
      if(a[i] < a[pos2]) pos2 = i;
    }
    ans = a[pos1] + a[pos2];
    printf("%lld\n", ans);
  }
  return 0;
}