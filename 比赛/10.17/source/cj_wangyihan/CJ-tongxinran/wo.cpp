#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
	return x*f;
}

void file(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);   
}

const int N=2e6+10,mod=998244353;
int T,n,p[N],vis[N];
int fac[N],pw[N];

int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b/=2;
    }
    return ans;
}

void solve(){
    memset(vis,0,sizeof(vis));
    n=read();
    n*=2;
    int cnt=0,num=0,w=0,t=0;
    for(int i=1;i<=n;i++){
        p[i]=read();
        if(i&1==1) continue;
        if(p[i] && p[i-1]) vis[p[i]]=vis[p[i-1]]=1;
        else if(!p[i] || !p[i-1]){
            vis[p[i]]=vis[p[i-1]]=-1;
            if(p[i] || p[i-1]) cnt++;
            num++;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==-1) t++;
        if(vis[i]!=1) w++;
        if(w>=num) {
            w=i;
            break;
        }
    }
    /*
    int ans=fac[num*2]*ksm(fac[cnt],mod-2)%mod*fac[cnt]%mod*fac[cnt]%mod;
    int s=pw[cnt];
    cout<<ans*s%mod<<"\n";*/
    int ans=fac[num-t]*fac[num-cnt+t]%mod*pw[num-cnt]%mod;
    cout<<ans<<"\n";
} 
signed main(){
    file();
	T=read();
    fac[0]=1,pw[0]=1;
    for(int i=1;i<N;i++)
        fac[i]=fac[i-1]*i%mod,pw[i]=pw[i-1]*2%mod;
    while(T--)
        solve();
	return 0;
}