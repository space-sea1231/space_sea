#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;
const int K = 32;

int n;
int a[N];

namespace Linear_Basis {
    int p[K];

    bool Insert(int x) {
        for (int i = K - 1; ~i; i--) {
            if (x & (1 << i)) {
                if (p[i]) x ^= p[i];
                else {p[i] = x; return true;}
            }
        }
        return false;
    }
} using namespace Linear_Basis;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, [&](int a, int b){
        return a > b;
    });
    ll ans = 0;
    for (int i = 1; i <= n; i++) if (!Insert(a[i])) ans += a[i];
    printf("%lld\n", ans);
    return 0;
}