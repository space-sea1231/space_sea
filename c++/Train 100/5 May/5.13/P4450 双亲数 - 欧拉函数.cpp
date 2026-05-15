#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int T;
int a, b, d;
int top;
int mu[N];
int vis[N], prime[N];

void Init() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
		if (!vis[i]) prime[++top] = i, mu[i] = -1;
		for (int j = 1; j <= top && i * prime[j] < N; j++){
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
		}
	}
    #ifdef __Debug
    // for (int i = 1; i < N; i++) printf("%d\n", mu[i]);
    #endif
    for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
    return ;
}

// int Calc(int x) {
//     if (x == 1) return 0;
//     int cnt = 0;
//     for (int i = 1; i <= top; i++) {
//         int sum = 0;
//         while (x % prime[i] == 0) {
//             x /= prime[i];
//             sum++;
//         }
//         cnt += (sum != 0);
//         if (sum >= 2) return 0;
//     }
//     return cnt % 2 == 0 ? 1 : -1;
// }

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Init();
    // cin >> T;
    // while (T--) {
        ll ans = 0;
        cin >> a >> b >> d;
        if (a < b) swap(a, b);
        int A = a / d, B = b / d, j = 0;
        for (int i = 1; i <= min(A, B); i = j + 1) {
            j = min(A/(A/i), B/(B/i));
            j = min(j, min(A, B));
            ans += (mu[j] - mu[i - 1]) * (ll)(A/i)*(B/i);
            #ifdef __Debug
            printf("l=%d r=%d\n", i, j);
            printf("Debug:%d\n", mu[j] - mu[i - 1]);
            #endif
        }
        printf("%lld\n", ans);
    // }
    
    
    return 0;
}