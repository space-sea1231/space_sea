#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;
typedef __int128 i128;

const int N = 1e5 + 10;

int n;

int Exgcd(int a, int b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = Exgcd(b, a % b, x, y);
    i128 z = x; x = y; y = z - y * (a / b);
    return d;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    i128 acc = 1, ans = 0;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        i128 x, y;
        int d = Exgcd(acc, a, x, y);
        x *= (b - ans) / d;
        x = (x % (a / d) + (a / d)) % (a / d);
        ans = ans + x * acc;
        acc = a / d * acc;
        ans = (ans % acc + acc) % acc;
    }
    printf("%lld\n", (ll)ans);
    return 0;
}