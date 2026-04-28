#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e4 + 10;

int n, m;
int f[N];
vector<int> v[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        v[x].emplace_back(y);
    }
    for (int i = n; i >= 1; i--) {
        if (!v[i].empty()) {
            for (auto j:v[i]) {
                f[i] = max(f[i], f[i + j]);
            }
        }
        else f[i] = f[i + 1] + 1;
    }
    printf("%d\n", f[1]);
    return 0;
}