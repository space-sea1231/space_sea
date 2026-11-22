#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int T;
int n;
ll a[N], sum[N];
int to[N], indeg[N];
bool vis[N];

void Solve(int cur) {
    ll ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> to[i];
        indeg[i] = 0;
        sum[i] = 0;
        vis[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        indeg[to[i]]++;
    }
    for (int i = 1; i <= n; i++) cin >> a[i];

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (a[u] > sum[u]) ans += a[u] - sum[u];

        int v = to[u];
        sum[v] += a[u];

        indeg[v]--;
        if (indeg[v] == 0) q.push(v);
    }

    for (int i = 1; i <= n; i++) {
        if (indeg[i] > 0 && !vis[i]) {
            vector<int> circle;
            int u = i;
            while (!vis[u]) {
                vis[u] = true;
                circle.emplace_back(u);
                u = to[u];
            }

            int k = (int)circle.size();
            vector<ll> need(k);

            for (int j = 0; j < k; j++) {
                int node = circle[j];
                need[j] = max(0LL, a[node] - sum[node]);
            }

            ll base = 0;
            for (int j = 0; j < k; j++) {
                int prv = circle[(j - 1 + k) % k];
                base += max(0LL, need[j] - a[prv]);
            }

            ll best = LLONG_MAX;
            for (int j = 0; j < k; j++) {
                int prv = circle[(j - 1 + k) % k];
                ll term = max(0LL, need[j] - a[prv]);
                ll curAns = base - term + need[j];
                best = min(best, curAns);
            }

            ans += best;
        }
    }

    cout << "Case #" << cur << ": " << ans << '\n';
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
天文单位（AU）：地球到太阳的平均距离，约 1.496 亿公里，主要用于太阳系内部。
光年（ly）：光在真空中走一年的距离，约 9.46 万亿公里，恒星之间的距离。
秒差距（pc）：基于视差测量定义的距离单位，约 3.086 × 10¹³ 公里，天文学研究论文。
泽米（Zm）：10²¹ 米	
尧米（Ym）：10²⁴ 米
1 秒差距 ≈ 3.26 光年 ≈ 206,265 天文单位
1 泽米 ≈ 10.5 万光年 ≈ 3.2 万秒差距
1 尧米 ≈ 1000 泽米 ≈ 1.05 亿光年
*/