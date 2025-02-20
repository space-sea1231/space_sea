#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll mod=998244353;
const ll INF=4e18;
mt19937 rd(random_device{}());
int P[2000010],id[2000010],res[2000010];
ll maxv,tAns,Ans;
vector<int> V;
int T,md,n,x,y;
ll m,pm;
int main()
{
   freopen("wo.in","r",stdin);
   freopen("wo.out","w",stdout);
   int T;scanf("%d",&T);
   while(T--)
   {
      scanf("%d",&n);n*=2;V.clear();V.push_back(0);Ans=1;pm=m=0;
      for(int i=1;i<=n;i++) scanf("%d",&P[i]),res[i]=0;
      for(int i=1;i<=n/2;i++) if(P[i*2-1]&&P[i*2]) res[P[i*2-1]]=res[P[i*2]]=1;
      for(int i=1;i<=n;i++) if(!res[i]) V.push_back(i);
      md=V[V.size()/2];
      for(int i=1;i<=n;i++) res[P[i]]=1;
      for(int i=1;i<=n;i++) if(!res[i]) i>md?pm++:m++;
      for(int i=1;i<=n/2;i++)
      {
         if(P[i*2-1]&&P[i*2]) continue;
         else if((!P[i*2-1])&&(!P[i*2])) (Ans*=m*pm%mod)%=mod,(Ans*=2)%=mod,m--,pm--;
         else if(P[i*2-1]) Ans*=(P[i*2-1]<=md)?pm--:m--,Ans%=mod;
         else Ans*=(P[i*2]<=md)?pm--:m--,Ans%=mod;
      }
      printf("%lld\n",Ans);
   }
   return 0;
}