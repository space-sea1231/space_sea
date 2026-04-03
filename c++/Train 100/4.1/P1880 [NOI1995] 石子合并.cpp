#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e2 + 10;
const int INF = 0x3f3f3f3f;

int n;
int a[N], sum[N];
int f[N][N], g[N][N];
int optf[N][N], optg[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = n + 1; i <= (n << 1); i++) {
        a[i] = a[i - n];
        sum[i] = sum[i - 1] + a[i];
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= (n << 1); i++) {
        f[i][i] = 0;
        optf[i][i] = i;
        optg[i][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= (n << 1) - len + 1; l++) {
            int r = l + len - 1;
            for (int k = optf[l][r - 1]; k <= optf[l + 1][r]; k++) {
                int tmp = f[l][k] + f[k + 1][r] + sum[r] - sum[l - 1];
                if (f[l][r] > tmp) {
                    f[l][r] = tmp;
                    optf[l][r] = k;
                }
            }
            for (int k = optg[l][r - 1]; k < optg[l + 1][r]; k++) {
                int tmp = g[l][k] + g[k + 1][r] + sum[r] - sum[l - 1];
                if (g[l][r] < tmp) {
                    g[l][r] = tmp;
                    optg[l][r] = k;
                }
            }
        }
    }
    int ansf = INF, ansg = 0;
    for (int i = 1; i <= n; i++) {
        ansf = min(ansf, f[i][i + n - 1]);
        ansg = max(ansg, g[i][i + n - 1]);
    }
    printf("%d\n%d\n", ansf, ansg);
    return 0;
}
/*
叛徒特务大军阀，反党分子野心家，走资派、投降派、修正主义大恶霸
黑线人物不革命，黑秀才黑手黑帮凶，经验主义民主派，中庸之道变色龙
绊脚石墙头草，老好人小修苗，造谣公司传话筒，逆流邪风小爬虫
*/