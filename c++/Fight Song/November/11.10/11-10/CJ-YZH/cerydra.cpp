#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;
const int K = 20;
const int Mod = 1e9 + 7;

int T;
int n;
int top, ans;
int stk[N];
int pw[N], inv[N];
ll a[N];

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll) sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
int C(int n, int m) {
    return (ll)pw[n] * inv[n - m] % Mod * inv[m] % Mod;
}
namespace Tree {
    int root;
    int f[N][K];
    struct Node {
        int siz, dep;
        int lson, rson;
    }; Node node[N];

    void Dfs(int u) {
        if (node[u].lson) {
            f[node[u].lson][0] = u;
            node[node[u].lson].dep = node[u].dep + 1;
            for (int i = 1; i < K; i++) f[node[u].lson][i] = f[f[node[u].lson][i - 1]][i - 1];
            Dfs(node[u].lson);
        }
        if (node[u].rson) {
            f[node[u].rson][0] = u;
            node[node[u].rson].dep = node[u].dep + 1;
            for (int i = 1; i < K; i++) f[node[u].rson][i] = f[f[node[u].rson][i - 1]][i - 1];
            Dfs(node[u].rson);
        }
        node[u].siz = node[node[u].lson].siz + node[node[u].rson].siz + 1;
    }
    int Lca(int x, int y) {
        if (node[x].dep < node[y].dep) swap(x, y);
        for (int i = K - 1; ~i; i--) {
            if (node[f[x][i]].dep >= node[y].dep) {
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
} using namespace Tree;

bool flag;
struct Que {
    ll val;
    int id;

    bool operator<(const Que &s) const {
        if (val == s.val) return id < s.id;
        return val < s.val;
    }
}; Que q[N];
void Search(int l, int r) {
    if (l >= r) return ;
    int mid = Lca(l, r);
    int L = 1, R = n, lst = 0;
    while (L <= R) {
        int Mid = L + R >> 1;
        if (q[Mid].val < a[mid] || (q[Mid].val == a[mid] && q[Mid].id <= r)) {
            L = Mid + 1;
            lst = Mid;
        } else R = Mid - 1;
    }
    cerr << l << " " << r << " " << mid << " " << q[lst].id << "\n";
    // if (a[mid] != q[lst].val) printf("(%d~%d)Debug:a[%d]=%lld, a[%d]=%lld\n", l, r, mid, a[mid], q[lst].id, q[lst].val);
    // if (mid != q[lst].id) printf("Debug:a[%d]=%lld, a[%d]=%lld\n", mid, a[mid], q[lst].id, q[lst].val);
    if (mid - l > r - q[lst].id) mid = q[lst].id; 
    // cerr << l << " " << r << " " << mid << "\n";
    if (a[mid] == (ll)(mid - l + 1) * (r - mid + 1)) {
        // cerr << l << " " << mid << " " << r << "\n";
        Search(l, mid - 1); if (flag) return ;
        Search(mid + 1, r); if (flag) return ;
        if (mid - 1 >= l && mid + 1 <= r) {
            ans = (ll)ans * C(r - l, mid - l);
            // cerr << l << " " << mid << " " << r << "\n";
        }

    } else {
        // ans = 0, flag = true;
        // cerr << l << " " << r << "\n";
    }
}
void Solve() {
    top = 0, ans = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) node[i].lson = node[i].rson = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        q[i] = (Que){a[i], i};
    }
    sort(q + 1, q + n + 1);
    // for (int i = 1; i <= n; i++) printf("Debug%d: %d %d\n", i, q[i].val, q[i].id);
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k && a[stk[k]] < a[i]) k--;
        if (k) node[stk[k]].rson = i;
        if (k < top) node[i].lson = stk[k + 1];
        stk[++k] = i;
        top = k;
    }
    // for (int i = 1; i <= n; i++) cerr<<"node["<<i<<"]: l="<<node[i].lson<<" r="<<node[i].rson<<"\n";
    // for (int i = 1; i <= n; i++) printf("node[%d]: l=%d r=%d", i, node[i].lson, node[i].rson);
    node[root = stk[1]].dep = 1;
    for (int i = 0; i < K; i++) f[root][i] = 0;
    Dfs(root); // cerr << node[1].dep << " " << node[333470].dep << "\n"; exit(0);
    Search(1, n);
    printf("%d\n", ans);
}
signed main() {
    freopen("cerydra.in", "r", stdin);
    freopen("cerydra.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * i % Mod;
    inv[N - 1] = Pow(pw[N - 1], Mod - 2);
    for (int i = N - 2; i; i--) inv[i] = (ll)inv[i + 1] * (i + 1) % Mod;
    cin >> T;
    while (T--) Solve();
    return 0;
}
