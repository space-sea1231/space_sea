#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

int t;
ll a, b, c;

int Exgcd(int a, int b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int rev = Exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return rev;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--){
        cin >> a >> b >> c;
        ll x, y;
        int gcd = Exgcd(a, b, x, y);
        x *= c / gcd, y *= c / gcd;
        // printf("%d %d   ", x, y);
        if (c % gcd) {printf("-1\n"); continue;}
        ll tmpx = x % (b / gcd) + (b / gcd);
        if (tmpx > (b / gcd)) tmpx %= (b / gcd);
        ll tmpy = y % (a / gcd) + (a / gcd);
        if (tmpy > (a / gcd)) tmpy %= (a / gcd);
        // printf("%d %d   ", tmpx, tmpy);
        if ((c - tmpx * a) / b <= 0) printf("%lld %lld\n", tmpx, tmpy);
        else printf("%lld %lld %lld %lld %lld\n", ((c - tmpy * b) / a - tmpx) / (b / gcd) + 1, tmpx, tmpy, (c - tmpy * b) / a, (c - tmpx * a) / b);
    }
    return 0;
}