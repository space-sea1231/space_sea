#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

int t = 5;
// int n = 10;

mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) {return Rand() % (r - l + 1) + l;}

int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        printf("%d %lld\n", Random(1, 10), Random(1, 100));
    }
    return 0;
}