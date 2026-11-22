#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int len;
int a[N];
int val[N];

bool Check(int mid) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) q.push(1);
        else if (a[i] >= mid) q.push(0);
        else q.push(INF);
    }
    while (q.size() >= 3) {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        int z = q.front(); q.pop();
        q.push(min(x + y + z - max(x, max(y, z)), INF));
    }
    return val + len + 1 - lower_bound(val + 1, val + len + 1, mid) >= q.front();
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) a[i] = -1;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> y >> x;
        a[x] = y;
    }
    for (int i = 1; i <= n - m; i++) cin >> val[++len];
    sort(val + 1, val + len + 1);
    int l = 1, r = INF, ans;
    while (l <= r) {
        int mid = l + r >> 1;
        if (Check(mid)) {
            ans = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}