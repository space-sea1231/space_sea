#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = 1e8;
const int M = 45;
const int N = 1e5 + 10;

int n;
int num[M][M];
int f[M][N];
string s;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s >> n;
    int siz = s.size(); s = " " + s;
    for (int i = 1; i <= siz; i++) {
        for (int j = 1; j <= siz; j++) {
            num[i][j] = INF;
        }
        num[i][i] = s[i] - '0';
    }
    for (int k = 2; k <= siz; k++) {
        for (int i = 1; i + k - 1 <= siz; i++) {
            int j = i + k - 1;
            if (num[i][j - 1] == INF) continue;
            num[i][j] = num[i][j - 1] * 10 + (s[j] ^ 48);
            if (num[i][j] > n) num[i][j] = INF;
            // printf("num[%d][%d]=%d\n", i, j, num[i][j]);
        }
    }
    for (int i = 0; i <= siz; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = INF;
        }
    }
    f[0][0] = 0;
    // cerr<<siz<<endl;
    for (int i = 1; i <= siz; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 1; k <= siz && i - k + 1 >= 1; k++) {
                if (num[i - k + 1][i] == INF || j - num[i - k + 1][i] < 0) continue;
                f[i][j] = min(f[i][j], f[i - k][j - num[i - k + 1][i]] + 1);
                // cerr<<i - k + 1 << " " << j - num[i - k + 1][i] << endl;
                // if (i == 40 && j == 99999 && f[i][j] == 8) printf("%d %d\n", i - k + 1, j - num[i - k + 1][i]);
            }
        }
    }
    // cerr<<f[5][3] << endl;
    // cerr<<num[6][10] << endl;
    printf("%d\n", f[siz][n] == INF ? -1 : f[siz][n] - 1);
    return 0;
}