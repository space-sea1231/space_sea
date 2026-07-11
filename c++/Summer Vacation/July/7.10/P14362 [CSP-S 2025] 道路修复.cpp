#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 4e4 + 10;
const int M = 2e6 + 10;

int n, m, k, l;
int cnt1, cnt2;
bool vis[N];
int fa[N];
int a[N];
int ans = INF;

struct Node {
    int u, v, w;
    int pos;
    bool operator<(const Node src) const {
        return w < src.w;
    }
};
Node node1[M], node2[M];

void Add1(int u, int v, int w) {
    node1[++cnt1].u = u;
    node1[cnt1].v = v;
    node1[cnt1].w = w;
}
void Add2(int u, int v, int w) {
    node2[++cnt2].u = u;
    node2[cnt2].v = v;
    node2[cnt2].w = w;
        // cerr<<u << ' ' << v << " " << w << endl;
}
int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}
void Kruskal1() {
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int u = node1[i].u, v = node1[i].v;
        if (Find(u) == Find(v)) continue;
        node2[++cnt2] = node1[i];
        fa[Find(u)] = fa[Find(v)];
        if (++tot == n - 1) return;
    }
}
void Kruskal2(int flag, int sum) {
    // cerr<<flag<<" " << sum << endl;
    // for (int i = 1; i <= n + k; i++) printf("vis[%d]=%d ", i, vis[i]);
    // printf("\n");
    for (int i = 1; i <= n + k; i++) fa[i] = i;
    int tot = 0;
    for (int i = 1; i <= l; i++) {
        int u = node2[i].u, v = node2[i].v, w = node2[i].w;
        // printf("%d u=%d v=%d %d\n", flag, u, v, tot);
        if (Find(u) == Find(v) || vis[u]) continue;
        sum += w;
        fa[Find(u)] = fa[Find(v)];
        if (++tot == flag) {
            // cerr<<1;
            ans = min(ans, sum);
            return;
        }
    }
}
void Dfs(int cur, int tot, int sum) {
    if (cur == n + k + 1) {
        Kruskal2(tot, sum);
        return;
    }
    vis[cur] = false;
    Dfs(cur + 1, tot + 1, sum + a[cur]);
    vis[cur] = true;
    Dfs(cur + 1, tot, sum);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        Add1(u, v, w);
    }
    sort(node1 + 1, node1 + m + 1);
    Kruskal1();
    // for (int i = 1; i < n; i++) printf("Debug u=%d v=%d w=%d\n", node2[i].u, node2[i].v, node2[i].w);
    for (int i = 1; i <= k; i++) {
        cin >> a[i + n];
        for (int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            Add2(i + n, j, w);
        }
    }
    l = n * k + n - 1;
    sort(node2 + 1, node2 + l + 1);
    Dfs(n + 1, n - 1, 0);
    printf("%lld\n", ans);
    return 0;
}