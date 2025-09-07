#include <iostream>
#include <stdio.h>
#include <queue>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m;

struct SegmentTree {
    struct Node {
        priority_queue<int> que;
        int maxn;
    };
    //I ak ioi
    Node node[N << 3];
    
    void PushUp(int x) {
        node[x].maxn = max(node[x << 1].maxn, node[x << 1 | 1].maxn);
        if (!node[x].que.empty()) node[x].maxn = max(node[x].maxn, node[x].que.top());
        return ;
    }
    void Add(int x, int l, int r, const int L, const int R, int val) {
        #ifdef __Debug
        printf("Debug:%d %d\n",l,r);
        #endif
        if (L <= l && r <= R) {
            node[x].que.push(val);
            node[x].maxn = max(node[x].maxn, val);
            return ;
        }
        int mid = (l + r) >> 1;
        if (L <= mid) Add(x << 1, l, mid, L, R, val);
        if (mid < R) Add(x << 1 | 1, mid + 1, r, L, R, val);
        PushUp(x);
        return ;
    }

    int Query(int x, int l, int r, const int L, const int R) {
        #ifdef __Debug
        printf("Debug:%d %d\n",l,r);
        #endif
        if (L <= l && r <= R) return node[x].maxn;
        int mid = (l + r) >> 1;
        int ans = 0;
        if (!node[x].que.empty()) ans = node[x].que.top();
        if (L <= mid) ans = max(ans, Query(x << 1, l, mid, L, R));
        if (mid < R) ans = max(ans, Query(x << 1 | 1, mid + 1, r, L, R));
        return ans;
    }

    void PushDown(int x, int l, int r, const int L, const int R, int val) {
        if (L <= l && r <= R) return ;
        if (l > R || r < L) {
            node[x].que.push(val);
            node[x].maxn = max(node[x].maxn, node[x].que.top());
            return ;
        }
        int mid = (l + r) >> 1;
        PushDown(x << 1, l, mid, L, R, val);
        PushDown(x << 1 | 1, mid + 1, r, L, R, val);
        PushUp(x);
        return ;
    }

    void Delete(int x, int l, int r, const int L, const int R, int val) {
        if (node[x].maxn < val) return ;
        if (!node[x].que.empty() && node[x].que.top() == val) {
            node[x].que.pop();
            PushDown(x, l, r, L, R, val);
            PushUp(x);
            return ;
        }
        int mid = (l + r) >> 1;
        if (L <= mid) Delete(x << 1, l, mid, L, R, val);
         if (mid < R) Delete(x << 1 | 1, mid + 1, r, L, R, val);
        PushUp(x);
        return ;
    }
};

SegmentTree seg;

signed main() {
    // freopen("memory.in", "r", stdin);
    // freopen("memory.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            seg.Add(1, 1, n, l, r, k);
        }
        if (opt == 2) {
            int l, r;
            cin >> l >> r;
            int val = seg.Query(1, 1, n, l, r);
            if (val == 0) continue;
            seg.Delete(1, 1, n, l, r, val);
        }
        if (opt == 3) {
            int l, r;
            cin >> l >> r;
            int val = seg.Query(1, 1, n, l, r);
            printf("%d\n", (val == 0 ? -1 : val));
        }
    }
    return 0;
}
/*
1000 9
1 165 249 25
2 694 740
1 407 997 23
2 292 293
1 319 999 27
2 283 830
2 3 847
2 177 365
3 188 836
*/