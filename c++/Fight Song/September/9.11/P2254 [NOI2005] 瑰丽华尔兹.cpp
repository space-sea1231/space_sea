#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
// #define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e2 + 10;
const int T = 4e4 + 10;

int n, m, sx, sy, K;
bool a[N][N];
int f[N][N][2];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> sx >> sy >> K;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = (c == 'x');
            f[i][j][0] = f[i][j][1] = -INF;   
        }
    }
    // #ifdef __Debug
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         printf("%d ", a[i][j]);
    //     }
    //     printf("\n");
    // }
    // #endif
    bool flag = false;
    f[sx][sy][flag ^ 1] = 0;
    for (int k = 1; k <= K; k++) {
        int s, t, d;
        cin >> s >> t >> d;
        // cerr<<s << " " << t << " " << d << "\n";
        int del = t - s + 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                f[i][j][flag] = f[i][j][flag ^ 1];
            }
        }
        if (d == 1) {
            deque<int> q;
            for (int j = 1; j <= m; j++) {
                q.clear();
                for (int i = n - 1; i; i--) {
                    if (a[i + 1][j]) q.clear();
                    if (a[i + 1][j] || a[i][j]) continue;
                    while (!q.empty() && q.front() > i + del) q.pop_front();
                    while (!q.empty() && f[q.back()][j][flag ^ 1] + q.back() - i <= f[i + 1][j][flag ^ 1] + 1) q.pop_back();
                    q.push_back(i + 1);
                    // if (j == 3) cerr<<j << " " << q.front() << "\n";
                    // if (j == 3) cerr<<f[4][3][flag^1]<<"\n";
                    f[i][j][flag] = max(f[i][j][flag ^ 1], f[q.front()][j][flag ^ 1] + q.front() - i);
                }
            }
        }
        if (d == 2) {
            deque<int> q;
            for (int j = 1; j <= m; j++) {
                q.clear();
                for (int i = 2; i <= n; i++) {
                    if (a[i - 1][j]) q.clear();
                    if (a[i - 1][j] || a[i][j]) continue;
                    while (!q.empty() && q.front() < i - del) q.pop_front();
                    while (!q.empty() && f[q.back()][j][flag ^ 1] + i - q.back()<= f[i - 1][j][flag ^ 1] + 1) q.pop_back();
                    q.push_back(i - 1);
                    f[i][j][flag] = max(f[i][j][flag ^ 1], f[q.front()][j][flag ^ 1] + i - q.front());
                }
            }
        }
        if (d == 3) {
            deque<int> q;
            for (int i = 1; i <= n; i++) {
                q.clear();
                for (int j = m - 1; j; j--) {
                    if (a[i][j + 1]) q.clear();
                    if (a[i][j + 1] || a[i][j]) continue;
                    while (!q.empty() && q.front() > j + del) q.pop_front();
                    while (!q.empty() && f[i][q.back()][flag ^ 1] + q.back() - j <= f[i][j + 1][flag ^ 1] + 1) q.pop_back();
                    q.push_back(j + 1);
                    f[i][j][flag] = max(f[i][j][flag ^ 1], f[i][q.front()][flag ^ 1] + q.front() - j);
                }
            }
        }
        if (d == 4) {
            deque<int> q;
            for (int i = 1; i <= n; i++) {
                q.clear();
                for (int j = 2; j <= m; j++) {
                    if (a[i][j - 1]) q.clear();
                    if (a[i][j - 1] || a[i][j]) continue;
                    while (!q.empty() && q.front() < j - del) q.pop_front();
                    while (!q.empty() && f[i][q.back()][flag ^ 1] + j - q.back() <= f[i][j - 1][flag ^ 1] + 1) q.pop_back();
                    q.push_back(j - 1);
                    f[i][j][flag] = max(f[i][j][flag ^ 1], f[i][q.front()][flag ^ 1] + j - q.front());
                }
            }
        }
        flag ^= 1;
    }
    // #ifdef __Debug
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         printf("%d ", f[i][j][flag ^ 1]);
    //     }
    //     printf("\n");
    // }
    // #endif
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = max(ans, f[i][j][flag ^ 1]);
        }
    }
    printf("%d\n", ans);
    return 0;
}