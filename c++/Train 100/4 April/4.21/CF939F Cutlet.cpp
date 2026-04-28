#include <iostream>
#include <stdio.h>
#include <cstring>
#include <deque>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int K = 1e2 + 10;
const int INF = 0x3f3f3f3f;

int n, k;
int l[K], r[K];
int f[2][N << 1];
deque<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> l[i] >> r[i];
    int now = 1, last = 0;
    for (int i = 1; i <= n; i++) f[0][i] = INF;
    for (int i = 1; i <= k; i++) {
        q.clear();
        for (int j = 0; j <= n; j++) f[now][j] = f[last][j];
        for (int j = r[i]; j >= 0; j--) {
            while (!q.empty() && f[last][q.back()] >= f[last][r[i] - j]) q.pop_back();
            q.push_back(r[i] - j);
            while (!q.empty() && q.front() < l[i] - j) q.pop_front();
            f[now][j] = min(f[now][j], f[last][q.front()] + 1);
        }
        q.clear();
        for (int j = 0, lim = min(n, r[i]); j <= lim; j++) {
            while (!q.empty() && f[last][q.back()] >= f[last][j]) q.pop_back();
            q.push_back(j);
            while (!q.empty() && q.front() < j - (r[i] - l[i])) q.pop_front();
            f[now][j] = min(f[now][j], f[last][q.front()] + 2);
        }
        now = now ^ 1;
        last = last ^ 1;
    }
    if (f[last][n] == INF) printf("Hungry\n");
    else printf("Full\n%d\n", f[last][n]);
    return 0;
}