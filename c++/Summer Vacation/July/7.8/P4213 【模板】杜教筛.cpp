#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e6 + 10;

int t, n;
int cnt;
ll phi[N], mu[N];
int prime[N];
bool vis[N];
unordered_map<int, int> vis_mu;
unordered_map<int, ll> vis_phi;

void Prime() {
    mu[1] = phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j]) {
                mu[i * prime[j]] = -mu[i];
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            } else {
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}
ll Mu(ll x) {
    if (x < N) return mu[x];
    if (vis_mu[x]) return vis_mu[x];
    ll ans = 1;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (r - l + 1) * Mu(x / l);
    }
    return vis_mu[x] = ans;
}
ll Phi(ll x) {
    if (x < N) return phi[x];
    if (vis_phi[x]) return vis_phi[x];
    ll ans = x * (x + 1) / 2;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (r - l + 1) * Phi(x / l);
    }
    return vis_phi[x] = ans;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> t;
    while (t--) {
        cin >> n;
        printf("%lld %lld\n", Phi(n), Mu(n));
    }
    return 0;
}