#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n;
int a[N], b[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    priority_queue<int> q;
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        q.emplace(a[i]);
        q.emplace(a[i]);
        res += q.top() - a[i];
        q.pop();
        b[i] = q.top();
        // printf("b[%d]=%d\n", i, b[i]);
    }
    for (int i = n - 1; i; i--) b[i] = min(b[i], b[i + 1]);
    printf("%lld\n", res);
    for (int i = 1; i <= n; i++) printf("%d\n", b[i] + i);
    return 0;
}