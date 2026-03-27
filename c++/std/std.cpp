#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, m;
bool a[N];

namespace SegmentTree {
    struct Node {
        int l_zero, r_zero;
        int l_one, r_one;
        int sum, vis;
        int max_zero, max_one;
    };
    Node node[N << 3];
    struct Pair {
        int l, mid, r;
    };

    void Up(int x, int l, int r) {
        int mid = (l + r) >> 1;
        node[x].max_one = max(max(node[x << 1].max_one, node[x << 1 | 1].max_one), node[x << 1].r_one + node[x << 1 | 1].l_one);
        node[x].max_zero = max(max(node[x << 1].max_zero, node[x << 1 | 1].max_zero), node[x << 1].r_zero + node[x << 1 | 1].l_zero);
        node[x].sum = node[x << 1].sum + node[x << 1 | 1].sum;
        if (node[x << 1].l_one == mid - l + 1) node[x].l_one = node[x << 1].l_one + node[x << 1 | 1].l_one;
        else node[x].l_one = node[x << 1].l_one;
        if (node[x << 1].sum == 0) node[x].l_zero = node[x << 1].l_zero + node[x << 1 | 1].l_zero;
        else node[x].l_zero = node[x << 1].l_zero;
        if (node[x << 1 | 1].r_one == r - mid) node[x].r_one = node[x << 1 | 1].r_one + node[x << 1].r_one;
        else node[x].r_one = node[x << 1 | 1].r_one;
        if (node[x << 1 | 1].sum == 0) node[x].r_zero = node[x << 1 | 1].r_zero + node[x << 1].r_zero;
        else node[x].r_zero = node[x << 1 | 1].r_zero;
        // #ifdef __Debug
        // printf("Debug3: l = %d r = %d de = %d %d %d x=%d\n", l, r, node[x].r_one, node[x << 1].r_one, node[x << 1 | 1].r_one, x << 1 | 1);
        // #endif
        return;
    }
    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].l_one = node[x].r_one = node[x].sum = node[x].max_one = a[l];
            node[x].l_zero = node[x].r_zero = node[x].max_zero = !a[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        Up(x, l, r);
        return;
    }
    void Down(int x, int l, int r) {
        if (node[x].vis == 0) return;
        int mid = (l + r) >> 1;
        if (node[x].vis == 1) {
            swap(node[x << 1].l_one, node[x << 1].l_zero);
            swap(node[x << 1].r_one, node[x << 1].r_zero);
            swap(node[x << 1].max_one, node[x << 1].max_zero);
            node[x << 1].sum = mid - l + 1 - node[x << 1].sum;
            swap(node[x << 1 | 1].l_one, node[x << 1 | 1].l_zero);
            swap(node[x << 1 | 1].r_one, node[x << 1 | 1].r_zero);
            swap(node[x << 1 | 1].max_one, node[x << 1 | 1].max_zero);
            node[x << 1 | 1].sum = r - mid - node[x << 1 | 1].sum;
            if (node[x << 1].vis < 2) node[x << 1].vis ^= 1;
            else {
                Down(x << 1, l, mid);
                node[x << 1].vis = 1;    
            }
            if (node[x << 1 | 1].vis < 2) node[x << 1 | 1].vis ^= 1;
            else {
                Down(x << 1 | 1, l, mid);
                node[x << 1 | 1].vis = 1;    
            }
        } 
        else {
            int val = node[x].vis - 2;
            node[x << 1].l_one = node[x << 1].r_one = node[x << 1].max_one = node[x << 1].sum = val?(mid - l + 1):(0);
            node[x << 1].l_zero = node[x << 1].r_zero = node[x << 1].max_zero = !val?(mid - l + 1):(0);
            node[x << 1 | 1].l_one = node[x << 1 | 1].r_one = node[x << 1 | 1].max_one = node[x << 1 | 1].sum = val?(r - mid):(0);
            node[x << 1 | 1].l_zero = node[x << 1 | 1].r_zero = node[x << 1 | 1].max_zero = !val?(r - mid):(0);
            node[x << 1].vis = node[x << 1 | 1].vis = node[x].vis;
        }
        node[x].vis = 0;
    }
    void Change(int x, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            node[x].vis = val + 2;
            node[x].l_one = node[x].r_one = node[x].max_one = node[x].sum = val?(r - l + 1):(0);
            node[x].l_zero = node[x].r_zero = node[x].max_zero = !val?(r - l + 1):(0);
            // #ifdef __Debug
            // printf("Debug1: l = %d r = %d L = %d R = %d maxn = %d\n", l, r, L, R, node[x].max_one);
            // #endif
            return;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) Change(x << 1, l, mid, L, R, val);
        if (mid + 1 <= R) Change(x << 1 | 1, mid + 1, r, L, R, val);
        Up(x, l, r);
        return;
    }
    void ExChange(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            if (node[x].vis != 0 && node[x].vis != 1) {
                Down(x, l, r);
                node[x].vis = 1;
            }
            else node[x].vis ^= 1;
            swap(node[x].l_one, node[x].l_zero);
            swap(node[x].r_one, node[x].r_zero);
            swap(node[x].max_one, node[x].max_zero);
            node[x].sum = r - l + 1 - node[x].sum;
            return;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) ExChange(x << 1, l, mid, L, R);
        if (mid + 1 <= R) ExChange(x << 1 | 1, mid + 1, r, L, R);
        Up(x, l, r);
        return;
    }
    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R)  {
            // #ifdef __Debug
            // printf("Debug2: l = %d r = %d sum = %d\n", l, r, node[x].sum);   
            // #endif
            return node[x].sum;
        }
        int mid = (l + r) >> 1, sum = 0;
        Down(x, l, r);
        if (L <= mid) sum += Query(x << 1, l, mid, L, R);
        if (mid + 1 <= R) sum += Query(x << 1 | 1, mid + 1, r, L, R);
        Up(x, l, r);
        return sum;
    }
    Pair QueryOne(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            #ifdef __Debug
            printf("Debug5: l=%d r=%d ll=%d mid=%d rr=%d\n", l, r, node[x].l_one, node[x].max_one, node[x].r_one);
            #endif
            return (Pair){node[x].l_one, node[x].max_one, node[x].r_one};
        }
        int mid = (l + r) >> 1, rev = 0, ll = 0, lr = 0, rl = 0, rr = 0;
        Down(x, l, r);
        if (L <= mid) {
            Pair tmp = QueryOne(x << 1, l, mid, L, R);
            rev = max(rev, tmp.mid);
            ll = tmp.l, lr = tmp.r;
        }
        if (mid + 1 <= R) {
            Pair tmp = QueryOne(x << 1 | 1, mid + 1, r, L, R);
            rev = max(rev, tmp.mid);
            rl = tmp.l, rr = tmp.r;
        }
        Up(x, l, r);
        #ifdef __Debug
        printf("Debug4: l=%d r=%d ll=%d rev=%d rr=%d\n", l, r, ll, rev, rr);
        #endif
        bool flag = false;
        if (ll == mid - l + 1) ll += rl, rl = ll, lr = ll, flag = true;
        else if (rr == r - mid) rr += lr, lr = rr, rl = rr, flag = true;
        else if (ll + rr == r - l + 1) ll = lr = rl = rr = r - l + 1, flag = true;
        if (flag) rev = max(ll, rr);
        else rev = max(rev, lr + rl);
        return (Pair){ll, rev, rr};
    }
    #ifdef __Debug
    void Out(int x, int l, int r) {
        if (l == r) {
            // printf("pos:%d L-1=%d R-1=%d L-0=%d R-0=%d vis=%d max=%d\n", l, node[x].l_one, node[x].r_one, node[x].l_zero, node[x].r_zero, node[x].vis, node[x].max_one);
            return;
        }
        Down(x, l, r);
        int mid = (l + r) >> 1;
        Out(x << 1, l, mid);
        Out(x << 1 | 1, mid + 1, r);
        Up(x, l, r);
        printf("pos:%d~%d L-1=%d R-1=%d L-0=%d R-0=%d vis=%d max=%d\n", l, r, node[x].l_one, node[x].r_one, node[x].l_zero, node[x].r_zero, node[x].vis, node[x].max_one);
        return;
    }
    #endif
}using namespace SegmentTree;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int opt, l, r;
        cin >> opt >> l >> r;
        l++, r++;
        if (opt == 0) Change(1, 1, n, l, r, 0);
        if (opt == 1) Change(1, 1, n, l, r, 1);
        if (opt == 2) ExChange(1, 1, n, l, r);
        if (opt == 3) printf("%d\n", Query(1, 1, n, l, r));
        if (opt == 4) printf("%d\n", QueryOne(1, 1, n, l, r).mid);
        #ifdef __Debug
        if (i == 6) {
            Out(1, 1, n);
        }
        #endif
    }
    return 0;
}