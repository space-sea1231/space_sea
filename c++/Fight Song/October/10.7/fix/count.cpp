#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
typedef __int128_t i128;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e6 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int n, m, x;
int cnt;
int prime[N], mu[N], phi[N];
bool vis[N];
unordered_map<int, int> vis_mu; 
unordered_map<int, int> vis_phi;

void Prime() {
    mu[1] = phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
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
        phi[i] = (phi[i] + phi[i - 1]) % Mod;
    }
}

int Mu(int x) {
    if (x < N) return mu[x];
    if (vis_mu.count(x)) return vis_mu[x];
    int ans = 1;
    for (int l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (ll)(r - l + 1) * Mu(x / l);
    }
    return vis_mu[x] = ans;
}

int Phi(int x) {
    if (x < N) return phi[x];
    if (vis_phi.count(x)) return vis_phi[x];
    int ans = (ll)x * (x + 1) / 2 % Mod;
    for (int l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans = (ans - (ll)(r - l + 1) * Phi(x / l)) % Mod;
    }
    if (ans < 0) ans += Mod;
    return vis_phi[x] = ans;
}

int C1(int a, int b) {
    if (a == 0 || b == 0) return 0;
    int lim = min(a, b);
    int res = 0;
    for (int l = 1, r; l <= lim; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        int mu_sum = (Mu(r) - Mu(l - 1)) % Mod;
        if (mu_sum < 0) mu_sum += Mod;
        res = (res + (ll)mu_sum * (a / l) % Mod * (b / l)) % Mod;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Prime();
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> x;
        // term1 = sum ((n-1)(m-1)-1)/2
        i128 A = (i128)n * (n - 1) / 2;
        i128 B = (i128)m * (m - 1) / 2;
        i128 S1 = A * B - (i128)n * m;
        int ans = ((S1 % Mod + Mod) % Mod) * inv2 % Mod;

        int lim = min(n, m);
        // term2 = sum d / 2  = G1 * inv2
        int G1 = 0;
        for (int l = 1, r; l <= lim; l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            int a = n / l, b = m / l;
            int phi_sum = (Phi(r) - Phi(l - 1)) % Mod;
            if (phi_sum < 0) phi_sum += Mod;
            G1 = (G1 + (ll)a * b % Mod * phi_sum) % Mod;
        }
        ans = (ans + (ll)G1 * inv2) % Mod;

        // term3 = sum d * floor(x/d)
        int term3 = 0;
        for (int l = 1, r; l <= lim; l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            int a = n / l, b = m / l;
            int cnt = C1(a, b);
            ll s = 0;
            if (x > 0) {
                int u = l;
                while (u <= r) {
                    int c = x / u;
                    if (c == 0) break;
                    int v = min(r, x / c);
                    ll sum_d = (ll)(u + v) * (v - u + 1) / 2;
                    s = (s + (ll)c * (sum_d % Mod)) % Mod;
                    u = v + 1;
                }
            }
            term3 = (term3 + (ll)cnt * s) % Mod;
        }
        ans = (ans + term3) % Mod;
        printf("%d\n", ans);
    }
    return 0;
}
/*
一曲定重楼
一眼半生筹
看的全都是那诡谲云涌
入得此门不回首
无需宣之于口
我对案再拜那风雨瓢泼的残陋
再聚首
戏子多秋
可怜一处情深旧
满座衣冠皆老朽
黄泉故事无止休
戏无骨难左右
换过一折又重头
只道最是人间不能留
误闯天家
劝余放下手中砂
张口欲唱声却哑
粉面披衣叫个假
怜余来安座下
不敢沾染佛前茶
只作凡人赴雪月风花
绕过胭脂楼
打散结发扣
唱的全都是那情深不寿
入得此门不回首
无需宣之于口
我对镜遮掩那风雨瓢泼的残陋
碑已旧
戏子多秋
可怜一处情深旧
满座衣冠皆老朽
黄泉故事无止休
戏无骨难左右
换过一折又重头
只道最是人间不能留
误闯天家
劝余放下手中砂
送那人御街打马
才子佳人断佳话
怜余来苦咽下
求不得佛前茶
只留三寸土种二月花
*/