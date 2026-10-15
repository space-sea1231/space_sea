#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int K = 61;

int T;
ll n, s, x;

signed main() {
    freopen("ardent.in", "r", stdin);
    freopen("ardent.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> s >> x;
        if (n == 2) {
            ll a = 0, b = 0;
            for (int i = K - 1; ~i; i--) {
                if (x & (1LL << i)) {
                    if (a) b += (1LL << i);
                    else a += (1LL << i);
                } else if (a + b + (1LL << (i + 1)) <= s) a += (1LL << i), b += (1LL << i);
            }
            if (a + b == s) printf("%lld\n", a);
            else printf("-1\n");
        } else if (s == x) {
            if (n == 1) printf("%lld\n", s);
            else if (s == 0) printf("0\n");
            else {
                for (int i = K - 1; ~i; i--) {
                    if (x & (1LL << i)) {
                        printf("%lld\n", (1LL << i));
                        break;
                    }
                }
            }
        } 
        // else if (x == 0) {
        //     if (s & 1) printf("-1\n");
        //     else {

        //         printf("")                
        //     }
        // }
    }
    return 0;
}
/*
10101010
01010101
00101011
00101011
00101010
00101010

*/