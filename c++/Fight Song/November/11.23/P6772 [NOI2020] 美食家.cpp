#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 260;
const int K = 32;

int n, m, T, k;
int c[N];
int id[N][6];

struct Matrix {
    int n, m;
    vector<ll> mat;
    Matrix(int _n, int _m) : n{_n}, m{_m}, mat((n + 1) * (m + 1), -INF) {}
    // vector<vector<ll>> mt;
    // Matrix(int _n,int _m):n(_n),m(_m),mt(n+1,vector<ll>(m+1)){}
    ll *operator[](int i) {
        return &mat[i * (m + 1)];
    }
    const ll *operator[](int i) const {
        return &mat[i * (m + 1)];
    }
    Matrix operator*(const Matrix &s) const {
        int x = n, y = s.m, z = m;
        Matrix res(x, y);
        for (int k = 1; k <= z; k++) {
            for (int i = 1; i <= x; i++) {
                if ((*this)[i][k] == -INF) continue;
                for (int j = 1; j <= y; j++) {
                    if (s[k][j] == -INF) continue;
                    res[i][j] = max(res[i][j], (*this)[i][k] + s[k][j]);
                }
            }
        }
        return res;
    }
}; Matrix f(1, N);
vector<Matrix> t(K, Matrix(N, N));

struct Query {
    int t, x, y;

    bool operator<(const Query &s) const {
        return t < s.t;
    }
}; Query q[N];
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> T >> k;
    int num = 0;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            id[i][j] = ++num;
        }
        for (int j = 1; j < 5; j++) {
            t[0][id[i][j]][id[i][j + 1]] = 0;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t[0][id[u][w]][id[v][1]] = c[v];
    }
    for (int i = 1; i < K; i++) t[i] = t[i - 1] * t[i - 1];
    
    for (int i = 1; i <= k; i++) cin >> q[i].t >> q[i].x >> q[i].y;
    q[++k] = (Query){T, 1, 0};
    sort(q + 1, q + k + 1);
    
    f[1][id[1][1]] = c[1];
    for (int i = 1; i <= k; i++) {
        int del = q[i].t - q[i - 1].t;
        // cerr << del << "\n";
        for (int j = K - 1; ~j; j--) {
            if ((del >> j) & 1) {
                cerr << j << " ";
                f = f * t[j];
            }
        }
        if (f[1][id[q[i].x][1]] != -INF) f[1][id[q[i].x][1]] += q[i].y;
    }
    // for (int i = 1; i <= n; i++) printf("f[%d]=%lld\n", i, f[1][i]);
    if (f[1][id[1][1]] == -INF) printf("-1\n");
    else printf("%lld\n", f[1][id[1][1]]);
    
    return 0;
}
/*
梦境，是多么漫长。
*/