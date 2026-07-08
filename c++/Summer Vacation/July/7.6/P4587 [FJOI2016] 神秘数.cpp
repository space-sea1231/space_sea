#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define mid ((l + r) >> 1)
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
namespace PST {
    int num;
    int root[N];
    struct Node {
        int l, r;
        int val;
    };
    
    Node node[N << 5];

    // int Build(int l, int r) {
    //     int p = ++num;
    //     if (l == r) return p;
    //     node[p].l = Build(l, mid);
    //     node[p].r = Build(mid + 1, r);
    //     return p;
    // }
    int Update(int q, int l, int r, int pos, int val) {
        int p = ++num;
        node[p] = node[q];
        node[p].val += val;
        if (l == r) return p;
        if (pos <= mid) node[p].l = Update(node[q].l, l, mid, pos, val);
        if (mid < pos) node[p].r = Update(node[q].r, mid + 1, r, pos, val);
        return p;
    }
    int Query(int p, int q, int l, int r, int L, int R) {
        if (node[q].val - node[p].val == 0) return 0;
        if (L <= l && r <= R) return node[q].val - node[p].val;
        int sum = 0;
        if (L <= mid) sum += Query(node[p].l, node[q].l, l, mid, L, R);
        if (mid < R) sum += Query(node[p].r, node[q].r, mid + 1, r, L, R);
        return sum;
    }
} using namespace PST;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    // root[0] = Build(1, INF);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        root[i] = Update(root[i - 1], 1, INF, x, x);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        int ans = 0, last = 0;
        while (true) {
            int tmp = Query(root[l - 1], root[r], 1, INF, last + 1, ans + 1);
            if (tmp) {last = ans + 1; ans += tmp;}
            else break;
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}