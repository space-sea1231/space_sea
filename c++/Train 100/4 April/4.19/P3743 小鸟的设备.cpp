#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const double EPS = 1e-6;

int n, m;
ll a[N], b[N];
ll sum;

bool Check(double mid) {
    double sum = m * mid;
    for (int i = 1; i <= n; i++) sum -= max(0.0, a[i] * mid - b[i]);
    return sum > 0;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        sum += a[i];
    }
    if (sum <= m) {
        printf("-1\n");
        return 0; 
    }
    double l = 0, r = 1e10;
    while (r - l > EPS) {
        double mid = (l + r) * 0.5;
        if (Check(mid)) l = mid;
        else r = mid;
    }
    printf("%lf\n", l);
    return 0;
}