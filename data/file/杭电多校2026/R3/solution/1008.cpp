/**
 * std.cpp — 正解 (线段树 + 矩阵快速转移)
 *
 * 状态编码: (tight_l, tight_r)
 *   0: (0,0)  1: (0,1)  2: (1,0)  3: (1,1)
 * 转移矩阵 make_mat(lb, rb, C): lb/rb = l/r 当前位的值
 *
 * 复杂度: O(2^n + B log B + t log B) per test case, B = 100000
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXB = 100005;

// ---------- 系数 C ----------
int count_filters(int n, const vector<int>& must1) {
    int full = (1 << n) - 1, cnt = 0;
    for (int mask = 0; mask <= full; mask++) {
        if (!(mask & 1)) continue;
        if (mask & (1 << (n - 1))) continue;
        bool ok = true;
        for (int u = 0; u < n && ok; u++)
            if ((mask >> u) & 1)
                if ((mask & must1[u]) != must1[u]) ok = false;
        if (ok) cnt++;
    }
    return cnt % MOD;
}

// ---------- 4×4 转移矩阵 ----------
struct Mat {
    ll a[4][4];
    Mat() { memset(a, 0, sizeof(a)); }
    Mat operator*(const Mat& o) const {
        Mat r;
        for (int i = 0; i < 4; i++)
            for (int k = 0; k < 4; k++) if (a[i][k])
                for (int j = 0; j < 4; j++) if (o.a[k][j])
                    r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
        return r;
    }
};

Mat make_mat(int lb, int rb, ll C) {
    Mat m;
    if (lb == 0 && rb == 0) {
        m.a[0][0] = (2 + C) % MOD; m.a[0][1] = 1;
        m.a[1][1] = (1 + C) % MOD;
        m.a[2][2] = m.a[3][3] = 1;
    } else if (lb == 0 && rb == 1) {
        m.a[0][0] = (2 + C) % MOD; m.a[0][1] = m.a[0][2] = 1;
        m.a[1][1] = (1 + C) % MOD; m.a[1][3] = 1;
        m.a[2][2] = (1 + C) % MOD; m.a[2][3] = 1;
        m.a[3][3] = C;
    } else if (lb == 1 && rb == 0) {
        m.a[0][0] = (2 + C) % MOD;
        m.a[1][1] = m.a[2][2] = 1;
    } else { // lb=1, rb=1
        m.a[0][0] = (2 + C) % MOD; m.a[0][2] = 1;
        m.a[1][1] = m.a[3][3] = 1;
        m.a[2][2] = (1 + C) % MOD;
    }
    return m;
}

// ---------- 线段树 ----------
Mat seg[MAXB * 4];
char L[MAXB], R[MAXB];
int B;

void build(int o, int l, int r, ll C) {
    if (l == r) { seg[o] = make_mat(L[l] - '0', R[l] - '0', C); return; }
    int m = (l + r) >> 1;
    build(o << 1, l, m, C);
    build(o << 1 | 1, m + 1, r, C);
    seg[o] = seg[o << 1 | 1] * seg[o << 1];
}

void upd(int o, int l, int r, int p, ll C) {
    if (l == r) { seg[o] = make_mat(L[p] - '0', R[p] - '0', C); return; }
    int m = (l + r) >> 1;
    if (p <= m) upd(o << 1, l, m, p, C);
    else        upd(o << 1 | 1, m + 1, r, p, C);
    seg[o] = seg[o << 1 | 1] * seg[o << 1];
}

ll query() {
    Mat& M = seg[1];
    ll v[4] = { 0, 0, 0, 1 }, r[4] = { 0, 0, 0, 0 };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            r[i] = (r[i] + M.a[i][j] * v[j]) % MOD;
    return (r[0] + r[1] + r[2] + r[3]) % MOD;
}

// ---------- 单组求解 ----------
void solve() {
    int n, m, t;
    cin >> n >> m >> t;

    bitset<20> reach[20];
    for (int i = 0; i < n; i++) {
        reach[i].reset(); reach[i][i] = 1;
        reach[i][0] = 1; reach[n - 1][i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        reach[b][a] = 1;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (reach[i][k]) reach[i] |= reach[k];

    vector<int> must1(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (reach[i][j]) must1[i] |= (1 << j);
    ll C = count_filters(n, must1);

    string ls, rs; cin >> ls >> rs;
    int lenL = ls.size(), lenR = rs.size();
    B = MAXB;
    memset(L, '0', B); memset(R, '0', B);
    for (int i = 0; i < lenL; i++) L[B - lenL + i] = ls[i];
    for (int i = 0; i < lenR; i++) R[B - lenR + i] = rs[i];

    build(1, 0, B - 1, C);
    cout << query() << '\n';

    while (t--) {
        int op, i; cin >> op >> i;
        // i: 从左到右 1-indexed (最高位为第1位)
        int p;
        if (op == 0) p = B - lenL + (i - 1);
        else         p = B - lenR + (i - 1);
        if (p >= 0 && p < B) {
            if (op == 0) L[p] ^= 1;
            else         R[p] ^= 1;
            upd(1, 0, B - 1, p, C);
        }
        cout << query() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
