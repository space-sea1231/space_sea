#include<bits/stdc++.h>
#define int long long
using namespace std;
const int P=998244353;
int power(int x,int y=P-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    if(y&1)return tmp*tmp%P*x%P;
    return tmp*tmp%P;
}
int T;
int n;
int p[2000005];;
bool vis[2000005];
int rnk[2000005];
bool tag[2000005];
int fac[2000005];
int invfac[2000005];
int C(int n,int m){
    return fac[n]*invfac[m]%P*invfac[n-m]%P;
}
void solve(){//对于已经配对的就不管，否则的话必然能够配满，然后取到分界点之后，考虑只要分配好单点，数对可以直接阶乘，这就变成单纯的组合数了
    scanf("%lld",&n);
    for(int i=1;i<=2*n;i++){
        scanf("%lld",&p[i]);
        rnk[p[i]]=i;
        vis[i]=false;
    }
    for(int i=1;i<=2*n;i++){
        for(int j=i+1;j<=2*n;j++){
            if(!p[i]||!p[j])continue;
            assert(p[i]^p[j]);
        }
    }
    vector<int> tmp;
    //假设现在有i个单点和j个对
    int all=2*n;
    for(int i=1;i<=2*n;i+=2){
        if(p[i]&&p[i+1]){//标记掉数对
            vis[p[i]]=vis[p[i+1]]=true;
            all-=2;
        }
    }
    // printf("all=%lld\n",all);
    int neta=0,need=-1;
    int ruozhi=0;
    for(int i=1;i<=2*n;i++){
        ruozhi+=!vis[i];
    }//
    // printf("ruozhi=%lld\n",ruozhi);//有283个位置是空的,但是只有135个双0
    for(int i=1;i<=2*n;i++){
        // printf("%lld ",vis[i]);
        neta+=!vis[i];
        if(neta*2==all){//说明i就是分界点
            need=i;
            break;
        }
    }
    // puts("");
    int ans=1;//假设现在要填X个大点和Y个小点，那就把他们组进空对，然后两边各自阶乘
    //
    // printf("need=%lld\n",need);
    int X=2*n-need,Y=need;
    for(int i=1;i<=2*n;i++){
        if(!p[i])continue;
        if(p[i]>need)X--;
        else Y--;
    }
    int seta=0;
    for(int i=1;i<=2*n;i+=2){
        if(!p[i]&&!p[i+1]){
            seta++;
        }
    }
    // printf("%lld %lld %lld\n",X,Y,seta);
    ans=C(X,seta)*C(Y,seta)%P*fac[seta]%P*fac[X-seta]%P*fac[seta]%P*fac[Y-seta]%P;
    ans=ans*power(2,seta)%P;
    printf("%lld\n",ans);
    return;
}
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    fac[0]=1;
    for(int i=1;i<=2000000;i++)fac[i]=fac[i-1]*i%P;
    invfac[2000000]=power(fac[2000000]);
    for(int i=2000000;i>=1;i--)invfac[i-1]=invfac[i]*i%P;
    scanf("%lld",&T);
    while(T--){
        solve();
    }
    return 0;
}
/*
原来是相邻两个数，唐吧。

考虑对于一个数，如果他在n以上，我肯定希望他做加法，反之我希望他做减法。

抛开已经确定状态的不谈，把剩下的都弄正。

然后每个点有一个集合表示他必须选这个集合里的点才可以。
*/