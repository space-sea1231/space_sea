#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

int xa, xb, va, vb, l;

int Exgcd(int a, int b, int &x, int &y) {
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
    cin >> xa >> xb >> va >> vb >> l;
    int x, y;
    int d = Exgcd(vb - va, l, x, y);
    if ((xa - xb) % d) printf("Impossible\n");
    else printf("%lld\n", ((x * ((xa - xb) / d) % l) + abs(l / d)) % abs(l / d));
    return 0;
}