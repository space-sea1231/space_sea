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

int w, b;
double f[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> w >> b;
    for (int i = 1; i <= w; i++) f[i][0] = 1;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= b; j++) {
            f[i][j] += (double)i / (i + j);
            if (j >= 3) f[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * (j - 2) / (i + j - 2) * f[i][j - 3];
            if (i >= 1 && j >= 2) f[i][j] += (double)j / (i + j) * (j - 1) / (i + j - 1) * i / (i + j - 2) * f[i - 1][j - 2];
        }
    }
    printf("%.9lf", f[w][b]);
    return 0;
}