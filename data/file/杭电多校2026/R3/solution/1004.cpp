#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2010;  // source + n + m + sink ≤ 2002
const ll INF = 1e18;

struct Edge {
    int to, rev;
    ll cap, cost;
};

vector<Edge> graph[MAXN];

void add_edge(int u, int v, ll cap, ll cost) {
    graph[u].push_back({v, (int)graph[v].size(), cap, cost});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, -cost});
}

// Min-cost max-flow (successive shortest augmenting path with potentials)
pair<ll, ll> mcmf(int s, int t) {
    int N = t + 1;
    vector<ll> pot(N, 0);  // Johnson's potentials
    ll flow = 0, cost = 0;

    // Initial potentials via Bellman-Ford (SPFA)
    vector<ll> dist(N, INF);
    vector<bool> inq(N, false);
    vector<int> prevv(N, -1), preve(N, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (int i = 0; i < (int)graph[u].size(); i++) {
            auto& e = graph[u][i];
            if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                prevv[e.to] = u;
                preve[e.to] = i;
                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }
    pot = dist;

    while (true) {
        // Dijkstra with reduced costs
        dist.assign(N, INF);
        prevv.assign(N, -1);
        preve.assign(N, -1);
        dist[s] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                auto& e = graph[u][i];
                if (e.cap == 0) continue;
                ll nd = dist[u] + e.cost + pot[u] - pot[e.to];
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    prevv[e.to] = u;
                    preve[e.to] = i;
                    pq.push({nd, e.to});
                }
            }
        }

        if (dist[t] >= INF / 2) break;

        // Update potentials
        for (int v = 0; v < N; v++) {
            if (dist[v] < INF / 2) pot[v] += dist[v];
        }

        // Augment 1 unit of flow
        ll add = INF;
        for (int v = t; v != s; v = prevv[v]) {
            add = min(add, graph[prevv[v]][preve[v]].cap);
        }
        for (int v = t; v != s; v = prevv[v]) {
            auto& e = graph[prevv[v]][preve[v]];
            e.cap -= add;
            graph[v][e.rev].cap += add;
        }
        flow += add;
        cost += add * pot[t];  // Real cost along path
    }

    return {flow, cost};
}

void solve() {
    int n, m;
    cin >> n >> m;

    // Clear graph
    int total_nodes = 1 + n + m + 1;  // source(0) + children(1..n) + toys(n+1..n+m) + sink(n+m+1)
    for (int i = 0; i < total_nodes; i++) graph[i].clear();

    int S = 0, T = n + m + 1;

    // Source -> children
    for (int i = 1; i <= n; i++) {
        add_edge(S, i, 1, 0);
    }

    // Children -> toys they like
    vector<int> toy_demand(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < x; j++) {
            int toy;
            cin >> toy;
            add_edge(i, n + toy, 1, 0);
            toy_demand[toy]++;
        }
    }

    // Toys -> sink (multiple edges, one per possible purchase)
    for (int i = 1; i <= m; i++) {
        int y;
        cin >> y;
        // y should equal toy_demand[i], but we trust input
        for (int j = 1; j <= y; j++) {
            ll w;
            cin >> w;
            add_edge(n + i, T, 1, w);
        }
    }

    auto [flow, cost] = mcmf(S, T);
    cout << cost << '\n';
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
