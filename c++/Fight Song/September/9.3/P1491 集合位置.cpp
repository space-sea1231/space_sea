#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

const double INF = 1e18;
const int N = 205;

struct Edge {
    int v;
    double w;
};

int n, m;
double x[N], y[N];
vector<Edge> adj[N];
int pre[N]; 
double dist[N];

inline double Calc(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

double Dijkstra(int u1, int v1, bool flag) {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;

    dist[1] = 0;
    q.push({0.0, 1});

    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (d > dist[u]) continue;
        
        for (auto& edge : adj[u]) {
            int v = edge.v;
            double w = edge.w;
            // cerr<<u << " " << v << " " << w << " " << dist[v] << endl;
            if ((u == u1 && v == v1) || (u == v1 && v == u1)) {
                continue;
            }
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (flag) pre[v] = u; 
                q.push({dist[v], v});
            }
        }
    }
    return dist[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        double w = Calc(u, v);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        // cerr<<u<<" " << v << " " << w << endl;
    }

    double dis1 = Dijkstra(-1, -1, true);
    // cerr<<dis1<<endl;
    if (dis1 >= INF) {
        printf("-1\n");
        return 0;
    }

    vector<int> path;
    int curr = n;
    while (curr != 1) {
        path.push_back(curr);
        curr = pre[curr];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    double dis2 = INF;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        
        double d = Dijkstra(u, v, false);
        if (d < dis2) {
            dis2 = d;
        }
    }

    if (dis2 >= INF - 1e-9) printf("-1\n");
    else printf("%.2lf\n", dis2);

    return 0;
}