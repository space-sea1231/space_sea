#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

int t = 1;
int a[300000 + 10];
set<int> st;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
int Random(int l, int r) {
	return Rand() % (r - l + 1) + l;
}
int main() {
    freopen("aaa.in", "r", stdin);
    freopen("aaa.out", "w", stdout);
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        int n = Random(1, 3);
        int m = Random(1, 3);
        printf("%d %d\n", n, m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int a = Random(1, 4);
                printf("%d ", a);
            }
            printf("\n");
        }
    }
    return 0;
}