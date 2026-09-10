#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int M = 4e5 + 10;

int T;
int n, m;
int Q, K, S;
int dist[N], altt[N];
bool vis[N];

struct Edge {
    int u, v, w, a;
    
    bool operator<(const Edge &s) const {return w > s.w;}
}; Edge e[M];

vector<pair<int, int> > e1[N];

namespace PUF {
    struct Node {
        int fa;
        int dep, dis;
        Node *l, *r;
        
        void Init() {
            fa = dep = 0;
            l = r = nullptr;
        }
        void *operator new(size_t);
    };
    Node *root[M];

    void Build(Node *&p, int l, int r) {
        p = new Node();
        if (l == r) { p->fa = l; p->dis = dist[l]; return; }
        int mid = l + r >> 1;
        Build(p->l, l, mid);
        Build(p->r, mid + 1, r);
    }
    Node *Query(Node *p, int l, int r, int pos) {
        if (l == r) return p;
        int mid = l + r >> 1;
        if (pos <= mid) return Query(p->l, l, mid, pos);
        else return Query(p->r, mid + 1, r, pos);
    }
    Node *Find(Node *p, int pos) {
        Node *fa = Query(p, 1, n, pos);
        if (fa->fa == pos) return fa;
        return Find(p, fa->fa);
    }
    void Merge(Node *q, Node *&p, int l, int r, int pos, int fa) {
        if (p->fa == 0) p = new Node(*q);
        if (l == r) {
            p->fa = fa;
            p->dep = q->dep;
            return ;
        }
        int mid = l + r >> 1;
        if (pos <= mid) Merge(q->l, p->l, l, mid, pos, fa);
        else Merge(q->r, p->r, mid + 1, r, pos, fa);
    }
    void Update(Node *q, Node *&p, int l, int r, int pos) {
        if (p->fa == 0) p = new Node (*q);
        if (l == r) {p->dep++; return;}
        int mid = l + r >> 1;
        if (pos <= mid) Update(q->l, p->l, l, mid, pos);
        else Update(q->r, p->r, mid + 1, r, pos);
    }
    void CMerge(int x, int y, int v) {
        Node *fx = Find(root[v], x);
        Node *fy = Find(root[v], y);
        if (fx->fa != fy->fa) {
            if (fx->dep > fy->dep) swap(fx, fy);
            Merge(root[v - 1], root[v], 1, n, fx->fa, fy->fa);
            fy->dis = min(fy->dis, fx->dis);
            if (fx->dep == fy->dep) {Node *t = root[v]; Update(t, root[v], 1, n, fy->fa);}
        }
    }
    Node *p = (Node*)calloc(8000000, sizeof(Node));
    int cnt;
    void *Node::operator new(size_t s) { return p+(cnt++); }
} using namespace PUF;

void Dijstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> >> q;
    q.push(make_pair(0, 1));
    while(!q.empty()) {
        int u = q.top().second; q.pop();
        // cerr<<u << " " << vis[u] << "\n";
        if(vis[u]) continue;
        vis[u] = true;
        for(pair<int, int> cur:e1[u]) {
            int v = cur.first, w = cur.second;
            // cerr<<v << " " << w << "\n";
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push(make_pair(dist[v], v));
            }
        }
    }
}
void Init() {
    cnt = 0;
    for (int i = 0; i < cnt; i++) (p + i)->Init();
    for (int i = 1; i <= n; i++) {
        e1[i].clear();
        root[i] = nullptr;
        dist[i] = INF;
        vis[i] = false;
    }
    dist[1] = 0;
}
void Solve() {
    cin >> n >> m;
    Init();
    for (int i = 1; i <= m; i++) {
        int u, v, w, a;
        cin >> u >> v >> w >> a;
        e[i] = (Edge){u, v, w, a};
        e1[u].emplace_back(make_pair(v, w));
        e1[v].emplace_back(make_pair(u, w));
    }
    cin >> Q >> K >> S;

    Dijstra();
    for (int i = 1; i <= n; i++) printf("dist[%d]=%d\n", i, dist[i]);
    Build(root[0], 1, n);
    int ddd = 2;
    // printf("Debug:fa[%d]=%d\n", 2, Find(root[0], 2)->dis);
    sort(e + 1, e + m + 1);
    int pre_tot = 0;
    for (int i = 1; i <= m; i++) {
        if (e[i].w != e[i - 1].w) {
            pre_tot++;
            root[pre_tot] = root[pre_tot - 1];
            altt[pre_tot] = e[i].w;
        }
        CMerge(e[i].u, e[i].v, pre_tot);
    }
    sort(allt + 1, allt + pre_tot + 1);
    int lastans = 0;
    for (int i = 1; i <= Q; i++) {
        int u, p;
        cin >> u >> p;
        // cerr << u << " " << p << "\n";
        u = (u + K * lastans) % n + 1;
        p = (p + K * lastans) % (S + 1);
        int line = lower_bound(altt, altt + pre_tot + 1, p) - altt; 
        cerr<<line << " " << altt[line] << endl;
        printf("%d\n", lastans = Find(root[line], u)->dis);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) Solve();
    return 0;
}
/*
Altitude 海拔  
*/