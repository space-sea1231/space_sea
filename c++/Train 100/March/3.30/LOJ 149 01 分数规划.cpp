#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const double EPS = 1e-6;
int n, k;
int a[N], b[N];
double c[N];

bool Cmd(double a, double b) {
    return a - b > EPS;
}
bool Check(double mid) {
    for (int i = 1; i <= n; i++) c[i] = a[i] - b[i] * mid;
    sort(c + 1, c + n + 1, Cmd);
    double sum = 0;
    for (int i = 1; i <= k; i++) sum += c[i];
    return sum >= -EPS;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    double l = 0, r = 1;
    while (r - l > EPS) {
        double mid = (l + r) * 0.5;
        if (Check(mid)) l = mid;
        else r = mid;
    }
    printf("%lf", r);
    return 0;
}