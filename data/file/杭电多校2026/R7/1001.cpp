#include <iostream>
#include <algorithm>
#include <string.h>
#include <numeric>
#include <math.h>
#include <vector>
#include <time.h>
#include <queue>
using namespace std;
const int N = 100005, S = 200005, SQ = 650;
const int P = 998244353;
inline void Madd(int &x, int y) { (x += y) >= P ? (x -= P) : 0; }
inline int Msum(int x, int y) { return Madd(x, y), x; }
int n;
string str[N];
vector<int> G[S];
int dfn[S], _dfn[S], son[S], sz[S], dep[S], top[S], fa[S], dfncnt;
int ed[S], _ed[S];
vector<int> id[N], lca[N];
int ncnt;
struct AC_Automaton {
    struct node { int son[26], fail; } T[S];
    void Clear() {
        memset(T, 0, (ncnt + 1) * sizeof(node));
        ncnt = 1;
    }
    void Insert(string s, vector<int> &vec) {
        int p = 0;
        for (auto v : s) {
            int &t = T[p].son[v - 'a'];
            vec.emplace_back(p = (t ? t : (t = ncnt++)));
        }
    }
    queue<int> q;
    void Build() {
        for (int i = 0; i < 26; i++) if (T[0].son[i]) q.push(T[0].son[i]);
        while (q.size()) {
            int x = q.front(); q.pop();
            G[T[x].fail].emplace_back(x);
            for (int i = 0; i < 26; i++) {
                if (T[x].son[i]) T[T[x].son[i]].fail = T[T[x].fail].son[i], q.push(T[x].son[i]);
                else T[x].son[i] = T[T[x].fail].son[i];
            }
        }
    }
} ACAM;
void dfs1(int x, int _f, int d) {
    dep[x] = d;
    fa[x] = _f;
    sz[x] = 1, son[x] = 0;
    for (auto v : G[x]) {
        dfs1(v, x, d + 1);
        sz[x] += sz[v];
        if (sz[v] > sz[son[x]]) son[x] = v;
    }
}
void dfs2(int x, int t) {
    top[x] = t;
    _dfn[dfn[x] = ++dfncnt] = x;
    if (son[x]) dfs2(son[x], t);
    for (auto v : G[x]) if (v != son[x]) dfs2(v, v);
}
int LCA(int x, int y) {
    while (top[x] ^ top[y]) (dep[top[x]] < dep[top[y]]) ? (y = fa[top[y]]) : (x = fa[top[x]]);
    return (dep[x] < dep[y] ? x : y);
}
int f[S], pre[S], ans[N];
vector<int> tmp;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        ACAM.Clear(), dfncnt = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> str[i];
        for (int i = 1; i <= n; i++) {
            id[i].clear();
            ACAM.Insert(str[i], id[i]);
            _ed[ed[i] = id[i].back()] = i;
        }
        for (int i = 0; i <= ncnt; i++) G[i].clear();
        ACAM.Build();
        dfs1(0, -1, 1);
        dfs2(0, 0);
        for (int i = 1; i <= n; i++) {
            sort(id[i].begin(), id[i].end(), [](int x, int y) { return dfn[x] < dfn[y]; });
            lca[i].clear();
            for (int j = 0; j < (int)id[i].size() - 1; j++) lca[i].emplace_back(LCA(id[i][j], id[i][j + 1]));
        }
        for (int i = 1; i <= n; i++) f[i] = 1;
        tmp.resize(ncnt + 1);
        for (int i = 0; i < ncnt; i++) tmp[dfn[i]] = _ed[i];
        for (int i = 1; i <= ncnt; i++) _ed[i] = tmp[i];
        for (int i = 1; i < ncnt; i++) tmp[dfn[i]] = dfn[fa[i]];
        for (int i = 1; i <= ncnt; i++) fa[i] = tmp[i];
        for (int i = 1; i <= n; i++) {
            for (auto &v : id[i]) v = dfn[v];
            for (auto &v : lca[i]) v = dfn[v];
        }
        for (int i = 1; i <= n; i++) ans[i] = 0;
        ans[1] = n;
        for (int i = 2; i <= min(n, SQ); i++) {
            for (int j = 2; j <= dfncnt; j++) pre[j] = Msum(f[_ed[j]], pre[fa[j]]);
            for (int j = 1; j <= n; j++) {
                long long t = 0;
                for (auto v : id[j]) t += pre[v];
                for (auto v : lca[j]) t -= pre[v];
                f[j] = (t - f[j]) % P;
                Madd(f[j], P);
            }
            ans[i] = accumulate(f + 1, f + n + 1, 0ll) % P;
        }
        for (int i = 0; i < n; i++) cout << ans[n - i] << " ";
        cout << "\n";
        for (int i = 0; i <= ncnt; i++) _ed[i] = 0;
    }
    return 0;
}