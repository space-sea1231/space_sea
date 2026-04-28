#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e3 + 10;

int n, m;
int num, cnt;
int c[N << 1];
int head[N << 1], to[N << 1], nxt[N << 1];
int siz[N << 1], dfn[N << 1];
int f[N << 1][N];

void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void Dfs(int u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        Dfs(v);
        siz[u] += siz[v];
    }
    dfn[++num] = u;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int u = 1; u <= n - m; u++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int v;
            cin >> v >> c[v];
            Add(u, v);
            c[v] = -c[v];
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        int a;
        cin >> a;
        c[i] += a;
    }
    Dfs(1);
    memset(f, 0xcf, sizeof(f));
    for (int i = 0; i <= n; i++) f[i][0] = 0;
    for (int i = 1; i <= n; i++) {
        int u = dfn[i];
        for (int j = 1; j <= m; j++) {
            if (n - m + 1 <= u) f[i][j] = max(f[i - 1][j - 1] + c[u], f[i - 1][j]);
            else f[i][j] = max(f[i - siz[u]][j], f[i - 1][j] + c[u]);
        }
    }
    for (int i = m; i >= 0; i--) {
        if (f[n][i] >= 0) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}