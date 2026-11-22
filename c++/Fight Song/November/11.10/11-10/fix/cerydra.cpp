#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define int long long 
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;
const int Mod = 1e9 + 7;

int T;
int n;
int top;
int pw[N], inv[N];
int stk[N], rgt[N], siz[N], a[N];

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
void Solve() {
    top = 0;
    cin >> n;
    bool flag = true;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (top && rgt[stk[top]] == i - 1) top--;
        int l = top ? stk[top] + 1 : 1;
        int llen = i - l + 1;
        if (a[i] % llen) { flag = false; break; }
        int r = i + (a[i] / llen) - 1;
        if (a[i] / llen < 1 || r > n) { flag = false; break; }
        if (top && r > rgt[stk[top]]) { flag = false; break; }
        rgt[i] = r; siz[i] = r - l + 1;
        // cerr << i << " " << l << " " << r << "\n";
        stk[++top] = i;
    }
    if (flag) {
        int ans = pw[n];
        for (int i = 1; i <= n; i++) ans = (ll)ans * inv[siz[i]] % Mod;
        // for (int i = 1; i <= n; i++) cerr << siz[i] << "\n";
        printf("%lld\n", ans);
    } else printf("0\n");
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * i % Mod;
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = ((ll)-(Mod / i) * inv[Mod % i] % Mod + Mod) % Mod;
    // cerr << 
    cin >> T;
    while (T--) Solve();
    return 0;
}