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
int ans[M], cnt[M];
vector<int> fa[M], siz[M];

int Find(int u, int k) {
	if ((int)fa[u].size() <= k) return u;
	if (fa[u][k] == u) return u;
	return fa[u][k] = Find(fa[u][k], k);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> n >> m;
        for (int i = 1; i <= n; i++) {fa[i].clear(); siz[i].clear();}
		int maxk = -1;
		for (int i = 1; i <= m; i++) {
			int u, v;
			cin >> u >> v;
			int l = 0, r = maxk, k = maxk + 1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (Find(u, mid) == Find(v, mid)) l = mid + 1;
				else {
					r = mid - 1;
					k = mid;
				}
			}
			// cerr<<k<<" ";
			int fu = Find(u, k);
			int fv = Find(v, k);
			// cerr<< fu << " " << fa[u].size() << endl;
			while ((int)siz[fu].size() <= k) {
				siz[fu].emplace_back(1);
				fa[fu].emplace_back(fu);
			}
			while ((int)siz[fv].size() <= k) {
				siz[fv].emplace_back(1);
				fa[fv].emplace_back(fv);
			}
			if (siz[fu][k] < siz[fv][k]) swap(fu, fv);
			fa[fv][k] = fu; siz[fu][k] += siz[fv][k];
			ans[i] = k, cnt[k]++;
            maxk = max(maxk, k);
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