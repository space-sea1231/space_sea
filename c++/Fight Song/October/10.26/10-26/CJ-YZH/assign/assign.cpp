#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MOD = 998244353;

long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> color(n + 1, -1);
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            // BFS
            queue<int> q;
            q.push(i);
            color[i] = 0;
            int cnt[2] = {0, 0};
            bool ok = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                cnt[color[u]]++;
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        ok = false;
                    }
                }
            }
            if (!ok) {
                ans = 0;
                break;
            } else {
                long long ways = (power(2, cnt[0]) + power(2, cnt[1]) - 2) % MOD;
                if (ways < 0) ways += MOD;
                ans = (ans * ways) % MOD;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    freopen("assign.in", "r", stdin);
    freopen("assign.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int C, T;
    cin >> C >> T;
    while (T--) {
        solve();
    }
    return 0;
}