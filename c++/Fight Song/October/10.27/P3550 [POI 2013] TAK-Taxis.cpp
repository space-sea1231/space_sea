#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

ll n, m, d;
ll a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> d >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, [&](ll a, ll b) {
        return a > b;
    });
    ll lst = 0;
    bool flag = false;
    // for (int i = 1; i <= n; i++) if (a[i] >= m - d) printf("%d ", i);
    for (int i = 1; i <= n; i++) {
        if (a[i] <= d - lst) break;
        lst += a[i] - (d - lst);
        if (lst >= d) {
            if (lst >= m) { printf("%d\n", i); return 0; }
            else if (a[i + 1] >= m - d) { printf("%d\n", i + 1); return 0; }
            break;
        }
    }
    int pos = -1;
    for (int i = 1; i <= n; i++) if (a[i] >= m - d) pos = i;
    if (pos == -1) { printf("0\n"); return 0; }
    lst = 0;
    for (int i = 1; i <= n; i++) {
        if (i == pos) continue;
        if (a[i] <= d - lst) break;
        lst += a[i] - (d - lst);
        if (lst >= d) {
            printf("%d\n", i + (lst < m ? 0 : -1));
            return 0;
        }
        if (lst + (a[pos] - (d - lst)) >= m) {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}
/*
You are allowed to be both strong and tired
你可以同时坚强和疲惫
*/