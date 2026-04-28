#include <iostream>
#include <stdio.h>
#include <cmath> 
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e2 + 10;
const int M = 1e3 + 10;
const double EPS = 1e-6;
int n, m;
int w[N], v[N];
double f[M];
double ans;

bool Check(double mid) {
    for (int i = 1; i <= m; i++) f[i] = -1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            int k = min(m, j + w[i]);
            f[k] = max(f[k], f[j] + v[i] - mid * w[i]);
        }
    }
    ans = max(ans, f[m]);
    return f[m] >= 0;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    double l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        r = max(r, (double)v[i] / w[i]);
    }
    while (r - l > EPS) {
        double mid = (l + r) * 0.5;
        if (Check(mid)) l = mid;
        else r = mid;
    }
    printf("%lld\n", (ll)floor(l * 1000));
    return 0;
}