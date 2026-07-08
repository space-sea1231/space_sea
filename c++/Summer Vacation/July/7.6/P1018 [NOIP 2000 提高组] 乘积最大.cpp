#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;
typedef __int128_t i128;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 50;

int n, m;
int c[N << 1];
string s, rev;
string f[N][N];

string Mul(string a, string b) {
    rev.clear();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    // printf("gg:%s %s\n", a.c_str(), b.c_str());
    int lena = a.size(), lenb = b.size();
    int x = 0, lenc = lena + lenb - 1;
    for (int i = 1; i <= lenc; i++) c[i] = 0;
    for (int i = 0; i < lena; i++) {
        for (int j = 0; j < lenb; j++) {
            c[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            // if (i + j + 1 == 1) cerr<<(a[i] - '0') * (b[j] - '0') << " "<< c[i + j + 1] << endl;
        }
    }
    for (int i = 1; i <= lenc; i++) {
        c[i] += x;
        x = c[i] / 10;
        c[i] %= 10;
    }
    while (x) {
        c[++lenc] = x % 10;
        x /= 10;
    }
    while (c[lenc] == 0 && lenc > 1) lenc--;
    for (int i = lenc; i >= 1; i--) rev += c[i] + '0';
    // printf("%s %d %d\n", rev.c_str(), c[1], lenc);
    return rev;
}
string Max(string a, string b) {
    int lena = a.size(), lenb = b.size();
    if (lena > lenb) return a;
    if (lena < lenb) return b;
    for (int i = 0; i < lena; i++) {
        if (a[i] > b[i]) return a;
        if (a[i] < b[i]) return b;
    }
    return a;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    s = " " + s;
    for (int i = 1; i <= n; i++) f[i][0] = s.substr(1, i);
    for (int i = 1; i <= n; i++) {
        for (int k = 1, lim = min(i - 1, m); k <= lim; k++) {
            for (int j = k - 1; j < i; j++) {
                // printf("Debug%d~%d: %s\n", j + 1, i, s.substr(j + 1, i - j).c_str());
                f[i][k] = Max(f[i][k], Mul(f[j][k - 1], s.substr(j + 1, i - j)));
                // printf("f[%d][%d]=%s\n", j, k - 1, f[j][k - 1].c_str());
            }
        }
    }
    printf("%s\n", f[n][m].c_str());
    return 0;
}
/*
1 2 3 4
4

4 3 2 1
4
*/