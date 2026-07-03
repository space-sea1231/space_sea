#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define lson x << 1
#define rson x << 1 | 1
#define mid (l + r) >> 1
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int a[N];

namespace SegmentTree {
    struct Node {
        bool up, down, equal;
        int maxn, minn;
    };

    Node node[N << 2];

    void Up(int x) {
        if (node[lson].maxn < node[rson].minn) node[x].up = node[lson].up & node[rson].up;
        if (node[lson].minn > node[rson].maxn) node[x].down = node[lson].down & node[rson].down;
        if (node[lson].maxn == node[rson].maxn) node[x].equal = node[lson].equal & node[rson].equal;
        node[x].maxn = max(node[lson].maxn, node[rson].maxn);
        node[x].minn = min(node[lson].minn, node[rson].minn);
    }
    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].up = node[x].down = node[x].equal = true;
            node[x].maxn = node[x].minn = a[l];
            return;
        }
        Build(lson, l, mid);
        Build(rson, mid + 1, r);
        Up(x);
    }
    void Add(int x, int l, int r, int L, int R, int y) {
        if (L <= l && r <= R) {
            node[x].maxn += y; node[x].minn += y;
            return;
        }
        if (L <= mid) Add(x << 1, l, mid, L, R, y);
        if (mid < R) Add(x << 1 | 1, mid + 1, r, L, R, y);
        Up(x);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    Build(1, 1, n);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            Add(1, 1, n, l, r, x);
        }
        if (opt == 2) {
            int l, r;
            cin >> l >> r;
        }
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
        }
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
        }
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
        }
    }
    return 0;
}