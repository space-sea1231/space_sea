#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <map>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
int top;
int a[N];
int siz[N], frt[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(frt + 1, frt + top + 1, a[i]) - frt;
        while (pos < top && frt[pos + 1] == a[i]) pos++;
        if (pos > top || frt[pos] != a[i]) {
            top++;
            frt[top] = a[i] + 1;
            siz[top] = 1;
        } else {
            frt[pos]++;
            siz[pos]++;
        }
        #ifdef __Debug
        printf("i=%d, pos=%d, top=%d\n", i, pos, top);
        #endif
    }
    int ans = INF;
    for (int i = 1; i <= top; i++) ans = min(ans, siz[i]);
    printf("%d\n", ans);
    return 0;
}