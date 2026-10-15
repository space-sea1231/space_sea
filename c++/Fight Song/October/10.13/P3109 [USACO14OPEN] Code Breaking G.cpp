#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;
const int Mod = 1234567;

int n, m;
int num;
int f[N], rt[N];
int vis[N];
int ch[N][11];
vector<int> e[N];
vector<string> q[N];

void Insert(int p, string s) {
    for (char c: s) {
        if (!ch[p][c - '0']) ch[p][c - '0'] = ++num, vis[num] = 1;
        p = ch[p][c - '0'];
    }
    f[p] = Mod - 1;
}
void App(int u, int x) {
    f[u] = f[u] * x % Mod;
    vis[u] = vis[u] * x % Mod;
}
void Down(int p) {
    for (int i = 0; i < 10; i++) if (ch[p][i]) App(ch[p][i], vis[p]);
    vis[p] = 1;
}
int Merge1(int x, int y, int sx, int sy) {
    if (x > y) swap(x, y), swap(sx, sy);
    if (!y) return 0;
    if (!x) {
        App(y, sx);
        return y;
    }
    int sum = Mod - sx * sy % Mod;
    Down(x), Down(y);
    sx = (sx + f[x]) % Mod, sy = (sy + f[y]) % Mod;
    sum = (sum + sx * sy) % Mod;
    for (int i = 0; i < 10; i++) ch[x][i] = Merge1(ch[x][i], ch[y][i], sx, sy);
    f[x] = sum;
    return x;
}
int Merge2(int x, int y) {
    if (!x || !y) return x + y;
    Down(x), Down(y);
    for (int i = 0; i < 10; i++) ch[x][i] = Merge2(ch[x][i], ch[y][i]);
    f[x] = (f[x] + f[y]) % Mod;
    return x;
}
void Dfs(int u) {
    for (int v : e[u]) Dfs(v);
    f[rt[u] = ++num] = 1; vis[num] = 1;
    for (string s: q[u]) Insert(rt[u], s);
    for (int v : e[u]) rt[u] = Merge1(rt[u], rt[v], 0, 0);
    int tmp = 0;
    for (int i = 0; i < 10; i++) tmp = Merge2(tmp, ch[rt[u]][i]);
    if (!tmp) vis[tmp = ++num] = 1;
    f[tmp] = (f[rt[u]] * 10 + f[tmp]) % Mod;
    rt[u] = tmp;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    for (int i = 0; i < N; i++) vis[i] = 1;
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        e[++fa].emplace_back(i);
    }
    for (int i = 1; i <= m; i++) {
        int x; string s;
        cin >> x >> s;
        q[++x].emplace_back(s);
    }
    Dfs(1);
    int ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * 10 % Mod;
    printf("%lld\n", (ans - f[rt[1]] + Mod) % Mod);
    
    return 0;
}