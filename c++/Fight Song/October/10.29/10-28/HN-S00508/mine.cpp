#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;

ll n, m;
int Pow(int a, ll b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
signed main() {
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    printf("%d\n", Pow(2, n * m));
    return 0;
}