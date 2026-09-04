#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int M = 1e6 + 10;
const int K = 20;

int n;
int cnt, top;
int a[K], f[K], b[M];
int prime[N];
double ans;
double lg[N];
bool vis[N];

void Prime() {
    for (int i = 2; i < N; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) continue;
        }
    }
    for (int i = 1; i <= cnt; i++/) lg[prime[i]] = log(prime[i]);
}
inline void Init() {
    ans = INF;
    top = 1;
    b[1] = 1;
    Prime();
}
void Dfs(int tol, double cur, int dep) {
    if (ans < cur || dep == 17) return;
    if (tol == 1) {
        if (ans > cur) {
            ans = cur;
            memcpy(a, f, sizeof(f));
        }
        return;
    }
    for (int i = 1; i * i <= tol; i++) {
        if (tol % i == 0) {
            f[dep] = i - 1;
            Dfs(tol / i, cur + f[dep] * lg[prime[dep]], dep + 1);
            f[dep] = tol / i - 1;
            Dfs(i, cur + f[dep] * lg[prime[dep]], dep + 1);
            f[dep] = 0;
        }
    }
}
void Mul(int a) {
    for (int i = 1; i <= top; i++) b[i] *= a;
    ll x = 0;   
    for (int i = 1; i <= top; i++) {
        b[i] += x;
        x = b[i] / 10;
        b[i] %= 10;
    }
    while (x) {
        b[++top] = x % 10;
        x /= 10;
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Init();
    // cerr<<prime[3];
    cin >> n;
    Dfs(n, 0, 1);
    for (int i = 1; i <= 17; i++) {
        // printf("a[%d]=%d\n", i, a[i]);
        for (int j = 1; j <= a[i]; j++) {
            Mul(prime[i]);
        }
    }
    for (int i = top; i; i--) printf("%d", b[i]);
    return 0;
}