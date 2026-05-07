#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int a[N];
int tmp[N];
vector<int> st[N], ed[N];

namespace PST {
    struct Node {
        ll sum, cnt;
        int l, r;
    };

    int num;
    int root[N];
    Node node[N << 9];

    int Insert(int l, int r, int pos, int val, int ver) {
        int p = ++num;
        node[p] = node[ver];
        node[p].cnt += val;
        node[p].sum += (ll)val * tmp[pos];
        if (l == r) return p;
        int mid = l + r >> 1;
        if (pos <= mid) node[p].l = Insert(l, mid, pos, val, node[ver].l);
        if (mid + 1 <= pos) node[p].r = Insert(mid + 1, r, pos, val, node[ver].r);
        return p;
    }

    ll Query(int l, int r, int pos, int ver) {
        if (l == r) return tmp[l] * pos;
        int lsiz = node[node[ver].l].cnt;
        int mid = l + r >> 1;
        if (pos <= lsiz) return Query(l, mid, pos, node[ver].l);
        else return Query(mid + 1, r, pos - lsiz, node[ver].r) + node[node[ver].l].sum;
    }
} using namespace PST;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y >> a[i];
        st[x].push_back(i);
        ed[y + 1].push_back(i);
        tmp[i] = a[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= m; i++) {
        root[i] = root[i - 1];
        for (auto v:st[i]) root[i] = Insert(1, len, lower_bound(tmp + 1, tmp + len + 1, a[v]) - tmp, 1, root[i]);
        for (auto v:ed[i]) root[i] = Insert(1, len, lower_bound(tmp + 1, tmp + len + 1, a[v]) - tmp, -1, root[i]);
    }
    ll pre = 1;
    for (int i = 1; i <= m; i++) {
        int x, a, b, c;
        cin >> x >> a >> b >> c;
        int k = 1 + ((ll)a * pre + b) % c;
        if (k > node[root[x]].cnt) pre = node[root[x]].sum;
        else pre = Query(1, len, k, root[x]);
        printf("%lld\n", pre);
    }
    return 0;
}