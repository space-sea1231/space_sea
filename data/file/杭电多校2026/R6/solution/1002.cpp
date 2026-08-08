#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll f[64];

void init() {
    int p[3][2] = {{1, 6}, {2, 5}, {3, 4}};
    int a[3] = {0, 1, 2};
    do {
        int inv = 0;
        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                inv += a[i] > a[j];

        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                for (int z = 0; z < 2; z++) {
                    if ((inv + x + y + z) & 1) continue;
                    int t[3] = {x, y, z}, b[6];
                    for (int i = 0; i < 3; i++) {
                        b[i * 2] = p[a[i]][t[i]];
                        b[i * 2 + 1] = p[a[i]][t[i] ^ 1];
                    }
                    for (int s = 0; s < 64; s++) {
                        int sum = 0;
                        for (int i = 0; i < 6; i++)
                            if (s >> i & 1) sum += b[i];
                        f[s] = max(f[s], 1LL * sum);
                    }
                }
    } while (next_permutation(a, a + 3));
}

ll solve(const vector<ll>& h, int m, int x, int y) {
    auto at = [m, &h](int i, int j) { return h[1LL * i * (m + 2) + j]; };
    ll H = at(x, y);
    if (!H) return 0;

    ll q[8] = {1, 2, H, H + 1,
        at(x - 1, y) + 1, at(x + 1, y) + 1,
        at(x, y - 1) + 1, at(x, y + 1) + 1};
    sort(q, q + 8);

    int k = 0;
    for (int i = 0; i < 8; i++)
        if (q[i] >= 1 && q[i] <= H + 1 && (!k || q[i] != q[k - 1]))
            q[k++] = q[i];

    ll res = 0;
    for (int i = 0; i + 1 < k; i++) {
        ll z = q[i];
        int s = 0;
        if (z == H) s |= 1;
        if (z == 1) s |= 2;
        if (at(x - 1, y) < z) s |= 4;
        if (at(x + 1, y) < z) s |= 8;
        if (at(x, y - 1) < z) s |= 16;
        if (at(x, y + 1) < z) s |= 32;
        res += (q[i + 1] - q[i]) * f[s];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<ll> h(1LL * (n + 2) * (m + 2));
        auto at = [m, &h](int i, int j) -> ll& { return h[1LL * i * (m + 2) + j]; };
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) cin >> at(i, j);

        ll ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) ans += solve(h, m, i, j);
        cout << ans << '\n';
    }
    return 0;
}
