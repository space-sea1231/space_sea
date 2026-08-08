#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 60;
const int Mod = 2008;

int n, m;

namespace Linear_Basis {
    ll p[N], q[N];
    int top;

    void Insert(ll x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x & (1LL << i)) {
                if (p[i]) x ^= p[i];
                else {p[i] = x; return;}
            }
        }
        return ;
    }
    ll Query() {
        for (int i = N - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (p[i] & (1LL << j)) p[i] ^= p[j];
            }
            if (p[i]) q[++top] = p[i];
        }
        return 1LL << top;
    }
} using namespace Linear_Basis;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        ll x = 0;
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            x += (ll)(c == 'O') << (n - j);
        }
        Insert(x);
    }
    printf("%lld\n", Query() % Mod);
    return 0;
}