#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

int n, sum;

int Gcd(int a, int b) {
    while (b ^= a ^= b ^= a %= b);
    return a;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> sum;
    for (int i = 2; i <= n; i++) {
        int a;
        cin >> a;
        if (a) sum = Gcd(sum, a);
    }
    printf("%d\n", abs(sum));
    return 0;
}