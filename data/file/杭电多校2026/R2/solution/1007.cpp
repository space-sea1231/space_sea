#include <bits/stdc++.h>

using i64 = long long;

#define debug(a) std::cout << #a << '=' << (a) << ' '

template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

const int N = 200100;

int primeCount, prime[N], fac[N];
int miu[N];

std::vector<int> factor[N];

void sieve(const int &n) {
    miu[1] = 1;
    for (int i = 2; i <= n; i ++) {
        if (!fac[i]) {
            prime[++ primeCount] = i, fac[i] = i, miu[i] = -1;
        }
        for (int j = 1; j <= primeCount; j ++) {
            if (prime[j] > fac[i] || prime[j] > n / i) break;
            fac[i * prime[j]] = prime[j];
            miu[i * prime[j]] = miu[i] * (i % prime[j] ? -1 : 0);
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = i; j <= n; j += i) {
            factor[j].push_back(i);
        }
    }
}

int n;
std::vector<std::vector<int>> G;

int sze[N];
int son[N];

void dfs_init(int u, int fu) {
    sze[u] = factor[u].size();
    son[u] = 0;
    for (int v : G[u]) {
        if (v == fu) {
            continue;
        }
        dfs_init(v, u);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}

int cnt[N];
i64 ans;

inline void calc(int u, int k) {
    for (int x : factor[u]) {
        if (x % k == 0) {
            ans += miu[x / k] * cnt[x];
        }
    }
}
void calcTree(int u, int fu, int k) {
    calc(u, k);
    for (int v : G[u]) {
        if (v == fu) {
            continue;
        }
        calcTree(v, u, k);
    }
}

inline void add(int u, int d) {
    for (int x : factor[u]) {
        cnt[x] += d;
    }
}
void addTree(int u, int fu, int d) {
    add(u, d);
    for (int v : G[u]) {
        if (v == fu) {
            continue;
        }
        addTree(v, u, d);
    }
}

void solve(int u, int fu, int save) {
    for (int v : G[u]) {
        if (v == fu || v == son[u]) {
            continue;
        }
        solve(v, u, 0);
    }
    if (son[u]) {
        solve(son[u], u, 1);
    }

    for (int v : G[u]) {
        if (v == fu || v == son[u]) {
            continue;
        }
        calcTree(v, u, u);
        addTree(v, u, +1);
    }

    ans += cnt[u];
    add(u, +1);

    if (!save) {
        addTree(u, fu, -1);
    }
}

void work() {
    std::cin >> n;

    G.assign(n + 1, {});
    for (int i = 1; i < n; i ++) {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    dfs_init(1, 0);

    ans = 0;
    solve(1, 0, 0);

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    sieve(200000);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }

    return 0;
}