#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

int T, n;

int Phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) res = res / i * (i - 1);
        while (x % i == 0) x = x / i;
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

int Pow(int a, int b, int p) {
    if (b == 0) return 1;
    int sum = 1;
    while (b) {
        if (b & 1) sum = ((ll)sum * a) % p;
        a = ((ll)a * a) % p;
        b >>= 1;
    }
    return sum;
}

int Search(int cur) {
    if (cur == 1) return 0;
    int res = Search(Phi(cur));
    if (cur % 2 == 0) res += Phi(cur);
    return Pow(2, res, cur);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        printf("%d\n", Search(n));
    }
    return 0;
}