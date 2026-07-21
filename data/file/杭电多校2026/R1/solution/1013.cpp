#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;

const int N = 155, E = N * N;
const ull MOD = (1ULL << 61) - 1;
inline ull add(ull a, ull b) { if ((a += b) >= MOD) a -= MOD; return a; }
inline ull sub(ull a, ull b) { return a >= b ? a - b : a + MOD - b; }
inline ull mul(ull a, ull b) {
    u128 c = (u128)a * b;
    return add((ull)(c >> 61), (ull)(c & MOD));
}
inline ull neg(ull x) { return x ? MOD - x : 0; }
ull qpow(ull a, ull e = MOD - 2) {
    ull r = 1;
    while (e) { if (e & 1) r = mul(r, a); a = mul(a, a); e >>= 1; }
    return r;
}

int n, m, tot, ecnt;
int hd[N], nxt[E], to[E], col[E];
int el[E], er[E], et[E], eid[N][N];
int ans[N], vis[N], act[N], acnt;
ull ew[E], mat[N][N], inv[N][N][N], det[N];
ull lag[N][N][N], pol[N], tmp[N], quo[N], fac[N], ifac[N];
ull val[N], piv[N], ipiv[N], prd[N];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ull> dis(1, MOD - 1);

void pre() {
    for (int d = 0; d <= 150; ++d) {
        int pts = d + 1;
        fill(pol, pol + pts + 1, 0);
        pol[0] = 1;
        for (int rt = 1; rt <= pts; ++rt) {
            fill(tmp, tmp + pts + 1, 0);
            ull nrt = neg((ull)rt);
            for (int i = 0; i < rt; ++i) {
                tmp[i] = add(tmp[i], mul(pol[i], nrt));
                tmp[i + 1] = add(tmp[i + 1], pol[i]);
            }
            copy(tmp, tmp + pts + 1, pol);
        }
        fac[0] = 1;
        for (int i = 1; i < pts; ++i) fac[i] = mul(fac[i - 1], i);
        ifac[pts - 1] = qpow(fac[pts - 1]);
        for (int i = pts - 1; i >= 1; --i) ifac[i - 1] = mul(ifac[i], i);
        for (int p = 1; p <= pts; ++p) {
            quo[pts - 1] = pol[pts];
            for (int i = pts - 1; i >= 1; --i)
                quo[i - 1] = add(pol[i], mul(p, quo[i]));
            ull den = mul(ifac[p - 1], ifac[pts - p]);
            if ((pts - p) & 1) den = neg(den);
            for (int deg = 0; deg <= d; ++deg)
                lag[d][deg][p] = mul(quo[deg], den);
        }
    }
}
ull coef(int d, int deg) {
    if (deg < 0 || deg > d) return 0;
    ull res = 0;
    for (int p = 1; p <= d + 1; ++p)
        res = add(res, mul(val[p], lag[d][deg][p]));
    return res;
}
void link(int u, int v, int c) {
    el[ecnt] = u; er[ecnt] = v; et[ecnt] = c;
    to[ecnt] = v; col[ecnt] = c; nxt[ecnt] = hd[u]; hd[u] = ecnt;
    eid[u][v] = ecnt++;
}

bool gauss(int pt) {
    ull (*out)[N] = inv[pt];
    static int per[N];
    static ull idg[N];
    ull res = 1;
    for (int i = 1; i <= n; ++i) per[i] = i;
    for (int k = 1; k <= n; ++k) {
        int p = k;
        while (p <= n && mat[p][k] == 0) ++p;
        if (p > n) { det[pt] = 0; return 0; }
        if (p != k) {
            for (int j = 1; j <= n; ++j) swap(mat[p][j], mat[k][j]);
            swap(per[p], per[k]); res = neg(res);
        }
        ull x = mat[k][k]; res = mul(res, x);
        ull iv = idg[k] = qpow(x);
        for (int i = k + 1; i <= n; ++i) {
            ull x = mat[i][k] = mul(mat[i][k], iv);
            if (!x) continue;
            for (int j = k + 1; j <= n; ++j)
                mat[i][j] = sub(mat[i][j], mul(x, mat[k][j]));
        }
    }
    for (int i = 1; i <= n; ++i) {
        ull *row = out[i]; fill(row + 1, row + n + 1, 0); row[per[i]] = 1;
        for (int r = 1; r < i; ++r) {
            ull x = mat[i][r]; if (!x) continue;
            for (int j = 1; j <= n; ++j) row[j] = sub(row[j], mul(x, out[r][j]));
        }
    }
    for (int i = n; i >= 1; --i) {
        ull *row = out[i];
        for (int r = i + 1; r <= n; ++r) {
            ull x = mat[i][r]; if (!x) continue;
            for (int j = 1; j <= n; ++j) row[j] = sub(row[j], mul(x, out[r][j]));
        }
        ull iv = idg[i];
        for (int j = 1; j <= n; ++j) row[j] = mul(row[j], iv);
    }
    det[pt] = res;
    return true;
}

void gdet(int pt) {
    ull res = 1;
    for (int k = 1; k <= n; ++k) {
        int p = k;
        while (p <= n && mat[p][k] == 0) ++p;
        if (p > n) { det[pt] = 0; return; }
        if (p != k) {
            for (int j = k; j <= n; ++j) swap(mat[p][j], mat[k][j]);
            res = neg(res);
        }
        ull x = mat[k][k]; res = mul(res, x); ull iv = qpow(x);
        for (int i = k + 1; i <= n; ++i) {
            ull x = mul(mat[i][k], iv); if (!x) continue;
            for (int j = k + 1; j <= n; ++j)
                mat[i][j] = sub(mat[i][j], mul(x, mat[k][j]));
        }
    }
    det[pt] = res;
}

bool init() {
    for (int p = 1; p <= n + 1; ++p) {
        for (int i = 1; i <= n; ++i) fill(mat[i] + 1, mat[i] + n + 1, 0);
        for (int id = 0; id < m; ++id) {
            ull x = ew[id]; if (et[id]) x = mul(x, p);
            mat[el[id]][er[id]] = x;
        }
        if (p <= n) { if (!gauss(p)) return 0; }
        else gdet(p);
    }
    return true;
}
int calc(int u, int rem, int sz) {
    int deg = sz - 1;
    for (int id = hd[u]; id != -1; id = nxt[id]) {
        int v = to[id]; if (vis[v]) continue;
        int tar = rem - col[id];
        if (tar < 0 || tar > deg) continue;
        bool flg = true;
        for (int p = 1; p <= sz; ++p) {
            ull x = inv[p][v][u];
            if (!x) { flg = 0; break; }
            val[p] = mul(det[p], x);
        }
        if (flg && coef(deg, tar)) return id;
    }
    return -1;
}
void del(int u, int v, int sz) {
    prd[0] = 1;
    for (int p = 1; p <= sz; ++p) {
        piv[p] = inv[p][v][u];
        prd[p] = mul(prd[p - 1], piv[p]);
    }
    ull iv = qpow(prd[sz]);
    for (int p = sz; p >= 1; --p) {
        ipiv[p] = mul(iv, prd[p - 1]);
        iv = mul(iv, piv[p]);
    }
    for (int p = 1; p <= sz; ++p) {
        ull (*iv)[N] = inv[p];
        det[p] = mul(det[p], piv[p]);
        for (int i = 1; i <= acnt; ++i) {
            int r = act[i]; if (r == v) continue;
            ull x = mul(iv[r][u], ipiv[p]); if (!x) continue;
            for (int c = u + 1; c <= n; ++c) iv[r][c] = sub(iv[r][c], mul(x, iv[v][c]));
        }
    }
    vis[v] = 1;
    int pos = 1; while (act[pos] != v) ++pos;
    act[pos] = act[acnt--];
}
bool chk() {
    static int seen[N]; fill(seen + 1, seen + n + 1, 0);
    int red = 0;
    for (int u = 1; u <= n; ++u) {
        int v = ans[u];
        if (v < 1 || v > n || seen[v] || eid[u][v] < 0) return 0;
        seen[v] = 1; red += et[eid[u][v]];
    }
    return red == tot;
}
bool solve() {
    for (int id = 0; id < m; ++id) ew[id] = dis(rng);
    if (!init()) return 0;
    for (int p = 1; p <= n + 1; ++p) val[p] = det[p];
    if (!coef(n, tot)) return 0;
    for (int i = 1; i <= n; ++i) vis[i] = 0, act[i] = i, ans[i] = 0;
    acnt = n; int rem = tot;
    for (int u = 1; u <= n; ++u) {
        int sz = n - u + 1, id = calc(u, rem, sz);
        if (id < 0) return 0;
        int v = to[id]; ans[u] = v; rem -= col[id];
        if (sz > 1) del(u, v, sz); else vis[v] = 1;
    }
    return rem == 0 && chk();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pre();
    int T; cin >> T;
    while (T--) {
        cin >> n >> m >> tot; ecnt = 0;
        fill(hd + 1, hd + n + 1, -1);
        for (int i = 1; i <= n; ++i) fill(eid[i] + 1, eid[i] + n + 1, -1);
        for (int i = 0, u, v, c; i < m; ++i) { cin >> u >> v >> c; link(u, v, c); }
        if (!solve()) cout << "-1\n";
        else for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
    }
    return 0;
}
