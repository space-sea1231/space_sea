#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int Mod = 1e9 + 7;

ll n, p;
ll x[N], y[N];

signed main() {
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> p;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        if (x[i] != y[i]) flag = false;
    }
    if (flag) {
        return 0;
    }
    printf("%lld\n", (n + 1) * (n + 2) / 2 % Mod);
    return 0;
}