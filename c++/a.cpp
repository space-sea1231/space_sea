#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}

    void add(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }

    int query_greater(int v) {
        return query(n) - query(v);
    }
};

vector<long long> count_2d(int n, const vector<int>& X, const vector<int>& Y) {
    struct Pt { int x, y, id; };
    vector<Pt> pts(n);
    for (int i = 0; i < n; ++i) {
        pts[i] = {X[i], Y[i], i};
    }
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x > b.x;
    });

    BIT bit(n + 2);
    vector<long long> res(n, 0);
    for (int i = 0; i < n; ++i) {
        res[pts[i].id] = bit.query_greater(pts[i].y + 1); 
        bit.add(pts[i].y + 1, 1);
    }
    return res;
}

struct Pt3D {
    int a, b, c, id;
};

void cdq(int l, int r, vector<Pt3D>& pts, vector<long long>& d, BIT& bit) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    cdq(l, mid, pts, d, bit);
    cdq(mid + 1, r, pts, d, bit);

    vector<Pt3D> left(pts.begin() + l, pts.begin() + mid + 1);
    vector<Pt3D> right(pts.begin() + mid + 1, pts.begin() + r + 1);

    sort(left.begin(), left.end(), [](const Pt3D& p1, const Pt3D& p2) {
        return p1.b > p2.b;
    });
    sort(right.begin(), right.end(), [](const Pt3D& p1, const Pt3D& p2) {
        return p1.b > p2.b;
    });

    int j = 0;
    for (const auto& r_pt : right) {
        while (j < (int)left.size() && left[j].b > r_pt.b) {
            bit.add(left[j].c + 1, 1);
            j++;
        }
        d[r_pt.id] += bit.query_greater(r_pt.c + 1);
    }

    for (int k = 0; k < j; ++k) {
        bit.add(left[k].c + 1, -1);
    }
}

vector<long long> count_3d(int n, const vector<int>& A, const vector<int>& B, const vector<int>& C) {
    vector<Pt3D> pts(n);
    for (int i = 0; i < n; ++i) {
        pts[i] = {A[i], B[i], C[i], i};
    }
    sort(pts.begin(), pts.end(), [](const Pt3D& p1, const Pt3D& p2) {
        return p1.a > p2.a;
    });

    vector<long long> d(n, 0);
    BIT bit(n + 2);
    cdq(0, n - 1, pts, d, bit);
    return d;
}

long long C2(long long x) {
    return x < 2 ? 0 : x * (x - 1) / 2;
}

long long C3(long long n) {
    return n < 3 ? 0 : n * (n - 1) * (n - 2) / 6;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<int> A(n), B(n), C(n);
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
    for (int i = 0; i < n; ++i) cin >> C[i];

    vector<long long> mAB = count_2d(n, A, B);
    vector<long long> mAC = count_2d(n, A, C);
    vector<long long> mBC = count_2d(n, B, C);

    vector<long long> d = count_3d(n, A, B, C);

    long long sum_2d = 0;
    long long sum_2d_c2 = 0;
    for (int i = 0; i < n; ++i) {
        sum_2d += mAB[i] + mAC[i] + mBC[i];
        sum_2d_c2 += C2(mAB[i]) + C2(mAC[i]) + C2(mBC[i]);
    }

    long long sum_3d = 0;
    long long sum_3d_c2 = 0;
    for (int i = 0; i < n; ++i) {
        sum_3d += d[i];
        sum_3d_c2 += C2(d[i]);
		cerr<<sum_3d_c2 << endl; 
    }

    long long ans = 1;                          
    ans += n;                               
    ans += (sum_2d - 3 * sum_3d);                 
    ans += C3(n) - sum_2d_c2 + 2 * sum_3d_c2;    
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}