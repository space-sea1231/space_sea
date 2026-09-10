#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

int t = 1;
int n = 5;

mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) {return Rand() % (r - l + 1) + l;}

int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) printf("%d ", Random(1, 200000));
        printf("\n");
    }
    return 0;
}