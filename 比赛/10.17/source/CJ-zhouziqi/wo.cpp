#include <algorithm>
#include <cstdio>

namespace FastIO {
template <typename T> void readInt(T &x) {
    char ch;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');

    int f = 1;
    if (ch == '-') {
        f = -1;
        x = 0;
    } else {
        x = ch - '0';
    }

    while ((ch = getchar()) >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
    }
}

template <typename First, typename ... Args>
  void read(First &first, Args&... args) {
    read(first);
    read(args...);
}

template <typename T> void putInt(T x, char ch) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (!x) {
        putchar('0');
    }

    static int len = 0;
    static char buf[20];

    while (x) {
        buf[len ++] = x % 10 + '0';
        x /= 10;
    }
    while (len) {
        putchar(buf[-- len]);
    }
    putchar(ch);
}
}

constexpr int MAXN = 1000000 + 2;
constexpr int P = 998244353;

int p[MAXN], tmp[MAXN];

bool vis[MAXN];

void add(int &x, int y) {
    (x += y) >= P && (x -= P);
}

void solve() {
    int n, ans = 1;
    FastIO::readInt(n);

    for (int i = 1; i <= n + n; i ++) {
        FastIO::readInt(p[i]);
        vis[i] = false;
    }

    for (int i = 1; i <= n; i ++) {
        int u = p[i + i - 1];
        int v = p[i + i];
        if (u && v) {
            vis[u] = vis[v] = true;
        }
        if (!u && !v) {
            add(ans, ans);
        }
    }

    int res = 0;
    for (int i = 1; i <= n + n; i ++) {
        if (!vis[i]) {
            tmp[++ res] = i;
        }
    }
    res >>= 1;

    int x = res, y = res;
    for (int i = 1; i <= n; i ++) {
        int u = p[i + i - 1];
        int v = p[i + i];
        if (u < v) {
            std::swap(u, v);
        }
        if (u && !v) {
            x -= u <= tmp[res];
            y -= u > tmp[res];
        }
    }

    for (int i = 2; i <= x; i ++) {
        ans = (long long){ans} * i % P;
    }
    for (int i = 2; i <= y; i ++) {
        ans = (long long){ans} * i % P;
    }

    FastIO::putInt(ans, '\n');
}

int main() {
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);

    int T;
    FastIO::readInt(T);

    while (T --) {
        solve();
    }

    return 0;
}
