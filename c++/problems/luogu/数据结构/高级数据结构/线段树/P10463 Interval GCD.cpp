#include <iostream>
#include <stdio.h>
#include <assert.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n, m;
ll a[N];

ll Gcd(ll x, ll y) {
    if (x == 0) return y;
    if (y == 0) return x;
    while (x ^= y ^= x ^= y %= x);
    return y;
}

struct SegmentTree {
    struct Node {
        ll sum;
        ll gcd;
    };
    
    Node node[N << 2];

    Node PushUp(const Node L, const Node R) {
        Node tmp;
        tmp.sum = L.sum + R.sum;
        tmp.gcd = Gcd(L.gcd, R.gcd);
        return tmp;
    }
    
    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].sum = a[l];
            node[x].gcd = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        node[x] = PushUp(node[x << 1], node[x << 1 | 1]);        
        return;
    }

    void Add(int x, int l, int r, int pos, ll val) {
        if (l == r) {
            node[x].sum += val;
            node[x].gcd += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) Add(x << 1, l, mid, pos, val);
        else if (pos > mid) Add(x << 1 | 1, mid + 1, r, pos, val);
        node[x] = PushUp(node[x << 1], node[x << 1 | 1]);
        return;
    }

    Node Query(int x, int l, int r, const int L, const int R) {
        if (L <= l && r <= R) return node[x];
        int mid = (l + r) >> 1;
        if (R <= mid) return Query(x << 1, l, mid, L, R);
        if (L > mid) return Query(x << 1 | 1, mid + 1, r, L, R);
        return PushUp(Query(x << 1, l, mid, L, R), Query(x << 1 | 1, mid + 1, r, L, R));
    }
};

SegmentTree seg;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
    seg.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        char opt;
        cin >> opt;
        if (opt == 'C') {
            int l, r;
            ll d;
            cin >> l >> r >> d;
            seg.Add(1, 1, n, l, d);
            if (r + 1 <= n) seg.Add(1, 1, n, r + 1, -d);
        }
        if (opt == 'Q') {
            int l, r;
            cin >> l >> r;
            ll resa = seg.Query(1, 1, n, 1, l).sum, resb = 0;
            if (l + 1 <= r) resb = seg.Query(1, 1, n, l + 1, r).gcd;
            printf("%lld\n", abs(Gcd(resa, resb)));
        }
    }
    return 0;
}
/*
Gcd(a, b) = Gcd(a, a - b)
Gcd(a, b, c, d) = Gcd(a, a - b, b - c, c - d)
1 2 3 4 5
1 1 1 1 1
2 1 1 0 1

*/