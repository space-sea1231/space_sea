#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;
const int M = 1e3 + 10;
const double EPS = 1e-7;

int k, q;
double f[N][M]; // f[i][j]表示第i天有j个宝珠

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> k >> q;
    f[1][1] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1, lim = min(i, k); j <= lim; j++) {
            if (i == 1 && j == 1) continue;
            f[i][j] = f[i - 1][j] * ((double)j / k) +
                      f[i - 1][j - 1] * (1 - (double)(j - 1) / k);

        }
    }
    for (int i = 1; i <= q; i++) {
        int p;
        cin >> p;
        int l = 1, r = N - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f[mid][k] * 2000 > p - EPS) r = mid - 1;
            else l = mid + 1;
        }
        printf("%d\n", r + 1);
    }
    return 0;
}