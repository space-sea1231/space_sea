#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
int n, m, N;
vector<ll> fx;      // fx[pos]: 固定值, LLONG_MIN 表示自由位置
vector<ll> fr;      // 自由亚基的值
vector<int> f;

bool check(ll X) {
    int c1 = 0;
    for (ll v : fr) if (v >= X) c1++;
    for (int i = 1; i <= n; i++)
        f[i] = (fx[i] == LLONG_MIN) ? 1 : (fx[i] >= X ? 0 : INF);
    for (int j = 1; j <= (n - 1) / 2; j++) {
        int a = f[3*j-2], b = f[3*j-1], c = f[3*j];
        int mx = max(a, max(b, c));
        ll s = (ll)a + b + c - mx;
        f[n + j] = (int)min(s, (ll)INF);
    }
    return f[N] <= c1;
}

int main() {
    freopen("mushroom.in", "r", stdin);
    freopen("mushroom.out", "w", stdout);
    scanf("%d %d", &n, &m);
    N = n + (n - 1) / 2;
    fx.assign(n + 1, LLONG_MIN);
    f.assign(N + 1, 0);
    vector<ll> all;
    for (int i = 1; i <= m; i++) {
        ll a; int p; scanf("%lld %d", &a, &p);
        fx[p] = a; all.push_back(a);
    }
    for (int i = m + 1; i <= n; i++) {
        ll a; scanf("%lld", &a);
        fr.push_back(a); all.push_back(a);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int lo = 0, hi = all.size() - 1, ans = 0;
    while (lo <= hi) {                 // 找最大的可行 X
        int mid = (lo + hi) / 2;
        if (check(all[mid])) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    printf("%lld\n", all[ans]);
    return 0;
}