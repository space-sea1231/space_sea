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
const int N = 1e5 + 10;
const int B = 400;
const int M = 5e5 + 10;
const int C = 26;
const int K = 19;

int dfn;
int n, m;
int rt[M], lg[N];
int ans[N], lsh[N << 1];
int ord[M], dep[M], siz[M];
int L[M], R[M];
int f[M][K], st[N][K];
int tmp[B << 1], per[B << 1];
vector<int> pos[N];
vector<int> ed[M];
vector<int> e[M];

struct ChainTree {
    int num;
    struct Node {
        int l, r;
    }; Node node[N * 20];
    void Update(int &p, int q, int l, int r, int pos) {
        p = ++num;
        node[p] = node[q];
        if (l == r) return;
        int mid = l + r >> 1;
        if (pos <= mid) Update(node[p].l, node[q].l, l, mid, pos);
        if (mid < pos) Update(node[p].r, node[q].r, mid + 1, r, pos);
    }
    bool Query(int p, int l, int r, int L, int R) {
        if (!p) return false;
        if (L <= l && r <= R) return true;
        int mid = l + r >> 1;
        if (R <= mid) return Query(node[p].l, l, mid, L, R);
        else if (mid < L) return Query(node[p].r, mid + 1, r, L, R);
        else return Query(node[p].l, l, mid, L, R) || Query(node[p].r, mid + 1, r, L, R);
    }
}; 

ChainTree tr;

namespace AC {
    int num;
    int len[N];
    int ch[M][C];
    int fail[M];

    void Insert(int id, string &s) {
        len[id] = s.size();
        int p = 0;
        pos[id].resize(len[id]);
        for (int i = 0; i < len[id]; i++) {
            if (!ch[p][s[i] - 'a']) ch[p][s[i] - 'a'] = ++num;
            pos[id][i] = p = ch[p][s[i] - 'a'];
        }
    }
    void Build() {
        queue<int> q;
        for (int i = 0; i < C; i++) if (ch[0][i]) q.push(ch[0][i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            e[fail[u]].emplace_back(u);
            for (int i = 0; i < C; i++) {
                if (ch[u][i]) { fail[ch[u][i]] = ch[fail[u]][i]; q.push(ch[u][i]); }
                else ch[u][i] = ch[fail[u]][i];
            }
        }
    }
} using namespace AC;

int Lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
        }
    }
    if (x == y) return x;
    for (int i = K - 1; ~i; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
void Dfs(int u) {
    L[u] = ++dfn, ord[dfn] = u;
    for (int id : ed[u]) tr.Update(rt[u], rt[u], 1, n, id);
    for (int v : e[u]) {
        dep[v] = dep[u] + 1;
        f[v][0] = u; rt[v] = rt[u];
        for (int i = 1; i < K; i++) f[v][i] = f[f[v][i - 1]][i - 1];
        Dfs(v);
    }
    R[u] = dfn;
}
struct Query {
    int l, r, k;
    int id;
    bool operator<(const Query &s) const { return k < s.k; }
}; Query qry[N];
bool Cmp(int a, int b) { return L[a] < L[b]; }
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    dep[0] = 1, lg[0] = -1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        Insert(i, s);
        ed[pos[i][len[i] - 1]].emplace_back(i);
        lg[i] = lg[i >> 1] + 1;
    }
    Build(); Dfs(0);
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        qry[i] = (Query){l, r, k, i};
    }
    sort(qry + 1, qry + m + 1);
    // for (int i = 1; i <= m; i++) printf("%d\n", qry[i].id);

    for (int i = 1, t = 1; i <= n && t <= m; i++) {
        if (qry[t].k != i) continue;
        if (len[i] < B - 10) {
            for (int j = 0; j < len[i]; j++) tmp[j] = pos[i][j];
            sort(tmp, tmp + len[i], Cmp);
            for (int j = 0; j < len[i] - 1; j++) tmp[len[i] + j] = Lca(tmp[j], tmp[j + 1]);
            sort(tmp, tmp + (len[i] << 1) - 1, Cmp);
            int _len = unique(tmp, tmp + (len[i] << 1) - 1) - tmp;
            for (int j = 0; j < _len; j++) {
                int u = tmp[j]; siz[u] = 0;
                for (int k = 0; k < len[i]; k++) {
                    siz[u] += L[u] <= L[pos[i][k]] && L[pos[i][k]] <= R[u];
                }
            }
            for (int j = 0; j < _len; j++) per[j] = j;
            sort(per, per + _len, [&](int a, int b) {
                return siz[tmp[a]] > siz[tmp[b]];
            });
            for (; t <= m && qry[t].k == i; t++) {
                // cerr<<qry[t].id<<"\n";
                for (int j = 0; j < _len; j++) {
                    if (tr.Query(rt[tmp[per[j]]], 1, n, qry[t].l, qry[t].r)) {
                        ans[qry[t].id] = siz[tmp[per[j]]];
                        break;
                    }
                }
            }
        } else {
            int l = 0;
            for (int j = t; j <= m && qry[j].k == i; j++) {
                if (qry[j].l != 1) lsh[++l] = qry[j].l - 1;
                lsh[++l] = qry[j].r;
            }
            sort(lsh + 1, lsh + l + 1);
            l = unique(lsh + 1, lsh + l + 1) - lsh - 1;
            for (int j = t; j <= m && qry[j].k == i; j++) {
                qry[j].l = upper_bound(lsh + 1, lsh + l + 1, qry[j].l - 1) - lsh;
                qry[j].r = lower_bound(lsh + 1, lsh + l + 1, qry[j].r) - lsh;
            }
            memset(siz, 0, (num + 1) * sizeof(int));
            for (int j = 0; j < len[i]; j++) siz[pos[i][j]]++;
            for (int j = dfn; j > 1; j--) siz[fail[ord[j]]] += siz[ord[j]];
            for (int j = 1, p = 0; j <= n; j++) {
                if (lsh[p] < j) { 
                    p++; 
                    st[p][0] = 0; 
                }
                if (p > l) break;
                st[p][0] = max(st[p][0], siz[pos[j][len[j] - 1]]);
            }
            for (int k = 1; k <= lg[l]; k++) {
                for (int j = 1; j + (1 << k) - 1 <= l; j++) {
                    st[j][k] = max(st[j][k - 1], st[j + (1 << (k - 1))][k - 1]);
                }
            }
            for (; t <= m && qry[t].k == i; t++) {
                int ql = qry[t].l, qr = qry[t].r;
                int g = lg[qr - ql + 1];
                ans[qry[t].id] = max(st[ql][g], st[qr - (1 << g) + 1][g]);
            }
        }
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
/*
前路漫漫 总有绕不过的弯
人生太短 悲欢自渡皆是伤
这熙攘的人潮 谁不迷惘
谁不是 在崩溃的边缘 苦求着希望
想要用魔法 解开生活的惆怅
谁不是奔跑在黑暗中 追寻微弱的光
也曾轻言过失败 也曾被冷眼相待
在最平庸的日子里 频繁受伤害
人生呐 能不能放过我这一次
下辈子我只想做个
不会长大的孩子
有人取暖有人依靠
不会有太多心事
用最天真的橡皮
就能擦去生活的争执
人生呐 能不能放过我这一次
有时候明明很累
却不知道为什么要坚持
残酷的现实
在击碎内心坚强的城池
擦干眼泪对着鸡零狗碎的日子
一笑了之
想要用魔法 解开生活的惆怅
谁不是奔跑在黑暗中 追寻微弱的光
也曾轻言过失败 也曾被冷眼相待
在最平庸的日子里 频繁受伤害
人生呐 能不能放过我这一次
下辈子我只想做个
不会长大的孩子
有人取暖有人依靠
不会有太多心事
用最天真的橡皮
就能擦去生活的争执
人生呐 能不能放过我这一次
有时候明明很累
却不知道为什么要坚持
残酷的现实
在击碎内心坚强的城池
擦干眼泪对着鸡零狗碎的日子
人生呐 能不能放过我这一次
下辈子我只想做个
不会长大的孩子
有人取暖有人依靠
不会有太多心事
用最天真的橡皮
就能擦去生活的争执
人生呐 能不能放过我这一次
有时候明明很累
却不知道为什么要坚持
残酷的现实
在击碎内心坚强的城池
擦干眼泪对着鸡零狗碎的日子
一笑了之
*/