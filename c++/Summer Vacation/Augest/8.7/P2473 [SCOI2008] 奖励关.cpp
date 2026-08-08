#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 16;
const int M = 7e4 + 10;
const int K = 1e2 + 10;

int k, n;
double f[K][M];
int val[N], pre[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> k >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        int x;
        while (cin >> x, x) pre[i] |= (1 << (x - 1));
    }
    // for (int i = 1; i <= k; i++) {
    //     for (int j = 0; j < (1 << n); j++) {
    //         for (int l = 1; l <= n; l++) {
    //             if ((1 << (l - 1)) & j && pre[l] & j == pre[l]) {
    //                 f[i][j] = max(f[i][j], f[i][j ^ (1 << (l - 1))] + val[l]);
    //             }
    //         }
    //     }
    // }
    for (int i = k; i; i--) {
        for (int j = (1 << n) - 1; j >= 0; j--) {
            if (i == k && j == (1 << n) - 1) continue;
            for (int l = 1; l <= n; l++) {
                if ((pre[l] & j) == pre[l]) f[i][j] += max(f[i + 1][j], f[i + 1][j | (1 << (l - 1))] + val[l]);
                else f[i][j] += f[i + 1][j];
            }
            f[i][j] /= n;
        }
    }
    printf("%.6lf\n", f[1][0]);
    return 0;
}