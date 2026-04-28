#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    printf("%d\n", n - a - b - c - d);
    return 0;
}