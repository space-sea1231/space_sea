#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const double Eps = 1e-7;

int n;
double a[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        int cur = i;
        for (int j = i + 1; j <= n; j++) {
            if (fabs(a[cur][i]) < fabs(a[j][i])) {
                cur = j;
            }
        }
        if (fabs(a[cur][i]) < Eps) { printf("No Solution\n"); return 0; }
        swap(a[cur], a[i]);
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double b = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; k++) a[j][k] -= b * a[i][k];
        }
    }
    for (int i = 1; i <= n; i++) printf("%.2lf\n", round(a[i][n + 1] / a[i][i] * 100) / 100);
    return 0;
}