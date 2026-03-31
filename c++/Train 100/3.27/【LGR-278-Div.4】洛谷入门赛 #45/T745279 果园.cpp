#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;
int n, k;
int a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i <= k) maxn = max(maxn, a[i]);
        else if (a[i] > maxn) {
            printf("%d\n", a[i]);
            return 0;
        }
    }
    printf("%d\n", a[n]);
    return 0;
}