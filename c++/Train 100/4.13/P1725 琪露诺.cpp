#include <iostream>
#include <stdio.h>
#include <cstring>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, l, r;
int head, back = 1;     
int que[N];
int a[N], f[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> l >> r;
    int len = r - l;
    for (int i = 0; i <= n; i++) cin >> a[i];
    memset(f, -0x3f, sizeof(f));
    f[0] = 0;
    for (int i = l; i <= n; i++) {
        while (back <= head && f[que[head]] < f[i - l]) head--;
        que[++head] = i - l;
        while (back <= head && que[back] < i - r) back++;
        f[i] = f[que[back]] + a[i];
        #ifdef __Debug
        printf("Debug:f[%d] = %d\n", i, f[i]);
        #endif
    }
    int ans = -INF;
    for (int i = n - r + 1; i <= n; i++) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}