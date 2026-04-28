#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;
const int K = 80;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll n, m;
ll v[N], w[N], tmp[N];
priority_queue<ll> q[K];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
        tmp[i] = w[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) {
        w[i] = lower_bound(tmp + 1, tmp + len + 1, w[i]) - tmp;
        q[w[i]].push(v[i]);
    }
    // for (int i = 1; i <= len; i++) printf("tmp[%d] = %lld\n", i, tmp[i]);
    ll ans = 0;
    tmp[len + 1] = INF;
    for (int i = 1; i <= len; i++) {
        ll cnt = 0;
        // if (i == 2) {
        //     printf("---------i = %d---------\n", i);
        //     queue<int> tmp;
        //     while (!q[i].empty()) {
        //         tmp.push(q[i].top());
        //         printf("%d ", q[i].top());
        //         q[i].pop();
        //     }
        //     while (!tmp.empty()) {
        //         q[i].push(tmp.front());
        //         tmp.pop();
        //     }
        //     printf("\n---------END---------\n", i);
        // }
        while (!q[i].empty() && cnt + tmp[i] <= m % tmp[i + 1]) {
            // if (i == 1) printf("Debug:%lld\n", m % tmp[i + 1]);
            ans += q[i].top();
            q[i].pop();
            cnt += tmp[i];
        }
        ll sum = 0;
        while (!q[i].empty()) {
            sum = cnt = 0;
            while (!q[i].empty() && cnt < tmp[i + 1] / tmp[i]) {
                sum += q[i].top();
                q[i].pop();
                cnt++;
            }
            q[i + 1].push(sum);
        }
        // printf("Debug:%d\n", i);
    }
    printf("%lld\n", ans);
    return 0;
}