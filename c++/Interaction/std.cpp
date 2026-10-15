#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int type, n, m, p;
int f[N][2];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> type >> n >> m >> p;
    f[0][0] = f[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0] + f
    }
    return 0;
}