#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const double EPS = 1e-4;

int n, m, k;

bool Check(double mid) {
    double sum = n;
    for (int i = 1; i <= k; i++) sum -= m - sum * mid;
    return sum > 0;
}

signed main() {
    // cin.tie(nullptr) -> ios::sync_with_stdio(false);
    
    cin >> n >> m >> k;
    double l = 0, r = 300;
    while (r - l > EPS) {
        double mid = (l + r) * 0.5;
        if (Check(mid)) r = mid;
        else l = mid;
    }
    printf("%.1lf\n", l*100);
    return 0;
}