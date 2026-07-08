#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e3 + 10;
const int Mod = 998244353;

int n;
int a[N];
int f[N] = {1};

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 5001; j > a[i]; j--) ans = (ans + f[j]) % Mod;
        for (int j = 5001; j >= 5001 - a[i]; j--) f[5001] = (f[5001] + f[j]) % Mod;
        for (int j = 5000; j >= a[i]; j--) f[j] = (f[j] + f[j - a[i]]) % Mod;
    }
    printf("%d\n", ans);
    return 0;
}