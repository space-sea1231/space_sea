#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

string c, s;
int d[N << 1];
int l[N << 1], r[N << 1];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> c;
    s = "$#";
    for (char ch:c) {
        s += ch;
        s += "#";
    }
    int n = s.size();
    int lpos = 0, rpos = -1;
    for (int i = 1; i <= n; i++) {
        int k = (i > rpos) ? 1 : min(d[lpos + rpos - i], rpos - i + 1);
        while (0 <= i - k && k + i < n && s[i - k] == s[i + k]) k++;
        d[i] = k--;
        if (i + k > rpos) {
            lpos = i - k;
            rpos = i + k;
        }
    }
    int now = 1;
    for (int i = 1; i <= n; i++) while (now <= i + d[i] - 1 && d[i] != 1) l[now++] = i;
    now = n;
    for (int i = n; i >= 1; i--) while (now >= i - d[i] + 1 && d[i] != 1) r[now--] = i;
    int ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d\n", l[i], r[i]);
    // }
    for (int i = 1; i < n; i++) ans = max(ans, r[i] - l[i]);
    printf("%d\n", ans);
    return 0;
}
/*
x, y
x + f[x] = y - f[y] + 1
f[x]+f[y]
$#a#b#a#
01234567
*/