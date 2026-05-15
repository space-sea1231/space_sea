#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n;
int cnt;
int prime[N], phi[N];
bool vis[N];

void Phi(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j]) phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) phi[i] += phi[i - 1];
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    Phi(n);
    ll ans = 0;
    // for (int i = 1; i <= n; i++) ans += i * ((phi[n / i] << 1) - 1);
    for (int i = 1; i <= n; i++) ans += i * (phi[n / i] - 1);
    printf("%lld\n", ans);
    return 0;
}