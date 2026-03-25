#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n, m;

struct Farmer {
    int val, price;
    
    bool operator<(const Farmer src)const {
        return price < src.price;
    }
};

Farmer farmer[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> farmer[i].price >> farmer[i].val;
    sort(farmer + 1, farmer + m + 1);
    int ans = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n - sum >= farmer[i].val) {
            sum += farmer[i].val;
            ans += farmer[i].val * farmer[i].price;
        } else {
            ans += (n - sum) * farmer[i].price;
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}