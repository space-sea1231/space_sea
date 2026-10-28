#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;

int n, m;
int s, t;
int ans;
int dis[N];
bool vis[N], safe[N];
vector<int> e1[N], e2[N];

void Bfs1() {
    queue<int> q;
    q.push(t);
    vis[t] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : e2[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

void Bfs2() {
    for (int i = 1; i <= n; i++) safe[i] = vis[i]; 
    for (int u = 1; u <= n; u++) {
        if (!safe[u]) continue;
        for (int v : e1[u]) {
            if (!vis[v]) {
                safe[u] = false;
                break;
            }
        }
    }
}

void Bfs3() {
    if (!safe[s]) return;
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    memset(vis, 0, sizeof(vis));
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) {
            ans = dis[u];
            return;
        }
        for (int v : e1[u]) {
            if (!vis[v] && safe[v]) {
                vis[v] = true;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e1[u].emplace_back(v);
        e2[v].emplace_back(u);
    }
    cin >> s >> t;
    ans = INF;
    Bfs1(); Bfs2(); Bfs3();  
    printf("%d\n", (ans == INF ? -1 : ans));
    return 0;
}