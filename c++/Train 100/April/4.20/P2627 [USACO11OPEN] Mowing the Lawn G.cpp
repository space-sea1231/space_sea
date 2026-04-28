#include <iostream>
#include <stdio.h>
#include <deque>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
ll sum;
int a[N];
ll f[N];
deque<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    q.push_back(0);
    for (int i = 1; i <= n + 1; i++) {
        while (!q.empty() && q.front() < i - m - 1) q.pop_front();
        f[i] = f[q.front()] + a[i];
        while (!q.empty() && f[q.back()] > f[i]) q.pop_back();
        q.push_back(i);
    }
    printf("%lld\n", sum - f[n + 1]);
    return 0;
}