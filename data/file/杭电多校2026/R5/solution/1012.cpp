#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 998244353, N = 1e5;
int fac[N + 5], ifac[N + 5], ans;

void init() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
    ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= N; i++) ifac[i] = 1LL * ifac[i - 2] * (i - 1) % mod;
}

pair<int, int> dfs(int u, int p, int K, const vector<vector<int>>& g, vector<char>& vis) {
    vis[u] = 1;
    vector<pair<int, int>> a;
    for (int v : g[u]) {
        if (v == p) continue;
        auto z = dfs(v, u, K, g, vis);
        if (!ans) return {0, 0};
        int len = z.first + 1, leaf = z.second;
        if (len == K) continue;
        if (len < K)
            a.push_back({len, leaf});
        else {
            ans = 0;
            return {0, 0};
        }
    }

    if (a.empty()) return {0, u};
    sort(a.begin(), a.end());
    int i = 0, j = (int)a.size() - 1;
    vector<char> used(a.size());
    while (i < j) {
        if (a[i].first + a[j].first == K)
            used[i] = used[j] = 1, ++i, --j;
        else if (a[i].first + a[j].first < K)
            ++i;
        else
            --j;
    }

    int ri = -1;
    pair<int, int> rem = {0, 0};
    for (int k = 0; k < (int)a.size(); k++) {
        if (!used[k]) {
            if (ri != -1) {
                ans = 0;
                return {0, 0};
            }
            ri = k;
            rem = a[k];
        }
    }

    map<int, int> cnt;
    for (auto [len, leaf] : a) ++cnt[min(len, K - len)];
    if (ri != -1) ++cnt[min(rem.first, K - rem.first)];
    for (auto [len, c] : cnt) {
        if (len * 2 == K)
            ans = 1LL * ans * ifac[c] % mod;
        else
            ans = 1LL * ans * fac[c / 2] % mod;
    }
    if (ri == -1) return {0, u};
    return rem;
}

void solve() {
    int n;
    cin >> n;
    map<int, vector<pair<int, int>>> lay;
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (c > 1) lay[c].push_back({u, v});
    }

    ans = 1;
    vector<vector<int>> g(n + 1);
    vector<char> vis(n + 1);
    for (auto& [L, e] : lay) {
        if (!ans) break;
        int K = L - 1;
        vector<int> v;
        for (auto [x, y] : e) {
            g[x].push_back(y);
            g[y].push_back(x);
            v.push_back(x);
            v.push_back(y);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (int x : v) {
            if (!vis[x]) {
                auto z = dfs(x, 0, K, g, vis);
                if (z.first) ans = 0;
            }
        }
        for (int x : v) {
            g[x].clear();
            vis[x] = 0;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
