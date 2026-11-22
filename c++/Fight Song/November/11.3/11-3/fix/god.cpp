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
const int N = 1e6 + 10;
const int Mod = 998244353;

int n;
int top, ans;
int a[N], f[N], t[N];
int pw[N];
int pos[N], stk[N], now[N];
int rt[N], lt[N];

int read() {
    char c = getchar();
    int flag = 1;
    while (c < '0' || c > '9') {
        if (c == '-') flag = -1;
        c = getchar();
    }
    int sum = 0;
    while ('0' <= c && c <= '9') {
        sum = (sum << 3) + (sum << 1) + (c ^ 48);
        c = getchar();
    }
    return sum * flag;
}
int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = sum * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return sum;
}

int Calc(int st, int d, int l, int r) {
    st = st * Pow(d, l) % Mod;
    if (d == 1) return st * (r - l + 1) % Mod;
    return st * (Pow(d, r - l + 1) - 1) % Mod * Pow(d - 1, Mod - 2) % Mod;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    n = read();
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = pw[i - 1] * 2 % Mod;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        pos[a[i]] = i;
    }
    stk[top = 0] = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[stk[top]] < a[i]) top--;
        lt[i] = stk[top]; stk[++top] = i;
    }
    stk[top = 0] = n + 1;
    for (int i = n; i; i--) {
        while (top && a[stk[top]] < a[i]) top--;
        rt[i] = stk[top]; stk[++top] = i;
    }
    for (int i = 1; i <= n + 1; i++) t[i] = n;
    f[n + 1] = 1, now[n + 1] = 0, a[n + 1] = INF;
    for (int i = n; i; i--) {
        int x = pos[i], j = rt[x];
        if (t[j] != i) ans = (ans + Calc(f[j] * Pow(2, (n - (j - now[j] - 1)) * t[j] - 1) % Mod, pw[j - now[j] + 1], i + 1, t[j] - 1)) % Mod;
        f[j] = f[j] * Pow(pw[n - (j - now[j] - 1)], t[j] - i) % Mod;
        f[x] = f[j];
        now[x] = now[rt[x]], now[rt[x]] = x;
        t[x] = t[j] = i;
    }
    for (int i = 1; i <= n + 1; i++) {
        ans = (ans + Calc(f[i] * Pow(2, (n - (i - now[i] - 1)) * t[i] - 1) % Mod, pw[i - now[i] + 1], 1, t[i] - 1)) % Mod;
        f[i] = f[i] * Pow(pw[n - (i - now[i] - 1)], t[i]) % Mod;
        ans = (ans + f[i]) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}

/*
anew 新奇

Teach me the wonder of seeing things anew.
教我怀着新奇重新看世界

《青春修炼手册》
*/