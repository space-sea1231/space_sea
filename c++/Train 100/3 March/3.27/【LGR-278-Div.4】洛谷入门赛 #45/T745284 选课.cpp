#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e2 + 10;
int n, m;
int les[N], sum[N], dnf[N], a[N];
int head[N], to[N*N], nxt[N*N];
int cnt, tdnf[N];
bool vis[N], tvis[N];
bool ans[N], OK[N], tOK[N];

void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return; 
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        for (int j = 1; j <= sum[i]; j++) {
            int a;
            cin >> a;
            Add(a, i);
        }
    }
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        bool flag = false;
        for (int j = 1; j <= n; j++) tvis[j] = vis[j], tdnf[j] = dnf[j], ans[j] = false, tOK[j] = OK[j];
        for (int j = 1; j <= k; j++) cin >> les[j];
        for (int j = 1; j <= k; j++) cin >> a[j];
        for (int j = 1; j <= k; j++) {
            if (tvis[les[j]] || tOK[les[j]]) {
                flag = true;
                break;
            }
            if (tdnf[les[j]] != sum[les[j]]) {
                flag = true;
                break;
            }
            if (a[j] >= 60) {
                ans[j] = true;
                tOK[les[j]] = true;
                for (int k = head[les[j]]; k; k = nxt[k]) {
                    int v = to[k];
                    tdnf[v]++;
                }
            }
        }
        if (flag) printf("Error\n");
        else {
            for (int j = 1; j <= n; j++) OK[j] = tOK[j], vis[j] = tvis[j], dnf[j] = tdnf[j];
            for (int j = 1; j <= k; j++) {
                if (ans[j]) printf("P");
                else printf("F");
            }
            printf("\n");
        }
    }
    return 0;
}