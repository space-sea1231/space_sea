#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) {return Rand() % (r - l + 1) + l;}
const int INF = sizeof(int) == 4 ? 1e9 + 1 : 1e18 + 1;

int Log(int x) {
    for (int i = 0; i < INF; i++) {
        if ((1 << i) >= x) return i;
    }
    return 0;
}

int main() {
    srand((unsigned)time(0));
    int n = Random(1, 1);
    int mark = (Log(n), 100);
    int x = Random(1, n);
    int y = Random(1, n);
    // int n = 5, mark = 100, x = 2, y = 1;
    printf("%d %d %d %d\n", n, mark, x, y);
    return 0;
}