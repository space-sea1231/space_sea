#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 10, mod = 998244353;
int p[N];
void solve() {
	int n;
	cin >> n;
	int cnt = 0, cnt1 = 0, cnt2 = 0, ans = 1;
	int mid = n;
	for (int i = 1; i <= n * 2; ++i) {
		cin >> p[i];
		if (p[i] && p[i] > mid) cnt1++;
		if (p[i] && p[i] <= mid) cnt2++;
	}
	cnt1 = n - cnt1, cnt2 = n - cnt2;
	for (int i = 1; i <= n; ++i) {
		int x = 2 * i - 1, y = 2 * i;
		if (x == 0) continue;
		if ((p[x] && !p[y]) || (!p[x] && p[y])) {
			int kx = max(p[x], p[y]);
			if (cnt1 == 0) {
				ans = (ans * cnt2);
				cnt2--;
			}
			else if (cnt2 == 0) {
				ans = (ans * cnt1);
				cnt1--;
			}
			else if (kx <= mid) {
				ans = (ans * cnt2);
				cnt2--;
			}
			else {
				ans = (ans * cnt1);
				cnt1--;
			}
		} 
		if (!p[x] && !p[y]) {
			int kk = (int)(cnt1 + cnt2) % mod / 2 % mod * (int)(ceil(1.0 * (cnt1 + cnt2 + 1) / 2)) % mod;
			ans = ((ans * kk) % mod * 2) % mod;
			cnt1--; cnt2--;
		}
//		cout << cnt1 << ' ' << cnt2 << '\n';
	}
	cout << max(1ll, ans % mod) << '\n';
}
signed main() {
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

