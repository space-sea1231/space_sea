#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;
using ld = long double;

struct Point {
    ll x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

Point operator+(const Point& a, const Point& b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator-(const Point& a) {
    return {-a.x, -a.y};
}

i128 cross_vec(const Point& a, const Point& b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

i128 cross3(const Point& a, const Point& b, const Point& c) {
    return cross_vec(b - a, c - a);
}

// 求凸包，返回逆时针顺序，且去掉边上的共线点。
// 若所有点共线，会返回两个端点。
vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int n = (int)p.size();
    if (n <= 1) return p;

    vector<Point> lower, upper;

    for (const auto& pt : p) {
        while ((int)lower.size() >= 2 &&
               cross3(lower[(int)lower.size() - 2], lower.back(), pt) <= 0) {
            lower.pop_back();
        }
        lower.push_back(pt);
    }

    for (int i = n - 1; i >= 0; --i) {
        const auto& pt = p[i];
        while ((int)upper.size() >= 2 &&
               cross3(upper[(int)upper.size() - 2], upper.back(), pt) <= 0) {
            upper.pop_back();
        }
        upper.push_back(pt);
    }

    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

// 将凸多边形循环移位到 y 最小、若并列 x 最小的点作为起点。
// 输入应为逆时针凸包。
vector<Point> normalize_polygon(vector<Point> p) {
    int n = (int)p.size();
    if (n <= 1) return p;

    int s = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i].y < p[s].y || (p[i].y == p[s].y && p[i].x < p[s].x)) {
            s = i;
        }
    }

    rotate(p.begin(), p.begin() + s, p.end());
    return p;
}

vector<Point> translate_polygon(const vector<Point>& p, const Point& v) {
    vector<Point> res;
    res.reserve(p.size());

    for (auto a : p) {
        res.push_back(a + v);
    }

    return res;
}

// 凸多边形 Minkowski 和。
// 输入可以是普通点集，会先取凸包。
// 返回结果也会做凸包清理，方便处理共线和退化情况。
vector<Point> minkowski_sum(vector<Point> A, vector<Point> B) {
    A = convex_hull(A);
    B = convex_hull(B);

    if (A.empty()) return B;
    if (B.empty()) return A;

    if (A.size() == 1 && B.size() == 1) {
        return {A[0] + B[0]};
    }

    if (A.size() == 1) {
        return translate_polygon(B, A[0]);
    }

    if (B.size() == 1) {
        return translate_polygon(A, B[0]);
    }

    // 若有一个凸包退化成线段，则直接枚举端点与另一个凸包顶点。
    // 复杂度仍是线性的。
    if (A.size() == 2 || B.size() == 2) {
        vector<Point> pts;
        pts.reserve(A.size() * B.size());

        for (auto a : A) {
            for (auto b : B) {
                pts.push_back(a + b);
            }
        }

        return convex_hull(pts);
    }

    A = normalize_polygon(A);
    B = normalize_polygon(B);

    int n = (int)A.size();
    int m = (int)B.size();

    vector<Point> res;
    res.reserve(n + m);

    Point cur = A[0] + B[0];
    res.push_back(cur);

    int i = 0, j = 0;

    while (i < n || j < m) {
        if (i == n) {
            Point e = B[(j + 1) % m] - B[j];
            cur = cur + e;
            ++j;
        } else if (j == m) {
            Point e = A[(i + 1) % n] - A[i];
            cur = cur + e;
            ++i;
        } else {
            Point eA = A[(i + 1) % n] - A[i];
            Point eB = B[(j + 1) % m] - B[j];

            i128 cr = cross_vec(eA, eB);

            if (cr > 0) {
                cur = cur + eA;
                ++i;
            } else if (cr < 0) {
                cur = cur + eB;
                ++j;
            } else {
                cur = cur + eA + eB;
                ++i;
                ++j;
            }
        }

        res.push_back(cur);
    }

    // 最后一个点会回到起点，删掉。
    if (!res.empty()) {
        res.pop_back();
    }

    return convex_hull(res);
}

Point rotate90(const Point& p) {
    return {-p.y, p.x};
}

ld perimeter(const vector<Point>& p) {
    int n = (int)p.size();
    if (n <= 1) return 0.0L;

    ld res = 0.0L;

    for (int i = 0; i < n; ++i) {
        Point a = p[i];
        Point b = p[(i + 1) % n];

        ld dx = (ld)b.x - (ld)a.x;
        ld dy = (ld)b.y - (ld)a.y;

        res += sqrtl(dx * dx + dy * dy);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const ld PI = acosl(-1.0L);

    int T;
    cin >> T;

    cout.setf(ios::fixed);
    cout << setprecision(15);

    while (T--) {
        int n;
        cin >> n;

        vector<Point> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }

        // K：原点集凸包
        vector<Point> K = convex_hull(p);

        // -K
        vector<Point> negK;
        negK.reserve(K.size());

        for (auto pt : K) {
            negK.push_back(-pt);
        }

        // D = K + (-K)
        vector<Point> D = minkowski_sum(K, negK);

        // C = conv(D ∪ R90(D))
        vector<Point> all;
        all.reserve(2 * D.size());

        for (auto pt : D) {
            all.push_back(pt);
        }

        for (auto pt : D) {
            all.push_back(rotate90(pt));
        }

        vector<Point> C = convex_hull(all);

        ld ans = 2.0L * perimeter(C) / PI;

        if (fabsl(ans) < 5e-13L) {
            ans = 0.0L;
        }

        cout << ans << '\n';
    }

    return 0;
}