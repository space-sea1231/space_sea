#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int M = 3e5 + 10;

int t;
int n, m;
int ans[N], cnt[N];
vector<int> fa[N], siz[N];

int Find(int u, int k) {
    // cerr<<1;
    if (k >= (int)fa[u].size()) return u;
    if (fa[u][k] == u) return u;
    return fa[u][k] = Find(fa[u][k], k);
    
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        // memset(ans, 0, sizeof(ans));
        // memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) {fa[i].clear(); siz[i].clear();}
        int maxk = -1;
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            int l = 0, r = maxk, level = maxk + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                // cerr<<mid;
                if (Find(u, mid) == Find(v, mid)) l = mid + 1;
                else {
                    r = mid - 1;
                    level = mid;
                }
            }
            int fu = Find(u, level);
            int fv = Find(v, level);
            while ((int)fa[fu].size() <= level) {
                fa[fu].emplace_back(fu);
                siz[fu].emplace_back(1);
            }
            while ((int)fa[fv].size() <= level) {
                fa[fv].emplace_back(fv);
                siz[fv].emplace_back(1);
            }
            if (siz[fu][level] < siz[fv][level]) swap(fu, fv);
            fa[fv][level] = fu, siz[fu][level] += siz[fv][level];
            ans[i] = level; cnt[level]++;
            maxk = max(maxk, level);
        }
        int max_cnt = -1;
        while (cnt[max_cnt + 1] == n - 1) max_cnt++;
        for (int i = 1; i <= m; i++) {
            if (ans[i] > max_cnt) printf("-1 ");
            else printf("%d ", ans[i] + 1);
        }
        printf("\n");
        for (int i = 0; i <= maxk + 1; i++) cnt[i] = 0;
    }
    return 0;
}