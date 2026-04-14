#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1.1e7 + 10;

string c, s;
int d[N << 1];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> c;
    s = "$#";
    for (char ch:c) {
        s += ch;
        s += "#";
    }
    int n = s.size();
    int l = 0, r = -1, ans = 0;
    for (int i = 1; i <= n; i++) {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
        while (0 <= i - k && k + i < n && s[i - k] == s[i + k]) k++;
        d[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
        ans = max(ans, d[i]);
    }
    #ifdef __Debug
    printf("%s\n", s.c_str());
    #endif
    printf("%d\n", ans - 1);
    return 0;
}