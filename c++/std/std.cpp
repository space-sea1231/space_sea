#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

bool Check(int src) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt++;
        if (cnt == src) {
            cnt = 0;
            continue;
        }
        if (a[i] != a[])
    }
}

signed main() {
    cin.tie (nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int l = 1, r = n;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (Check(mid)) {
            ans = l;
            l = mid + 1;
        }
        r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}