#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 160;

int T, n;
int l[N], r[N];
int a[N];

signed main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> l[i];
        for (int i = 1; i <= n; i++) cin >> r[i];
        int ans = 0;
        for (int i = 1; i <= n - 2; i++) {
            a[1] = l[i], a[2] = l[i + 1], a[3] = l[i + 2];
            sort(a + 1, a + 3 + 1);
            ans = max(ans, a[2]);
        }
        printf("%d\n", ans);
    }
    return 0;
}