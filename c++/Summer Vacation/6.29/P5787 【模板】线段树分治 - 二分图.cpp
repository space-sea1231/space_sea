#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m, k;
int top;
int fa[N << 1], sz[N << 1];
int s1[N << 1], s2[N << 1];
vector<int> q[N << 2];

struct Edge {
    int u, v;
};

Edge e[N << 1];

void Add(int x, int l, int r, int L, int R, int y) {
    if (L <= l && r <= R){
        q[x].emplace_back(y);
        return ;
    }
    int mid = l + r >> 1;
    if (L <= mid) Add(x << 1, l, mid, L, R, y);
    if (mid < R) Add(x << 1 | 1, mid + 1, r, L, R, y);
}
int Find(int x) {
    if (fa[x] == x) return x;
    return Find(fa[x]);
}
void Merge(int x, int y) {
    x = Find(x), y = Find(y);
    if (sz[x] < sz[y]) swap(x, y);
    fa[y] = x, sz[x] += sz[y];
    s1[++top] = x, s2[top] = y;
}
void Dfs(int x, int l, int r) {
    bool flag = true;
    int ed = top;
    for (auto i:q[x]) {
        if (Find(e[i].u) == Find(e[i].v)) {
            flag = false;
            break;
        }
        Merge(e[i].u, e[i].v + n);
        Merge(e[i].v, e[i].u + n);
    }
    int mid = l + r >> 1;
    if (flag) {
        if (l == r) printf("Yes\n");
        else {
            Dfs(x << 1, l, mid);
            Dfs(x << 1 | 1, mid + 1, r);
        }
    } else for (int i = l; i <= r; i++) printf("No\n");
    for (;top > ed; top--) fa[s2[top]] = s2[top], sz[s1[top]] -= sz[s2[top]];
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= n * 2; i++) fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> e[i].u >> e[i].v >> l >> r;
        if (l < r) Add(1, 1, k, l + 1, r, i);
    }
    Dfs(1, 1, k);
    return 0;
}