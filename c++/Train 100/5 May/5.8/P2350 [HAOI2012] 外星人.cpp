#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int T, m;
int f[N];
int prm[N];
bool vis[N];

void Prime() {
    int top = 0;
    f[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prm[++top] = i;
            f[i] = f[i - 1];
        }
        for (int j = 1; j <= top && i * prm[j] < N; j++) {
            vis[i * prm[j]] = true;
            f[i * prm[j]] = f[i] + f[prm[j]];
            if (i % prm[j] == 0) break;
        }
    }
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> T;
    while (T--) {
        cin >> m;
        int ans = 1;
        for (int i = 1; i <= m; i++) {
            int p, q;
            cin >> p >> q;
            if (p == 2) ans--;
            ans += f[p] * q;
        }
        printf("%lld\n", ans);
    }
    return 0;
}