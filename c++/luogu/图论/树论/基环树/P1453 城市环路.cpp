#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, s, t;
double k;
int cnt=1, ans;
int a[N], dp[N][2];
int head[N], nxt[N<<1], to[N<<1], val[N<<1];
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
namespace Pseduotree{
    int num;
    int father[N], dfn[N];
    void Dfs(int u, int fa){
        father[u]=fa;
        dfn[u]=++num;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            if (dfn[v]){
                if (dfn[v]>dfn[u]){
                    to[i]=to[i^1]=0;
                    s=u, t=v;
                }
            }else{
                Dfs(v, u);
            }
        }
    }

}using namespace Pseduotree;

void Dp(int u, int fa){
    dp[u][0]=0, dp[u][1]=a[u];
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa){
            continue;
        }
        Dp(v, u);
        dp[u][0]+=max(dp[v][0], dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    for (int i=1; i<=n; i++){
        int u, v;
        cin >> u >> v;
        u++, v++;
        Add(u, v), Add(v, u);
    }
    cin >> k;
    Dfs(1, 0);
    Dp(s, 0);
    ans=max(ans, dp[s][0]);
    Dp(t, 0);
    ans=max(ans, dp[t][0]);
    printf("%.1lf\n", ans*k);

    return 0;
}