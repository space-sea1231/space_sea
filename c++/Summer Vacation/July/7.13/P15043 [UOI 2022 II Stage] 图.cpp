#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, g;
int ans, cnt;
int dep[N];
bool flag[N];
bool vis[N];
vector<pair<int, int> > q[N];
vector<int> p, loop;
bool flag_tmp;

void Dfs1(int u, int fa) {
    vis[u] = true;
    p.emplace_back(u);
    for (auto [v, w] : q[u]) {
        if (v == fa) continue;
        if (vis[v]) {
            int cur = 0;
            while (cur != v) {
                cur = p.back();
                loop.emplace_back(cur);
                p.pop_back();
                flag[cur] = true;
                cnt++;
            }
            flag_tmp = true;
            return;
        }
        Dfs1(v, u);
        if (flag_tmp) return;
    }
    p.pop_back();
}
void Dfs2(int u, int fa) {
    dep[u] = 0;
    int tmp = 0;
    for (auto [v, w] : q[u]) {
        if (v == fa || flag[v]) continue;
        Dfs2(v, u);
        if (dep[u] < dep[v] + w) {
            tmp = dep[u];
            dep[u] = dep[v] + w;
        } else if (tmp < dep[v] + w) {
            tmp = dep[v] + w;
        }
        ans = max(ans, tmp + dep[u]);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> g;
    for (int i = 1; i <= n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        q[u].emplace_back(make_pair(v, w));
        q[v].emplace_back(make_pair(u, w));
    }
    Dfs1(1, 0);
    for (auto root : loop) Dfs2(root, 0);
    vector<int> edge_w(cnt);
    for (int i = 0; i < cnt; i++) {
        int u = loop[i];
        int v = loop[(i + 1) % cnt];
        for (auto [to, w] : q[u]) {
            if (to == v) {
                edge_w[i] = w;
                break;
            }
        }
    }
    int s = 0;
    for (int i = 0; i < cnt; i++) s += edge_w[i];
    vector<int> cycle_nodes(2 * cnt);
    vector<int> cycle_sum(2 * cnt);
    for (int i = 0; i < 2 * cnt; i++) {
        cycle_nodes[i] = loop[i % cnt];
    }
    cycle_sum[0] = 0;
    for (int i = 1; i < 2 * cnt; i++) {
        cycle_sum[i] = cycle_sum[i - 1] + edge_w[(i - 1) % cnt];
    }
    deque<int> dq;
    for (int i = 0; i < 2 * cnt; i++) {
        while (!dq.empty() && cycle_sum[i] - cycle_sum[dq.front()] > s / 2) {
            dq.pop_front();
        }
        if (!dq.empty()) {
            int j = dq.front();
            ans = max(ans, dep[cycle_nodes[i]] + dep[cycle_nodes[j]] + cycle_sum[i] - cycle_sum[j]);
        }
        while (!dq.empty() && dep[cycle_nodes[dq.back()]] - cycle_sum[dq.back()] <= dep[cycle_nodes[i]] - cycle_sum[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    printf("%lld\n", ans);
    return 0;
}