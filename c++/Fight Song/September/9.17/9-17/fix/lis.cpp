#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int siz = 1e6;

int n, Q;
int a[N];
int prevr[N], prevl[N];
namespace SegmentTree {
    struct Node {
        int l, r;
        int vl, vr;
        int ans;
    }; Node node[siz << 2];

    void Up(int p) {
        node[p].vl = max(node[p << 1].vl, node[p << 1 | 1].vl);
        node[p].vr = max(node[p << 1].vr, node[p << 1 | 1].vr);
        node[p].ans = max(node[p << 1].vl + node[p << 1 | 1].vr, max(node[p << 1].ans, node[p << 1 | 1].ans));
    }
    void UpdateL(int p, int l, int r, int pos, int val) {
        if (l == r) {
            node[p].vl = val;
            node[p].ans = max(node[p].vl, node[p].vr);
            return ;
        }
        int mid = l + r >> 1;
        if (pos <= mid) UpdateL(p << 1, l, mid, pos, val);
        if (mid < pos) UpdateL(p << 1 | 1, mid + 1, r, pos, val);
        Up(p);
    }
    void UpdateR(int p, int l, int r, int pos, int val) {
        if (l == r) {
            node[p].vr = val;
            node[p].ans = max(node[p].vl, node[p].vr);
            return ;
        }
        int mid = l + r >> 1;
        if (pos <= mid) UpdateR(p << 1, l, mid, pos, val);
        if (mid < pos) UpdateR(p << 1 | 1, mid + 1, r, pos, val);
        Up(p);
    }
    int QueryR(int p, int l, int r, int L, int R) {
        if (L > R) return 0;
        if (L <= l && r <= R) {
            return node[p].vr;
        }
        int mid = l + r >> 1;
        if (mid >= R) return QueryR(p << 1, l, mid, L, R);
        if (mid < L) return QueryR(p << 1 | 1, mid + 1, r, L, R);
        return max(QueryR(p << 1, l, mid, L, R), QueryR(p << 1 | 1, mid + 1, r, L, R));
    }
    int QueryL(int p, int l, int r, int L, int R) {
        if (L > R) return 0;
        if (L <= l && r <= R) {
            return node[p].vl;
        }
        int mid = l + r >> 1;
        // cerr<<L << " " << R << ":  " << l  << " " << r << "\n";
        if (mid >= R) return QueryL(p << 1, l, mid, L, R);
        if (mid < L) return QueryL(p << 1 | 1, mid + 1, r, L, R);
        return max(QueryL(p << 1, l, mid, L, R), QueryL(p << 1 | 1, mid + 1, r, L, R));
    }
    int QueryA(int p, int l, int r, int L, int R) {
        if (L > R) return 0;
        if (L <= l && r <= R) {
            return node[p].ans;
        }
        int mid = l + r >> 1;
        if (mid >= R) return QueryA(p << 1, l, mid, L, R);
        if (mid < L) return QueryA(p << 1 | 1, mid + 1, r, L, R);
        return max(QueryA(p << 1, l, mid, L, R), QueryA(p << 1 | 1, mid + 1, r, L, R));
    }
} using namespace SegmentTree;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> Q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i > 1; i--) {
        prevr[i] = QueryR(1, 1, siz, a[i], a[i]);
        int tmp = QueryR(1, 1, siz, a[i] + 1, siz) + 1;
        if (tmp > prevr[i]) UpdateR(1, 1, siz, a[i], tmp);
    }
    int pos = 1;
    while (Q--) {
        char c;
        cin >> c;
        if (c == '<') {
            prevr[pos] = QueryR(1, 1, siz, a[pos], a[pos]);
            int tmp = QueryR(1, 1, siz, a[pos] + 1, siz) + 1;
            if (tmp > prevr[pos]) UpdateR(1, 1, siz, a[pos], tmp);
            pos--;
            UpdateL(1, 1, siz, a[pos], prevl[pos]);
        }
        if (c == '>') {
            prevl[pos] = QueryL(1, 1, siz, a[pos], a[pos]);
            int tmp = QueryL(1, 1, siz, 1, a[pos] - 1) + 1;
            if (tmp > prevl[pos]) UpdateL(1, 1, siz, a[pos], tmp);
            pos++;
            UpdateR(1, 1, siz, a[pos], prevr[pos]);
        }
        if (c == '!') {
            int x;
            cin >> x;
            a[pos] = x;
            prevl[pos] = QueryL(1, 1, siz, a[pos], a[pos]);
            int tmp = QueryL(1, 1, siz, 1, a[pos] - 1) + 1;
            if (tmp > prevl[pos]) UpdateL(1, 1, siz, a[pos], tmp);
            printf("%d\n", node[1].ans);
            UpdateL(1, 1, siz, a[pos], prevl[pos]);
        }
    }
    return 0;
}