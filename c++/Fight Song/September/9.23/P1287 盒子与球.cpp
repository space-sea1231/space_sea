#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n, m;

int Dfs(int a, int b) {
    if (a < b) return 0;
    if (b == 0) return (a == 0);
    return Dfs(a - 1, b) * b + Dfs(a - 1, b - 1);
}
int Fac(int x) {
    int sum = 1;
    while (x--) sum *= (x + 1);
    return sum;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    printf("%d\n", Dfs(n, m) * Fac(m));
    return 0;
}