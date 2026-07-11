#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n, m;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= min(n, m); i++) {
        ans1 += (n - i + 1) * (m - i + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == j) continue;
            ans2 += (n - i + 1) * (m - j + 1);
        }
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}