#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 2e7 + 10;

int a, m;
char c[N];

int Phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) res = res / i * (i - 1); 
        while (x % i == 0) x /= i;
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

int Pow(int a, int b, int p) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = sum * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return sum;
}

int n;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    int ans = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans += i * Phi(n / i);
            if (i * i != n) ans += n / i * Phi(i);
        }
    }
    printf("%lld\n", ans);
    return 0;
}