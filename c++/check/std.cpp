#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;
int n;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        printf("---%d---\n", t);
        cin >> n;
        int lim;
        if (n < 3) lim = n;
        else lim = n / 3 + 2 + n % 3;
        int cnt = 0;
        cerr<<lim;
        for (int i = 1; i <= lim; i++) {
            printf("%d %d\n", 1, i + 1);
            cnt++;
        }
        if (n <= 8) {
            if ((n - lim) / 2 >= 1) {
                printf("%d %d\n", 2, 3);
                printf("%d %d\n", 2, 4);
            }
            for (int i = 4; i <= (n - lim) / 2; i++) printf("%d %d\n", 2, i + 1);
    
            if ((n - lim) / 2 >= 2) {
                printf("%d %d\n", 3, 4);
                printf("%d %d\n", 3, 5);
            }
            for (int i = 5; i <= (n - lim) / 2; i++) printf("%d %d\n", 3, i + 1);
            if ((n - lim) / 2 >= 3) {
                printf("%d %d\n", 4, 5);
                printf("%d %d\n", 4, 6);
            }
            if ((n - lim) / 2 >= 4) {
                printf("%d %d\n", 5, 6);
            }
        } else {
            for (int i = 3; i <= n / 3 + 2; i++) {
                printf("%d %d\n", 2, i);
                cnt++;
            }
            for (int i = cnt; i < n; i++) {
                printf("%d %d\n", 3, i - cnt + 4);
            }
        }
    }
    return 0;
}