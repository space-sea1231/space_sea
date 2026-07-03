#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define mid ((l + r) >> 1)
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e5 + 10;

int n, m;
int a[N], b[N];

namespace PST {
    int num;
    int root[N];
    struct Node {
        int l, r;
        int cnt;
    };

    Node node[N << 5];
    
    int Build(int l, int r) {
        int p = ++num;
        if (l == r) return p;
        node[p].l = Build(l, mid);
        node[p].r = Build(mid + 1, r);
        return p;
    }
    int Update(int l, int r, int pos, int ver) {
        int p = ++num;
        node[p] = node[ver];
        node[p].cnt++;
        if (l == r) return p;
        if (pos <= mid) node[p].l = Update(l, mid, pos, node[ver].l);
        if (mid < pos) node[p].r = Update(mid + 1, r, pos, node[ver].r);
        return p;
    }
    int Query(int l, int r, int pos, int p, int q) {
        if (l == r) return l;
        int cur = node[node[q].l].cnt - node[node[p].l].cnt;
        if (pos <= cur) return Query(l, mid, pos, node[p].l, node[q].l);
        if (cur < pos) return Query(mid + 1, r, pos - cur, node[p].r, node[q].r);
        return 0;
    }
} using namespace PST;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    root[0] = Build(1, n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
        root[i] = Update(1, n, a[i], root[i - 1]);
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        printf("%d\n", b[Query(1, n, k, root[l - 1], root[r])]);
    }
    return 0;