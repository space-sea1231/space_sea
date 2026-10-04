#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int n, m;
int a[N], b[N];
int cnt[N];
int tmp[N << 1];
bool final[N];

namespace SegmentTree {
    bool node[N << 2];

    void Down(int p) {
        node[p << 1] |= node[p];
        node[p << 1 | 1] |= node[p];
        node[p] = false;
    }
    void Update(int p, int l, int r, int L, int R) {
        if (node[p]) return ;
        if (L <= l && r <= R) {
            node[p] = true;
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update(p << 1, l, mid, L, R);
        if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R);
    }
    void Get(int p, int l, int r) {
        if (l == r) {
            final[l] = node[p];
            return ;
        }
        Down(p);
        int mid = l + r >> 1;
        Get(p << 1, l, mid);
        Get(p << 1 | 1, mid + 1, r);
    }
    // bool Query(int p, int l, int r, int pos) {
    //     if (node[p]) return true;
    //     if (l == r) return node[p];
    //     Down(p);
    //     int mid = l + r >> 1;
    //     if (pos <= mid) return Query(p << 1, l, mid, pos);
    //     if (mid < pos) return Query(p << 1 | 1, mid + 1, r, pos);
    //     return false;
    // }
} using namespace SegmentTree;
signed main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
        cnt[a[i]]++, cnt[b[i]]++;
        if (a[i] > b[i]) swap(a[i], b[i]);
        tmp[i] = a[i], tmp[i + m] = b[i];
        if (b[i] - a[i] >= 2) Update(1, 1, n, a[i] + 1, b[i] - 1);
    }
    Get(1, 1, n);
    tmp[0] = 1; tmp[(m << 1) + 1] = n;
    sort(tmp, tmp + (m << 1) + 2);
    int len = unique(tmp, tmp + (m << 1) + 2) - tmp - 1;
    // for (int i = 0; i <= len; i++) cerr<<tmp[i] << " ";
    // cerr<<endl;
    ll ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 1; i <= len; i++) {
        int mid = tmp[i] - tmp[i - 1] - 1;
        // printf("Debug1[%d]: mid=%d cur=%lld\n", i, mid, (ll)2 * mid * (n - mid));
        ans1 = max(ans1, (ll)2 * mid * (n - mid));
        if (mid >= n / 2) ans1 = (ll)2 * (n / 2) * ((n + 1) / 2);
    
        if (!final[tmp[i]] && cnt[tmp[i]] == 1) {
            ans2 = max(ans2, max((ll)2 * tmp[i] * (n - tmp[i]), (ll)2 * (tmp[i] - 1) * (n - (tmp[i] - 1))));
        }
    }
    for (int l = 1, r; l <= n; l++) {
        if (final[l]) continue;
        for (r = l + 1; r <= n; r++) {
            if (final[r]) {
                r--;
                break;
            } 
        }
        ll L = l - 1, R = n - r;
        for (int k = r - l + 1; k; k--) {
            ans3 = max(ans3, 2 * (- L * L - R * R + L * n + R * n));
            if (L < R) L++;
            else R++;
        }
    }
    // cerr<<ans1 << " " << ans2 << " " << ans3 << endl;
    printf("%lld\n", max(ans1, max(ans2, ans3)));
    return 0;
}
/*
无自环或重边
*/