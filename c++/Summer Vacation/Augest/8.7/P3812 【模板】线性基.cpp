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

int n;

namespace Linear_Basis {
    ll p[N];

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
        ll rev = 0;
        for (int i = N - 1; i >= 0; i--) if ((rev & (1LL << i)) == 0) rev ^= p[i];
        return rev;
    }
} using namespace Linear_Basis;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        Insert(x);
    }
    printf("%lld\n", Query());
    return 0;
}