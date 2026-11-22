#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int T;
int n, k;
int num, len;
int a[N], b[N], tmp[N];
int siz[N], dfn[N]; int id[N];
int f[N][2];
vector<int> e[N];

namespace BinaryTree {
    int tree[N];

    int Lowbit(int x) { return x & -x; }
    void Update(int x, int y) {
        for (int i = x; i <= n; i += Lowbit(i)) tree[i] += y;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i; i -= Lowbit(i)) rev += tree[i];
        return rev;
    }
} using namespace BinaryTree;
namespace Mu_ {
    int sqrtn;
    struct Mu {
        int id;
        int l, r, pos;
        bool flag;

        bool operator<(const Mu &s) const {
            if (l / sqrtn != s.l / sqrtn) return l / sqrtn < s.l / sqrtn;
            return (l / sqrtn & 1 ? r > s.r : r < s.r);
        }
    };
    vector<Mu> q;

    void Add(int x) { Update(b[x], 1); } // cerr << "b["<<x<<"]="<<b[x]<<"\n";}
    void Del(int x) { Update(b[x], -1); }
} using namespace Mu_;
void Dfs(int u) {
    dfn[u] = ++num; id[num] = u;
    siz[u] = 1;
    for (int v : e[u]) {
        Dfs(v);
        // cerr << u << " " << v << "\n";
        siz[u] += siz[v];
    }
    int pos = lower_bound(tmp + 1, tmp + len + 1, (a[u] - 1) / k) - tmp;
    q.emplace_back((Mu){u, dfn[u] + 1, dfn[u] + siz[u] - 1, pos, 0});
    q.emplace_back((Mu){u, 1, dfn[u] - 1, pos, 1});
    q.emplace_back((Mu){u, dfn[u] + siz[u], n, pos, 1});
}
void Solve(int cur) {
    num = 0; q.clear();
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        e[i].clear();
        f[i][0] = f[i][1] = 0;
    }
    sqrtn = sqrt(n * 3);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = (a[i] - 1) / k;
    }
    sort(tmp + 1, tmp + n + 1);
    len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        e[fa].emplace_back(i);
    }
    Dfs(1);
    for (int i = 1; i <= n; i++) b[dfn[i]] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
    sort(q.begin(), q.end());
    int L = 1, R = 0;
    
    // for (int i = 1; i <= n; i++) printf("id[%d]=%d\n", i, id[i]);
    // int pos = lower_bound(tmp + 1, tmp + len + 1, (a[7] - 1) / k) - tmp;
    // q.clear();
    // q.emplace_back((Mu){7, 1, dfn[7] - 1, pos, 1});
    for (auto [i, l, r, pos, flag] : q) {
        if (l > r) continue;
        while (L > l) Add(--L);
        while (R < r) Add(++R);
        while (L < l) Del(L++);
        while (R > r) Del(R--);
        f[i][flag] += Query(pos);
        // if (i == 7 && flag == 1) {
        //     printf("L=%d R=%d Que=%d\n", L, R, Query(pos));
        // }
    }
    while (L <= R) Del(L++);
    ll ans = 0;
    // for (int i = 1; i <= n; i++) printf("Debug: f[%d]={%d, %d}\n", i, f[i][0], f[i][1]);
    for (int i = 1; i <= n; i++) ans += (ll)f[i][0] * f[i][1];
    printf("Case #%d: %lld\n", cur, ans);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
A simlpe lamp makes the whole street feel kind.
一盏灯，就让整个街道变得温柔

污泥啊 血肉啊
石头和大地也是你啊
莫要哭 莫要怕
走过了东路就到家
*/