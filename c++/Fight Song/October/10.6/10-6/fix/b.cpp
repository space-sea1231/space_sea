#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 40;
const int M = 1e3 + 10;

int n, m;
int a[M], b[M];
int sta[N];
bool ans[N];

void Dfs(int cur) {
    if (cur == m + 1) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) cnt += (sta[i] == 1);
        for (int i = 1; i <= n; i++) {
            int tot = 0;
            for (int j = i; j <= n; j++) {
                if (sta[j] == 0) break;
                if ((tot += (sta[j] == 1)) == cnt) ans[j - i + 1] ^= 1;
            }
        }
        return ;
    }
    int x = a[cur], y = b[cur];
    if (sta[x] == -1 && sta[y] == -1) {
        sta[x] = sta[y] = 1;
        Dfs(cur + 1);
        sta[x] = sta[y] = 0;
        Dfs(cur + 1);
        sta[x] = sta[y] = -1;
    } else if (sta[x] == -1 || sta[y] == -1) {
        if (sta[x] == 0 || sta[y] == 1) Dfs(cur + 1);
        else if (sta[x] == 1) {
            sta[x] = -1, sta[y] = 1;
            Dfs(cur + 1);
            sta[x] = 1, sta[y] = -1;
        }
        else if (sta[y] == 0) {
            sta[x] = 0, sta[y] = -1;
            Dfs(cur + 1);
            sta[x] = -1, sta[y] = 0;
        }
    } else {
        if (sta[x] == 1 && sta[y] == 0) {
            sta[x] = 0, sta[y] = 1;
            Dfs(cur + 1);
            sta[x] = 1, sta[y] = 0;
        } else Dfs(cur + 1);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) sta[i] = -1;
    Dfs(1);
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}