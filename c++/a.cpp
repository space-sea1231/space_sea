#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m, s, g;
int x[N], h[N];
int l[N], r[N], y[N];
int tmp[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> h[i];
        tmp[i] = x[i];
    }
    for (int i = 1; i <= m; i++) cin >> l[i] >> r[i] >> y[i];
    cin >> s >> g;
    
    sort(tmp + 1, tmp + n + 1);
    for (int i = 1; i <= m; i++) {
        int lpos = lower_bound(tmp + 1, tmp + n + 1, l[i]) - tmp;
        int rpos = lower_bound(tmp + 1, tmp + n + 1, r[i]) - tmp - 1;
        
    }
    return 0;
}