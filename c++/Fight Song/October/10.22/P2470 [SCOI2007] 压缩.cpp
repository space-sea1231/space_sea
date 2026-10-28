#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 51;

string s;
int f[N][N][2];

bool Check(int l, int r) {
    int mid = l + r >> 1;
    for (int i = l; i <= mid; i++) if (s[i] != s[mid + i - l + 1]) return false;
    return true;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s; s = " " + s;
    int len = s.size() - 1;
    for (int i = 1; i <= len; i++) {
        for (int l = 1; l + i - 1 <= len; l++) {
            int r = l + i - 1;
            f[l][r][0] = f[l][r][1] = r - l + 1;
            for (int k = l; k < r; k++) f[l][r][1] = min(f[l][r][1], min(f[l][k][0], f[l][k][1]) + 1 + min(f[k + 1][r][0], f[k + 1][r][1]));
            for (int k = l; k < r; k++) f[l][r][0] = min(f[l][r][0], f[l][k][0] + r - k);
            if (!((r - l + 1) & 1) && Check(l, r)) f[l][r][0] = f[l][l + r >> 1][0] + 1;
        }
    }
    // for (int l = len; l; l--) {
    //     for (int r = l; r <= len; r++) {
    //         f[l][r][0] = f[l][r][1] = r - l + 1;
    //         for (int k = l; k < r; k++) f[l][r][1] = min(f[l][r][1], min(f[l][k][0], f[l][k][1]) + 1 + min(f[k + 1][r][0], f[k + 1][r][1]));
    //         for (int k = l; k < r; k++) f[l][r][0] = min(f[l][r][0], f[l][k][0] + r - k);
    //         if (!((r - l + 1) & 1) && Check(l, r)) f[l][r][0] = f[l][l + r >> 1][0] + 1;
    //     }
    // }
    printf("%d\n", min(f[1][len][0], f[1][len][1]));

    return 0;
}