#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll mod=998244353;
const ll INF=1e9+8;
int A[3000010],opt[39000010];
int n,x,y,Ans,q,p[2]={1,-1};
char s[3000010];
void sol()
{
   for(int i=1;i<n-1;i++)
   {
      if(A[i]==0)
      {
         opt[++q]=i+1;
         if(!A[i+1]) Ans++,Ans+=p[A[i+2]],A[i+2]^=1,A[i]=1;
         else
         {
            Ans-=A[i+2];A[i+2]=0;
            if(i+2<n)
            {
               opt[++q]=i+2;Ans+=p[A[i+3]],A[i+3]^=1;A[i+1]=0;
               opt[++q]=i+1;Ans++,A[i+2]=A[i]=1;
            }
         }
      }
      if(Ans==n-1) break;
   }
   if(Ans==n-1) return;
   if(A[n]==0&&A[n-1]==0)
   {
      Ans=n-1;
      opt[++q]=n-2;opt[++q]=n-1;opt[++q]=n-2;
   }
   else if(A[n]==0&&n>4)
   {
      Ans=n-1;
      opt[++q]=n-3;opt[++q]=n-2;opt[++q]=n-1;
      opt[++q]=n-3;opt[++q]=n-2;
   }return;
}
int main()
{
   freopen("shi.in","r",stdin);
   freopen("shi.out","w",stdout);
   int T;scanf("%d",&T);
   while(T--)
   {
      scanf("%s",(s+1));n=strlen(s+1);Ans=q=0;
      for(int i=1;i<=n;i++) A[i]=s[i]-'0',Ans+=A[i];
      if(n<=2||Ans==n){printf("%d 0\n",Ans);puts("");continue;}
      if(n==3)
      {
         if(!Ans) q=1,Ans+=2;
         printf("%d %d\n",Ans,q);
         if(q) printf("2");puts("");continue;
      }
      sol();printf("%d %d\n",Ans,q);
      for(int i=1;i<=q;i++) printf("%d ",opt[i]);puts("");
   }
   return 0;
}