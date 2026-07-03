#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n;
int cnt, ans;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (ans == a) cnt++;
        else {
            if (cnt == 0) {
                ans = a;
                cnt++;
            } else cnt--;
        }
    }
    printf("%d\n", ans);
    return 0;
}