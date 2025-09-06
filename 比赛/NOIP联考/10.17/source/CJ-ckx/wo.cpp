#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;
using db = long double;

template <typename T>
inline bool ckmin(T &x, const T &y) {
    return y < x && (x = y, true);
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
    return x < y && (x = y, true);
}

constexpr int N = 1e6 + 5, mo = 998244353;

int n, p[2 * N];
int fac[N], pw[N];
bool vis[2 * N];

void math(int n) {
    *fac = *pw = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = ll(fac[i - 1]) * i % mo;
        pw[i] = 2 * pw[i - 1] % mo;
    }
}

void proc() {
    cin >> n;
    memset(vis + 1, false, 2 * n);
    for (int i = 1; i <= 2 * n; ++i)
        cin >> p[i];
    int e = 0, rk = n;
    for (int i = 1; i <= 2 * n; i += 2) {
        if (p[i] == 0 && p[i + 1] == 0)
            ++e;
        else if (p[i] && p[i + 1])
            vis[p[i]] = vis[p[i + 1]] = true, --rk;
    }
    int mid = 1, l = rk, r = rk;
    while (rk)
        rk -= !vis[mid++];
    for (int i = 1; i <= 2 * n; i += 2) {
        if (p[i] && p[i + 1])
            continue;
        for (int j : {i, i + 1}) {
            if (p[j] > 0 && p[j] < mid)
                --l;
            else if (p[j] >= mid)
                --r;
        }
    }
    // cerr << "e = " << e << ", l = " << l << ", r = " << r << "\n";
    cout << ll(pw[e]) * fac[l] % mo * fac[r] % mo << "\n";
}

int main() {
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    math(N - 1);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        proc();
}
