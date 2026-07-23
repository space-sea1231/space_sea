#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

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

const int inf = 2e9;

const int N = 100100, MaxQ = 100100;

int n, Q;

struct point {
    i64 x, y;
    point() {}
    point(i64 _x, i64 _y) : x(_x), y(_y) {}
};

struct frac {
    i64 p, q;
    frac() {}
    frac(i64 _p, i64 _q) : p(_p), q(_q) {
        if (q < 0) {
            p = -p, q = -q;
        }
    }

    auto operator < (const frac &rhs) const {
        return i128(p) * rhs.q < i128(rhs.p) * q;
    }
    auto operator > (const frac &rhs) const {
        return i128(p) * rhs.q > i128(rhs.p) * q;
    }
};

point seq[N];

frac slope(point a, point b) {
    return frac(a.y - b.y, a.x - b.x);
}

// 检测连续三个点的凸性（大于 0 下凸，小于 0 上凸）
i128 check(point a, point b, point c) {
    return i128(b.x - a.x) * (c.y - a.y) - i128(c.x - a.x) * (b.y - a.y);
}

point qp[MaxQ];
frac ans[MaxQ];

std::vector<int> lay[N * 4];
void layout(int p, int l, int r, int s, int e, int id) {
    if (s <= l && r <= e) {
        lay[p].push_back(id);
        return;
    }
    int mid = (l + r) >> 1;
    if (s <= mid) {
        layout(p * 2, l, mid, s, e, id);
    }
    if (mid < e) {
        layout(p * 2 + 1, mid + 1, r, s, e, id);
    }
}

void solve(int p, int l, int r) {
    if (l < r) {
        int mid = (l + r) >> 1;
        solve(p * 2, l, mid);
        solve(p * 2 + 1, mid + 1, r);
    }

    if (!lay[p].size()) {
        return;
    }

    std::vector<point> ps;
    for (int i = l; i <= r; i ++) {
        ps.push_back(seq[i]);
    }
    std::sort(ps.begin(), ps.end(), [&] (point l, point r) -> bool {
        if (l.x == r.x) {
            return l.y > r.y;
        } else {
            return l.x < r.x;
        }
    });

    std::sort(lay[p].begin(), lay[p].end(), [&] (int l, int r) -> bool {
        return qp[l].x < qp[r].x;
    });

    std::vector<point> hull;
    auto get = [&] (point p) {
        if (!hull.size()) {
            return frac(inf, 1);
        }
        int l = 0, r = hull.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (slope(p, hull[mid]) > slope(p, hull[mid + 1])) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return slope(p, hull[l]);
    };

    /* LHS */
    int t = 0;
    for (int id : lay[p]) {
        for (; t < ps.size() && ps[t].x < qp[id].x; t ++) {
            if (hull.size() && hull.back().x == ps[t].x) {
                continue;
            }
            while (hull.size() >= 2 && check(hull.rbegin()[1], hull.back(), ps[t]) >= 0) {
                hull.pop_back();
            }
            hull.push_back(ps[t]);
        }
        chmin(ans[id], get(qp[id]));
    }

    /* RHS */
    std::reverse(ps.begin(), ps.end());
    std::reverse(lay[p].begin(), lay[p].end());
    hull = {};
    t = 0;
    for (int id : lay[p]) {
        for (; t < ps.size() && ps[t].x > qp[id].x; t ++) {
            if (hull.size() && hull.back().x == ps[t].x) {
                continue;
            }
            while (hull.size() >= 2 && check(hull.rbegin()[1], hull.back(), ps[t]) >= 0) {
                hull.pop_back();
            }
            hull.push_back(ps[t]);
        }
        chmin(ans[id], get(qp[id]));
    }
}

void work() {
    std::cin >> n >> Q;

    for (int i = 1; i <= n; i ++) {
        int x, v;
        std::cin >> x >> v;
        seq[i] = point(v, x);
    }

    for (int i = 1; i <= n * 4; i ++) {
        lay[i].clear();
    }
    for (int i = 1; i <= Q; i ++) {
        ans[i] = frac(inf, 1);
    }
    for (int i = 1; i <= Q; i ++) {
        int l, r, a, b;
        std::cin >> l >> r >> a >> b;
        qp[i] = point(b, a);
        layout(1, 1, n, l, r, i);
    }

    solve(1, 1, n);

    for (int i = 1; i <= Q; i ++) {
        auto [x, y] = ans[i];
        x = -x;
        if (x < 0) {
            std::cout << -1 << '\n';
            continue;
        }

        i64 g = std::gcd(x, y);
        x /= g, y /= g;

        std::cout << x << '/' << y << '\n';
    }
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