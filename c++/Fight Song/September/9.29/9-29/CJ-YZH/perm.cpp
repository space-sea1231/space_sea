#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;
const int N = 510;

int n;
int a[N], b[N], c[N];

namespace Pts1 {
    bool vis[20];
    int num[20];
    int ccc, ans;

    void Calc() {
        int cnta = 0, cntb = 0, cntc = 0;
        int maxa = 0, maxb = 0;
        for (int i = 1; i <= ccc; i++) {
            if (maxa < num[i]) {
                maxa = num[i];
                cnta++;
            }
            if (num[i] < num[i + 1]) cntc++;
        }
        for (int i = ccc; i; i--) {
            if (maxb < num[i]) {
                maxb = num[i];
                cntb++;
            }
        }
        // cerr<<cnta << " " << cntb << " " << cntc << endl;
        ans = (ans + (a[cnta] * b[cntb] % Mod * c[cntc] % Mod)) % Mod;
        // for (int i = 1; i <= ccc; i++) printf("%d ", num[i]);
        // printf("\n");
    }
    void Dfs(int cur) {
        if (cur == ccc + 1) {
            Calc();
            return ;
        }
        for (int i = 1; i <= ccc; i++) {
            if (!vis[i]) {
                vis[i] = true;
                num[cur] = i;
                Dfs(cur + 1);
                vis[i] = false;
            }
        }
    }
}
signed main() {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    if (n <= 10) {
        using namespace Pts1;
        for (ccc = 1; ccc <= n; ccc++) {
            ans = 0; Dfs(1);
            printf("%d ", ans);
        }
    }
    return 0;
}
/*
1 2 3 4 5
*/