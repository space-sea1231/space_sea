#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdio.h>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 20;

int n;
int a[N], b[N];

int Exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = Exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return d;
}

int Mul(int a, int b, int mod) {
    int sum = 0;
    while (b) {
        if (b & 1) sum = (sum + a) % mod; 
        a = (a + a) % mod;
        b >>= 1;
    }
    return sum;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int acc = 1;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        acc *= b[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        int d = Exgcd(acc / b[i], b[i], x, y);
        x = (x % (b[i] / d) + (b[i] / d)) % (b[i] / d);
        ans = (ans + Mul(Mul(acc / b[i], x, acc), (a[i] + acc) % acc, acc)) % acc;
    }
    printf("%lld\n", ans);
    return 0;
}