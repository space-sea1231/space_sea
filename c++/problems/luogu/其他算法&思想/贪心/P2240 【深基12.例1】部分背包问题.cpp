#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;

int n, t;

struct Coin {
    double v, w;

    bool operator < (const Coin srca)const {
        return v / w > srca.v / srca.w;
    }
};

Coin coin[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i].w >> coin[i].v;
    }
    sort(coin + 1, coin + n + 1);
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (t >= coin[i].w) {
            ans += coin[i].v;
            t -= coin[i].w;
        }
        else {
            ans += coin[i].v / coin[i].w * t;
            break;
        }
    }
    printf("%.2lf\n", ans);
    return 0;
}