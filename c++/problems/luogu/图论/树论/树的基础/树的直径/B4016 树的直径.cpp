#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int cnt, ans;
int head[N], to[N<<1], nxt[N<<1];
int dp[N];
void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;
        Dfs(v, u);
        ans=max(ans, dp[u]+dp[v]+1);
        dp[u]=max(dp[u], dp[v]+1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Dfs(1, 0);
    printf("%d\n", ans);

    return 0;
}