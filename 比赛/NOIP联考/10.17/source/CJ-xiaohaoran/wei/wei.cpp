#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 4294967296;
int a[400010];

signed main() {
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    int T;
    cin >> T;
    while (T --> 0) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        int x = 1, y = 1;
        for (int i = 2; i <= n; i++) {
            if (a[i] > a[i - 1]) {
                y = (y + 1) % mod;
                x = (x + y) % mod;
            }
            else {
                x = (x + 1) % mod;
                y = 1 % mod;
            }
        }
        ans = max(ans, x);
        for (int j = 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                swap(a[j], a[k]);
                x = 1, y = 1;
                for (int i = 2; i <= n; i++) {
                    if (a[i] > a[i - 1]) {
                        y = (y + 1) % mod;
                        x = (x + y) % mod;
                    }
                    else {
                        x = (x + 1) % mod;
                        y = 1 % mod;
                    }
                }
                ans = max(ans, x);
                swap(a[j], a[k]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}