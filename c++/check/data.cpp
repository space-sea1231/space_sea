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
    int n = 5;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) printf("%d ", Random(0, 5));
    return 0;
}