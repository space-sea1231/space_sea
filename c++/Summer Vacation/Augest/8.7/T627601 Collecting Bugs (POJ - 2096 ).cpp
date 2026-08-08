#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;

int n, s;
double f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> s;
    for (int i = n; i >= 0; i--) {
        for (int j = s; j >= 0; j--) {
            if (i == n && j == s) continue;
            f[i][j] = (f[i][j + 1] * i * (s - j) + f[i + 1][j] * (n - i) * j +
                       f[i + 1][j + 1] * (n - i) * (s - j) + n * s) /
                       (n * s - i * j); 
        }
    }
    printf("%.4lf\n", f[0][0]);
    return 0;
}