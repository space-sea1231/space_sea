#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 5e3 + 10;

int n, k, m;
ll a[N];
ll f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k >> m;
    if (n / k > m) {
        printf("-1\n");
        return 0;
    }
    for (int i = 0;i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = -INF;
        }
    }
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int j = 1; j <= m; j++) {
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= n; i++) {
            if (i / k > j) break;
            // if (i == 3 && j == 1) cerr<<f[i][j] << endl;
            while (!q.empty() && q.front()< i - k) q.pop_front();
            if (!q.empty()) f[i][j] = f[q.front()][j - 1] + a[i];
            while (!q.empty() && f[q.back()][j - 1] <= f[i][j - 1]) q.pop_back();
            q.push_back(i);
        }
    }
    ll ans = 0;
    // printf("%lld\n", f[1][])
    for (int i = n - k + 1; i <= n; i++) ans = max(ans, f[i][m]);
    printf("%lld\n", ans);
    return 0;
}