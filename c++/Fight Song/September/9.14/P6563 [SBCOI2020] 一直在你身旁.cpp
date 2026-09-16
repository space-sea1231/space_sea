#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
// typedef long long ll;

const int INF = 1e18 + 1;
const int N = 7110;

int T;
int n;
int a[N];
int f[N][N], q[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        // for (int l = 1; l <= n; l++) {
        //     for (int r = l; r <= n; r++) {
        //         f[l][r] = 0;
        //     }
        // }
        for (int r = 2; r <= n; r++) {
            int p = r;
            int ll = 1, rr = 2;
            q[1] = r;
            for (int l = r; l; l--) {
                if (l == r) {f[l][r] = 0; continue;}
                if (r - l == 1) {f[l][r] = a[l]; continue;}
                
                while (p > l && f[l][p - 1] > f[p][r]) p--;
                f[l][r] = f[l][p] + a[p];

                while (ll < rr && q[ll] >= p) ll++;
                if (ll < rr) f[l][r] = min(f[l][r], f[q[ll] + 1][r] + a[q[ll]]);
                while(ll < rr && f[q[rr - 1] + 1][r] + a[q[rr - 1]] >= f[l + 1][r] + a[l]) rr--;
                q[rr++] = l;
            } 
        }
        printf("%lld\n", f[1][n]);
    }
    return 0;
}