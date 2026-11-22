#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 8e4 + 10;
const int M = 2e5 + 10;

int n, m, t, cnt, tot, T, s, ans;
int head[N], dfn[N], low[N], vis[N];
int col[N], H[N], sum[N], dis[N], V[N];

struct Edge {
    int from, to, next, val, k;
} e[M], E[M];

stack<int> st;
queue<int> q;

void Add(int u, int v, int w, int k) {
    e[++t] = (Edge){u, v, head[u], w, k};
    head[u] = t;
}

void add(int u, int v, int w) {
    E[++T].to = v;
    E[T].next = H[u];
    E[T].val = w;
    H[u] = T;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    vis[u] = 1;
    st.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        tot++;
        int v;
        do {
            v = st.top();
            st.pop();
            col[v] = tot;
            vis[v] = 0;
        } while (v != u);
    }
}

void Spfa(int s) { 
    memset(dis, -1, sizeof(dis));
    memset(V, 0, sizeof(V));
    dis[s] = sum[s];
    V[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        V[u] = 0;
        for (int i = H[u]; i; i = E[i].next) {
            int v = E[i].to, w = E[i].val;
            if (dis[v] < dis[u] + w + sum[v]) {
                dis[v] = dis[u] + w + sum[v];
                if (!V[v]) {
                    V[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
        int x, y, z;
        double k;
		cin >> x >> y >> z >> k;
        Add(x, y, z, k * 10); 
    }
    
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
        
    for (int i = 1; i <= m; i++) {
        int x = e[i].from, y = e[i].to, z = e[i].val, k = e[i].k;
        if (col[x] == col[y]) {
            while (z) { 
                sum[col[x]] += z;
                z = z * k / 10; 
            }
        } else add(col[x], col[y], z);
    }
    
	cin >> s;
    s = col[s];
    Spfa(s);
    
    for (int i = 1; i <= tot; i++) ans = max(ans, dis[i]); // 终点是未知的，所以通过比较dis找到最长路
        
    printf("%d\n", ans);
    return 0;
}