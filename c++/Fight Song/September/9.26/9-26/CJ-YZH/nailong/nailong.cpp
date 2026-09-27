#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n, ed;
int ans;
int a[N], b[N];

void Dfs(int cur, int maxn, int minn, int cnt) {
    if (cur == ed + 1) {
        ans = max(ans, cnt);
        return ;
    }
    if (a[cur] <= minn && b[cur] >= maxn) Dfs(cur + 1, max(maxn, a[cur]), min(minn, b[cur]), cnt + 1);
    else Dfs(cur + 1, maxn, minn, cnt);
}
signed main() {
    freopen("nailong.in", "r", stdin);
    freopen("nailong.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    if (n <= 18) {
        for (ed = 1; ed <= n; ed++) {
            ans = 0;
            Dfs(1, 0, INF, 0);
            printf("%d\n", ans);
        }
    } else {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] <= n && b[i] >= n + 1) ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}