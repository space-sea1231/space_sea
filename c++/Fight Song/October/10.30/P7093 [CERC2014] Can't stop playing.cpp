#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;
const int K = 13;

int T;
int n;
int a[N];
bool f[N][(1 << K) + 1];
pair<pair<int, int>, bool> g[N][(1 << K) + 1];

int Lowbit(int x) { return x & -x; }
int Hbit(int x) { x|=x>>1,x|=x>>2,x|=x>>4,x|=x>>8,x|=x>>16;return x-(x>>1); }

void Dfs(int dep, int sum) {
    if (!dep) return ;
    Dfs(g[dep][sum].first.first, g[dep][sum].first.second);
    printf("%c", g[dep][sum].second ? 'r' : 'l');
}
void Solve() {
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (__builtin_popcount(sum) != 1) { printf("no\n"); return; }
    f[0][0] = 1; sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum + a[i]; j++) {
            f[i][j] = 0;
            g[i][j] = make_pair(make_pair(-1, -1), false);
        }
        for (int j = 0; j <= sum; j++) {
            int l = j, r = sum - j;
            int low_l = Lowbit(l);
            int low_r = Lowbit(r);
            if (low_l >= a[i] || !l) {
                if (f[i - 1][l]) {
                    f[i][l + a[i]] = true;
                    g[i][l + a[i]] = make_pair(make_pair(i - 1, l), false);
                }
            }
            int d = (Hbit(l) <= Hbit(r + a[i]) ? 1 : 0) * Hbit(r + a[i]);
            if (low_r >= a[i] || !r) {
                if (f[i - 1][l]) {
                    f[i][l + d] = true;
                    g[i][l + d] = make_pair(make_pair(i - 1, l), true);
                }
            }
        }
        sum += a[i];
    }
    if (f[n][sum]) Dfs(n, sum);
    else printf("no");
    printf("\n");
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) Solve();
    return 0;
}