#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int P=998244353;
const int N=2e6+3;
ll fp(ll a,int b=P-2){
    ll ans=1;
    for(;b;b>>=1,a=a*a%P)
        if(b&1)ans=ans*a%P;
    return ans;
}
int inv[N],fc[N],p[N];
int n;
bitset<N>vis;
int C(int n,int m){if(n<m)return 0;return (ll)fc[n]*inv[m]%P*inv[n-m]%P;}
int A(int n,int m){if(n<m)return 0;return (ll)fc[n]*inv[n-m]%P;}
void solve(){
    int u,v,w,x,y,z;
    cin>>n;
    for(int i=0;i<=n<<1;++i)vis[i]=0;
    for(int i=1;i<=n<<1;++i)cin>>p[i];
    int c3=0;
    for(int i=1;i<=n;++i)
        if(p[i*2]&&p[i*2-1])
            vis[p[i*2]]=vis[p[i*2-1]]=1;
        else if(!p[i*2]&&!p[i*2-1])++c3;
    int sum=0;
    for(int i=1;i<=n<<1;++i)sum+=!vis[i];
    int mid=1;
    for(int k=0;;++mid){
        if(!vis[mid])++k;
        if(k==sum/2)break;
    }
    int c1=0,c2=0;
    for(int i=1;i<=n<<1;++i)if(!vis[p[i]]&&p[i])
        if(p[i]<=mid)++c1;
        else ++c2;
    c1=sum/2-c1;c2=sum/2-c2;
    // printf("%d %d\n",c1,c2);
    printf("%lld\n",(ll)fc[c1]*fc[c2]%P*fp(2,c3)%P);
}
int main(){
    int u,v,w,x,y,z;
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    inv[0]=fc[0]=1;
    for(int i=1;i<N;++i)fc[i]=(ll)fc[i-1]*i%P;
    inv[N-1]=fp(fc[N-1]);
    for(int i=N-2;i;--i)inv[i]=(i+1ll)*fc[i+1]%P;
    int T;for(cin>>T;T--;)solve();
    return 0;
}