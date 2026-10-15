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

char c[20] = {' ', 'P', 'K', 'D', 'F', 'N', 'W', 'J', 'Z'};
signed main() {
    srand((unsigned)time(0));

    int n = 5, m = 10;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
        if (i == 1) printf("MP ");
        else {
            bool flag = Random(0, 1);
            if (flag) printf("ZP ");
            else printf("FP ");
        } 
        for (int j = 1; j <= 4; j++) {
            int card = Random(1, 8);
            printf("%c ", c[card]);
        }
        printf("\n");
    }
    for (int i = 1; i < m; i++) {
        int card = Random(1, 8);
        printf("%c ", c[card]);
    }
    printf("K\n");
    return 0;
}