#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int dis[20][20];
int need[20][20];
int n,m;
int mp[20][20];
int dp[1<<16][20],num[1<<16][20];
const int P=998442353;
int lowbit(int x){
    return x&-x;
}
int popcount(int x){
    int tmp=0;
    while(x){
        tmp++;
        x-=lowbit(x);
    }
    return tmp;
}
int fac[4000005];
int invfac[4000005];
int power(int x,int y=P-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    if(y&1)return tmp*tmp%P*x%P;
    return tmp*tmp%P;
}
//先全排列再去差异化
void solve(){
    scanf("%lld%lld",&n,&m);
    for(int i=0;i<m;i++){
        for(int j=1;j<=n;j++){
            scanf("%lld",&mp[i][j]);
        }
    }
    for(int S=0;S<(1<<m);S++){
        for(int i=0;i<m;i++){
            dp[S][i]=1e18;
        }
    }
    int flg=false;
    for(int i=0;i<m;i++){
        int tmp;
        scanf("%lld",&tmp);
        if(tmp){
            num[(1<<i)][i]=1;
            dp[(1<<i)][i]=0;
        }
        flg|=tmp;
    }
    if(!flg){
        puts("NIE");
        return;
    }
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            int tmp=0;
            int num=1;
            int all=0;
            for(int k=1;k<=n;k++){
                int len=abs(mp[i][k]-mp[j][k]);
                tmp+=len;
                num=num*invfac[len]%P;
                all+=len;
            }
            num=num*fac[all]%P;
            dis[i][j]=dis[j][i]=tmp;
            need[i][j]=need[j][i]=num;
        }
    }
    for(int S=1;S<(1<<m);S++){
        // if(popcount(S)==1)continue;
        for(int i=0;i<m;i++){//集合为S 结尾为i
            if((S>>i)&1){
                // printf("S=%lld now=%lld dp=%lld\n",S,i,dp[S][i]);
                for(int j=0;j<m;j++){
                    if((S>>j)&1)continue;
                    if(dp[S][i]+dis[i][j]<dp[S|(1<<j)][j]){
                        dp[S|(1<<j)][j]=dp[S][i]+dis[i][j];
                        num[S|(1<<j)][j]=0;
                    }
                    if(dp[S|(1<<j)][j]==dp[S][i]+dis[i][j]){
                        num[S|(1<<j)][j]+=num[S][i]*need[i][j];
                        num[S|(1<<j)][j]%=P;
                    }
                }
            }
        }
    }
    int ans=1e18;
    int all=0;
    for(int i=0;i<m;i++){
        if(dp[(1<<m)-1][i]<ans){
            ans=dp[(1<<m)-1][i];
            all=0;
        }
        if(dp[(1<<m)-1][i]==ans){
            all+=num[(1<<m)-1][i];
            if(all>=P)all-=P;
        }
    }
    printf("%lld %lld\n",ans,all);
    return;
}
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    fac[0]=1;
    for(int i=1;i<=4000000;i++)fac[i]=fac[i-1]*i%P;
    invfac[4000000]=power(fac[4000000]);
    for(int i=4000000;i>=1;i--)invfac[i-1]=invfac[i]*i%P;
    scanf("%lld",&T);
    while(T--){
        solve();
    }
    return 0;
}
/*
容易发现这个东西就是相邻两个点之间移动的方案数。


*/