#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 400;
const int Mod = 1e9 + 7;

int T, n;
int tot, ans;
int tmp[N];
int l[N], r[N];
int f[N][3];

void Add(int &a, int b) {a = ((ll)a + b < Mod ? a + b : (ll)a + b - Mod);}

int Pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return res;
}
int Calc(int x) {
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (x > l[i]) f[i][0] = ((ll)f[i - 1][0] + f[i - 1][1]) * (min(r[i], x - 1) - l[i] + 1) % Mod;
        else f[i][0] = 0;
        if (x > l[i]) f[i][1] = (ll)f[i - 1][2] * (min(r[i], x - 1) - l[i] + 1) % Mod;
        else f[i][1] = 0;
        if (x <= r[i]) f[i][2] = (ll)f[i - 1][0] * (r[i] - max(l[i], x) + 1) % Mod;
        else f[i][2] = 0;
    }
    return ((ll)tot - f[n][0] - f[n][1] - f[n][2] + (ll)3 * Mod) % Mod;
}
int Query(int x, int y) {
    int res = 0, cur = 0;
    if (y - x + 1 <= n + 2) {
        for (int i = x; i <= y; i++) Add(res, Calc(i));
        return res;
    }
    for (int i = x; i <= x + n + 1; i++) {
        int mul1 = 1, mul2 = 1;
        for (int j = x; j <= x + n + 1; j++) {
            if (i == j) continue;
            mul1 = mul1 * ((ll)y - j + Mod) % Mod;
            mul2 = mul2 * ((ll)i - j + Mod) % Mod;
        }
        Add(cur, Calc(i));
        Add(res, (ll)mul1 * Pow(mul2, Mod - 2) % Mod * cur % Mod);
    }
    return res;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        ans = 0, tot = 1;
        cin >> n;
        for (int i = 1; i <= n; i++) {cin >> l[i]; tmp[i] = l[i];}
        for (int i = 1; i <= n; i++) {cin >> r[i]; tmp[i + n] = r[i];}
        for (int i = 1; i <= n; i++) tot = (ll)tot * (r[i] - l[i] + 1) % Mod;
        sort(tmp + 1, tmp + (n << 1) + 1);
        for (int i = 1; i <= (n << 1); i++) Add(ans, Query(tmp[i - 1] + 1, tmp[i]));
        printf("%d\n", ans);
    }
    return 0;
}