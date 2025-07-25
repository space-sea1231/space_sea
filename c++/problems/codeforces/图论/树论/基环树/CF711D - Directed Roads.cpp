#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int Mod=1e9+7;
int n;
int cnt, sum, tot, cnt1;
int tmp[N];
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

namespace Pseudotree{
    int num;
    int dfn[N], father[N];
    bool vis[N];
    void Dfs(int u, int fa){
        dfn[u]=++num;
        father[u]=fa;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            if (dfn[v]){
                if (dfn[v]>dfn[u]){
                    while (v!=u){
                        tot++;
                        v=father[v];
                    }
                    tot++;
                }
            }else{
                Dfs(v, u);
            }
        }
    }
}using namespace Pseudotree;

int Power(int a, int b){
    int sum=1;
    while (b){
        if (b&1){
            sum=(sum*a)%Mod;
        }
        a=(a*a)%Mod;
        b>>=1;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int u=i, v;
        cin >> v;
        Add(u, v), Add(v, u);
    }
    for (int i=1; i<=n; i++){
        if (!dfn[i]){
            tot=0;
            Dfs(i, 0);
            tmp[++cnt1]=tot;
            sum+=tot;
        }
    }
    int ans=Power(2, n-sum);
    for (int i=1; i<=cnt1; i++){
        ans=(ans*(Power(2, tmp[i])-2))%Mod;
    }
    printf("%lld\n", ans);

    return 0;
}