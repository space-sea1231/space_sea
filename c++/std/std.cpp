#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int Maxn = 1e9;

int t, n, m;
int val[N], opt[N];
vector<pair<int, int> > q[N];

int Search(int u) {
    if (opt[u] == 0) return val[u];
    int sum = 0;
    for (auto v:q[u]) {
        int rev = Search(v.second);
        if (rev > Maxn) return INF;
        sum += v.first * rev;
        if (sum > Maxn) return INF;
    }
    return sum;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) q[i].clear();
        for (int i = 1; i <= n; i++) {
            cin >> opt[i];
            if (opt[i] == 0) cin >> val[i];
            if (opt[i] == 1) {
                int k;
                cin >> k;
                for (int j = 1; j <= k; j++) {
                    int x, y;
                    cin >> x >> y;
                    q[i].emplace_back(make_pair(x, y));
                }
            }
        }
        int ans = 0, maxn = 0;
        for (auto v:q[m]) {
            int rev = Search(v.second);
            if (maxn > Maxn && (rev == INF || v.first * rev > Maxn)) {
                ans = -1;
                break;
            } else maxn = max(maxn, v.first * rev);
            ans += v.first * rev;
        }
        ans -= maxn;
        if (opt[m] == 0) ans = val[m];
        if (ans == -1 || ans > Maxn) printf("Impossible\n");
        else printf("%lld\n", ans);
    }
    return 0;
}