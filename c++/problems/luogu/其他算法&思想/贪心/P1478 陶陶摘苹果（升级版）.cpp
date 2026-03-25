#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e3 + 10;

int n, m, k;

struct Apple {
    int x, y;

    bool operator<(const Apple src)const {
        return y < src.y;
    }
};

Apple apple[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int a, b;
    cin >> a >> b;
    k = a + b;
    for (int i = 1; i <= n; i++) cin >> apple[i].x >> apple[i].y;
    sort(apple + 1, apple + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (apple[i].x <= k && apple[i].y <= m) {
            m -= apple[i].y;
            ans++;
        }
    }
    printf("%d\n", ans);

    return 0;
}