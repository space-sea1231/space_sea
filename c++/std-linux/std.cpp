#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=1e5+10;
const int INF=0x3f3f3f3f;
int S, T;
int n, m, s, t;
int ans, cnt=1;
int Change(int x, int y){
    return (x-1)*m+y;
}
struct edge {
    int v, f, c, next;
  } e[100005];
  
  struct node {
    int v, e;
  } p[10005];
  
  struct mypair {
    int dis, id;
  
    bool operator<(const mypair& a) const { return dis > a.dis; }
  
    mypair(int d, int x) { dis = d, id = x; }
  };
  
  int head[5005], dis[5005], vis[5005], h[5005];
  
  void addedge(int u, int v, int f, int c) {
    e[++cnt].v = v;
    e[cnt].f = f;
    e[cnt].c = c;
    e[cnt].next = head[u];
    head[u] = cnt;
  }
  
  bool dijkstra() {
    priority_queue<mypair> q;
    for (int i = 1; i <= n; i++) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(mypair(0, s));
    while (!q.empty()) {
      int u = q.top().id;
      q.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v, nc = e[i].c + h[u] - h[v];
        if (e[i].f && dis[v] > dis[u] + nc) {
          dis[v] = dis[u] + nc;
          p[v].v = u;
          p[v].e = i;
          if (!vis[v]) q.push(mypair(dis[v], v));
        }
      }
    }
    return dis[t] != INF;
  }
  
  void spfa() {
    queue<int> q;
    memset(h, 63, sizeof(h));
    h[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = 0;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (e[i].f && h[v] > h[u] + e[i].c) {
          h[v] = h[u] + e[i].c;
          if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
          }
        }
      }
    }
  }
  void Insert(int u, int v, int f, int c){
    addedge(u, v, f, c);
    addedge(v, u, 0, -c);
  }
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> S >> T >> n >> m;
    n++, m++;
    s=0, t=((n*m)<<2)+2;
    for (int i=1; i<=n; i++){
        for (int j=1; j<m; j++){
            int x;
            cin >> x;
            Insert(Change(i, j), Change(i, j+1), 1, x);
            Insert(Change(i, j), Change(i, j+1), INF, 0);
        }
    }
    for (int j=1; j<=m; j++){
        for (int i=1; i<n; i++){
            int x;
            cin >> x;
            Insert(Change(i, j), Change(i+1, j), 1, x);
            Insert(Change(i, j), Change(i+1, j), INF, 0);
        }
    }
    for (int i=1; i<=S; i++){
        int z, x, y;
        cin >> z >> x >> y;
        x++, y++;
        Insert(s, Change(x, y), z, 0);
    }
    for (int i=1; i<=T; i++){
        int z, x, y;
        cin >> z >> x >> y;
        x++, y++;
        Insert(Change(x, y), t, z, 0);
    }
    spfa();  // 先求出初始势能
    while (dijkstra()) {
    int minf = INF;
    for (int i = 1; i <= n; i++) h[i] += dis[i];
    for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
    for (int i = t; i != s; i = p[i].v) {
      e[p[i].e].f -= minf;
      e[p[i].e ^ 1].f += minf;
    }
    ans += minf * h[t];
  }
    printf("%d\n", ans);

    return 0;
}