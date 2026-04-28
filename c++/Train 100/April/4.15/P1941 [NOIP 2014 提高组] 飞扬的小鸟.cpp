#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e4 + 10;
const int M = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m, o;
int up[N], down[N];
int l[N], r[N];
int cnt[N];
int f[N][M];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> o;
    for (int i = 1; i <= n; i++) cin >> up[i] >> down[i];
    for (int i = 0; i <= n; i++) l[i] = 1, r[i] = m;

    for (int i = 1; i <= o; i++) {
        int p;
        cin >> p >> l[p] >> r[p];
        l[p]++;
        r[p]--;
        cnt[p] = 1;
    }
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];

    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= m; i++) f[0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = up[i] + 1; j <= m; j++) {
            f[i][j] = min(f[i - 1][j - up[i]] + 1, f[i][j - up[i]] + 1);
        }
        f[i][m] = min(f[i][m], f[i - 1][m] + 1);
        if (r[i] == m) {
            for (int j = max(1, m - up[i]); j < m; j++) {
                f[i][m] = min(f[i][m], f[i][j] + 1);
                f[i][m] = min(f[i][m], f[i - 1][j] + 1);
            }
        }
        for (int j = 1; j + down[i] <= m; j++) {
            f[i][j] = min(f[i][j], f[i - 1][j + down[i]]);
        }
        for (int j = 1; j <= m; j++) {
            if (j < l[i] || j > r[i])
            f[i][j] = INF;
        }
        bool ok = false;
        for (int j = 1; j <= m; j++) if (f[i][j] < INF) ok = true;
        if (!ok) {
            cout << "0\n" << cnt[i-1] << endl;
            return 0;
        }
    }
    // for (int i = m; i >= 1; i--) {
    //     for (int j = 1; j <= n; j++) {
    //         if (i < l[j] || i > r[j]) printf("| ");
    //         else printf("%d ", f[j][i] != INF);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 1; i <= n; i++) printf("%d ", up[i]);
    // printf("\n");
    // for (int i = 1; i <= n; i++) printf("%d ", down[i]);
    // printf("\n");
    int ans = INF;
    for (int j = 1; j <= m; j++) ans = min(ans, f[n][j]);
    printf("1\n%d\n", ans);
    return 0;
}