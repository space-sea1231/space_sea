#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
int cnt, ans;
int head[N], nxt[N << 1], to[N << 1], val[N << 1];
int a[N], dp[N];
void Add(int u, int v, int w) {
    to[++cnt] = v;
    val[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void Dp(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i], w = val[i];
        if (v == fa) continue;
        Dp(v, u);
        ans = max(ans, dp[u] + dp[v] + w);
        dp[u] = max(dp[u], dp[v] + w);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v, a[u] ^ a[v]);
        Add(v, u, a[u] ^ a[v]);
    }
    Dp(1, 0);
    printf("%d\n", (ans+1) >> 1);
    return 0;
}