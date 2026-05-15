#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <set>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int T, n, m;
int a[N], b[N], p[N], t[N];
multiset<int> s;

int Exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = Exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return d;
}

int Mul(int a, int b, int p) {
    int sum = 0;
    while (b) {
        if (b & 1) sum = (sum + a) % p;
        a = (a + a) % p;
        b >>= 1; 
    }
    return sum;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        s.clear();
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> t[i];
        for (int i = 1; i <= m; i++) {
            int x;
            cin >> x;
            s.insert(x);
        }
        int maxn = 0;
        for (int i = 1; i <= n; i++) {
            auto tp = s.upper_bound(a[i]);
            if (tp != s.begin()) tp--;
            b[i] = *tp;
            s.erase(tp);
            s.insert(t[i]);
            maxn = max(maxn, (a[i] - 1) / b[i] + 1);
        }
        int acc = 1, ans = 0;
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            int x, y;
            int d = Exgcd(Mul(acc, b[i], p[i]), p[i], x, y);
            int c = (a[i] - b[i] * ans % p[i] + p[i]) % p[i];
            if (c % d) {
                flag = false;
                break;
            }
            int mod = p[i] / d;
            x = (x % mod + mod) % mod;
            ans = ans + Mul(acc, Mul(x, (c / d), mod), acc * mod);
            acc = acc * mod;
            ans = ans % acc;
        }
        if (flag) printf("%lld\n", max(ans, maxn));
        else printf("-1\n");
    }
    return 0;
}