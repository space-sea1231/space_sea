#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int M = 1e4 + 10;

int n;
int a[N], b[N];
int f[M], g[M];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) sum += a[i];
    for (int i = 1; i < M; i++) f[i] = g[i] = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = M - 1; j >= b[i]; j--) {
            if (f[j] > f[j - b[i]] + 1 || (f[j] == f[j - b[i]] + 1 && g[j] > g[j - b[i]] + a[i])) {
                f[j] = f[j - b[i]] + 1;
                g[j] = g[j - b[i]] + a[i];
            }
        }
    }
    // for (int i = )
    int ans1 = INF, ans2 = INF;
    for (int i = sum; i < M; i++) {
        if (ans1 > f[i] || (ans1 == f[i] && ans2 > g[i])) {
            ans1 = f[i], ans2 = g[i];
        }
    } 
    printf("%d %d\n", ans1, sum - ans2);
    return 0;
}
/*
f[i]表示选择容器为i的情况下容器中的最小值
*/