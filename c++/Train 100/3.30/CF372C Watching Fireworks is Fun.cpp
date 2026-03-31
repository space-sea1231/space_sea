#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 5e4 + 10;
const int M = 3e2 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, d;
int a[M], b[M], t[M];
ll f[2][N];
int que[N];
bool flag = true;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> d;
    memset(f, -0x3f, sizeof(f));
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i] >> t[i];
    for (int i = 1; i <= n; i++) f[0][i] = 0;
    for (int i = 1; i <= m; i++) {
        int back = 1, top = 1, k = 1;
        for (int j = 1; j <= n; j++) {
            int lim1 = min((ll)n, j + (ll)(t[i] - t[i - 1]) * d);
            for (; k <= lim1; k++) {
                while (back < top && f[flag ^ 1][que[top - 1]] <= f[flag ^ 1][k]) top--;
                que[top++] = k;
            }
            int lim2 = max(1LL, j - (ll)(t[i] - t[i - 1]) * d);
            while (back < top && que[back] < lim2) back++;
            f[flag][j] = f[flag ^ 1][que[back]] - abs(a[i] - j) + b[i];
        }
        flag ^= 1;
    }
    ll ans = -INF;
    for (int i = 1; i <= n; i++) ans = max(ans, f[flag ^ 1][i]);
    printf("%lld\n", ans);
    return 0;
}