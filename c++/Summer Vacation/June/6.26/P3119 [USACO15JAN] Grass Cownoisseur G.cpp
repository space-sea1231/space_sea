#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int cnt;
int from[N], head[N], to[N], nxt[N];
int u[N], v[N];

void Add(int u, int v) {
    from[++cnt] = u;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

namespace Tarjan {
    int num, top, tot;
    int dfn[N], low[N];
    int crr[N], belong[N];
    int sum[N];
    bool vis[N];

    void Dfs(int u) {
        dfn[u] = low[u] = ++num;
        crr[++top] = u, vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (!dfn[v]) {
                Dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (vis[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            tot++;
            int now = -1;
            while (now != u){
                now = crr[top--];
                belong[now] = tot;
                sum[tot]++;
                vis[now] = false;
            }
        }
    }
} using namespace Tarjan;

vector<int> q[N][2];
queue<int> p;
int f[N][2];
int ru[N][2];
bool viss[N][2];

void Topu(int flag) {
    for (int i = 1; i <= tot; i++) {
        if (!ru[i][flag]) p.push(i); 
    }
    viss[belong[1]][flag] = true;
    while (!p.empty()) {
        int u = p.front();
        p.pop();
        f[u][flag] += sum[u];
        for (auto v:q[u][flag]) {
            ru[v][flag]--;
            if (viss[u][flag]) {
                viss[v][flag] = true;
                f[v][flag] = max(f[v][flag], f[u][flag]);
            }
            if (!ru[v][flag]) p.push(v);
        }
    }
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        Add(u[i], v[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Dfs(i);
    }
    for (int i = 1; i <= m; i++) {
        u[i] = belong[from[i]];
        v[i] = belong[to[i]];
        if (u[i] == v[i]) continue;
        q[u[i]][0].push_back(v[i]);
        q[v[i]][1].push_back(u[i]);
        ru[v[i]][0]++;
        ru[u[i]][1]++;
    }
    Topu(0), Topu(1);
    int ans = sum[belong[1]];
    for (int i = 1; i <= m; i++) {
        if (viss[u[i]][1] && viss[v[i]][0]) ans = max(ans, f[u[i]][1] + f[v[i]][0] - sum[belong[1]]);
    }
    printf("%d\n", ans);
}