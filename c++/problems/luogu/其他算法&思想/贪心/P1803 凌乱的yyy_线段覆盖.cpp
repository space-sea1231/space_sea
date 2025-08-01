#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n;

struct Race {
    int l, r;
    
    bool operator < (const Race src) {
        return r < src.r;
    }
};

Race race[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> race[i].l >> race[i].r;
    sort(race + 1, race + n + 1);
    int cnt = 0, last = 0;
    for (int i = 1; i <= n; i++) {
        if (race[i].l >= last) {
            cnt++;
            last = race[i].r;
        }
    }
    printf("%d\n", cnt);

    return 0;
}