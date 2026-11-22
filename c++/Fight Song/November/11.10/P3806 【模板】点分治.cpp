#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;
const int M = 1e2 + 10;
const int K = 1e7 + 10;

int n, m;
int root, mnsiz, top;
int qry[M], que[N];
int siz[N], dis[N], mxsiz[N], belong[N];
bool vis[N], ans[N];
vector<pair<int, int> > e[N];

void Dfs1(int u, int fa, int sz) {
    int maxn = 0;
    mxsiz[u] = 0, siz[u] = 1;
    for (auto [v, w] : e[u]) {
        if (v == fa || vis[v]) continue;
        Dfs1(v, u, sz);
        siz[u] += siz[v];
        mxsiz[u] = max(mxsiz[u], siz[v]);
    }
    mxsiz[u] = max(mxsiz[u], sz - siz[u]);
    if (mnsiz > mxsiz[u]) {
        mnsiz = mxsiz[u];
        root = u;
    }
}
void Dfs3(int u, int fa, int dist, int root) {
    que[++top] = u;
    dis[u] = dist;
    belong[u] = root;
    for (auto [v, w] : e[u]) {
        if (v == fa || vis[v]) continue;
        Dfs3(v, u, dist + w, root);
    }
}
void Calc(int u) {
    que[top = 1] = u;
    dis[u] = 0;
    belong[u] = u;
    for (auto [v, w] : e[u]) {
        if (vis[v]) continue;
        Dfs3(v, u, w, v);
    }
    sort(que + 1, que + top + 1, [&](int a, int b) {
        return dis[a] < dis[b];
    });
    for (int i = 1; i <= m; i++) {
        int l = 1, r = top;
        while (l < r) {
            if (dis[que[l]] + dis[que[r]] > qry[i]) r--;
            else if (dis[que[l]] + dis[que[r]] < qry[i]) l++;
            else if (belong[que[l]] == belong[que[r]]) {
                if (dis[que[r]] == dis[que[r - 1]]) r--;
                else l++;
            } else {
                ans[i] = true;
                break;
            }
        }
    }
}
void Dfs2(int u) {
    vis[u] = true;
    Calc(u);
    for (auto [v, w] : e[u]) {
        if (vis[v]) continue;
        root = 0; mnsiz = INF;
        Dfs1(v, 0, siz[v]);
        Dfs2(root);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(make_pair(v, w));
        e[v].emplace_back(make_pair(u, w));
    }
    for (int i = 1; i <= m; i++) cin >> qry[i];
    mnsiz = INF;
    Dfs1(1, 0, n); Dfs2(root);
    for (int i = 1; i <= m; i++) printf("%s\n", ans[i] ? "AYE":"NAY");
    return 0;
}
/*
Frost paints the sleeping land with patient silver.
雾耐心的给沉睡的大地刷上银色
*/