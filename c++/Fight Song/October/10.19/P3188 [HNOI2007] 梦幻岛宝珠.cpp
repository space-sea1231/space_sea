#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define int long long
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int K = 31;

int n, W;
int g[K][N * 50];
int f[K][N * 50];
vector<int> val[K], wei[K];

void Init() {
    for (int i = 0; i < K; i++) val[i].clear(), wei[i].clear();
    for (int i = 0; i < K; i++) {
        for (int j = 0; j <= 1000; j++) {
            f[i][j] = g[i][j] = 0;
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    while (1) {
        Init();
        cin >> n >> W;
        if (n == -1) return 0;
        for (int i = 1; i <= n; i++) {
            int w, v;
            cin >> w >> v;
            int t = 0;
            while (((w >> t) & 1) == false) t++;
            val[t].emplace_back(v);            
            wei[t].emplace_back(w >> t);
        }
        int s = 0;
        while ((W >> s)) s++; s--;
        for (int i = 0; i <= s; i++) {
            for (int l = 0, lim = wei[i].size(); l < lim; l++) {
                for (int j = 1000; j >= wei[i][l]; j--) {
                    g[i][j] = max(g[i][j], g[i][j - wei[i][l]] + val[i][l]);
                    // if (g[i][j]) cerr<<g[i][j] << " " << i  << " " << j << "\n";
                }
            }
        }
        for (int i = 0; i <= s; i++) {
            for (int j = 1000; ~j; j--) {
                for (int p = 0; p <= j; p++) {
                    if (i == 0) f[i][j] = max(f[i][j], g[i][p]);
                    else f[i][j] = max(f[i][j], f[i - 1][(j - p) * 2 + ((W >> (i - 1)) & 1)] + g[i][p]);
                }
                // if (f[i][j]) cerr<<f[i][j] << " " << i << " " << j << "\n";
            }
        }
        printf("%lld\n", f[s][1]);
    }
    return 0;
}