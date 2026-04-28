#include <iostream>
#include <stdio.h>
#include <deque>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e3 + 10;

int n, m, k;
int ap[N], bp[N], as[N], bs[N];
int f[N][N];
deque<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    memset(f, 0xcf, sizeof(f));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= as[i]; j++) f[i][j] = max(f[i][j], -ap[i] * j);
        for (int j = 0; j <= m; j++) f[i][j] = max(f[i][j], f[i - 1][j]);
        if (i <= k) continue;
        q.clear();
        for (int j = 0; j <= m; j++) {
            while (!q.empty() && q.front() < j - as[i]) q.pop_front();
            while (!q.empty() && f[i - k - 1][q.back()] + q.back() * ap[i] < f[i - k - 1][j] + j * ap[i]) q.pop_back();
            q.push_back(j); 
            f[i][j] = max(f[i][j], f[i - k - 1][q.front()] + (q.front() - j) * ap[i]);
        }
        q.clear();
        for (int j = m; j >= 0; j--) {
            while (!q.empty() && q.front() > j + bs[i]) q.pop_front();
            while (!q.empty() && f[i - k - 1][q.back()] + q.back() * bp[i] < f[i - k - 1][j] + j * bp[i]) q.pop_back();
            q.push_back(j); 
            f[i][j] = max(f[i][j], f[i - k - 1][q.front()] + (q.front() - j) * bp[i]);
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) ans = max(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}