#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <deque>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n, Q;
int a[N], f[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> Q;
    while (Q--) {
        int k;
        cin >> k;
        for (int i = 1; i <= n; i++) f[i] = INF;
        f[1] = 0;
        deque<int> q;
        q.push_front(1);
        for (int i = 2; i <= n; i++) {
            while (!q.empty() && q.front() < i - k) q.pop_front();
            f[i] = f[q.front()] + (a[q.front()] <= a[i]);
            while (!q.empty() && f[q.back()] > f[i] || (f[q.back()] == f[i] && a[q.back()] <= a[i])) q.pop_back();
            q.push_back(i);
        }
        // for (int i = 1; i <= n; i++) printf("%d ", f[i]);
        printf("%d\n", f[n]);
    }
    return 0;
}