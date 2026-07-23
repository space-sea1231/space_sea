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

const int N = 100100;
const i64 inf = 1e18;

int n;
int a[N];

i64 f[N][2];

int op(int x, int y) {
    return std::max(x, y);
}

void work() {
    std::cin >> n;

    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    if (n == 1) {
        std::cout << 0 << '\n';
        return;
    }

    f[2][0] = op(0, a[2]), f[2][1] = op(0, 0);
    for (int i = 3; i <= n; i ++) {
        f[i][0] = f[i][1] = inf;

        chmin(f[i][1], f[i - 1][0] + op(0, 0));
        chmin(f[i][0], f[i - 1][0] + op(0, a[i]));

        chmin(f[i][1], f[i - 1][1] + op(a[i - 2], 0));
        chmin(f[i][0], f[i - 1][1] + op(a[i - 2], a[i]));
    }

    i64 ans = inf;
    chmin(ans, f[n][0] + op(0, 0));
    chmin(ans, f[n][1] + op(a[n - 1], 0));

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }

    return 0;
}