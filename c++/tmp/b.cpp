#include <bits/stdc++.h>
using namespace std;
int n,q,k,tr[6000010][2],sum[6000010],cnt,fp[130];
vector<int> vec[6000010];
const int mod=998244353;
long long a,l,r;
void chmod(int &x,int y) {
    x+=y;
    if (x>=mod) x-=mod;
}
void insert(long long p) {
    int u=1,t;
    ++sum[u];
    for (int i=59;~i;--i) {
        t=p>>i&1;
        if (!tr[u][t]) tr[u][t]=++cnt;
        u=tr[u][t];
        ++sum[u];
    }
}
void solve(int u,int d) {
    vec[u].resize(sum[u]);
    if (!d) return;
    if (tr[u][0]) solve(tr[u][0],d-1);
    if (tr[u][1]) solve(tr[u][1],d-1);
    for (int i=0;i<sum[tr[u][0]];++i) vec[u][i]=vec[tr[u][0]][i];
    for (int i=sum[tr[u][0]];i<sum[u];++i) {
        vec[u][i]=vec[tr[u][1]][i-sum[tr[u][0]]]+fp[2*d-2];
        if (vec[u][i]>=mod) vec[u][i]-=mod;
    }
    for (int i=0;i<sum[tr[u][1]];++i) chmod(vec[u][i],vec[tr[u][1]][i]);
    for (int i=sum[tr[u][1]];i<sum[u];++i) {
        chmod(vec[u][i],vec[tr[u][0]][i-sum[tr[u][1]]]);
        chmod(vec[u][i],fp[2*d-2]);
    }
}
int query(int u,int d,long long p,int x) {
    if (p==(1ll<<d)) return vec[u][x-1];
    if (p<=(1ll<<d-1)) {
        if (x<=sum[tr[u][0]]) return query(tr[u][0],d-1,p,x);
        return (query(tr[u][1],d-1,p,x-sum[tr[u][0]])+p%mod*fp[d-1])%mod;
    }
    long long q=p^1ll<<d-1;
    int t=query(u,d,1ll<<d-1,x);
    if (x<=sum[tr[u][1]]) return (query(tr[u][1],d-1,q  ,x)+t)%mod;
    return (query(tr[u][0],d-1,q,x-sum[tr[u][1]])+q%mod*fp[d-1]+t)%mod;
}
int main() {
    freopen("cosmic.in","r",stdin);
    freopen("cosmic.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q;
    cnt=1;
    for (int i=1;i<=n;++i) cin>>a,insert(a);
    fp[0]=1;
    for (int i=1;i<=120;++i) {
        fp[i]=fp[i-1]*2;
        if (fp[i]>=mod) fp[i]-=mod;
    }
    solve(1,60);
    for (int i=1;i<=q;++i) {
        cin>>l>>r>>k;
        if (l==0) cout<<query(1,60,r+1,k)<<'\n';
        else cout<<(query(1,60,r+1,k)-query(1,60,l,k)+mod)%mod<<'\n';
    }
}
/*

*/