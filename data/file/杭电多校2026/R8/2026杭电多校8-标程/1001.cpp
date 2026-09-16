#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<int> p(q);
    vector<char> active(n + 1, true);

    for (int i = 0; i < q; ++i) {
        cin >> p[i];
        active[p[i]] = false;
    }

    vector<char> reachable(n + 1, false);
    vector<char> expanded(n + 1, false);
    queue<int> que;

    reachable[1] = true;
    que.push(1);

    auto expand = [&]() {
        while (!que.empty()) {
            int u = que.front();
            que.pop();

            if (!active[u] || expanded[u]) {
                continue;
            }

            expanded[u] = true;

            for (int v : graph[u]) {
                if (reachable[v]) {
                    continue;
                }

                reachable[v] = true;
                if (active[v]) {
                    que.push(v);
                }
            }
        }
    };

    // 当前状态对应全部 q 次操作均已执行。
    expand();

    if (reachable[n]) {
        cout << "YES\n";
        return;
    }

    for (int i = q - 1; i >= 0; --i) {
        int u = p[i];
        active[u] = true;

        if (reachable[u] && !expanded[u]) {
            que.push(u);
        }

        expand();

        if (reachable[n]) {
            cout << i << '\n';
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}

