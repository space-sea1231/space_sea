#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 100;

int n, k;
bool ans[N];

int Log(int x) {
    int cnt = 0;
    while (x) {
        x >>= 1;
        cnt++;
    }
    return cnt;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    int lg = Log(n);
    for (int i = lg; i; i--) {
        vector<int> q;
        for (int j = 1; j <= n; j += (1 << i)) {
            for (int k = j; k <= j - 1 + (1 << i - 1) && k <= n; k++) {
                q.push_back(k);
            }
        }
        for (int j = 1; j <= 2; j++) {
            printf("1 %d ", q.size());
            for (int x:q) printf("%d ", x);
            printf("\n");
        }
    }
    printf("2\n");
    fflush(stdout);
    for (int i = 1; i <= lg; i++) {
        int a, b;
        cin >> a >> b;
        ans[i] = a | b;
    }
    int l = 1, r = n;
    // cerr<<lg << "\n";
    for (int i = lg - 1; ~i; i--) {
        if (!ans[i]) r = l - 1 + (1 << i);
        if (ans[i]) l = l + (1 << i);
    }
    printf("%d\n", l);
    fflush(stdout);
    return 0;
}
/*
-----
11110
11001
10101


--------
11110000
11001100
10101010
interaction library
*/