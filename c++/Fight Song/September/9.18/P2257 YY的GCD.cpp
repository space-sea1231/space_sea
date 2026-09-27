#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e7 + 10;

int T, n, m;
int cnt;
int f[N], sum[N];
int prime[N], mu[N];
bool vis[N];

void Prime() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j * prime[i] < N; j++) {
            f[j * prime[i]] += mu[j];
        }
    }
    for (int i = 1; i < N; i++) sum[i] = sum[i - 1] + f[i];
}

ll Query() {
    ll ans = 0;
    for (int l = 1, r = 0; l <= n; l = r + 1) {
        r = min(n/(n/l), m/(m/l));
        ans += (ll)(sum[r] - sum[l - 1]) * (n/l) * (m/l);
    }
    return ans;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (n > m) swap(n, m);
        printf("%lld\n", Query());
    }
    return 0;
}