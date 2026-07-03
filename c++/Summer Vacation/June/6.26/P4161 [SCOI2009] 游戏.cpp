#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e4 + 10;

int n, m;
ll f[N] = {1};
bool vis[N];
vector<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) q.emplace_back(i);
        for (int j = i * i; j <= n; j += i) vis[j] = true;
    }
    for (auto v:q) {
        for (int j = n; j >= v; j--) {
            int tmp = v;
            while (tmp <= j) {
                f[j] += f[j - tmp];
                tmp *= v;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) ans += f[i];
    printf("%lld\n", ans);
    return 0;
}