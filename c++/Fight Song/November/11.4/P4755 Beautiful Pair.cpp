#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>
#define int long long
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int n, en, r, len;
int a[N], L[N], R[N], b[N];
pair<int,int> s[N];
vector<int> g[N];
ll ans;
ll tr[N];

namespace BIT {
    inline int lowbit(int x) { return x & -x; }
    ll query(int x) {
        ll res = 0;
        while (x) { res += tr[x]; x -= lowbit(x); }
        return res;
    }
    void update(int x, int v) {
        while (x <= n) { tr[x] += v; x += lowbit(x); }
    }
} using namespace BIT;

namespace Solve {
    inline int abs_(int x) { return x >= 0 ? x : -x; }
    inline int find_ind(int x) { return x >= b[n] ? n : upper_bound(b + 1, b + len + 1, x) - b - 1; }
} using namespace Solve;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
        cin >> n;
        for (int i = 1; i <= n; i++) b[i] = a[i] = (cin >> a[i], a[i]);
        for (int i = 1; i <= n; i++) {
            while (en && s[en].first < a[i]) en--;
            L[i] = en ? s[en].second + 1 : 1;
            s[++en] = make_pair(a[i], i);
        }
        en = 0;
        for (int i = n; i; i--) {
            while (en && s[en].first <= a[i]) en--;
            R[i] = en ? s[en].second - 1 : n;
            s[++en] = make_pair(a[i], i);
        }
        for (int i = 1; i <= n; i++) {
            if (i - L[i] <= R[i] - i) {
                g[i - 1].push_back(-1);
                g[R[i]].push_back(1);
                for (int j = L[i]; j < i; j++) {
                    g[i - 1].push_back(-a[i] / a[j]);
                    g[R[i]].push_back(a[i] / a[j]);
                }
            } else {
                g[L[i] - 1].push_back(-1);
                g[i].push_back(1);
                for (int j = i + 1; j <= R[i]; j++) {
                    g[L[i] - 1].push_back(-a[i] / a[j]);
                    g[i].push_back(a[i] / a[j]);
                }
            }
        }
        sort(b + 1, b + n + 1);
        len = unique(b + 1, b + n + 1) - b - 1;
        for (int i = 1; i <= n; i++)
            a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
        for (int i = 1; i <= n; i++) {
            update(a[i], 1);
            int to = g[i].size();
            for (int j = 0; j < to; j++) {
                r = find_ind(abs_(g[i][j]));
                g[i][j] < 0 ? ans -= query(r) : ans += query(r);
            }
        }
        printf("%lld\n", ans);
    return 0;
}