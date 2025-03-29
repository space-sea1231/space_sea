#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e6 + 10;

const int kMod = 998244353;

int T;

int n;

int p[kMaxN];

int ban[kMaxN];
int id[kMaxN], tot;

int ans;

int main() {
	freopen("wo.in", "r", stdin);
	freopen("wo.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n * 2; ++i) {
			cin >> p[i];
		}
		ans = 1;
		fill(ban + 1, ban + n * 2 + 1, 0);
		for (int i = 1; i <= n; ++i) {
			if (!p[i * 2 - 1] && !p[i * 2]) ans = 2ll * ans % kMod;
			if (p[i * 2 - 1] && p[i * 2])
				ban[p[i * 2 - 1]] = ban[p[i * 2]] = 1;
		}
		fill(id + 1, id + n * 2 + 1, -1);
		tot = 0;
		for (int i = 1; i <= n * 2; ++i) {
			if (!ban[i]) id[i] = ++tot;
		}
		for (int i = 1; i <= n * 2; ++i) ban[p[i]] = 1;
		int cnt = 0;
		for (int i = 1; i <= n * 2; ++i) {
			if (!ban[i] && id[i] <= tot / 2) ++cnt;
		}
		//cout << "cnt1 = " << cnt << '\n';
		for (int i = 1; i <= cnt; ++i) ans = 1ll * ans * i % kMod;
		cnt = 0;
		for (int i = 1; i <= n * 2; ++i) {
			if (!ban[i] && id[i] > tot / 2) ++cnt;
		}
		//cout << "cnt2 = " << cnt << '\n';
		for (int i = 1; i <= cnt; ++i) ans = 1ll * ans * i % kMod;
		cout << ans << '\n';
	}
	return 0;
}
