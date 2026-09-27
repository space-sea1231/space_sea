#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e5 + 10;

int T;
ll n, k;
int ans[N];
bool vis[N];
bool flag;

void Dfs(int cur, int minn, int maxn, int sum) {
    if (cur == n + 1) {
        if (sum == k) {
            // int maxn = 0, minn = INF;
            // for (int i = 1; i <= n; i++) {
            //     maxn = max(maxn, ans[i]);
            //     minn = min(minn, ans[i]);
            //     printf("%d ", maxn - minn);
            // }
            // printf("-> ");
            for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
            printf("\n");
            flag = true;
        }
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            ans[cur] = i;
            Dfs(cur + 1, min(minn, i), max(maxn, i), sum + max(maxn, i) - min(minn, i));
            vis[i] = false;
            if (flag) return ;
        }
    }
}
void Dfs1(int cur, int minn, int maxn, int sum) {
    if (cur == n + 1) {
        if (sum == k) {
            // int maxn = 0, minn = INF;
            // for (int i = 1; i <= n; i++) {
            //     maxn = max(maxn, ans[i]);
            //     minn = min(minn, ans[i]);
            //     printf("%d ", maxn - minn);
            // }
            // printf("-> ");
            for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
            printf("\n");
            flag = true;
        }
        return ;
    }
    for (int i = n; i; i--) {
        if (!vis[i]) {
            vis[i] = true;
            ans[cur] = i;
            Dfs1(cur + 1, min(minn, i), max(maxn, i), sum + max(maxn, i) - min(minn, i));
            vis[i] = false;
            if (flag) return ;
        }
    }
}
int a[N], b[N];
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    int ttt, gg = T;
    bool flag = true;
    while (T--) {
        cin >> n >> k;
        int tmp;
        cin >> tmp;
        if (tmp == -1) continue;
        int maxn = tmp, minn = tmp;
        ll sum1 = 0, sum2 = 0;
        for (int i = 2; i <= n; i++) {
            cin >> tmp;
            maxn = max(maxn, tmp);
            minn = min(minn, tmp);
            sum1 += maxn - minn;
        }
        cin >> tmp;
        maxn = tmp, minn = tmp;
        for (int i = 2; i <= n; i++) {
            cin >> tmp;
            maxn = max(maxn, tmp);
            minn = min(minn, tmp);
            sum2 += maxn - minn;
        }
        if (sum1 != k || sum2 != k) flag = false, ttt = gg - T;
    }
    if (flag) printf("ok\n");
    else printf("%d\n", ttt);
    return 0;
}
/*
4 4 = 0
2 4 = 2
1 4 = 3
1 4 = 3
1 5 = 4
*/