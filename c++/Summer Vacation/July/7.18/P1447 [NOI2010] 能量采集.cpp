#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int cnt;
ll phi[N];
int prime[N];
bool vis[N];

void Prime() {
	phi[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!vis[i]) {
			phi[i] = i - 1;
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt &&  i * prime[j] < N; j++) {
			vis[i * prime[j]] = true;
			if (i % prime[j]) phi[i * prime[j]] = phi[i] * phi[prime[j]];
			else {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
		}
	}
	// for (int i = 1; i < N; i++) phi[i] += phi[i - 1];
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Prime();
	cin >> n >> m;
	ll ans = 0;
	// for (int i = 1; i <= max(n, m); i++) printf("phi[%d]=%d\n", i, phi[i]);
	for (int i = 1, lim = min(n, m); i <= lim; i++) ans += (ll)(n / i) * (m / i) * phi[i];
	cerr<<ans;
	printf("%lld\n", (ans << 1) - (ll)n * m);
	return 0;
}