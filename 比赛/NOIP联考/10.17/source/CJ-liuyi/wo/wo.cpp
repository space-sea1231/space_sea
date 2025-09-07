#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define rll register long long
#define ll long long
#define MOD 998244353

int T,n,p[2000005];
bool vis[2000005];
ll fac[2000005],maxn,ans;
inline ll fast_pow(rll a,rll b){
    rll res=1;
    while(b){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}
inline void dfs(rint x){
    if(x==2*n+1){
        rll res=0;
        for(rint i=1;i<=n;i++)res+=abs(p[2*i]-p[2*i-1]);
        if(maxn<res)maxn=res,ans=1;
        else if(maxn==res)ans++;
        return ;
    }
    if(p[x])dfs(x+1);
    else{
        for(rint i=1;i<=2*n;i++){
            if(!vis[i]){
                p[x]=i,vis[i]=1;
                dfs(x+1);
                p[x]=vis[i]=0;
            }
        }
    }
}
int main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    fac[0]=1;
    for(rint i=1;i<=1000000;i++)fac[i]=fac[i-1]*i%MOD;
    cin>>T;
    while(T--){
        cin>>n,maxn=0,ans=0;
        for(rint i=1;i<=2*n;i++)vis[i]=0;
        for(rint i=1;i<=2*n;i++)cin>>p[i],vis[p[i]]=1;
        if(n<=5){
            dfs(1);
            cout<<ans%MOD<<"\n";
        }else{
            rll cnt1=n,cnt2=n;
            for(rint i=1;i<=n;i++){
                if(!p[2*i]&&p[2*i-1])swap(p[2*i],p[2*i-1]);
                if(p[2*i]){
                    if(p[2*i]<=n)cnt1--;
                    else cnt2--;
                }
                if(p[2*i-1]){
                    if(p[2*i-1]<=n)cnt1--;
                    else cnt2--;
                }
            }
            rll res=1,sum1=cnt1,sum2=cnt2;
            for(rint i=1;i<=n;i++){
                if(p[2*i]&&p[2*i-1])continue;
                if(p[2*i]){
                    if(p[2*i]<=n){
                        if(cnt2)res=res*cnt2%MOD,cnt2--;
                        else res=res*cnt1%MOD,cnt1--;
                    }else{
                        if(cnt1)res=res*cnt1%MOD,cnt1--;
                        else res=res*cnt2%MOD,cnt2--;
                    }
                }
            }
            for(rint i=1;i<=n;i++){
                if(p[2*i])continue;
                if(cnt1&&cnt2){
                    res=res*2*cnt1%MOD*cnt2%MOD;
                    cnt1--,cnt2--;
                }
            }
            if(!cnt1&&!cnt2)cout<<res<<"\n";
            else{
                if(cnt1)cout<<res*fac[sum1+sum2-cnt1/2]%MOD*fast_pow(fac[cnt1/2],MOD-2)%MOD*fast_pow(fac[sum1+sum2-cnt1],MOD-2)%MOD<<"\n";
                else cout<<res*fac[sum1+sum2-cnt2/2]%MOD*fast_pow(fac[cnt2/2],MOD-2)%MOD*fast_pow(fac[sum1+sum2-cnt2],MOD-2)%MOD<<"\n";
            }
        }
    }
    return 0;
}