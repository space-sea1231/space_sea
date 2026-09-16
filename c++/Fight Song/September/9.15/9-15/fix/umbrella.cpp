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
const int N = 2e6 + 10;

int n, Q;
int num;
int root;
int fa[N], dfn[N], siz[N];
bool vis[N];
vector<int> e[N], e1[N], cont[N];

void Dfs(int u) {
    dfn[u] = ++num;
    siz[u] = 1;
    if (u <= n) {cont[u].emplace_back(u); return;}
    int son = 0;
    for (int v:e[u]) {
        Dfs(v);
        siz[u] += siz[v];
        if (dfn[v] <= dfn[u - n]) son = v;
    }
    // printf("son[%d]=%d\n", u, son);
    if (son) {
        for (int v:e[u]) {
            if (v == son) continue;
            for (int v1:cont[v]) {
                e1[u - n].emplace_back(v1);
                // printf("%d -> %d\n", u-n, v1);
                vis[v1] = true;
            }
            cont[v].clear();
        }
        swap(cont[u], cont[son]); // u=son;
    } else {
        for (int v:e[u]) {
            if (cont[u].size() < cont[v].size()) swap(cont[u], cont[v]);
            for (int i:cont[v]) cont[u].emplace_back(i);
            cont[v].clear();
        }
    }
}
void Dfs1(int u) {
    dfn[u] = ++num;
    siz[u] = 1;
    for (int v:e1[u]) {
        Dfs1(v);
        siz[u] += siz[v];
    }
}
bool Check(int a, int b) {
    if (dfn[a] > dfn[b]) swap(a, b);
    return dfn[b] < dfn[a] + siz[a];
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> Q;
    for (int i = 1; i <= (n << 1); i++) {
        cin >> fa[i];
        if (!fa[i]) root = i;
        e[fa[i]].emplace_back(i);    
    }
    // cerr<<root;
    Dfs(root); num = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]){
            Dfs1(i);
        }
    }
    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (Check(a, b)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}