#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7, Mod = 998244353;
int n, m, idx, a[N];
long long ans = 1;
int main() {
    freopen("detect.in", "r", stdin);
    freopen("detect.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    if (m <= 3 * (n - 1)) {
        if (m == 1) {cout << "1\n1 " << n << '\n';return 0;}
        while (m) {
            if (m == 4)
                a[++ idx] = 2, a[++ idx] = 2, m = 0, ans = ans * 4 % Mod;
            else if (m == 2)
                a[++ idx] = 2, m = 0, ans = ans * 2 % Mod;
            else
                a[++ idx] = 3, m -= 3, ans = ans * 3 % Mod;
        }
    }
    else {
        int x = m / (n - 1), num = m % (n - 1);
        idx = n - 1;
        for (int i = 1; i <= num; i ++)
            a[i] = x + 1, ans = ans * (x + 1) % Mod;
        for (int i = num + 1; i <= n - 1; i ++)
            a[i] = x, ans = ans * x % Mod;
    }
    cout << ans << '\n';
    for (int u = 1; u <= idx; u ++) {
        int v = (u == idx ? n : u + 1);
        for (int i = 1; i <= a[u]; i ++)
            cout << u << ' ' << v << '\n';
    }
    return 0;
}
