#include <bits/stdc++.h>
#define int unsigned int
using namespace std;

const int N = 3e3 + 7;
int t, n, sum, ans, cnt, a[N];

signed main() {
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n, ans = 0;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                swap(a[i], a[j]);
                sum = 0, cnt = 1;
                for (int k = 2; k <= n; ++k) {
                    if (a[k] > a[k - 1]) ++cnt;
                    else sum += cnt * (cnt + 1) / 2, cnt = 1;
                }
                ans = max(ans, sum + cnt * (cnt + 1) / 2);
                swap(a[i], a[j]);
            }
        }
        cout << ans << '\n';
    }
	return 0;
}