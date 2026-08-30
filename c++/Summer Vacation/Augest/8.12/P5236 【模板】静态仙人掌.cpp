#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
// #define __Debug_Dis1
// #define __DebugE2
// #define __Debug_Dis2
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;
const int K = 17;

int n, m, q;
int dis1[N], dis2[N << 1];
int clen[N << 1], edge[N << 1];
int fa[N << 1][K], dep[N << 1];
bool vis[N];
vector<pair<int, int> > e1[N];
vector<int> e2[N << 1];
map<int, int> cpos[N << 1];
struct Node {
    int fa, l, r;
};
namespace Tarjan_ {
    int num, top, cnt;
    int dfn[N], low[N];
    int stk[N];

    int Getw(int u, int v) {
        for (auto [x, w] : e1[u]) if (x == v) return w;
        return 0;
    }
    void Tarjan(int u) {
        dfn[u] = low[u] = ++num;
        stk[++top] = u;
        for (auto [v, w]:e1[u]) {
            if (!dfn[v]) {
                edge[v] = w;
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == dfn[u]) {
                    // cerr << v << " " << u << " " << low[v] << endl;
                    // printf("---%d %d %d---\n", v, u, low[v]);
                    cnt++;
                    vector<int> cyc;
                    // if (stk[top] == v) {top--; continue;}
                    do {
                        e2[cnt].emplace_back(stk[top]);
                        e2[stk[top]].emplace_back(cnt);
                        #ifdef __DebugE2
                        printf("%d %d\n", cnt, stk[top]);
                        #endif
                        cyc.emplace_back(stk[top]);
                        vis[stk[top]] = true, top--;
                    } while (stk[top + 1] != v);
                    e2[cnt].emplace_back(u);
                    e2[u].emplace_back(cnt);
                    vis[u] = true;
                    #ifdef __DebugE2
                    printf("%d %d\n", cnt, u);
                    #endif
                    if ((int)cyc.size() >= 2) {
                        int sum = 0;
                        reverse(cyc.begin(), cyc.end());  
                        cpos[cnt][u] = 0;
                        for (int cur:cyc) {
                            #ifdef __Debug
                            printf("%d ", cur);
                            #endif
                            sum += edge[cur];
                            cpos[cnt][cur] = sum; 
                        }
                        // printf("\n");
                        clen[cnt] = sum + Getw(cyc.back(), u);
                    }
                }
            } else low[u] = min(low[u], dfn[v]);
        }
    }
} using namespace Tarjan_;

void Dijkstra() {
    for (int i = 1; i <= n; i++) dis1[i] = INF;
    dis1[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d != dis1[u]) continue;
        for (auto [v, w]:e1[u]) {
            if (dis1[v] > dis1[u] + w) {
                dis1[v] = dis1[u] + w;
                q.push({dis1[v], v});
            }
        }
    }
}
void Dfs1(int u, int f) {
    #ifdef __Debug_Dis2
    printf("dis2[%d]=%d\n", u, dis2[u]);
    #endif
    for (auto v:e2[u]) {
        if (v == f) continue;
        if (v > n) dis2[v] = dis1[u];
        else dis2[v] = dis1[v];
        Dfs1(v, u);
    }
}
void Dfs2(int u, int f) {
    dep[u] = dep[f] + 1;
    for (auto v:e2[u]) {
        if (v == f) continue;
        fa[v][0] = u;
        for (int i = 1; i < K; i++) fa[v][i] = fa[fa[v][i - 1]][i - 1];
        Dfs2(v, u);
    }
}
Node LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return (Node){y, 0, 0};
    for (int i = K - 1; ~i; i--) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return (Node){fa[x][0], x, y};
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> q; cnt = n;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e1[u].emplace_back(make_pair(v, w));
        e1[v].emplace_back(make_pair(u, w));
    }
    Dijkstra();
    for (int i = 1; i <= n; i++) if (!dfn[i]) Tarjan(i);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            for (auto [v, w]:e1[i]) {
                e2[i].emplace_back(v);
                if (vis[v]) e2[v].emplace_back(i);
                #ifdef __DebugE2
                printf("%d %d\n", i, v);
                #endif
            }
        }
    }
    Dfs1(1, 0); Dfs2(1, 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        Node node = LCA(u, v);
        // cerr<<u << " " << v << " " << node.fa << endl;
        // cerr<<node.fa << " " << node.l << " " << node.r << endl;
        if (node.fa <= n) printf("%d\n", dis2[u] + dis2[v] - dis2[node.fa] * 2);
        else {
            int ex;
            if (clen[node.fa]) {
                int pa = cpos[node.fa][node.l];
                int pb = cpos[node.fa][node.r];
                // cerr<<pa<<" "<<pb<<endl;
                int d = abs(pa - pb);
                ex = min(d, clen[node.fa] - d);
                // cerr<<ex << endl;
            } else ex = abs(dis2[node.l] - dis2[node.r]);
            printf("%d\n", dis2[u] + dis2[v] - (dis2[node.l] + dis2[node.r]) + ex);
        }
    }
    #ifdef __Debug_Dis1
    for (int i = 1; i <= n; i++) printf("dis1[%d]=%d\n", i, dis1[i]);
    #endif
    // for (int i = 1; i <= n; i++) printf("dfn[%d]=%d low[%d]=%d\n", i, dfn[i], i, low[i]);
    // for (int i = 1; i <= n; i++) 
    return 0;
}
/*
我们是时代的眼泪
小学毕业后，母校装修一新，新校区，新球场，还有游泳馆。ta甚至还让我们游了一次，让你谗完后把你踢出学校
初二生地会考，到我们这一届正好改成了等第制，本来就指望生地拉分了，这下全完了
初三开学，初二初一直接换上新教材了qwq
初三毕业中考，在初一学弟学妹的教师考。平板+触屏笔+可上下左右360度无死角移动的黑板...这都是些什么高科技啊
中考完，tm还搞上12年义务教育了...
*/