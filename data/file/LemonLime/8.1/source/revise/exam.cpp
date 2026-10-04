#include <iostream>
#include <stdio.h>
#include <string.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 8e3 + 10;

int n, m, k;
int bel[N];
int v[N], p[N];
int a[N], b[N];
int f1[N], f2[N];

signed main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        cin >> p[i];
        for (int j = p[i - 1] + 1; j <= p[i]; j++){
            bel[j] = i;
        }
    }
    for (int i = 1; i <= k; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    memset(f1, 0xcf, sizeof(f1));
    f1[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= m; j++){
            f1[j] = max(f1[j], f1[j - a[i]] + b[i]);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (f1[i] <= 0) continue;
        int exp = v[bel[(100 * f1[i] - 1) / i + 1]];
        for (int j = i; j <= m; j++) {
            f2[j] = max(f2[j], f2[j - i] + exp * i);
        }
    }
    printf("%d\n", f2[m]);

    return 0;
}