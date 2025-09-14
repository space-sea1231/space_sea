#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
const int K = 30;

int n, k;
int cnt;
int head[N], to[N << 1], nxt[N << 1];
int sum[N];
int father[N][K], dep[N];

void Add(int u, int v) {
    cnt++;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void Dfs1(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        father[v][0] = u;
        dep[v] = dep[u] + 1;
        for (int j = 1; j < K; j++) {
            father[v][j] = father[father[v][j - 1]][j - 1];
        }
        Dfs1(v, u);
    }
    return;
}

void Dfs2(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        Dfs2(v, u);
        sum[u] += sum[v];
    }
    return;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; i >= 0; i--) {
        if (dep[father[x][i]] >= dep[y]) {
            x = father[x][i];
        }
    }
    if (x == y) return x;
    for (int i = K - 1; i >= 0; i--) {
        if (father[x][i] != father[y][i]) {
            x = father[x][i];
            y = father[y][i];
        }
    }
    return father[x][0];
}

signed main(){
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }
    Dfs1(1, 0);
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        sum[LCA(x, y)]--;
        sum[father[LCA(x, y)][0]]--;
        sum[x]++, sum[y]++;
    }
    Dfs2(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, sum[i]);
    printf("%d\n", ans);
    return 0;
}