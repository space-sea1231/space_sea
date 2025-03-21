#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
const int INF = 0x7f7f7f7f;
int n, m;
int cnt;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int dis1[N], dis2[N], up[N];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dfs1(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) {
            continue;
        }
        Dfs1(v, u);
        if (dis1[u] < dis1[v] + w) {
            dis2[u] = dis1[u];
            dis1[u] = dis1[v] + w;
        }
        else if (dis2[u] < dis1[v] + w) {
            dis2[u] = dis1[v] + w;
        }
    }
}
void Dfs2(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) {
            continue;
        }
        up[v] = up[u] + w;
        if (dis1[v] + w != dis1[u]) {
            up[v] = max(up[u], dis1[u]+w);
        }else {
            up[v] = max(up[v], dis2[u]+w);
        }
        Dfs2(v, u);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    Dfs1(1, 0);
    Dfs2(1, 0);
    int ans, minn = INF;
    for (int i = 1; i <= n; i++) {
        if (minn > max(dis1[i], up[i])) {
            minn = max(dis1[i], up[i]);
        }
    }
    printf("%d\n", minn);

    return 0;
}