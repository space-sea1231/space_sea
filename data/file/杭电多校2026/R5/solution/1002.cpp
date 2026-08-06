#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;
ll p[N], q[N], id[N];

bool cmp(ll a, ll b) {
    return p[a] * q[b] < p[b] * q[a];
}

pair<ll, ll> eg(ll a, ll b, ll c, ll d) {
    ll x = (a + b - 1) / b;
    if (x * d <= c) return {x, 1};
    ll t = a / b;
    auto z = eg(d, c % d, b, a % b);
    return {t * z.first + z.second, z.first};
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, k, i;
        ll x, y, my;
        scanf("%d%d", &n, &m);
        iota(id + 1, id + n + 1, 1);
        for (i = 1; i <= n; ++i) scanf("%lld", &p[i]);
        for (i = 1; i <= n; ++i) scanf("%lld", &q[i]);
        sort(id + 1, id + n + 1, cmp);

        if (p[id[n]] * p[id[n - 1]] < q[id[n]] * q[id[n - 1]]) {
            while (m--) {
                scanf("%d%lld", &k, &x);
                printf("No\n");
            }
            continue;
        }

        my = eg(q[id[n - 1]], p[id[n - 1]], p[id[n]], q[id[n]]).second;
        while (m--) {
            scanf("%d%lld", &k, &x);
            y = k != id[n] ? x * p[k] / q[k] : x;
            printf(y >= my ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
