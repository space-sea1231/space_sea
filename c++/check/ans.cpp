#include <bits/stdc++.h>
#define maxn 200100
#define int long long
using namespace std;
const double eps = 1e-8;
vector<int> e[maxn], cyc, s;
int mxd[maxn], f[maxn], g[maxn], s1_p[maxn], s1_n[maxn], s2_p[maxn], s2_n[maxn], p[maxn], nx[maxn];
bool vis[maxn];

bool dfs(int x, int fa) {
    vis[x] = true;
    for (auto u : e[x]) {
        if(u == fa)  continue;
        if(vis[u]) {
            while(s.back() != u)  cyc.push_back(s.back()), s.pop_back();
            cyc.push_back(s.back()), s.pop_back();
            return false;
        }
        s.push_back(u);
        if(!dfs(u, x))  return false;
        if(s.size())  s.pop_back();
    }
    return true;
}

void dfs(int x, int f1, int f2) {
    for (auto u : e[x]) {
        if(u == f1 || u == f2)  continue;
        dfs(u, x, x);
        mxd[x] = max(mxd[u] + 1, mxd[x]);
    }
}

void dfs(int x, int f1, int f2, int cur) {
    int mx1 = cur, mx2 = 0;
    for (auto u : e[x]) {
        if(u == f1 || u == f2)  continue;
        if(mxd[u] + 1 > mx1)  mx2 = mx1, mx1 = mxd[u] + 1;
        else if(mxd[u] + 1 > mx2)  mx2 = mxd[u] + 1;
    }
    if(!g[x])  f[x] = max({f[x], mx1 + mx2});
    for (auto u : e[x]) {
        if(u == f1 || u == f2)  continue;
        if(mxd[u] + 1 == mx1)  dfs(u, x, x, mx2 + 1);
        else  dfs(u, x, x, mx1 + 1);
    }
}


void solve() {
    int n;  cin >> n;
    for (int i = 1; i <= n; ++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);  e[v].push_back(u);
    }
    s.push_back(1);
    dfs(1, -1);
    int k = cyc.size();
    for (int i = 0; i < k; ++i)  dfs(cyc[i], cyc[(i + k - 1) % k], cyc[(i + 1) % k]), cyc.push_back(cyc[i]);
    deque<int> q1, q2;
    for (int i = 0; i < 2 * k; ++i) {
        if(q1.size() && q1.front() + k == i)  q1.pop_front();
        if(i >= k)  g[cyc[i % k]] = max(g[cyc[i % k]], mxd[cyc[q1.front() % k]] + i - q1.front());
        int c1 = mxd[cyc[i % k]] + (2 * k - i);
        while(q1.size() && mxd[cyc[q1.back() % k]] + (2 * k - q1.back()) <= c1)  q1.pop_back();
        q1.push_back(i);
    }
    for (int i = 2 * k - 1; i >= 0; --i) {
        if(q2.size() && q2.front() - k == i)  q2.pop_front();
        if(i < k)  g[cyc[i % k]] = max(g[cyc[i % k]], mxd[cyc[q2.front() % k]] + q2.front() - i);
        int c2 = mxd[cyc[i % k]] + i;
        while(q2.size() && mxd[cyc[q2.back() % k]] + q2.back() <= c2)  q2.pop_back();
        q2.push_back(i);
    }
    for (int i = 0; i < k; ++i)  dfs(cyc[i], cyc[(i + k - 1) % k], cyc[(i + 1) % k], g[cyc[i]]);

    for (int i = 0; i <= k; ++i)  s1_n[i] = s1_p[k] = s2_n[i] = s2_p[i] = p[i] = nx[i] = -1e9;
    for (int i = 0; i < k; ++i)  s1_p[i] = max(s1_p[max(0ll, i - 1)], mxd[cyc[i]] - i), s2_p[i] = max(s2_p[max(0ll, i - 1)], mxd[cyc[i]] + i);
    for (int i = k - 1; i >= 0; --i)  s1_n[i] = max(s1_n[i + 1], mxd[cyc[i]] - i), s2_n[i] = max(s2_n[i + 1], mxd[cyc[i]] + i);
    vector<pair<int, int>> t1, t2;
    for (int i = 0; i < k; ++i) {
        t1.push_back({mxd[cyc[i]] + i + s1_n[i + 1] + k, i});
        if(i)  t2.push_back({mxd[cyc[i]] - i + s2_p[i - 1] + k, i});
    }
    sort(t1.begin(), t1.end(), greater<>());  sort(t2.begin(), t2.end(), greater<>());
    int sz1 = t1.size(), p1 = 0;
    int sz2 = t2.size(), p2 = 0;
    for (int i = 0; i < k; ++i) {
        if(i)  f[cyc[i]] = max({f[cyc[i]], s1_p[i] + s2_n[i + 1], s1_p[i - 1] + s2_n[i]});
        else  f[cyc[i]] = max({f[cyc[i]], s1_p[i] + s2_n[i + 1]});
        while(p1 < sz1 && t1[p1].second < i)  p1++;
        if(p1 < sz1)  f[cyc[i]] = max({f[cyc[i]], t1[p1].first});
    }
    for (int i = k - 1; i >= 0; --i) {
        while(p2 < sz2 && t2[p2].second > i)  p2++;
        if(p2 < sz2)  f[cyc[i]] = max(f[cyc[i]], t2[p2].first);
    }

    for (int i = 1; i <= n; ++i)  cout << f[i] << " \n"[i == n];
    for (int i = 0; i <= n; ++i)  e[i].clear(), vis[i] = false, mxd[i] = g[i] = f[i] = s1_p[i] = s1_n[i] = s2_p[i] = s2_n[i] = p[i] = nx[i] = 0;
    cyc.clear();  s.clear();
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);  cout.tie(0);
    int t = 1;  cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}