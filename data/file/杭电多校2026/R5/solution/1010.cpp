#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MX = 100;
using BS = bitset<MX + 1>;

struct Basis {
    array<BS, MX + 1> a{};
    array<int, MX + 1> v{};

    bool ins(BS x, int y) {
        for (int i = MX; i >= 1; i--) {
            if (!x[i]) continue;
            if (a[i].none()) {
                a[i] = x;
                v[i] = y;
                return true;
            }
            x ^= a[i];
            y ^= v[i];
        }
        return y == 0;
    }

    optional<int> get(BS x) const {
        int y = 0;
        for (int i = MX; i >= 1; i--) {
            if (!x[i]) continue;
            if (a[i].none()) return nullopt;
            x ^= a[i];
            y ^= v[i];
        }
        return y;
    }
};

BS read(int n) {
    BS a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.flip(x);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int h;
        cin >> h;
        Basis bs;
        for (int i = 0; i < h; i++) {
            int n, x;
            cin >> n >> x;
            bs.ins(read(n), x);
        }
        int q;
        cin >> q;
        while (q--) {
            int n;
            cin >> n;
            auto x = bs.get(read(n));
            cout << (x ? *x : -1) << '\n';
        }
    }
    return 0;
}
