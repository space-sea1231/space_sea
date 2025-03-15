#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, s, t;
int cnt, sum;
int head[N], nxt[N << 1], to[N << 1];
int dis[N], pre[N];
void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) {
            continue;
        }
        dis[v] = dis[u] + 1;
        pre[v] = u;
        Dfs(v, u);
        if (dis[s] < dis[v]) {
            s=v;
        }
    }
}
int main() {    
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    Dfs(1, 0);
    dis[s] = 0, pre[s] = 0;
    Dfs(s, 0);
    t=s;
    while (pre[s]){
        sum++;
        s=pre[s];
    }
    printf("%d\n", ((n-1)<<1)-sum+1);

    return 0;
}