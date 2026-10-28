#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <bitset>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e3 + 10;

int n;
ll a[N];
bitset<N> bs[N];

ll Gcd(ll a, ll b) {
    while (b ^= a ^= b ^= a %= b);
    return a;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (Gcd(a[i], a[j]) == 1) {
                bs[i][j] = bs[j][i] = true;
                // cerr<<i << " " << j << "\n";
            }
        }
    }
    bitset<N> tmp;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            tmp = bs[i] & bs[j];
            int cnt = tmp.count();
            ans += (ll)cnt * (cnt - 1) / 2;
        }
    }
    printf("%lld\n", ans * 4);
    return 0;
}
/*
The wind reads every leaf before it falls
风在每片叶子落下前，都读过它

粪塔，委托，滑梯，分别...还有什么？
*/