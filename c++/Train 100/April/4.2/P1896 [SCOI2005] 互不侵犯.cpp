#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 10;
const int M = 2e3 + 10;

int n, m;
int num;
int sit[M], sta[M];
ll f[N][M][N * N];

void Dfs(int x, int cnt, int cur) {
    if (cur >= n) {
        sit[++num] = x;
        sta[num] = cnt;
        return; 
    }
    Dfs(x, cnt, cur + 1);
    Dfs(x + (1 << cur), cnt + 1, cur + 2);
    return;
}
bool Check(int x, int y) {
    if (x & y) return false;
    if ((x << 1) & y) return false;
    if (x & (y << 1)) return false;
    return true;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    Dfs(0, 0, 0);
    for (int i = 1; i <= num; i++) f[1][i][sta[i]] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= num; j++) {
            for (int k = 1; k <= num; k++) {
                if (Check(sit[j], sit[k])) {
                    for (int l = sta[k]; l <= m; l++) f[i][k][l] += f[i - 1][j][l - sta[k]];
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= num; i++) ans += f[n][i][m];
    printf("%lld\n", ans);
    return 0;
}